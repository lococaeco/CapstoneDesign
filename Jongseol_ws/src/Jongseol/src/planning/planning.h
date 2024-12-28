#ifndef PLANNING_H
#define PLANNING_H

#include "global/global.h"

void PlanningProcessing(PLANNING_DATA_t *pst_PlanningData,
                        OBJECT_DATA_t *pst_ObjectData,
                        SLAM_DATA_t *pst_SlamData,
                        ENCODER_DATA_t *pst_EncoderData);

void EgoVehicleDataProcessing(PLANNING_DATA_t *pst_PlanningData, SLAM_DATA_t *pst_SlamData, ENCODER_DATA_t *pst_EncoderData);
void ObjectDataProcessing(PLANNING_DATA_t *pst_PlanningData, OBJECT_DATA_t *pst_ObjectData);
void UpdateInlierData(PLANNING_DATA_t *pst_PlanningData);
void A_STAR();
void FinalPath(PLANNING_DATA_t *pst_PlanningData);

void GoalPointVisualize(PLANNING_DATA_t *pst_PlanningData, OBJECT_DATA_t *pst_ObjectData, ros::Publisher &marker_pub);
void GPPVisualize(PLANNING_DATA_t *pst_PlanningData, ros::Publisher &Path_pub);
void GridVisualize(vector<vector<int>> &BinaryFinalGridMap, ros::Publisher &Grid_pub);
void EgoVisualize(PLANNING_DATA_t *pst_PlanningData, ros::Publisher &Ego_pub);
void ImuViz(IMU_DATA_t *imu_data, ros::Publisher &imu_pub, tf2_ros::TransformBroadcaster &tf_broadcaster);



void PathMake(SLAM_DATA_t *pst_SlamData);
vector<Point> Astar(vector<vector<int>>& Map, Point start, Point end, int vehicle_radius);

#endif
