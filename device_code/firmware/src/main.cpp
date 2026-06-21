#include <Arduino.h>
#include "config.h"
#include "robot_state.h"
#include "motor_control.h"
#include "kinematics.h"
#include "gcode_parser.h"
#include "servo_control.h"
#include "gcode_executor.h"
#include "web_server.h"

RobotState robotState;
MotorController motors;
Kinematics kinematics;
GCodeParser gcodeParser;
ServoController servoControl;
GCodeExecutor gcodeExecutor(&motors, &kinematics, &servoControl, &robotState);
WebServerManager webServer(&motors, &kinematics, &gcodeParser, &servoControl, &gcodeExecutor, &robotState);

void setup() {
    Serial.begin(115200);
    delay(200);
    Serial.println("Cable robot booting...");

    robotState.currentX = START_X_MM;
    robotState.currentY = START_Y_MM;

    motors.begin();
    servoControl.begin();

    if (!webServer.setupWiFi(AP_SSID, AP_PASSWORD)) {
        while (true) { delay(1000); }
    }

    webServer.begin();
    Serial.printf("Paper-first model ready. Start=(%.1f, %.1f) mm\n", START_X_MM, START_Y_MM);
}

void loop() {
    webServer.handleClient();
    gcodeExecutor.update();
    if (!motors.isBusy()) {
        robotState.isMoving = false;
    }
    delay(1);
}
