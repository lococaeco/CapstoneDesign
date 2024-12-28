#include "lidar.h"

parameter P;


inline float cal_dist(float x, float y){return sqrt(x*x+y*y);}


inline float MidPt(float a, float b){
    return (a + b) / 2;
}


inline void print_coord(pcl::PointXYZ tmp){
    //  cout << fixed << setprecision(3) <<"dist : " << cal_dist(tmp.x,tmp.y) << "   x : " << tmp.x << "   y : " << tmp.y <<endl;
}


inline bool check_in(pcl::PointXYZ a, pcl::PointXYZ b) {
	return ((abs(a.x - b.x) <= P.REMOVE_FACTOR) && (abs(a.y - b.y) <= P.REMOVE_FACTOR));
}



void pub_process(pcl::PointCloud<pcl::PointXYZI>& input, sensor_msgs::PointCloud2& output){
    pcl::PCLPointCloud2 tmp_PCL;                               //declare PCL_PC2
    pcl::toPCLPointCloud2(input, tmp_PCL);                     //PC -> PCL_PC2
    pcl_conversions::fromPCL(tmp_PCL, output);                 //PCL_PC2 -> sensor_msg_PC2
    output.header.frame_id = "map_o3d";
}


void pub_process(pcl::PointCloud<pcl::PointXYZ>& input, sensor_msgs::PointCloud2& output){
    pcl::PCLPointCloud2 tmp_PCL;                               //declare PCL_PC2
    pcl::toPCLPointCloud2(input, tmp_PCL);                     //PC -> PCL_PC2
    pcl_conversions::fromPCL(tmp_PCL, output);                 //PCL_PC2 -> sensor_msg_PC2
    output.header.frame_id = "map_o3d";
}


void ROI(pcl::PointCloud<pcl::PointXYZI>& rawData, ros::Publisher& publisher){            //setting ROI
    for(unsigned int j = 0; j<rawData.points.size(); j++){     //actual ROI setting
        float *x = &rawData.points[j].x, *y = &rawData.points[j].y, *z = &rawData.points[j].z;
        if(*x > P.ROI_xMin && *x < P.ROI_xMax && *y > P.ROI_yMin && *y < P.ROI_yMax && *z > P.ROI_zMin && *z < P.ROI_zMax) continue;
        *x = *y = *z = 0;
    }
    sensor_msgs::PointCloud2 output;                           //to output ROIdata formed PC2
    pub_process(rawData,output);
    publisher.publish(output);
}


void DownSampling(pcl::PointCloud<pcl::PointXYZI>& rawData, pcl::PointCloud<pcl::PointXYZ>::Ptr downsampledCloud, ros::Publisher& publisher) { 
    pcl::PointCloud<pcl::PointXYZ> Data_for_voxel;
    pcl::VoxelGrid<pcl::PointXYZ> vg;                   // Declare voxel

    // Copy raw data for voxel modification
    copyPointCloud(rawData, Data_for_voxel);
    vg.setInputCloud(Data_for_voxel.makeShared());      // Deep copy raw data into voxel grid
    vg.setLeafSize(P.voxel_size_x, P.voxel_size_y, P.voxel_size_z);  // Set voxel size
    vg.filter(*downsampledCloud);                      // Downsampled cloud

    // Filter the downsampled points based on z values
    pcl::PassThrough<pcl::PointXYZ> pass;
    pass.setInputCloud(downsampledCloud);
    pass.setFilterFieldName("z");
    pass.setFilterLimits(0.0, 0.4);                    // Keep points where 0m <= z <= 0.4m
    pass.filter(*downsampledCloud);                   // Filtered cloud with z constraints

    // Convert to PointCloud2 format and publish
    sensor_msgs::PointCloud2 output;
    pub_process(*downsampledCloud, output);
    publisher.publish(output);
}

