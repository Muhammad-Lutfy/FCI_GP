/* config.h - Cleaned hardware + relative paper model */
#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <cstddef>

// WiFi
static const char* AP_SSID = "CableRobot_Hotspot";
static const char* AP_PASSWORD = "robot123";

// Servo
static const int SERVO_PIN = 15;
static const int SERVO_UP_ANGLE = 25;
static const int SERVO_DOWN_ANGLE = 10;
static const unsigned long SERVO_SETTLE_MS = 300;

// Paper-first model (device can move from one table to another)
// The logical origin is the paper center, not a fixed table corner.
static constexpr float PAPER_WIDTH_MM = 210.0f;   // A4 default
static constexpr float PAPER_HEIGHT_MM = 297.0f;  // A4 default
static constexpr float PAPER_CENTER_X_MM = PAPER_WIDTH_MM / 2.0f;
static constexpr float PAPER_CENTER_Y_MM = PAPER_HEIGHT_MM / 2.0f;

// User said the device starts in the middle of the paper.
static constexpr float START_X_MM = PAPER_CENTER_X_MM;
static constexpr float START_Y_MM = PAPER_CENTER_Y_MM;

// Safe drawing area inside the sheet.
static constexpr float DRAW_MARGIN_X_MM = 20.0f;
static constexpr float DRAW_MARGIN_Y_MM = 20.0f;
static constexpr float DRAW_AREA_X = DRAW_MARGIN_X_MM;
static constexpr float DRAW_AREA_Y = DRAW_MARGIN_Y_MM;
static constexpr float DRAW_AREA_WIDTH = PAPER_WIDTH_MM - 2.0f * DRAW_MARGIN_X_MM;
static constexpr float DRAW_AREA_HEIGHT = PAPER_HEIGHT_MM - 2.0f * DRAW_MARGIN_Y_MM;

// Workspace exposed to G-code.
static constexpr float WORKSPACE_WIDTH_MM = PAPER_WIDTH_MM;
static constexpr float WORKSPACE_HEIGHT_MM = PAPER_HEIGHT_MM;
static constexpr float WORKSPACE_MARGIN_MM = 10.0f;
static constexpr float MIN_MOVE_MM = 0.5f;
static constexpr float MAX_SEGMENT_MM = 3.0f;  // segment long moves to improve line quality

// Relative anchor model around the sheet.
// These are not fixed table coordinates; they are offsets around the current paper.
static constexpr float ANCHOR_LEFT_OFFSET_MM = 55.0f;
static constexpr float ANCHOR_RIGHT_OFFSET_MM = 55.0f;
static constexpr float ANCHOR_TOP_OFFSET_MM = 55.0f;
static constexpr float ANCHOR_BOTTOM_OFFSET_MM = 55.0f;

// Motion profile
static const int NORMAL_SPEED_US = 2500;
static const int FAST_SPEED_US = 1800;
static constexpr float MANUAL_MOVE_MM = 5.0f;

// Upload
static const size_t MAX_GCODE_COMMANDS = 6000;
static const size_t MAX_UPLOAD_BYTES = 250000;

// ====== Motor Pins ======
static constexpr int M1_IN1 = 19;
static constexpr int M1_IN2 = 18;
static constexpr int M1_IN3 = 5;
static constexpr int M1_IN4 = 17;
static constexpr int M2_IN1 = 16;
static constexpr int M2_IN2 = 4;
static constexpr int M2_IN3 = 0;
static constexpr int M2_IN4 = 2;
static constexpr int M3_IN1 = 13;
static constexpr int M3_IN2 = 12;
static constexpr int M3_IN3 = 14;
static constexpr int M3_IN4 = 27;
static constexpr int M4_IN1 = 26;
static constexpr int M4_IN2 = 25;
static constexpr int M4_IN3 = 33;
static constexpr int M4_IN4 = 32;

struct MotorAnchor {
    float x;
    float y;
};

// Motor order: M1 TL, M2 TR, M3 BR, M4 BL.
static constexpr MotorAnchor MOTOR_ANCHORS[4] = {
    {-ANCHOR_LEFT_OFFSET_MM,              -ANCHOR_TOP_OFFSET_MM},
    {PAPER_WIDTH_MM + ANCHOR_RIGHT_OFFSET_MM, -ANCHOR_TOP_OFFSET_MM},
    {PAPER_WIDTH_MM + ANCHOR_RIGHT_OFFSET_MM, PAPER_HEIGHT_MM + ANCHOR_BOTTOM_OFFSET_MM},
    {-ANCHOR_LEFT_OFFSET_MM,               PAPER_HEIGHT_MM + ANCHOR_BOTTOM_OFFSET_MM}
};

// Starting calibration from the old working project.
static constexpr float MOTOR_STEPS_PER_MM[4] = {85.0f, 85.0f, 85.0f, 85.0f};
// User confirmed: winding onto the pulley = tighter cable. Start with positive winding.
static constexpr int MOTOR_DIRECTION_SIGN[4] = {1, 1, 1, 1};
static constexpr int MOTOR_MIN_EFFECTIVE_STEPS = 2;

#endif
