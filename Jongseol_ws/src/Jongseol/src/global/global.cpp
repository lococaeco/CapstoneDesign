#include "global.h"

extern bool b_Map;
extern bool b_Start;

void DataLoad(const char* filename, PATH_t &Path)
{
    FILE* p_File = fopen(filename, "r");
    if (!p_File)
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    int32_t s32_Num = 0;
    float32_t f32_X, f32_Y;

    while (fscanf(p_File, "%f, %f", &f32_X, &f32_Y) == 2)
    {
        Path.arf32_X[s32_Num] = f32_X;
        Path.arf32_Y[s32_Num] = f32_Y;
        s32_Num += 1;
    }
    Path.s32_Num = s32_Num;
    fclose(p_File);
}

void GridLoad(const char* filename, GRID_t &Grid)
{
    FILE* p_File = fopen(filename, "r");
    if (!p_File)
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    int16_t s16_Row = 0, s16_Col = 0;
    char line[1024 * 10];

    // 행 단위로 파일 읽기
    while (fgets(line, sizeof(line), p_File) && s16_Row < 1000)
    {
        s16_Col = 0;
        char* token = strtok(line, " "); // 공백으로 구분
        while (token != nullptr && s16_Col < 1000)
        {
            try
            {
                // 유효한 숫자인지 확인
                if (std::isdigit(token[0]) || (token[0] == '-' && std::isdigit(token[1])))
                {
                    Grid.s16_BinaryGrid[s16_Row][s16_Col] = std::stoi(token);
                }
                else
                {
                    std::cerr << "Invalid token (non-integer): " << token << std::endl;
                    Grid.s16_BinaryGrid[s16_Row][s16_Col] = 0; // 기본값 처리
                }
            }
            catch (const std::exception& e)
            {
                std::cerr << "Conversion error: " << e.what() << " for token: " << token << std::endl;
                Grid.s16_BinaryGrid[s16_Row][s16_Col] = 0; // 기본값 처리
            }
            token = strtok(nullptr, " ");
            s16_Col++;
        }
        s16_Row++;
    }

    // 행과 열의 실제 크기 저장
    Grid.s16_XNum = s16_Row;
    Grid.s16_YNum = s16_Col;

    fclose(p_File);
}



float32_t getDistance2d(float32_t f32_X1, float32_t f32_Y1, float32_t f32_X2, float32_t f32_Y2)
{
    return sqrtf(powf(f32_X1 - f32_X2, 2.f) + powf(f32_Y1 - f32_Y2, 2.f));
}


float64_t getDistance2d(float64_t f64_X1, float64_t f64_Y1, float64_t f64_X2, float64_t f64_Y2)
{
    return sqrtf(powf(f64_X1 - f64_X2, 2.f) + powf(f64_Y1 - f64_Y2, 2.f));
}


void GetModData(float32_t min, float32_t max, float32_t &data)
{
    if (data > max)
    {
        data = max;
    }
    else if (data < min)
    {
        data = min;
    }
}

void GetModData(float64_t min, float64_t max, float64_t &data)
{
    if (data > max)
    {
        data = max;
    }
    else if (data < min)
    {
        data = min;
    }
}

void GetModData(int32_t min, int32_t max, int32_t &data)
{
    if (data > max)
    {
        data = max;
    }
    else if (data < min)
    {
        data = min;
    }
}

float32_t pi2pi(float32_t f32_Angle)
{
    if (f32_Angle > M_PI)
        f32_Angle -= 2 * M_PI;
    else if(f32_Angle < -M_PI)
        f32_Angle += 2 * M_PI;

    return f32_Angle;
}

float64_t pi2pi(float64_t f64_Angle)
{
    if (f64_Angle > M_PI)
        f64_Angle -= 2 * M_PI;
    else if(f64_Angle < -M_PI)
        f64_Angle += 2 * M_PI;

    return f64_Angle;
}

float32_t axisRotate(float32_t f32_Heading_rad)
{
    float32_t f32_Result;
    if(-1*M_PI/2 < f32_Heading_rad && f32_Heading_rad < M_PI)
    {
        f32_Result = M_PI / 2.0f - f32_Heading_rad;
    }
    else
    {
        f32_Result = -1.5f * M_PI - f32_Heading_rad;
    }
    return f32_Result;
}

uint64_t getMilliSec()
{
    auto now = chrono::steady_clock::now();
    auto millisec = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();
    return millisec;
}


void keyboardCallback(int key)
{
    if (key == 108)
    {
        b_Map ^= 1; // b_Map 값 토글
    }
    else if (key == 32)
    {
        b_Start ^= 1; // b_Start 값 토글
    }
    printf("%d\n", key);
}
