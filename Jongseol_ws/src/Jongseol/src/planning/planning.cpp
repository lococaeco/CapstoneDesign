#include "planning.h"

extern bool b_Map;
extern PLANNING_DATA_t st_PlanningData;
extern int currentGoal; // 현재 목표 번호를 추적하는 변수

extern float32_t f32_GoalX_1, f32_GoalY_1;
extern float32_t f32_GoalX_2, f32_GoalY_2;
extern float32_t f32_GoalX_3, f32_GoalY_3;
extern float32_t f32_GoalX_4, f32_GoalY_4;

extern bool GoalPoint_1;
extern bool GoalPoint_2;
extern bool GoalPoint_3;
extern bool GoalPoint_4;

extern vector<vector<int>> BinaryFinalGridMap;

extern float32_t f32_GoalX, f32_GoalY;
extern pcl::PointCloud<pcl::PointXYZ>::Ptr st_DownSampledCloud;

extern float32_t f32_MinX, f32_MinY;
extern int32_t s32_Mode;

void PlanningProcessing(PLANNING_DATA_t *pst_PlanningData,
                        OBJECT_DATA_t *pst_ObjectData,
                        SLAM_DATA_t *pst_SlamData,
                        ENCODER_DATA_t *pst_EncoderData)
{
    if (s32_Mode == 0)
    {
        A_STAR();
    }

    EgoVehicleDataProcessing(pst_PlanningData, pst_SlamData, pst_EncoderData);
    ObjectDataProcessing(pst_PlanningData, pst_ObjectData);
    UpdateInlierData(pst_PlanningData);
    FinalPath(pst_PlanningData);


    if (b_Map) // Keyboard "L"
    {
        PathMake(pst_SlamData);
    }
}

void EgoVehicleDataProcessing(PLANNING_DATA_t *pst_PlanningData, SLAM_DATA_t *pst_SlamData, ENCODER_DATA_t *pst_EncoderData)
{
    VEHICLE_DATA_t *pst_EgoVehicleData = &pst_PlanningData->st_EgoVehicleData;

    float32_t f32_Yaw_rad = atan2f(2.0f * (pst_SlamData->f32_QuaternionW * pst_SlamData->f32_QuaternionZ
                              + pst_SlamData->f32_QuaternionX * pst_SlamData->f32_QuaternionY),
                              1.f - 2.f * (pst_SlamData->f32_QuaternionY * pst_SlamData->f32_QuaternionY
                              + pst_SlamData->f32_QuaternionZ * pst_SlamData->f32_QuaternionZ));

    if (f32_Yaw_rad > M_PI)
    {
        f32_Yaw_rad -= 2.0f * M_PI;
    }

    f32_Yaw_rad = f32_Yaw_rad + M_PI;

    if (f32_Yaw_rad > M_PI)
    {
        f32_Yaw_rad = f32_Yaw_rad - 2 * M_PI ; 
    }
    float32_t f32_Yaw_deg = f32_Yaw_rad * 180.0f / M_PI;

    pst_EgoVehicleData->f32_Yaw_deg_ENU = f32_Yaw_deg;
    pst_EgoVehicleData->f32_Yaw_rad_ENU = f32_Yaw_rad;
    pst_EgoVehicleData->f32_Yaw_rad_NED = axisRotate(f32_Yaw_rad);
    pst_EgoVehicleData->f32_Yaw_deg_NED = pst_EgoVehicleData->f32_Yaw_rad_ENU * 180.f / M_PI;

    pst_EgoVehicleData->f32_X = pst_SlamData->f32_TranslationX;
    pst_EgoVehicleData->f32_Y = pst_SlamData->f32_TranslationY;
    pst_EgoVehicleData->f32_Z = pst_SlamData->f32_TranslationZ;

    pst_EgoVehicleData->f32_EncoderSpeed_m_s = pst_EncoderData->f32_EncoderSpeed_m_s;
    pst_EgoVehicleData->f32_LeftWheelSpeed_m_s = pst_EncoderData->f32_LeftWheelSpeed_m_s; 
    pst_EgoVehicleData->f32_RightWheelSpeed_m_s = pst_EncoderData->f32_RightWheelSpeed_m_s; 
    pst_EgoVehicleData->f32_Velocity_m_s = pst_EgoVehicleData->f32_EncoderSpeed_m_s;
    pst_EgoVehicleData->f32_Velocity_kph = pst_EgoVehicleData->f32_Velocity_m_s * 3.6f;

}

void ObjectDataProcessing(PLANNING_DATA_t *pst_PlanningData, OBJECT_DATA_t *pst_ObjectData)
{
    VEHICLE_DATA_t *pst_ObjectVehicleData = pst_PlanningData->st_ObjectData;

    int32_t s32_I;
    int32_t s32_Num = pst_ObjectData->s32_ObjectNum;
    pst_PlanningData->s32_ObjectNum = s32_Num;
    
    // printf("-----------------------------------\n");
    // printf("Num: %d\n",pst_ObjectData->s32_ObjectNum);

    for (s32_I = 0;s32_I < s32_Num;s32_I++)
    {
        pst_ObjectVehicleData[s32_I].f32_X = pst_ObjectData->f32_X[s32_I];
        pst_ObjectVehicleData[s32_I].f32_Y = pst_ObjectData->f32_Y[s32_I];
        pst_ObjectVehicleData[s32_I].f32_Z = pst_ObjectData->f32_Z[s32_I];
        
        float32_t f32_TempHeading = pst_PlanningData->st_EgoVehicleData.f32_Yaw_rad_ENU;
        f32_TempHeading += M_PI;

        if (f32_TempHeading > M_PI)
        {
            f32_TempHeading = f32_TempHeading - 2*M_PI;
        }
        

        pst_ObjectVehicleData[s32_I].f32_X_global = pst_PlanningData->st_EgoVehicleData.f32_X + pst_ObjectVehicleData[s32_I].f32_X * cos(f32_TempHeading) - pst_ObjectVehicleData[s32_I].f32_Y * sin(f32_TempHeading);
        pst_ObjectVehicleData[s32_I].f32_Y_global = pst_PlanningData->st_EgoVehicleData.f32_Y + pst_ObjectVehicleData[s32_I].f32_X * sin(f32_TempHeading) + pst_ObjectVehicleData[s32_I].f32_Y * cos(f32_TempHeading);

        pst_ObjectVehicleData[s32_I].f32_DX = pst_ObjectData->f32_DX[s32_I];
        pst_ObjectVehicleData[s32_I].f32_DY = pst_ObjectData->f32_DY[s32_I];
        pst_ObjectVehicleData[s32_I].f32_DZ = pst_ObjectData->f32_DZ[s32_I];

        // printf("[%d]X: %f , Y: %f\n",s32_I, pst_ObjectVehicleData[s32_I].f32_X, pst_ObjectVehicleData[s32_I].f32_Y);
    }
}

void UpdateInlierData(PLANNING_DATA_t *pst_PlanningData)
{
    PATH_t *pst_FinalPath = &pst_PlanningData->st_FinalPath;
    VEHICLE_DATA_t *pst_ObjectVehicleData = pst_PlanningData->st_ObjectData;
    VEHICLE_DATA_t st_InlierData[1000];
    memset(&st_InlierData, 0, sizeof(VEHICLE_DATA_t));

    int32_t s32_Num = pst_PlanningData->s32_ObjectNum;
    int32_t s32_NearIdx = pst_FinalPath->s32_NearIdx;
    int32_t s32_InlierIdx = 0;
    float32_t threshold = 0.8f; // 장애물과 경로의 거리 임계값

    for (int32_t i = 0; i < s32_Num; i++)
    {
        float32_t objX_global = pst_ObjectVehicleData[i].f32_X_global;
        float32_t objY_global = pst_ObjectVehicleData[i].f32_Y_global;

        float32_t EgoX = pst_PlanningData->st_EgoVehicleData.f32_X;
        float32_t EgoY = pst_PlanningData->st_EgoVehicleData.f32_Y;

        float32_t distance = sqrtf((objX_global - EgoX) * (objX_global - EgoX) +
                                    (objY_global - EgoY) * (objY_global - EgoY));

        if (distance <= threshold)
        {
            // Inlier 데이터를 저장
            st_InlierData[s32_InlierIdx].f32_X = pst_ObjectVehicleData[i].f32_X;
            st_InlierData[s32_InlierIdx].f32_Y = pst_ObjectVehicleData[i].f32_Y;
            st_InlierData[s32_InlierIdx].f32_Z = pst_ObjectVehicleData[i].f32_Z;
            st_InlierData[s32_InlierIdx].f32_X_global = pst_ObjectVehicleData[i].f32_X_global;
            st_InlierData[s32_InlierIdx].f32_Y_global = pst_ObjectVehicleData[i].f32_Y_global;
            st_InlierData[s32_InlierIdx].f32_DX = pst_ObjectVehicleData[i].f32_DX;
            st_InlierData[s32_InlierIdx].f32_DY = pst_ObjectVehicleData[i].f32_DY;
            st_InlierData[s32_InlierIdx].f32_DZ = pst_ObjectVehicleData[i].f32_DZ;
            s32_InlierIdx++;
            break;
        }
    }
    // printf("iNLIER: %d\n",pst_PlanningData->s32_InlierNum);
    pst_PlanningData->s32_InlierNum = s32_InlierIdx; 
    memcpy(&pst_PlanningData->st_InlierData, &st_InlierData, sizeof(VEHICLE_DATA_t));
}



void FinalPath(PLANNING_DATA_t *pst_PlanningData)
{
    PATH_t *pst_FinalPath = &pst_PlanningData->st_FinalPath;

    if (s32_Mode == 0)
    {
        memcpy(pst_FinalPath, &pst_PlanningData->st_GppPath, sizeof(PATH_t));

        int32_t s32_I;

        pst_FinalPath->arf32_S[0] = 0.0f;

        for (s32_I = 1;s32_I < pst_FinalPath->s32_Num;s32_I++)
        {
            float32_t f32_Dx = pst_FinalPath->arf32_X[s32_I] - pst_FinalPath->arf32_X[s32_I - 1];
            float32_t f32_Dy = pst_FinalPath->arf32_Y[s32_I] - pst_FinalPath->arf32_Y[s32_I - 1];
            pst_FinalPath->arf32_S[s32_I] = pst_FinalPath->arf32_S[s32_I - 1] + sqrtf(f32_Dx * f32_Dx + f32_Dy * f32_Dy);
        }

        for (s32_I = 0;s32_I < pst_FinalPath->s32_Num - 1;s32_I++)
        {
            float32_t f32_Dx = pst_FinalPath->arf32_X[s32_I + 1] - pst_FinalPath->arf32_X[s32_I];
            float32_t f32_Dy = pst_FinalPath->arf32_Y[s32_I + 1] - pst_FinalPath->arf32_Y[s32_I];
            pst_FinalPath->arf32_Yaw_rad_ENU[s32_I] = atan2f(f32_Dy, f32_Dx); // ENU 기준 Yaw 계산
        }

        if (pst_FinalPath->s32_Num > 1)
        {
            pst_FinalPath->arf32_Yaw_rad_ENU[pst_FinalPath->s32_Num - 1] = pst_FinalPath->arf32_Yaw_rad_ENU[pst_FinalPath->s32_Num - 2];
        }
    }
    else
    {
        memcpy(pst_FinalPath, &pst_PlanningData->st_TemporalPath_global, sizeof(PATH_t));
    }
}

void PathMake(SLAM_DATA_t *pst_SlamData)
{
    static float32_t PrevX = 0.f;
    static float32_t PrevY = 0.f;
    static bool b_IsFirst = true;

    float32_t f32_CurrentX = pst_SlamData->f32_TranslationX;
    float32_t f32_CurrentY = pst_SlamData->f32_TranslationY;

    if (b_IsFirst)
    {
        PrevX = f32_CurrentX;
        PrevY = f32_CurrentY;
        b_IsFirst = false;
    }

    float32_t f32_Dist = sqrtf(powf(f32_CurrentX - PrevX, 2) + powf(f32_CurrentY - PrevY, 2));

    if (f32_Dist >= 0.1f)
    {
        FILE *p_File = fopen("./src/Jongseol/map/LabPath2.txt", "a");
        if (p_File == NULL)
        {
            return;
        }

        fprintf(p_File, "%f, %f\n", f32_CurrentX, f32_CurrentY);
        fclose(p_File);

        PrevX = f32_CurrentX;
        PrevY = f32_CurrentY;
    }

}


float heruistic(Point& a, Point& b)
{
    float dx = b.first - a.first;
    float dy = b.second - a.second;
        return sqrt(dx*dx + dy*dy);
}

bool is_valid_position(const vector<vector<int>>& Map, Point pos, int vehicle_radius) {
    int rows = Map.size();
    int cols = Map[0].size();

    // 차량 반경 내의 모든 위치 검사
    for (int i = -vehicle_radius; i <= vehicle_radius; ++i) {
        for (int j = -vehicle_radius; j <= vehicle_radius; ++j) {
            if (i * i + j * j > vehicle_radius * vehicle_radius) continue; // 반경 밖 제외
            int x = pos.first + i;
            int y = pos.second + j;

            if (x < 0 || x >= rows || y < 0 || y >= cols || Map[x][y] == 1) {
                return false; // 맵 바깥이거나 장애물에 겹침
            }
        }
    }
    return true;
}

vector<Point> Astar(vector<vector<int>>& Map, Point start, Point end, int vehicle_radius)
{
    vector<Point> neighbor_node = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    set<Point> close_list;
    map<Point, Point> Parent_Node;
    map<Point, float> G;
    map<Point, float> F;

    struct sorting
    {
        bool operator()(const pair<float, Point>& a, const pair<float, Point>& b) const {
            return a.first > b.first;
        }
    };

    priority_queue<pair<float, Point>, vector<pair<float, Point>>, sorting> openheap;

    G[start] = 0;
    F[start] = heruistic(start, end);
    openheap.push({F[start], start});

    while (!openheap.empty()) {
        Point current = openheap.top().second;
        openheap.pop();

        if (current == end) {
            vector<Point> path;
            while (Parent_Node.find(current) != Parent_Node.end()) {
                path.emplace_back(current);
                current = Parent_Node[current];
            }
            path.emplace_back(start);
            reverse(path.begin(), path.end());
            return path;
        }
        close_list.insert(current);

        for (auto neighbors : neighbor_node)
        {
            int i = neighbors.first;
            int j = neighbors.second;
            Point neighbor(current.first + i, current.second + j);

            if (!is_valid_position(Map, neighbor, vehicle_radius)) {
                continue; // 차량 반경을 고려한 충돌 체크
            }

            float neighbor_G = G[current] + heruistic(current, neighbor);

            if (close_list.find(neighbor) != close_list.end() && neighbor_G >= G[neighbor])
            {
                continue;
            }

            bool found = false;
            auto backup = openheap;
            while (!openheap.empty())
            {
                Point top = openheap.top().second;
                openheap.pop();
                if (top == neighbor) {
                    found = true;
                    break;
                }
            }
            openheap = backup;

            if (!found || neighbor_G < G[neighbor]) {
                Parent_Node[neighbor] = current;
                G[neighbor] = neighbor_G;
                F[neighbor] = G[neighbor] + heruistic(neighbor, end);
                openheap.push({F[neighbor], neighbor});
            }
        }
    }

    return vector<Point>(); // 경로가 없을 경우
}

int ConvertToGridIndex(float32_t f32_X, float32_t f32_Y,
                       float32_t f32_MinBoundX, float32_t f32_MinBoundY,
                       float32_t f32_GridSize, int &row, int &col)
{
    // 실제 좌표 -> 그리드 인덱스 변환
    col = static_cast<int>((f32_X - f32_MinBoundX) / f32_GridSize);
    row = static_cast<int>((f32_Y - f32_MinBoundY) / f32_GridSize);

    // 인덱스 유효성 확인 (범위를 초과하면 -1 반환)
    if (row < 0 || col < 0)
    {
        return -1; // 변환 실패
    }
    return 0; // 변환 성공
}

void UpdateBinaryDynamicGridMap(pcl::PointCloud<pcl::PointXYZ>::Ptr downsampledCloud,
                                 std::vector<std::vector<int>>& BinaryDynamicGridMap,
                                 float f32_MinBoundX, float f32_MinBoundY,
                                 float f32_GridSize, int x_count, int y_count,
                                 float f32_EgoX, float f32_EgoY, float f32_TempHeading)
{
    for (const auto& point : downsampledCloud->points)
    {
        float distance_squared = point.x * point.x + point.y * point.y;
        if (distance_squared <= 0.2f * 0.2f)
        {
            continue;
        }

        int32_t s32_GridX, s32_GridY;

        float rotated_x = f32_EgoX + point.x * cos(f32_TempHeading) - point.y * sin(f32_TempHeading);
        float rotated_y = f32_EgoY + point.x * sin(f32_TempHeading) + point.y * cos(f32_TempHeading);

        ConvertToGridIndex(rotated_x, rotated_y, f32_MinBoundX, f32_MinBoundY, f32_GridSize, s32_GridX, s32_GridY);

        if (s32_GridX >= 0 && s32_GridX < x_count &&
            s32_GridY >= 0 && s32_GridY < y_count)
        {
            BinaryDynamicGridMap[s32_GridX][s32_GridY] = 1;
        }
    }
}



void A_STAR()
{
    float32_t f32_GridSize = 0.1;
    float32_t f32_MinBoundX = f32_MinX;
    float32_t f32_MinBoundY = f32_MinY;

    int x_count = st_PlanningData.st_BinaryGrid.s16_XNum;
    int y_count = st_PlanningData.st_BinaryGrid.s16_YNum;

    vector<vector<int>> BinaryDynamicGridMap(x_count, vector<int>(y_count, 0));
    vector<vector<int>> BinaryStaticGridMap(x_count, vector<int>(y_count, 0));

    for (int i = 0; i < x_count; ++i)
    {
        for (int j = 0; j < y_count; ++j)
        {
            BinaryStaticGridMap[i][j] = st_PlanningData.st_BinaryGrid.s16_BinaryGrid[i][j];
        }
    }



    float32_t f32_EgoX = st_PlanningData.st_EgoVehicleData.f32_X; 
    float32_t f32_EgoY = st_PlanningData.st_EgoVehicleData.f32_Y;
    float32_t f32_Heading = st_PlanningData.st_EgoVehicleData.f32_Yaw_rad_ENU;
    f32_Heading += M_PI;
    if (f32_Heading > M_PI)
    {
        f32_Heading = f32_Heading - 2*M_PI;
    }
    UpdateBinaryDynamicGridMap(st_DownSampledCloud, BinaryDynamicGridMap, 
                           f32_MinBoundX, f32_MinBoundY, f32_GridSize, 
                           x_count, y_count, f32_EgoX, f32_EgoY,f32_Heading);


    BinaryFinalGridMap.resize(x_count);
    for (int i = 0; i < x_count; ++i)
    {
        BinaryFinalGridMap[i].resize(y_count, 0);
    }

    for (int x = 0; x < x_count; x++)
    {
        for (int y = 0; y < y_count; y++)
        {
            BinaryFinalGridMap[x][y] = BinaryStaticGridMap[x][y] || BinaryDynamicGridMap[x][y];
        }
    }

    int StartIdxX, StartIdxY;
    bool pathFound = false;

    ConvertToGridIndex(st_PlanningData.st_EgoVehicleData.f32_X ,
                       st_PlanningData.st_EgoVehicleData.f32_Y,
                       f32_MinBoundX, f32_MinBoundY, f32_GridSize, StartIdxX, StartIdxY);

    Point start = {StartIdxX, StartIdxY};

    int EndIdxX, EndIdxY;
    ConvertToGridIndex(f32_GoalX, f32_GoalY, f32_MinBoundX, f32_MinBoundY, f32_GridSize, EndIdxX, EndIdxY);
    Point end = {EndIdxX, EndIdxY};

    float32_t GoalDist = sqrtf(powf(st_PlanningData.st_EgoVehicleData.f32_X-f32_GoalX,2)+powf(st_PlanningData.st_EgoVehicleData.f32_Y-f32_GoalY,2));
    

    if (GoalDist < 0.6)
    {
        switch (currentGoal)
        {
        case 1:
            f32_GoalX = f32_GoalX_2;
            f32_GoalY = f32_GoalY_2;
            printf("Goal1\n");
            currentGoal = 2; // 다음 목표로 전환
            break;

        case 2:
            f32_GoalX = f32_GoalX_3;
            f32_GoalY = f32_GoalY_3;
            printf("Goal2\n");
            currentGoal = 3; // 다음 목표로 전환
            break;

        case 3:
            f32_GoalX = f32_GoalX_4;
            f32_GoalY = f32_GoalY_4;
            printf("Goal3\n");
            currentGoal = 4; // 다음 목표로 전환
            break;

        case 4:
            f32_GoalX = f32_GoalX_1;
            f32_GoalY = f32_GoalY_1;
            printf("Goal4\n");
            currentGoal = 1; // 처음으로 돌아감
            break;
        }
    }


    vector<Point> result = Astar(BinaryFinalGridMap, start, end, 4);

    if (!result.empty())
    {
        pathFound = true;
        st_PlanningData.st_GppPath.s32_Num = result.size();

        for (size_t i = 0; i < result.size(); ++i)
        {
            int row = result[i].first;
            int col = result[i].second;

            float32_t actual_x = f32_MinBoundX + col * f32_GridSize;
            float32_t actual_y = f32_MinBoundY + row * f32_GridSize;

            st_PlanningData.st_GppPath.arf32_X[i] = actual_x;
            st_PlanningData.st_GppPath.arf32_Y[i] = actual_y;

            st_PlanningData.st_GppPath.arf32_Yaw_rad_ENU[i] = 0.0f;
            st_PlanningData.st_GppPath.arf32_Yaw_rad_NED[i] = 0.0f;
        }

    }

    if (!pathFound)
    {
        printf("No Path\n");
    }

}



////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////Visualize///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

void GoalPointVisualize(PLANNING_DATA_t *pst_PlanningData, OBJECT_DATA_t *pst_ObjectData, ros::Publisher &marker_pub)
{
    VEHICLE_DATA_t *pst_InlierData = pst_PlanningData->st_InlierData;

    int32_t s32_I;
    int32_t s32_Num = pst_PlanningData->s32_InlierNum;

    visualization_msgs::MarkerArray marker_array;

    // Goal positions
    float goal_positions[4][2] = {
        {f32_GoalX_1, f32_GoalY_1},
        {f32_GoalX_2, f32_GoalY_2},
        {f32_GoalX_3, f32_GoalY_3},
        {f32_GoalX_4, f32_GoalY_4}
    };

    for (int i = 0; i < 4; ++i) {
        visualization_msgs::Marker goal_marker;
        goal_marker.header.frame_id = "map_o3d";
        goal_marker.header.stamp = ros::Time::now();
        goal_marker.ns = "goal";
        goal_marker.id = s32_Num + i; // 고유 ID 사용
        goal_marker.type = visualization_msgs::Marker::SPHERE;
        goal_marker.action = visualization_msgs::Marker::ADD;

        goal_marker.pose.position.x = goal_positions[i][0];
        goal_marker.pose.position.y = goal_positions[i][1];
        goal_marker.pose.position.z = 0.0f; // Adjust z as needed

        goal_marker.scale.x = 0.5f; // Sphere diameter
        goal_marker.scale.y = 0.5f;
        goal_marker.scale.z = 0.5f;

        goal_marker.color.r = 0.0f;
        goal_marker.color.g = 1.0f; // Green for goal
        goal_marker.color.b = 0.0f;
        goal_marker.color.a = 1.0f;

        goal_marker.lifetime = ros::Duration(1);

        marker_array.markers.push_back(goal_marker);
    }

    // Publish the marker array
    marker_pub.publish(marker_array);
}


void GridVisualize(vector<vector<int>> &BinaryFinalGridMap, ros::Publisher &Grid_pub)
{
    // OccupancyGrid 메시지 생성
    nav_msgs::OccupancyGrid gridMsg;

    // OccupancyGrid 메시지 설정
    gridMsg.header.stamp = ros::Time::now();
    gridMsg.header.frame_id = "map_o3d"; // 지정된 frame_id

    // OccupancyGrid 정보 설정
    float resolution = 0.1;             // 그리드 셀 크기 (단위: m)
    int x_count = BinaryFinalGridMap.size(); // 행 개수
    int y_count = BinaryFinalGridMap[0].size(); // 열 개수

    gridMsg.info.resolution = resolution;
    gridMsg.info.width = y_count;       // 그리드의 열 개수
    gridMsg.info.height = x_count;     // 그리드의 행 개수
    gridMsg.info.origin.position.x = f32_MinX;  // 맵의 시작점 (x 좌표)
    gridMsg.info.origin.position.y = f32_MinY;        // 맵의 시작점 (y 좌표)
    gridMsg.info.origin.position.z = 0.0;               // 맵의 시작점 (z 좌표)
    gridMsg.info.origin.orientation.w = 1.0;

    // OccupancyGrid 데이터 설정 (0과 1을 변환하여 저장)
    gridMsg.data.resize(x_count * y_count);
    for (int row = 0; row < x_count; ++row)
    {
        for (int col = 0; col < y_count; ++col)
        {
            int index = row * y_count + col;
            if (BinaryFinalGridMap[row][col] == 1)
            {
                gridMsg.data[index] = 100; // 점유 (Occupied)
            }
            else
            {
                gridMsg.data[index] = 0; // 비어 있음 (Free)
            }
        }
    }

    // OccupancyGrid 메시지 퍼블리시
    Grid_pub.publish(gridMsg);
}


void GPPVisualize(PLANNING_DATA_t *pst_PlanningData, ros::Publisher &Path_pub)
{
    visualization_msgs::Marker path_marker;

    path_marker.header.frame_id = "map_o3d";
    path_marker.header.stamp = ros::Time::now();
    path_marker.ns = "path_visualization";
    path_marker.id = 0;
    path_marker.type = visualization_msgs::Marker::LINE_STRIP;
    path_marker.action = visualization_msgs::Marker::ADD;

    path_marker.scale.x = 0.05;
    path_marker.color.r = 1.0;
    path_marker.color.g = 0.0;
    path_marker.color.b = 0.0;
    path_marker.color.a = 1.0;

    for (int i = 0; i < pst_PlanningData->st_GppPath.s32_Num; ++i)
    {
        geometry_msgs::Point p;
        p.x = pst_PlanningData->st_GppPath.arf32_X[i];
        p.y = pst_PlanningData->st_GppPath.arf32_Y[i];
        p.z = 0.0;
        path_marker.points.push_back(p);
    }
    Path_pub.publish(path_marker);
}

void EgoVisualize(PLANNING_DATA_t *pst_PlanningData, ros::Publisher &Ego_pub)
{
    float32_t f32_X = pst_PlanningData->st_EgoVehicleData.f32_X;
    float32_t f32_Y = pst_PlanningData->st_EgoVehicleData.f32_Y;
    float32_t f32_Heading_rad = pst_PlanningData->st_EgoVehicleData.f32_Yaw_rad_ENU;

    // Marker 메시지 생성
    visualization_msgs::Marker marker;
    marker.header.frame_id = "map"; // 좌표계 설정 (ex: "map")
    marker.header.stamp = ros::Time::now();
    marker.ns = "ego_vehicle";
    marker.id = 0; // ID 설정 (여러 마커를 관리할 때 사용)
    marker.type = visualization_msgs::Marker::ARROW; // 화살표 형태
    marker.action = visualization_msgs::Marker::ADD;

    // Ego 차량의 위치 설정
    marker.pose.position.x = f32_X;
    marker.pose.position.y = f32_Y;
    marker.pose.position.z = 0.0; // 차량은 일반적으로 지면에 있기 때문에 Z는 0으로 설정

    // Ego 차량의 방향 설정 (쿼터니언 사용)
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = sin(f32_Heading_rad / 2.0);
    marker.pose.orientation.w = cos(f32_Heading_rad / 2.0);

    // 크기 설정 (화살표의 길이, 두께)
    marker.scale.x = 2.0; // 화살표의 길이
    marker.scale.y = 0.5; // 화살표의 두께
    marker.scale.z = 0.5; // 화살표의 높이

    // 색상 설정 (RGBA)
    marker.color.r = 0.0f;
    marker.color.g = 1.0f; // 초록색
    marker.color.b = 0.0f;
    marker.color.a = 1.0f; // 불투명

    // 마커 메시지 퍼블리시
    Ego_pub.publish(marker);
}



// IMU

void ImuViz(IMU_DATA_t *imu_data, ros::Publisher &imu_pub, tf2_ros::TransformBroadcaster &tf_broadcaster)
{
    // Publish IMU data
    sensor_msgs::Imu imu_msg;
    imu_msg.header.stamp = ros::Time::now();
    imu_msg.header.frame_id = "imu_frame";

    // Fill orientation
    imu_msg.orientation.x = sin(imu_data->f32_Roll_deg * M_PI / 180.0 / 2);
    imu_msg.orientation.y = sin(imu_data->f32_Pitch_deg * M_PI / 180.0 / 2);
    imu_msg.orientation.z = sin(imu_data->f32_Yaw_deg * M_PI / 180.0 / 2);
    imu_msg.orientation.w = cos(imu_data->f32_Yaw_deg * M_PI / 180.0 / 2);

    // Fill angular velocity
    imu_msg.angular_velocity.x = imu_data->f32_GyroX_deg_s;
    imu_msg.angular_velocity.y = imu_data->f32_GyroY_deg_s;
    imu_msg.angular_velocity.z = imu_data->f32_GyroZ_deg_s;

    // Fill linear acceleration
    imu_msg.linear_acceleration.x = imu_data->f32_AccelX_m_s2;
    imu_msg.linear_acceleration.y = imu_data->f32_AccelY_m_s2;
    imu_msg.linear_acceleration.z = imu_data->f32_AccelZ_m_s2;

    imu_pub.publish(imu_msg);

    // Broadcast TF transform
    geometry_msgs::TransformStamped transform;
    transform.header.stamp = ros::Time::now();
    transform.header.frame_id = "map_o3d";
    transform.child_frame_id = "imu_frame";

    transform.transform.translation.x = 0.0;
    transform.transform.translation.y = 0.0;
    transform.transform.translation.z = 0.0;

    transform.transform.rotation = imu_msg.orientation;

    tf_broadcaster.sendTransform(transform);
}
