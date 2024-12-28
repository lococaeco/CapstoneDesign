#ifndef GLOBAL_H
#define GLOBAL_H
#pragma once

#include <ros/ros.h>
#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <math.h>
#include <vector>
#include <pthread.h>
#include <boost/asio.hpp>
#include <chrono>
#include <boost/format.hpp>
#include <ncurses.h>
#include <yaml-cpp/yaml.h>
#include <pcl_ros/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/common/common.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/statistical_outlier_removal.h> //noise filtering
#include <pcl/sample_consensus/ransac.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/kdtree/kdtree.h>
#include "Jongseol/objs.h"

#include <sensor_msgs/Imu.h>
#include <sensor_msgs/PointCloud2.h>

#include <tf2_ros/transform_broadcaster.h>
#include <tf2/LinearMath/Quaternion.h>
#include "Total_msgs/Control.h"
#include "Total_msgs/Encoder.h"

#include "geometry_msgs/TransformStamped.h"
#include <geometry_msgs/Point.h>

#include <visualization_msgs/MarkerArray.h>
#include <visualization_msgs/Marker.h>

#include <nav_msgs/OccupancyGrid.h>
#include <std_msgs/Header.h>

using namespace std;

using PointT = pcl::PointXYZ;
using PointCloudT = pcl::PointCloud<PointT>;

typedef pair<int,int> Point;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef short int16_t;
typedef float float32_t;
typedef double float64_t;

const bool b_Running = true;
const int32_t c_PLANNING_MAX_PATH_NUM = 5000;

typedef struct _RAW_IMU_DATA
{
    int32_t s32_IMUHeader;
    uint64_t u64_Timestamp;
    int32_t s32_Num;
    char arc_Buffer[20000];

} RAW_IMU_DATA_t;

typedef struct _RAW_SLAM_DATA
{
    int32_t s32_SLAMHeader;
    uint64_t u64_Timestamp;
    int32_t s32_Num;
    char arc_Buffer[50000];
} RAW_SLAM_DATA_t;



typedef struct _RAW_ENCODER_DATA
{
    int32_t s32_EncoderHeader;
    uint64_t u64_Timestamp;
    int32_t s32_Num;
    char arc_Buffer[20000];
} RAW_ENCODER_DATA_t;

typedef struct _RAW_OBJECT_DATA
{
    int32_t s32_ObjectHeader;
    uint64_t u64_Timestamp;
    int32_t s32_Num;
    char arc_Buffer[500000];
} RAW_OBJECT_DATA_t;


typedef struct _IMU_DATA
{

    float32_t f32_AccelX_m_s2;
    float32_t f32_AccelY_m_s2;
    float32_t f32_AccelZ_m_s2;

    float32_t f32_GyroX_deg_s;
    float32_t f32_GyroY_deg_s;
    float32_t f32_GyroZ_deg_s;

    float32_t f32_Roll_deg;
    float32_t f32_Pitch_deg;
    float32_t f32_Yaw_deg;

    float32_t f32_MagneticX_mT;
    float32_t f32_MagneticY_mT;
    float32_t f32_MagneticZ_mT;

} IMU_DATA_t;

typedef struct _SLAM_DATA
{
    float32_t f32_TranslationX;
    float32_t f32_TranslationY;
    float32_t f32_TranslationZ;

    float32_t f32_QuaternionX;
    float32_t f32_QuaternionY;
    float32_t f32_QuaternionZ;
    float32_t f32_QuaternionW;

} SLAM_DATA_t;


typedef struct _ENCODER_DATA
{
    int16_t s16_RightWheelRPM;
    int16_t s16_LeftWheelRPM;
    float32_t f32_RightWheelSpeed_m_s; 
    float32_t f32_LeftWheelSpeed_m_s; 
    float32_t f32_EncoderSpeed_m_s; 

} ENCODER_DATA_t;

typedef struct _OBJECT_DATA
{
    int32_t s32_ObjectNum;
    float32_t f32_X[3000];
    float32_t f32_Y[3000];
    float32_t f32_Z[3000];

    float32_t f32_DX[3000];
    float32_t f32_DY[3000];
    float32_t f32_DZ[3000];

} OBJECT_DATA_t;



typedef struct _PATH
{
    float32_t arf32_X[c_PLANNING_MAX_PATH_NUM];
    float32_t arf32_Y[c_PLANNING_MAX_PATH_NUM];
    float32_t arf32_S[c_PLANNING_MAX_PATH_NUM];
    float32_t arf32_Yaw_rad_ENU[c_PLANNING_MAX_PATH_NUM];
    float32_t arf32_Yaw_rad_NED[c_PLANNING_MAX_PATH_NUM];
    int32_t s32_Num;

    int32_t s32_NearIdx;
    float32_t f32_NearDist;

} PATH_t;

typedef struct _GRID
{

    int16_t s16_BinaryGrid[1000][1000];
    int16_t s16_XNum;
    int16_t s16_YNum;

} GRID_t;

typedef struct _VEHICLE_DATA
{
    float32_t f32_X;
    float32_t f32_Y;
    float32_t f32_Z;

    float32_t f32_X_global;
    float32_t f32_Y_global;
    float32_t f32_Z_global;

    float32_t f32_DX;
    float32_t f32_DY;
    float32_t f32_DZ;

    float32_t f32_Velocity_m_s;
    float32_t f32_Velocity_kph;

    float32_t f32_RightWheelSpeed_m_s; 
    float32_t f32_LeftWheelSpeed_m_s; 
    float32_t f32_EncoderSpeed_m_s;

    float32_t f32_Yaw_rad_ENU; //ENU
    float32_t f32_Yaw_rad_NED;  //NED
    float32_t f32_Yaw_deg_ENU; //ENU
    float32_t f32_Yaw_deg_NED;  //NED

} VEHICLE_DATA_t;

typedef struct _PLANNING_DATA
{
    PATH_t st_TemporalPath_global;

    VEHICLE_DATA_t st_EgoVehicleData;
    VEHICLE_DATA_t st_ObjectData[3000];
    int32_t s32_ObjectNum;
    VEHICLE_DATA_t st_InlierData[1000];
    int32_t s32_InlierNum;

    GRID_t st_BinaryGrid;
    PATH_t st_FinalPath;

    PATH_t st_GppPath;

} PLANNING_DATA_t;

typedef struct _Control_Param
{
    // vehicle parameters
    const float32_t f32_WB = 0.318f;
    const float32_t f32_GPS_to_Front = 1.07f;
    const float32_t f32_WheelDiameter = 0.125f;
    const float32_t f32_DT = 0.1f;

    // Dynamics
    const float32_t f32_MAX_SPEED_m_s = 1.3f;         // [m/s]
    const float32_t f32_MIN_SPEED_m_s = 0.f;          // [m/s]
    const float32_t f32_MAX_STEER_rad = 0.6088f;      // [rad]

} CONTROL_PARAM_t;

typedef struct _PID
{
    float32_t f32_KP = 2.0f;
    float32_t f32_KD = 0.05f;

    float32_t f32_Error = 0;
    float32_t f32_PreError = 0;

    float32_t f32_InputP = 0;
    float32_t f32_InputD = 0;

} PID_t;

typedef struct _PURE_PURSUIT
{
    float32_t f32_LD = 0.8;
    float32_t f32_Alpha;
    int32_t s32_WayIdx;

} PURE_PURSUIT_t;

typedef struct _CONTROL_DATA
{
    // Target Control Input
    float32_t f32_TargetSteer_deg;
    float32_t f32_TargetSteer_rad;
    float32_t f32_TargetSpeed_m_s;
    float32_t f32_TargetThrottle;

    // Control
    CONTROL_PARAM_t st_Param;
    PURE_PURSUIT_t st_PurePursuit;
    PID_t st_PID_Throttle;

} CONTROL_DATA_t;

void DataLoad(const char* filename, PATH_t &Path);
void GridLoad(const char* filename, GRID_t &Grid);

void GetModData(float32_t min, float32_t max, float32_t &data);
void GetModData(float64_t min, float64_t max, float64_t &data);
void GetModData(int32_t min, int32_t max, int32_t &data);
float32_t getDistance2d(float32_t f32_X1, float32_t f32_Y1, float32_t f32_X2, float32_t f32_Y2);
float64_t getDistance2d(float64_t f64_X1, float64_t f64_Y1, float64_t f64_X2, float64_t f64_Y2);
float32_t pi2pi(float32_t f32_Angle);
float64_t pi2pi(float64_t f64_Angle);
float32_t axisRotate(float32_t f32_Heading_rad);

uint64_t getMilliSec();

void keyboardCallback(int key);
#endif
