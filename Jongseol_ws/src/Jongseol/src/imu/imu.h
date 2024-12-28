#ifndef IMU_H
#define IMU_H

#include "global/global.h"

void PrintImuData(IMU_DATA_t *pst_ImuData);
void PubImuData(IMU_DATA_t *pst_ImuData, ros::Publisher &pub);

#endif
