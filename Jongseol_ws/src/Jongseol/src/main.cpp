#include "global/global.h"
#include "parser/parser.h"
#include "lidar/lidar.h"
#include "imu/imu.h"
#include "planning/planning.h"
#include "control/control.h"

using namespace std;

pthread_mutex_t st_ProcessingMutex;
pthread_mutex_t st_LidarRawDataMutex;
pthread_mutex_t st_ImuRawDataMutex;
pthread_mutex_t st_SlamRawDataMutex;
pthread_mutex_t st_EncoderRawDataMutex;
pthread_mutex_t st_ObjectRawDataMutex;
pthread_cond_t st_Cond = PTHREAD_COND_INITIALIZER;

////////////////////////////////////////////////////////
pcl::PointCloud<pcl::PointXYZI> st_LidarData = {};
pcl::PointCloud<pcl::PointXYZI> st_RawLidarData = {};

RAW_SLAM_DATA_t st_RawSlamData = {0};
SLAM_DATA_t st_SlamData = {0};

RAW_OBJECT_DATA_t st_RawObjectData = {0};
OBJECT_DATA_t st_ObjectData = {0};

RAW_IMU_DATA_t st_RawImuData = {0};
IMU_DATA_t st_ImuData = {0};

RAW_ENCODER_DATA_t st_RawEncoderData = {0};
ENCODER_DATA_t st_EncoderData = {0};

PLANNING_DATA_t st_PlanningData = {0};
CONTROL_DATA_t st_ControlData = {0};

/////////////////////////////////////////////////////////

// 전역 변수
int currentGoal = 1;
float32_t f32_GoalX, f32_GoalY;

float32_t f32_GoalX_1, f32_GoalY_1;
float32_t f32_GoalX_2, f32_GoalY_2;
float32_t f32_GoalX_3, f32_GoalY_3;
float32_t f32_GoalX_4, f32_GoalY_4;

bool b_Map = false;
bool b_Start = false;
bool data_ready = false;
bool b_MakeMap;

bool GoalPoint_1 = false;
bool GoalPoint_2 = false;
bool GoalPoint_3 = false;
bool GoalPoint_4 = false;

float32_t f32_MinX, f32_MinY;

pcl::PointCloud<pcl::PointXYZ>::Ptr st_DownSampledCloud (new pcl::PointCloud<pcl::PointXYZ>);

vector<vector<int>> BinaryFinalGridMap;

uint64_t u64_Sync = 0;

int32_t s32_Mode;
int32_t s32_WaitTime;
float32_t f32_Speed;
/////////////////////////////////////////////////////////

void InitYAML()
{

    YAML::Node st_Config = YAML::LoadFile("configuration.yaml");
    f32_GoalX_1 = st_Config["GoalX_1"].as<float32_t>();
    f32_GoalY_1 = st_Config["GoalY_1"].as<float32_t>();

    f32_GoalX_2 = st_Config["GoalX_2"].as<float32_t>();
    f32_GoalY_2 = st_Config["GoalY_2"].as<float32_t>();

    f32_GoalX_3 = st_Config["GoalX_3"].as<float32_t>();
    f32_GoalY_3 = st_Config["GoalY_3"].as<float32_t>();

    f32_GoalX_4 = st_Config["GoalX_4"].as<float32_t>();
    f32_GoalY_4 = st_Config["GoalY_4"].as<float32_t>();

    f32_GoalX = f32_GoalX_1;
    f32_GoalY = f32_GoalY_1;

    f32_MinX = st_Config["MinX"].as<float32_t>();
    f32_MinY = st_Config["MinY"].as<float32_t>();

    s32_Mode = st_Config["Mode"].as<int32_t>();
    s32_WaitTime = st_Config["WaitTime"].as<float32_t>();
    f32_Speed = st_Config["Speed"].as<float32_t>();
}

void InitKeyboard()
{
    YAML::Node st_Config = YAML::LoadFile("configuration.yaml");

    b_MakeMap = st_Config["Keyboard"].as<int32_t>();
    if (b_MakeMap)
    {
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
    }
}


void LoadData()
{
    DataLoad("./src/Jongseol/map/LabPath2.txt", st_PlanningData.st_TemporalPath_global);
    GridLoad("./src/Jongseol/GridMap/513Grid.txt", st_PlanningData.st_BinaryGrid);
}

void CopyData()
{
    // Copy Data
    pthread_mutex_lock(&st_LidarRawDataMutex);
    memcpy(&st_LidarData, &st_RawLidarData, sizeof(pcl::PointCloud<pcl::PointXYZI>));
    pthread_mutex_unlock(&st_LidarRawDataMutex);

    pthread_mutex_lock(&st_SlamRawDataMutex);
    memcpy(&st_SlamData, st_RawSlamData.arc_Buffer, sizeof(SLAM_DATA_t));
    pthread_mutex_unlock(&st_SlamRawDataMutex);

    pthread_mutex_lock(&st_ImuRawDataMutex);
    memcpy(&st_ImuData, st_RawImuData.arc_Buffer, sizeof(IMU_DATA_t));
    pthread_mutex_unlock(&st_ImuRawDataMutex);

    pthread_mutex_lock(&st_EncoderRawDataMutex);
    memcpy(&st_EncoderData, st_RawEncoderData.arc_Buffer, sizeof(ENCODER_DATA_t));
    pthread_mutex_unlock(&st_EncoderRawDataMutex);

    pthread_mutex_lock(&st_ObjectRawDataMutex);
    memcpy(&st_ObjectData, st_RawObjectData.arc_Buffer, sizeof(OBJECT_DATA_t));
    pthread_mutex_unlock(&st_ObjectRawDataMutex);
}

void* ProcessingThread(void* p_Arg)
{
    ros::NodeHandle *pst_NodeHandle = (ros::NodeHandle *)p_Arg;

    ros::Publisher st_Pub_ROI = pst_NodeHandle->advertise<sensor_msgs::PointCloud2> ("/ROI", 1);
    ros::Publisher st_Pub_DS = pst_NodeHandle->advertise<sensor_msgs::PointCloud2> ("/downsampled", 1);
    ros::Publisher st_Pub_OB = pst_NodeHandle->advertise<sensor_msgs::PointCloud2> ("/objects", 1); 
    ros::Publisher st_Pub_GR = pst_NodeHandle->advertise<sensor_msgs::PointCloud2> ("/ground", 1);
    ros::Publisher st_Pub_CL = pst_NodeHandle->advertise<sensor_msgs::PointCloud2> ("/clustered", 1);
    ros::Publisher st_Pub_Objs = pst_NodeHandle->advertise<Jongseol::objs> ("/lidar_objects", 1);
    ros::Publisher st_Pub_MK = pst_NodeHandle->advertise<visualization_msgs::MarkerArray>("/object_markers", 1);
    ros::Publisher st_Pub_GRID = pst_NodeHandle->advertise<nav_msgs::OccupancyGrid>("/grid_map", 1);
    ros::Publisher st_Pub_GPP = pst_NodeHandle->advertise<visualization_msgs::Marker>("/astar", 1);
    ros::Publisher st_Pub_EGO = pst_NodeHandle->advertise<visualization_msgs::Marker>("/ego", 1);


    int32_t s32_Getch;

    while(ros::ok())
    {
        s32_Getch = getch();
        if (s32_Getch != ERR)
        {
            keyboardCallback(s32_Getch);
        }

        pthread_mutex_lock(&st_ProcessingMutex);
        while (!data_ready) // 데이터 준비 플래그 확인
        {
            pthread_cond_wait(&st_Cond, &st_ProcessingMutex);
        }
        CopyData();

        data_ready = false; // 플래그 리셋
        ROI(st_LidarData, st_Pub_ROI);
        DownSampling(st_LidarData, st_DownSampledCloud, st_Pub_DS);

        PlanningProcessing(&st_PlanningData ,&st_ObjectData, &st_SlamData, &st_EncoderData);
        ControlProcessing(&st_PlanningData, &st_ControlData);

        GoalPointVisualize(&st_PlanningData, &st_ObjectData, st_Pub_MK);
        GridVisualize(BinaryFinalGridMap, st_Pub_GRID);
        GPPVisualize(&st_PlanningData, st_Pub_GPP);
        EgoVisualize(&st_PlanningData, st_Pub_EGO);

        pthread_mutex_unlock(&st_ProcessingMutex);

    }
}







int main(int argc, char** argv)
{
    ros::init(argc, argv, "Jongsul");
    ros::NodeHandle NodeHandle;

    InitKeyboard();
    LoadData();
    InitYAML();

    pthread_mutex_init(&st_ProcessingMutex, NULL);
    pthread_mutex_init(&st_LidarRawDataMutex, NULL);
    pthread_mutex_init(&st_SlamRawDataMutex, NULL);
    pthread_mutex_init(&st_ImuRawDataMutex, NULL);
    pthread_mutex_init(&st_EncoderRawDataMutex, NULL);
    pthread_mutex_init(&st_ObjectRawDataMutex, NULL);

    pthread_t th1;
    pthread_t th2;
    pthread_t th3;
    pthread_t th4;
    pthread_t th5;
    pthread_t th6;

    pthread_create(&th1, NULL, ImuParserWrapper, &NodeHandle);
    pthread_create(&th2, NULL, LidarParserWrapper, &NodeHandle);
    pthread_create(&th3, NULL, SlamParserWrapper, &NodeHandle);
    pthread_create(&th4, NULL, ProcessingThread, &NodeHandle);
    pthread_create(&th5, NULL, SerialParserWrapper, &NodeHandle);
    pthread_create(&th6, NULL, ObjectParserWrapper, &NodeHandle);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    pthread_join(th4, NULL);
    pthread_join(th5, NULL);
    pthread_join(th5, NULL);

    endwin();

    return 0;
}
