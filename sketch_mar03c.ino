#include <Adafruit_Sensor.h>
#define BLYNK_PRINT Serial
//#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
  
Adafruit_BMP085 bmp;
#define I2C_SCL 12
#define I2C_SDA 13
//#define DHTPIN 0
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

const int trigPin = A0;
const int echoPin = 3;
long duration;
float distanceCm;
float distanceInch;

float dst,bt,bp,ba;
char dstmp[20],btmp[20],bprs[20],balt[20];
bool bmp085_present=true;

char auth[] = "KbxQJPfwUrG615wYNqBUNPfZdAeBjklH";
char ssid[] = "Anbu";
char pass[] = "1234567890";
//#define DHTPIN 2
//#define DHTTYPE DHT11
//DHT dht(DHTPIN, DHTTYPE); //Defining the pin and the dhttype
BlynkTimer timer;
void sendSensor()
{

  if (!bmp.begin()) 
  {
           Serial.println("Could not find a valid BMP085 sensor, check wiring!");
              while (1) {}
        }

//float h = dht.readHumidity();
//float t = dht.readTemperature();
  

//  if (isnan(h) || isnan(t))
//  {
//  Serial.println("Failed to read from DHT sensor!");
//  return;
//  }
//
//  double gamma = log(h/100) + ((17.62*t) / (243.5+t));
//  double dp = 243.5*gamma / (17.62-gamma);
//
int bp =  bmp.readPressure()/100;
int ba =  bmp.readAltitude();
float bt =  bmp.readTemperature();
float dst = bmp.readSealevelPressure()/100;
//Blynk.virtualWrite(V5 , h);
//Serial.print(h);
//Blynk.virtualWrite(V6 , t);
//Serial.println(t);
Blynk.virtualWrite(V10, bp);
Blynk.virtualWrite(V11, ba);
Blynk.virtualWrite(V12, bt);
Blynk.virtualWrite(V13, dst);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
//Serial.println(duration);
  // Calculate the distance
distanceCm = duration * SOUND_VELOCITY/2;
  
  // Convert to inches
distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance on the Serial Monitor
Serial.print("Distance (cm): ");
Serial.println(distanceCm);
//  Serial.print("Distance (inch): ");
//  Serial.println(distanceInch);
Blynk.virtualWrite(V5, distanceCm/100);
delay(10);
//Blynk.virtualWrite(V14, dp);
}

void setup()
{
  pinMode(0,OUTPUT);
  analogWrite(0,1);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
//  dht.begin();
  Wire.begin(I2C_SDA, I2C_SCL);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
  pinMode(16, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(14, OUTPUT);
  delay(10);
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
//  digitalWrite(DHTPIN, LOW);
  Blynk.run();
  timer.run();

}
