#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/common/common.h>
#include <pcl/filters/extract_indices.h>

// #include <pcl/ExtractIndices.h>
#include <fstream>
#include <vector>

int main(int argc, char** argv)
{
    // 파일 경로 설정
    std::string inputFilePath = "/home/jongseol/Jongseol_2024/SLAM_ws/src/open3d_slam/ros/open3d_slam_ros/data/maps/513map.pcd";
    std::string outputFilePath = "/home/jongseol/Jongseol_2024/Jongseol_ws/src/Jongseol/GridMap/513Grid.txt";

    // 포인트 클라우드 객체 생성
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>());
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_no_floor(new pcl::PointCloud<pcl::PointXYZ>());

    // 포인트 클라우드 읽기
    if (pcl::io::loadPCDFile<pcl::PointXYZ>(inputFilePath, *cloud) == -1) {
        return -1;
    }


    // 다운샘플링
    pcl::VoxelGrid<pcl::PointXYZ> voxel_filter;
    voxel_filter.setInputCloud(cloud);
    voxel_filter.setLeafSize(0.1f, 0.1f, 0.1f);
    voxel_filter.filter(*cloud_filtered);

    // 바닥 제거 (첫 번째 RANSAC)
    pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients());
    pcl::PointIndices::Ptr inliers(new pcl::PointIndices());
    pcl::SACSegmentation<pcl::PointXYZ> seg;
    seg.setOptimizeCoefficients(true);
    seg.setModelType(pcl::SACMODEL_PLANE);
    seg.setMethodType(pcl::SAC_RANSAC);
    seg.setDistanceThreshold(0.2);
    seg.setInputCloud(cloud_filtered);
    seg.segment(*inliers, *coefficients);

    if (inliers->indices.empty()) {
        return -1;
    }

    pcl::ExtractIndices<pcl::PointXYZ> extract;
    extract.setInputCloud(cloud_filtered);
    extract.setIndices(inliers);
    extract.setNegative(true);
    extract.filter(*cloud_no_floor);

    // Z 필터링
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_z_filtered(new pcl::PointCloud<pcl::PointXYZ>());
    for (const auto& point : cloud_no_floor->points) {
        if (point.z >= 0.1 && point.z <= 0.6) {
            cloud_z_filtered->points.push_back(point);
        }
    }
    cloud_z_filtered->width = cloud_z_filtered->points.size();
    cloud_z_filtered->height = 1;
    cloud_z_filtered->is_dense = true;

    // 2D 바이너리 맵 생성
    float gridSize = 0.1;
    int threshold = 2; // 그리드 카운트 임계값

    // X, Y 좌표 범위 계산
    pcl::PointXYZ minPt, maxPt;
    pcl::getMinMax3D(*cloud_z_filtered, minPt, maxPt);

    printf("X:%f Y:%f\n",minPt.x, minPt.y );

    int gridX = static_cast<int>((maxPt.x - minPt.x) / gridSize) + 1;
    int gridY = static_cast<int>((maxPt.y - minPt.y) / gridSize) + 1;

    std::vector<std::vector<int>> gridMap(gridY, std::vector<int>(gridX, 0));

    for (const auto& point : cloud_z_filtered->points)
    {
        int xIdx = static_cast<int>((point.x - minPt.x) / gridSize);
        int yIdx = static_cast<int>((point.y - minPt.y) / gridSize);
        gridMap[yIdx][xIdx]++;
    }

    // 바이너리 맵 변환
    std::vector<std::vector<int>> gridMapBinary(gridY, std::vector<int>(gridX, 0));
    for (int y = 0; y < gridY; ++y) {
        for (int x = 0; x < gridX; ++x) {
            gridMapBinary[y][x] = (gridMap[y][x] >= threshold) ? 1 : 0;
        }
    }

    // 파일 저장
    std::ofstream outFile(outputFilePath);
    for (const auto& row : gridMapBinary) {
        for (const auto& val : row) {
            outFile << val << " ";
        }
        outFile << "\n";
    }
    outFile.close();


    return 0;
}
