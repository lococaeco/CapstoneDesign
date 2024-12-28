#ifndef LIDAR_H
#define LIDAR_H
#pragma once

#include "global/global.h"
#include <pcl/filters/passthrough.h>

class parameter{
public:
    double REMOVE_FACTOR;
    float voxel_size_x, voxel_size_y, voxel_size_z;
    float ROI_xMin, ROI_xMax, ROI_yMin, ROI_yMax, ROI_zMin, ROI_zMax;
    float clustering_offset;
    int MinClusterSize, MaxClusterSize;
    bool NoiseFiltering;
    double ransac_distanceThreshold; //함수 : double형 parameter

    parameter(){
        this -> set_para();
    }
    void set_para(){
        //jiwonFilter parameter
        this -> REMOVE_FACTOR = 0.2;

        //downsampling parameter
        this -> voxel_size_x = 0.1f; 
        this -> voxel_size_y = 0.1f; 
        this -> voxel_size_z = 0.1f;

        //ROI parameter
        this -> ROI_xMin = -2;
        this -> ROI_xMax = -0.2;
        this -> ROI_yMin = -0.5;
        this -> ROI_yMax = 0.5;
        this -> ROI_zMin = -0.2;
        this -> ROI_zMax = 0.3;

        //clustering parameter
        this -> clustering_offset = 0.23;
        this -> MinClusterSize = 2;
        this -> MaxClusterSize = 100;

        //ransac parameter
        this -> ransac_distanceThreshold = 0.2;
        
        //function on/off
        this -> NoiseFiltering = 1;
    }
};


inline float cal_dist(float x, float y);
inline float MidPt(float a, float b);
inline void print_coord(pcl::PointXYZ tmp);
inline bool check_in(pcl::PointXYZ a, pcl::PointXYZ b);
template<typename T>
void pub_process(pcl::PointCloud<pcl::PointXYZI>& input, sensor_msgs::PointCloud2& output);
void pub_process(pcl::PointCloud<pcl::PointXYZ>& input, sensor_msgs::PointCloud2& output);
void ROI(pcl::PointCloud<pcl::PointXYZI>& rawData, ros::Publisher& publisher);
void DownSampling(pcl::PointCloud<pcl::PointXYZI>& rawData, pcl::PointCloud<pcl::PointXYZ>::Ptr downsampledCloud, ros::Publisher& publisher);

#endif
