#include "parser.h"

extern pthread_mutex_t st_LidarRawDataMutex;
extern pthread_mutex_t st_ImuRawDataMutex;
extern pthread_mutex_t st_SlamRawDataMutex;
extern pthread_mutex_t st_EncoderRawDataMutex;
extern pthread_mutex_t st_ObjectRawDataMutex;

extern pcl::PointCloud<pcl::PointXYZI> st_RawLidarData;
extern RAW_SLAM_DATA_t st_RawSlamData;
extern RAW_IMU_DATA_t st_RawImuData;
extern RAW_ENCODER_DATA_t st_RawEncoderData;
extern RAW_ENCODER_DATA_t st_RawObjectData;
extern CONTROL_DATA_t st_ControlData;

extern pthread_mutex_t st_ProcessingMutex;;
extern pthread_cond_t st_Cond;
extern bool data_ready;
extern bool GoalPoint_1;
extern bool GoalPoint_2;
extern bool GoalPoint_3;
extern bool GoalPoint_4;
extern bool b_Start;
extern int currentGoal; // 현재 목표 번호를 추적하는 변수
extern int32_t s32_WaitTime;
extern int32_t s32_Mode;
extern float32_t f32_Speed;


// Imu 데이터 파싱

void ImuParserSerial(ros::NodeHandle* pst_NodeHandle)
{
    std::string port = "/dev/ttyUSB0";
    int32_t s32_BaudRate = 115200;

    boost::asio::io_service io_service;
    boost::asio::serial_port serial(io_service);

    try
    {
        serial.open(port); // 시리얼 포트 열기
        serial.set_option(boost::asio::serial_port_base::baud_rate(s32_BaudRate));
        std::cout << "Connected to port: " << port << " at baud rate: " << s32_BaudRate << std::endl;
    }
    catch (const boost::system::system_error& e)
    {
        // 시리얼 포트 열기 실패 시 예외 처리
        std::cerr << "Error opening serial port: " << e.what() << std::endl;
        // 시리얼 포트가 열리지 않더라도 루프는 계속 진행되게 함
        serial.close();
    }

    unsigned char buffer[256];
    unsigned char data[13];
    size_t buffer_pos = 0;
    auto last_received_time = std::chrono::steady_clock::now();
    IMU_DATA_t st_ImuData = {0};

    while (b_Running)
    {
        if (serial.is_open()) // 시리얼 포트가 열려 있는지 확인
        {
            try
            {
                // 시리얼 데이터 수신
                size_t len = serial.read_some(boost::asio::buffer(buffer + buffer_pos, sizeof(buffer) - buffer_pos));
                buffer_pos += len;
                last_received_time = std::chrono::steady_clock::now();
                // 패킷 처리
                for (size_t i = 0; i + 12 < buffer_pos; ++i)
                {

                    if (buffer[i] == 0x02 && buffer[i + 12] == 0x03) // STX와 ETX로 패킷의 시작과 끝을 찾음
                    {

                        std::memcpy(data, buffer + i, 13);

                        // Checksum 계산 및 검증
                        unsigned char checksum = 0;
                        for (int j = 2; j < 11; ++j)
                            checksum += data[j];

                        if (checksum != data[11])
                        {
                            std::cout << "Checksum error. Calculated: " << std::hex << static_cast<int>(checksum)
                                      << " but got: " << std::hex << static_cast<int>(data[11]) << std::endl;
                            continue;
                        }

                        // 데이터 해석
                        int16_t value1 = (data[5] | (data[6] << 8));
                        int16_t value2 = (data[7] | (data[8] << 8));
                        int16_t value3 = (data[9] | (data[10] << 8));

                        // 데이터 타입별로 지역 변수 구조체에 값 할당
                        switch (data[4])
                        {
                            case 0x33: // 가속도 데이터
                                st_ImuData.f32_AccelX_m_s2 = value1 / 1000.0f;
                                st_ImuData.f32_AccelY_m_s2 = value2 / 1000.0f;
                                st_ImuData.f32_AccelZ_m_s2 = value3 / 1000.0f;
                                printf("%f\n",st_ImuData.f32_AccelX_m_s2);
                                break;

                            case 0x34: // 각속도 데이터
                                st_ImuData.f32_GyroX_deg_s = value1 / 10.0f;
                                st_ImuData.f32_GyroY_deg_s = value2 / 10.0f;
                                st_ImuData.f32_GyroZ_deg_s = value3 / 10.0f;
                                break;

                            case 0x35: // 오일러 각도 데이터
                                st_ImuData.f32_Roll_deg = value1 / 100.0f;
                                st_ImuData.f32_Pitch_deg = value2 / 100.0f;
                                st_ImuData.f32_Yaw_deg = value3 / 100.0f;
                                break;

                            case 0x36: // 자기장 데이터
                                st_ImuData.f32_MagneticX_mT = value1 / 10.0f;
                                st_ImuData.f32_MagneticY_mT = value2 / 10.0f;
                                st_ImuData.f32_MagneticZ_mT = value3 / 10.0f;
                                break;

                            default:
                                break;
                        }

                        std::memmove(buffer, buffer + i + 13, buffer_pos - (i + 13));
                        buffer_pos -= (i + 13);
                        i = -1;
                    }
                }
            }
            catch (const boost::system::system_error& e)
            {
                std::cerr << "Read error: " << e.what() << std::endl;
            }
        }
        else
        {
            // 시리얼 포트가 열려 있지 않다면, 계속해서 이전 데이터를 보내도록 처리
            std::cerr << "Serial port not open, skipping data read..." << std::endl;
        }

        // Mutex로 보호된 데이터 복사
        pthread_mutex_lock(&st_ImuRawDataMutex);
        memcpy(st_RawImuData.arc_Buffer, &st_ImuData, sizeof(IMU_DATA_t));
        pthread_mutex_unlock(&st_ImuRawDataMutex);

        // 시리얼 포트가 열리지 않으면 계속해서 이전 데이터를 전송
    }
}

void* ImuParserWrapper(void* p_Arg)
{
    ros::NodeHandle *pst_NodeHandle = (ros::NodeHandle *)p_Arg;

    int32_t s32_Mode = 0;

    if (s32_Mode == 0)
    {
        ImuParserSerial(pst_NodeHandle);
    }
    else if (s32_Mode == 1)
    {

    }


    return NULL;
}

// LiDAR 데이터 파싱
void LidarParserCallback(const sensor_msgs::PointCloud2::ConstPtr& st_SensorMsg)
{
    pthread_mutex_lock(&st_LidarRawDataMutex);
    pcl::fromROSMsg(*st_SensorMsg, st_RawLidarData);
    pthread_mutex_unlock(&st_LidarRawDataMutex);
}



void* LidarParserWrapper(void* p_Arg)
{
    ros::NodeHandle *pst_NodeHandle = (ros::NodeHandle *)p_Arg;

    ros::Subscriber sub = pst_NodeHandle->subscribe<sensor_msgs::PointCloud2>("/livox/lidar", 1, LidarParserCallback);

    uint64_t u64_EndTime = getMilliSec();

    while(b_Running)
    {
        ros::spinOnce();
        usleep(10);

        uint64_t u64_StartTime = getMilliSec();
        uint64_t u64_ElapsedTime = u64_StartTime - u64_EndTime;

        if (u64_ElapsedTime >= 100)
        {
            pthread_mutex_lock(&st_ProcessingMutex);
            data_ready = true;
            pthread_cond_signal(&st_Cond);
            pthread_mutex_unlock(&st_ProcessingMutex);
            u64_EndTime = u64_StartTime;
        }
    }
}


// Slam 데이터 파싱
void SlamParserCallback(const geometry_msgs::TransformStamped::ConstPtr& st_Msg)
{
    SLAM_DATA_t st_SlamData = {0};

    st_SlamData.f32_TranslationX = st_Msg->transform.translation.x;
    st_SlamData.f32_TranslationY = st_Msg->transform.translation.y;
    st_SlamData.f32_TranslationZ = st_Msg->transform.translation.z;

    st_SlamData.f32_QuaternionX = st_Msg->transform.rotation.x;
    st_SlamData.f32_QuaternionY = st_Msg->transform.rotation.y;
    st_SlamData.f32_QuaternionZ = st_Msg->transform.rotation.z;
    st_SlamData.f32_QuaternionW = st_Msg->transform.rotation.w;

    pthread_mutex_lock(&st_SlamRawDataMutex);
    memcpy(st_RawSlamData.arc_Buffer, &st_SlamData, sizeof(SLAM_DATA_t));
    pthread_mutex_unlock(&st_SlamRawDataMutex);
}


void* SlamParserWrapper(void* p_Arg)
{
    ros::NodeHandle *pst_NodeHandle = (ros::NodeHandle *)p_Arg;

    ros::Subscriber sub = pst_NodeHandle->subscribe<geometry_msgs::TransformStamped>("/mapping_node/scan2map_transform", 1, SlamParserCallback);

    while(b_Running)
    {
        ros::spinOnce();
        usleep(10);

    }
}


// 엔코더 데이터 파싱
void EncoderParser_Callback(const Total_msgs::Encoder::ConstPtr& st_Msg)
{
    ENCODER_DATA_t st_EncoderData = {0};
    st_EncoderData.s16_RightWheelRPM = st_Msg->s16_RightWheelRPM;
    st_EncoderData.s16_LeftWheelRPM = st_Msg->s16_LeftWheelRPM;
    st_EncoderData.f32_RightWheelSpeed_m_s = -(float32_t)st_EncoderData.s16_RightWheelRPM * st_ControlData.st_Param.f32_WheelDiameter * M_PI / 60.f; 
    st_EncoderData.f32_LeftWheelSpeed_m_s = -(float32_t)st_EncoderData.s16_LeftWheelRPM * st_ControlData.st_Param.f32_WheelDiameter * M_PI / 60.f; 
    st_EncoderData.f32_EncoderSpeed_m_s = (st_EncoderData.f32_RightWheelSpeed_m_s + st_EncoderData.f32_LeftWheelSpeed_m_s) / 2.f; 

    pthread_mutex_lock(&st_EncoderRawDataMutex);
    memcpy(st_RawEncoderData.arc_Buffer, &st_EncoderData, sizeof(ENCODER_DATA_t));
    pthread_mutex_unlock(&st_EncoderRawDataMutex);
}

uint64_t startTime;
bool RealStart = false;
bool RealRealStart = false;

void SerialParser(ros::NodeHandle *pst_NodeHandle)
{
    static int32_t PrevGoal = 0;
    static bool goalChanged = false;
    static uint64_t goalChangeTime = 0;

    ros::Subscriber st_SubscribeSerial = pst_NodeHandle->subscribe<Total_msgs::Encoder>("encoder_msg", 1, EncoderParser_Callback);
    ros::Publisher st_PublishSerial = pst_NodeHandle->advertise<Total_msgs::Control>("control_msg", 1);
    Total_msgs::Control msg;

    while(b_Running)
    {
        ros::spinOnce();

        if (b_Start)
        {
            startTime = getMilliSec();
            b_Start = false;
            RealStart = true;
        }

        if (RealStart)
        {
            uint64_t EndTime = getMilliSec();
            if (EndTime - startTime > s32_WaitTime * 1000)
            {
                RealRealStart = true;
                RealStart = false;
            }
        }

        if (s32_Mode == 0)
        {
            if (currentGoal != PrevGoal)
            {
                goalChanged = true;
                goalChangeTime = getMilliSec();
                PrevGoal = currentGoal;
            }

            if (goalChanged)
            {
                uint64_t currentTime = getMilliSec();
                if (currentTime - goalChangeTime <= 1000)
                {
                    msg.s16_throttle = 0.f; // Stop for 1 second
                }
                else
                {
                    goalChanged = false;
                }
            }
            else if (RealRealStart)
            {
                msg.s16_throttle = f32_Speed; // Normal throttle
            }
            else
            {
                msg.s16_throttle = 0.f;
            }
        }
        else
        {
            if (RealRealStart)
            {
                msg.s16_throttle = f32_Speed; // Normal throttle
            }
            else
            {
                msg.s16_throttle = 0.f; // Normal throttle
            }
        }




        float32_t temp = - 1.0 * st_ControlData.f32_TargetSteer_rad / st_ControlData.st_Param.f32_MAX_STEER_rad * 100.f;
        GetModData(-100,100,temp);
        msg.s16_steering = temp;
        st_PublishSerial.publish(msg);
        usleep(10);
    }
}


void* SerialParserWrapper(void* p_Arg)
{
    ros::NodeHandle *pst_NodeHandle = (ros::NodeHandle *)p_Arg;
    SerialParser(pst_NodeHandle);

    return NULL;
}


void ObjectParserCallback(const Jongseol::objs::ConstPtr& st_Msg)
{
    OBJECT_DATA_t st_ObjectData = {0};

    int32_t s32_I;
    int32_t s32_Num = st_Msg->num;
    for (s32_I = 0;s32_I < s32_Num;s32_I++)
    {
        st_ObjectData.f32_X[s32_I] = st_Msg->obj[s32_I].x;
        st_ObjectData.f32_Y[s32_I] = st_Msg->obj[s32_I].y;
        st_ObjectData.f32_Z[s32_I] = st_Msg->obj[s32_I].z;

        st_ObjectData.f32_DX[s32_I] = st_Msg->obj[s32_I].dx;
        st_ObjectData.f32_DY[s32_I] = st_Msg->obj[s32_I].dy;
        st_ObjectData.f32_DZ[s32_I] = st_Msg->obj[s32_I].dz;
        // printf("[%d] x:%f, y:%f\n",s32_I, st_ObjectData.f32_X[s32_I], st_ObjectData.f32_Y[s32_I]);
    }
    st_ObjectData.s32_ObjectNum = s32_Num;
    // printf("parsernum:%d\n",st_ObjectData.s32_ObjectNum);

    pthread_mutex_lock(&st_ObjectRawDataMutex);
    memcpy(st_RawObjectData.arc_Buffer, &st_ObjectData, sizeof(OBJECT_DATA_t));
    pthread_mutex_unlock(&st_ObjectRawDataMutex);
}


void* ObjectParserWrapper(void* p_Arg)
{
    ros::NodeHandle *pst_NodeHandle = (ros::NodeHandle *)p_Arg;

    ros::Subscriber sub = pst_NodeHandle->subscribe<Jongseol::objs>("/lidar_objects", 1, ObjectParserCallback);

    while(b_Running)
    {
        ros::spinOnce();
        usleep(10);

    }
}

