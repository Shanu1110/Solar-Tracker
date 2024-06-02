#include <Servo.h>
Servo horizontal; // horizontal servo
int servoh = 140; // 90; // stand horizontal servo
int servohLimitHigh = 140;
int servohLimitLow = 10;
// 65 degrees MAX
Servo vertical; // vertical servo
int servov = 95; // 90; // stand vertical servo
int servovLimitHigh = 179;
int servovLimitLow = 1;
int ldrlt = 3; //LDR top left - BOTTOM LEFT <--- BDG
int ldrrt = 1; //LDR top rigt - BOTTOM RIGHT
int ldrld = 2; //LDR down left - TOP LEFT
int ldrrd = 0; //ldr down rigt - TOP RIGHT
void setup()
{ 
Serial.begin(9600);
horizontal.attach(9);
vertical.attach(10);
horizontal.write(140);
vertical.write(95);
delay(3000);
}

void loop()
{
int lt = analogRead(ldrlt); // top left
int rt = analogRead(ldrrt); // top right
int ld = analogRead(ldrld); // down left
int rd = analogRead(ldrrd); // down right

int dtime = 10; int tol = 50;
int avt = (lt + rt) / 2; // average value top
int avd = (ld + rd) / 2; // average value dow
int avl = (lt + ld) / 2; // average value left
int avr = (rt + rd) / 2; // average value righ
int dvert = avt - avd; // check the diffirence of up and down
int dhoriz = avl - avr;// check the diffirence og left and rigt

Serial.print(avt);
Serial.print(" ");
Serial.print(avd);
Serial.print(" ");
Serial.print(avl);
Serial.print(" ");
Serial.print(avr);
Serial.print(" ");
Serial.print(dtime);
Serial.print(" ");
Serial.print(tol);
Serial.println(" ");

if (-1*tol > dvert || dvert > tol) // check if the diffirence is in the tolerance else change vertical angle
{
if (avt > avd)
{
servov = ++servov;
if (servov > servovLimitHigh)
{
servov = servovLimitHigh;
}
}
else if (avt < avd)
{
servov= --servov;
if (servov < servovLimitLow)
{
servov = servovLimitLow;
}
}
vertical.write(servov);
}
if (-1*tol > dhoriz || dhoriz > tol) // check if the diffirence is in the tolerance else change horizontal angle
{
if (avl > avr)
{
servoh = --servoh;
if (servoh < servohLimitLow)
{
servoh = servohLimitLow;
}
}
else if (avl < avr)
{
servoh = ++servoh;
if (servoh > servohLimitHigh)
{
servoh = servohLimitHigh;
}
}
else if (avl = avr)
{
}
horizontal.write(servoh);
}
delay(dtime);
}
