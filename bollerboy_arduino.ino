#include <ESP32Servo.h>
#include <PS4Controller.h>

#define SERVO_PIN 12 // ESP32 pin GPIO26 connected to servo motor

Servo servoMotor;
int servoPosition = 105; // Start at 105 degrees

int max_speed_pos = 55;
int no_speed_pos = 105;

int controller_input = 0;

void setup() {
  servoMotor.attach(SERVO_PIN);  // Attaches the servo on ESP32 pin
  servoMotor.write(servoPosition); // Set the initial position to 105 degrees
  PS4.begin("dc:e5:5b:14:29:fd");
  Serial.begin(9600); // Initialize the serial communication
  Serial.println("Started");
}

void loop() {
  if (PS4.isConnected()) {
    // Read the controller input (0 to 127)
    controller_input = PS4.LStickY();

    // Map the controller input to the servo position
    if(controller_input < 10){
      controller_input = 0;
    }
    
    servoPosition = map(controller_input, 0, 127, no_speed_pos, max_speed_pos);
 
  } else {
    // If the controller is not connected, set the servo to no speed
    // This is a super duper security feature, do not remove loool
    servoPosition = no_speed_pos;
  }

  // Set the servo position
  servoMotor.write(servoPosition);
}
