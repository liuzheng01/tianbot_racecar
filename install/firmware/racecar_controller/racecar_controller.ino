#include <Servo.h>

#define    STX          0x02
#define    ETX          0x03

Servo myservo;
int servo_val = 90;     //120左  90中点  60右

Servo mymotor;
int motor_val = 90;     //120前进  90中点  60倒退
byte cmd[8] = {0, 0, 0, 0, 0, 0, 0, 0};                 // bytes received

void setup() {
  Serial.begin(57600);
  myservo.attach(3);
  mymotor.attach(9);
  myservo.write(servo_val);
  mymotor.write(motor_val);
}

void loop() {
  if (Serial.available())  {                          // data received from smartphone
    delay(2);
    cmd[0] =  Serial.read();
    if (cmd[0] == STX)  {
      int i = 1;
      while (Serial.available())  {
        delay(1);
        cmd[i] = Serial.read();
        if (cmd[i] > 127 || i > 7)                 break; // Communication error
        if ((cmd[i] == ETX) && (i == 7))           break; // Button or Joystick data
        i++;
      }
      if     (i == 7)          sendCmd(cmd);  // 3 Bytes  ex: < STX "C" ETX >
    }
  }
}

void sendCmd(byte data[8])    {
  int motor_val = data[1] * 100 + data[2] * 10 + data[3]; // obtain the Int from the ASCII representation
  int servo_val = data[4] * 100 + data[5] * 10 + data[6];
  if (motor_val < 20)
  {
    motor_val = 20;
  }
  if (motor_val > 120)
  {
    motor_val = 120;
  }
  mymotor.write(motor_val);
  if (servo_val < 60)
  {
    servo_val = 60;
  }
  if (servo_val > 120)
  {
    servo_val = 120;
  }
  myservo.write(servo_val);
}

