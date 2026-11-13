#ifndef CAN_DATA_H
#define CAN_DATA_H

#include <stdint.h>

enum class CAN_MsgType {
    Accel_Pedal,
    Acceleration,
    Active_Gear,
    Another_Drive_Mode,
    Brake_Pedal,
    Clutch_Pedal,
    Drive_Mode,
    Speed,
    Tachometer,
    Tripometer,
};

typedef struct {
    float time;
    CAN_MsgType msgType;
    float data;
} CAN_Data;

const CAN_Data data_Test_case_1[6][9] = {
    { {0.00000, CAN_MsgType::Acceleration, 5.95663}, {0.00000, CAN_MsgType::Speed, 1.91836}, {0.00000, CAN_MsgType::Tripometer, -5.40667}, {0.00000, CAN_MsgType::Accel_Pedal, 9.81417}, {0.00000, CAN_MsgType::Tachometer, -3.32100}, {0.00000, CAN_MsgType::Brake_Pedal, 5.93651}, {0.00000, CAN_MsgType::Clutch_Pedal, -6.40120}, {0.00000, CAN_MsgType::Active_Gear, 2.41404}, {0.00000, CAN_MsgType::Drive_Mode, -3.47559}, },
    { {0.20000, CAN_MsgType::Acceleration, 0.00000}, {0.20000, CAN_MsgType::Speed, 0.00000}, {0.20000, CAN_MsgType::Tripometer, 0.00000}, {0.20000, CAN_MsgType::Accel_Pedal, 0.00000}, {0.20000, CAN_MsgType::Tachometer, 0.00000}, {0.20000, CAN_MsgType::Brake_Pedal, 0.00000}, {0.20000, CAN_MsgType::Clutch_Pedal, 0.00000}, {0.20000, CAN_MsgType::Active_Gear, 0.00000}, {0.20000, CAN_MsgType::Drive_Mode, 0.00000}, },
    { {0.40000, CAN_MsgType::Acceleration, 0.00000}, {0.40000, CAN_MsgType::Speed, 0.00000}, {0.40000, CAN_MsgType::Tripometer, 0.00000}, {0.40000, CAN_MsgType::Accel_Pedal, 21.00000}, {0.40000, CAN_MsgType::Tachometer, 0.00000}, {0.40000, CAN_MsgType::Brake_Pedal, 0.00000}, {0.40000, CAN_MsgType::Clutch_Pedal, 0.00000}, {0.40000, CAN_MsgType::Active_Gear, 0.00000}, {0.40000, CAN_MsgType::Drive_Mode, 0.00000}, },
    { {0.60000, CAN_MsgType::Acceleration, 0.00000}, {0.60000, CAN_MsgType::Speed, 0.00000}, {0.60000, CAN_MsgType::Tripometer, 0.00000}, {0.60000, CAN_MsgType::Accel_Pedal, 0.00000}, {0.60000, CAN_MsgType::Tachometer, 0.00000}, {0.60000, CAN_MsgType::Brake_Pedal, 0.00000}, {0.60000, CAN_MsgType::Clutch_Pedal, 0.00000}, {0.60000, CAN_MsgType::Active_Gear, 0.00000}, {0.60000, CAN_MsgType::Drive_Mode, 1.00000}, },
    { {0.80000, CAN_MsgType::Acceleration, 0.00000}, {0.80000, CAN_MsgType::Speed, 0.00000}, {0.80000, CAN_MsgType::Tripometer, 0.00000}, {0.80000, CAN_MsgType::Accel_Pedal, 21.00000}, {0.80000, CAN_MsgType::Tachometer, 0.00000}, {0.80000, CAN_MsgType::Brake_Pedal, 0.00000}, {0.80000, CAN_MsgType::Clutch_Pedal, 0.00000}, {0.80000, CAN_MsgType::Active_Gear, 0.00000}, {0.80000, CAN_MsgType::Drive_Mode, 1.00000}, },
    { {1.00000, CAN_MsgType::Acceleration, 0.00000}, {1.00000, CAN_MsgType::Speed, 0.00000}, {1.00000, CAN_MsgType::Tripometer, 0.00000}, {1.00000, CAN_MsgType::Accel_Pedal, 0.00000}, {1.00000, CAN_MsgType::Tachometer, 0.00000}, {1.00000, CAN_MsgType::Brake_Pedal, 5.00000}, {1.00000, CAN_MsgType::Clutch_Pedal, 0.00000}, {1.00000, CAN_MsgType::Active_Gear, 0.00000}, {1.00000, CAN_MsgType::Drive_Mode, 1.00000}, },
};

const CAN_Data data_Test_case_1_2[6][10] = {
    { {0.00000, CAN_MsgType::Acceleration, 5.95663}, {0.00000, CAN_MsgType::Speed, 1.91836}, {0.00000, CAN_MsgType::Tripometer, -5.40667}, {0.00000, CAN_MsgType::Accel_Pedal, 9.81417}, {0.00000, CAN_MsgType::Tachometer, -3.32100}, {0.00000, CAN_MsgType::Brake_Pedal, 5.93651}, {0.00000, CAN_MsgType::Clutch_Pedal, -6.40120}, {0.00000, CAN_MsgType::Active_Gear, 2.41404}, {0.00000, CAN_MsgType::Drive_Mode, -3.47559}, {0.00000, CAN_MsgType::Another_Drive_Mode, -3.47559}, },
    { {0.20000, CAN_MsgType::Acceleration, 0.00000}, {0.20000, CAN_MsgType::Speed, 0.00000}, {0.20000, CAN_MsgType::Tripometer, 0.00000}, {0.20000, CAN_MsgType::Accel_Pedal, 0.00000}, {0.20000, CAN_MsgType::Tachometer, 0.00000}, {0.20000, CAN_MsgType::Brake_Pedal, 0.00000}, {0.20000, CAN_MsgType::Clutch_Pedal, 0.00000}, {0.20000, CAN_MsgType::Active_Gear, 0.00000}, {0.20000, CAN_MsgType::Drive_Mode, 0.00000}, {0.20000, CAN_MsgType::Another_Drive_Mode, 0.00000}, },
    { {0.40000, CAN_MsgType::Acceleration, 0.00000}, {0.40000, CAN_MsgType::Speed, 0.00000}, {0.40000, CAN_MsgType::Tripometer, 0.00000}, {0.40000, CAN_MsgType::Accel_Pedal, 21.00000}, {0.40000, CAN_MsgType::Tachometer, 0.00000}, {0.40000, CAN_MsgType::Brake_Pedal, 0.00000}, {0.40000, CAN_MsgType::Clutch_Pedal, 0.00000}, {0.40000, CAN_MsgType::Active_Gear, 0.00000}, {0.40000, CAN_MsgType::Drive_Mode, 0.00000}, {0.40000, CAN_MsgType::Another_Drive_Mode, 0.00000}, },
    { {0.60000, CAN_MsgType::Acceleration, 0.00000}, {0.60000, CAN_MsgType::Speed, 0.00000}, {0.60000, CAN_MsgType::Tripometer, 0.00000}, {0.60000, CAN_MsgType::Accel_Pedal, 0.00000}, {0.60000, CAN_MsgType::Tachometer, 0.00000}, {0.60000, CAN_MsgType::Brake_Pedal, 0.00000}, {0.60000, CAN_MsgType::Clutch_Pedal, 0.00000}, {0.60000, CAN_MsgType::Active_Gear, 0.00000}, {0.60000, CAN_MsgType::Drive_Mode, 1.00000}, {0.60000, CAN_MsgType::Another_Drive_Mode, 1.00000}, },
    { {0.80000, CAN_MsgType::Acceleration, 0.00000}, {0.80000, CAN_MsgType::Speed, 0.00000}, {0.80000, CAN_MsgType::Tripometer, 0.00000}, {0.80000, CAN_MsgType::Accel_Pedal, 21.00000}, {0.80000, CAN_MsgType::Tachometer, 0.00000}, {0.80000, CAN_MsgType::Brake_Pedal, 0.00000}, {0.80000, CAN_MsgType::Clutch_Pedal, 0.00000}, {0.80000, CAN_MsgType::Active_Gear, 0.00000}, {0.80000, CAN_MsgType::Drive_Mode, 1.00000}, {0.80000, CAN_MsgType::Another_Drive_Mode, 1.00000}, },
    { {1.00000, CAN_MsgType::Acceleration, 0.00000}, {1.00000, CAN_MsgType::Speed, 0.00000}, {1.00000, CAN_MsgType::Tripometer, 0.00000}, {1.00000, CAN_MsgType::Accel_Pedal, 0.00000}, {1.00000, CAN_MsgType::Tachometer, 0.00000}, {1.00000, CAN_MsgType::Brake_Pedal, 5.00000}, {1.00000, CAN_MsgType::Clutch_Pedal, 0.00000}, {1.00000, CAN_MsgType::Active_Gear, 0.00000}, {1.00000, CAN_MsgType::Drive_Mode, 1.00000}, {1.00000, CAN_MsgType::Another_Drive_Mode, 1.00000}, },
};

// Helper macros for cycling through data arrays
#define NUM_ROWS(arr)  (sizeof(arr) / sizeof((arr)[0]))
#define NUM_COLS(arr)  (sizeof((arr)[0]) / sizeof((arr)[0][0]))



#endif // CAN_DATA_H
