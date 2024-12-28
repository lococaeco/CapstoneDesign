#include "control.h"

void ControlProcessing(PLANNING_DATA_t *pst_PlanningData,
					   CONTROL_DATA_t *pst_ControlData)
{
    PurePursuit(pst_PlanningData, pst_ControlData);
    PIDControl(pst_PlanningData, pst_ControlData);
}

void PurePursuit(PLANNING_DATA_t *pst_PlanningData,
                 CONTROL_DATA_t *pst_ControlData)
{
    PURE_PURSUIT_t *pst_PurePursuit = &pst_ControlData->st_PurePursuit;
	CONTROL_PARAM_t *pst_Param = &pst_ControlData->st_Param;
	PATH_t *pst_FinalPath = &pst_PlanningData->st_FinalPath;
	VEHICLE_DATA_t *pst_EgoVehicleData = &pst_PlanningData->st_EgoVehicleData;

	float32_t f32_MinDist = 10000000.f;
    int32_t s32_NearestIdx = 0;

	//Find Near
    for(int32_t s32_I = 0;s32_I < pst_FinalPath->s32_Num;s32_I++)
    {
        float32_t f32_Dist = getDistance2d(pst_EgoVehicleData->f32_X, pst_EgoVehicleData->f32_Y,
                                           pst_FinalPath->arf32_X[s32_I], pst_FinalPath->arf32_Y[s32_I]);
        if(f32_Dist < f32_MinDist)
        {
            f32_MinDist = f32_Dist;
            s32_NearestIdx = s32_I;
        }
    }

    pst_FinalPath->s32_NearIdx = s32_NearestIdx;

	// Find Waypoint
	for (int32_t s32_i = pst_FinalPath->s32_NearIdx; s32_i < pst_FinalPath->s32_Num; s32_i++)
	{
		float32_t f32_TmpDist = getDistance2d(pst_EgoVehicleData->f32_X, pst_EgoVehicleData->f32_Y, pst_FinalPath->arf32_X[s32_i], pst_FinalPath->arf32_Y[s32_i]);
		if (f32_TmpDist >= pst_PurePursuit->f32_LD)
		{
			pst_PurePursuit->s32_WayIdx = s32_i;
			break;
		}
		else if (s32_i == pst_FinalPath->s32_Num - 1)
		{
			pst_PurePursuit->s32_WayIdx = pst_FinalPath->s32_Num - 1;
		}
	}

	pst_PurePursuit->f32_Alpha = atan2(pst_FinalPath->arf32_Y[pst_PurePursuit->s32_WayIdx] - pst_EgoVehicleData->f32_Y, 
									   pst_FinalPath->arf32_X[pst_PurePursuit->s32_WayIdx] - pst_EgoVehicleData->f32_X) - pst_EgoVehicleData->f32_Yaw_rad_ENU;

	pi2pi(pst_PurePursuit->f32_Alpha);

	pst_ControlData->f32_TargetSteer_rad = atan2(2 * pst_Param->f32_WB * sinf(pst_PurePursuit->f32_Alpha), pst_PurePursuit->f32_LD);
	pst_ControlData->f32_TargetSteer_deg = pst_ControlData->f32_TargetSteer_rad * 180 / M_PI;

}

void PIDControl(PLANNING_DATA_t *pst_PlanningData,
                CONTROL_DATA_t *pst_ControlData)
{
	CONTROL_PARAM_t *pst_Param = &pst_ControlData->st_Param;
    VEHICLE_DATA_t *pst_EgoVehicleData = &pst_PlanningData->st_EgoVehicleData;
	PID_t *pst_PID = &pst_ControlData->st_PID_Throttle;
    float32_t f32_TargetThrottle = 0;

	pst_ControlData->f32_TargetSpeed_m_s = 5 / 3.6;

	GetModData(pst_Param->f32_MIN_SPEED_m_s, pst_Param->f32_MAX_SPEED_m_s, pst_ControlData->f32_TargetSpeed_m_s);

	pst_PID->f32_Error = pst_ControlData->f32_TargetSpeed_m_s - pst_EgoVehicleData->f32_Velocity_m_s;
	
	
	pst_PID->f32_InputP = pst_PID->f32_KP * pst_PID->f32_Error;
	pst_PID->f32_InputD = pst_PID->f32_KD * (pst_PID->f32_Error - pst_PID->f32_PreError) / pst_Param->f32_DT;
	f32_TargetThrottle = (pst_PID->f32_InputP + pst_PID->f32_InputD);

	pst_PID->f32_PreError = pst_PID->f32_Error;

	pst_ControlData->f32_TargetThrottle = f32_TargetThrottle;
	GetModData(-1.0, 1.0, pst_ControlData->f32_TargetThrottle);
}
