#include<SoftwareSerial.h>

SoftwareSerial bluetoothSerial(6, 7);
String readvoice;

int IN2 = 14;
int IN1 = 15;
int IN4 = 16;
int IN3 = 17;

#define trigPin 8
#define echoPin 9

#define trigPin2 2
#define echoPin2 3

#define trigPin3 4
#define echoPin3 5

long duration;
int distance;

long duration2;
int distance2;

long duration3;
int distance3;

void setup() 
{
  bluetoothSerial.begin(9600);  
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  
  Serial.println("Robot..");
  delay(100);
}

void loop() 
{
  voice_read();
}

void voice_read()
{
  while (1)
  {  
    readvoice = "";
    while (bluetoothSerial.available())
    {
      delay(10);
      char ch = bluetoothSerial.read();
      readvoice += ch;
    }
    Serial.println(readvoice);

    if (readvoice == "A" || readvoice == "path1" || readvoice == "part1" || readvoice == "part 1"||readvoice=="admin block")
    {
      Serial.println("Path1");
      PATH_1();
    }
    else if (readvoice == "B" || readvoice == "path2" || readvoice == "part2" || readvoice == "part 2"||readvoice=="chemical block")
    {
      Serial.println("Path2");
      PATH_2();
    }
    else if (readvoice == "C" || readvoice == "path3" || readvoice == "part3" || readvoice == "part 3"||readvoice=="Archi block")
    {
      Serial.println("Path3");
      PATH_3();
    }
  } 
}

void PATH_1()
{
  for (int x = 0; x < 10; x++)
  {
    if (!moveForwardWithCheck(500))
      break;
  }
  Serial.println("Stop1...");
  stop1();
  delay(1000);
}

void PATH_2()
{
  left();
  delay(500);
  stop1();
  delay(1000);
  for (int x = 0; x < 10; x++)
  {
    if (!moveForwardWithCheck(500))
      break;
  }
  Serial.println("Stop1...");
  stop1();
  delay(1000);
}

void PATH_3()
{
  right();
  delay(500);
  stop1();
  delay(1000);
  for (int x = 0; x < 10; x++)
  {
    if (!moveForwardWithCheck(500))
      break;
  }
  Serial.println("Stop1...");
  stop1();
  delay(1000);
}

bool moveForwardWithCheck(int duration)
{
  forward();
  long startTime = millis();
  while (millis() - startTime < duration)
  {
    if (Front_UV())
    {
      stop1();
      delay(1000);
      maneuverAroundObstacle();
      return false;
    }
    delay(50); // Check every 50 milliseconds
  }
  return true;
}

bool Front_UV()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Front Distance = ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance < 30; // Adjust this distance as needed
}

void maneuverAroundObstacle()
{
  Serial.println("$Front Object Detected#");
  left();
  delay(500);
  stop1();
  delay(500);
  forward();
  delay(800);
  stop1();
  delay(500);
  right();
  delay(500);
  stop1();
  delay(500);
  forward();
  delay(800);
  stop1();
  delay(500);
  right();
  delay(500);
  stop1();
  delay(500);
  forward();
  delay(800);
  stop1();
  delay(500);
  left();
  delay(500);
  stop1();
  delay(500);
  forward();
  delay(800);
  stop1();
}

void forward()
{
  Serial.println("forward..");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void reverse()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(100);
}

void left()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(100);
}

void right()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(100);
}

void stop1()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(100);
}
