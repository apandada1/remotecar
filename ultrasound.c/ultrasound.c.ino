/* HC-SR04 Sensor based on
   https://www.dealextreme.com/p/hc-sr04-ultrasonic-sensor-distance-measuring-module-133696
  
   This sketch reads a HC-SR04 ultrasonic rangefinder and returns the
   distance to the closest object in range. To do this, it sends a pulse
   to the sensor to initiate a reading, then listens for a pulse 
   to return.  The length of the returning pulse is proportional to 
   the distance of the object from the sensor.
   
   The circuit:
  * VCC connection of the sensor attached to +5V
  * GND connection of the sensor attached to ground
  * TRIG connection of the sensor attached to digital pin 2
  * ECHO connection of the sensor attached to digital pin 4
   Original code for Ping))) example was created by David A. Mellis
   Adapted for HC-SR04 by Tautvidas Sipavicius
   This example code is in the public domain.
 */


const int trigPin = 2;

const int echoPinLeft = 3;
const int echoPinMid = 5;
const int echoPinRight = 6;

const int LedLeft = 10;
const int LedMid = 11;
const int LedRight = 12;



void setup() {
  // initialize serial communication:
  Serial.begin(9600);
}

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long durationLeft, durationMid, durationRight;
  long cmLeft, cmMid, cmRight;

  //Initialize LED and turn them LOW
  pinMode(LedLeft, OUTPUT);
  pinMode(LedMid, OUTPUT);
  pinMode(LedRight, OUTPUT);

  digitalWrite(LedLeft, LOW);
  digitalWrite(LedMid, LOW);
  digitalWrite(LedRight, LOW);

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPinLeft, INPUT);
  pinMode(echoPinMid, INPUT);
  pinMode(echoPinRight, INPUT);
  durationLeft = pulseIn(echoPinLeft, HIGH);
  durationMid = pulseIn(echoPinMid, HIGH);
  durationRight = pulseIn(echoPinRight, HIGH);

  // convert the time into a distance
  //inches = microsecondsToInches(duration);
  cmLeft = microsecondsToCentimeters(durationLeft);
  cmMid = microsecondsToCentimeters(durationMid);
  cmRight = microsecondsToCentimeters(durationRight);
  

  //Serial.print(inches);
  //Serial.print("in, ");
  
  Serial.print(cmLeft);
  Serial.print("cmLeft");
  Serial.print(cmMid);
  Serial.print("cmMid");
  Serial.print(cmRight);
  Serial.print("cmRight");

  Serial.println();
  
  if (cmLeft <= 10)
  {
  	digitalWrite(LedLeft, HIGH);
  }
  if (cmMid <= 10)
  {
  	digitalWrite(LedMid, HIGH);
  }
  if (cmRight <= 10)
  {
  	digitalWrite(LedRight, HIGH);
  }
  delay(5);
}

/*long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}*/

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

