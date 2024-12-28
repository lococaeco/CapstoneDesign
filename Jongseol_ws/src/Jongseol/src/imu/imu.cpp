#include "imu.h"



void PrintImuData(IMU_DATA_t *pst_ImuData)
{

    // 가속도 데이터
    printf("Acceleration Data (m/s^2):\n");
    printf("  X: %.4f, Y: %.4f, Z: %.4f\n",
           pst_ImuData->f32_AccelX_m_s2, pst_ImuData->f32_AccelY_m_s2, pst_ImuData->f32_AccelZ_m_s2);

    // 각속도 데이터
    printf("Gyroscope Data (deg/s):\n");
    printf("  X: %.4f, Y: %.4f, Z: %.4f\n",
           pst_ImuData->f32_GyroX_deg_s, pst_ImuData->f32_GyroY_deg_s, pst_ImuData->f32_GyroZ_deg_s);

    // 오일러 각도 데이터
    printf("Euler Angles (degrees):\n");
    printf("  Roll: %.4f, Pitch: %.4f, Yaw: %.4f\n",
           pst_ImuData->f32_Roll_deg, pst_ImuData->f32_Pitch_deg, pst_ImuData->f32_Yaw_deg);

    // 자기장 데이터
    printf("Magnetic Field Data (mT):\n");
    printf("  X: %.4f, Y: %.4f, Z: %.4f\n",
           pst_ImuData->f32_MagneticX_mT, pst_ImuData->f32_MagneticY_mT, pst_ImuData->f32_MagneticZ_mT);

}



void PubImuData(IMU_DATA_t *pst_ImuData, ros::Publisher &pub)
{
    sensor_msgs::Imu ImuMsg;

    ImuMsg.header.stamp = ros::Time::now();
    
    ImuMsg.linear_acceleration.x = pst_ImuData->f32_AccelX_m_s2;
    ImuMsg.linear_acceleration.y = pst_ImuData->f32_AccelY_m_s2;
    ImuMsg.linear_acceleration.z = pst_ImuData->f32_AccelZ_m_s2;

    ImuMsg.angular_velocity.x = pst_ImuData->f32_GyroX_deg_s * M_PI / 180.0;  // Convert to radians
    ImuMsg.angular_velocity.y = pst_ImuData->f32_GyroY_deg_s * M_PI / 180.0;  // Convert to radians
    ImuMsg.angular_velocity.z = pst_ImuData->f32_GyroZ_deg_s * M_PI / 180.0;  // Convert to radians

    tf2::Quaternion q;
    q.setRPY(pst_ImuData->f32_Roll_deg * M_PI / 180.0,  // Convert to radians
             pst_ImuData->f32_Pitch_deg * M_PI / 180.0, // Convert to radians
             pst_ImuData->f32_Yaw_deg * M_PI / 180.0);  // Convert to radians
    ImuMsg.orientation.x = q.x();
    ImuMsg.orientation.y = q.y();
    ImuMsg.orientation.z = q.z();
    ImuMsg.orientation.w = q.w();

    pub.publish(ImuMsg);
}
