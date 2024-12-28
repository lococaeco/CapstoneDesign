#ifndef CONTROL_H
#define CONTROL_H

#include "global/global.h"

void ControlProcessing(PLANNING_DATA_t *pst_PlanningData, CONTROL_DATA_t *pst_ControlData);
void ControlSetup(PLANNING_DATA_t *pst_PlanningData, CONTROL_DATA_t *pst_ControlData);
void PurePursuit(PLANNING_DATA_t *pst_PlanningData, CONTROL_DATA_t *pst_ControlData);
void PIDControl(PLANNING_DATA_t *pst_PlanningData, CONTROL_DATA_t *pst_ControlData);
void Control2Vehicle(CONTROL_DATA_t *pst_ControlData);
#endif 