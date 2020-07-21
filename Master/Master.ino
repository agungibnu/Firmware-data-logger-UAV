//inisialisasi MPU
#include <Wire.h>
#include <Servo.h>
#define SerialPort Serial
#include <SparkFunMPU9250-DMP.h>
MPU9250_DMP imu;
double roll , pitch, yaw;
long int pre_ts = 0;
char a; bool kirim = false;
//inisialisasi ASpeed
float V_0 = 5.0; // supply voltage to the pressure sensor
float rho = 1.204; // density of air 

// parameters for averaging and offset
int offset = 0;
int offset_size = 10;
int veloc_mean_size = 20;
int zero_span = 2;

//inisialisasi GPS
#include <SoftwareSerial.h>
#include <TinyGPS.h>
TinyGPS gps;
SoftwareSerial ss(4, 3);

//inisialisasi DHT11
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht (DHTPIN, DHTTYPE);

//inisialisasi tegangan dan arus
int analogVoltage = A0;
int analogCurrent = A1;
int Va = 0; //voltase Analog
int Aa = 0; //arus Analog
int V = 0; //voltase fix
int Arus = 0; // arus fix

String dataprint[15];

void setup()
{

  Serial.begin(9600);
  dht.begin();
  ss.begin(9600);
  {
    SerialPort.begin(9600);

    if (imu.begin() != INV_SUCCESS)
    {
      while (1)
      {
        SerialPort.println("Unable to communicate with MPU-9250");
        SerialPort.println("Check connections, and try again.");
        SerialPort.println();
        delay(3000);
      }
    }


    imu.setSensors(INV_XYZ_GYRO | INV_XYZ_ACCEL | INV_XYZ_COMPASS);


    imu.setGyroFSR(250); // Set gyro to 2000 dps
    // Accel options are +/- 2, 4, 8, or 16 g
    imu.setAccelFSR(2); // Set accel to +/-2g
    imu.setLPF(10); // Set LPF corner frequency to 5Hz
    imu.setSampleRate(10); // Set sample rate to 10Hz
    imu.setCompassSampleRate(50); // Set mag rate to 10Hz
  }

  pre_ts = millis();

   // Setup Aspeed
   for (int ii=0;ii<offset_size;ii++){
    offset += analogRead(A3)-(1023/2);
  }
  offset /= offset_size;

}

//}
void loop()
{

  mpu();
  gps_ublox();
  tegangan();
  airspeed();
  Suhu();
  
  //---------------------------------
  if (Serial.available())
  {
    a = Serial.read();
  }

  if (a != char())
  {
    if (a == 'a')
    {
      kirim = true;
    }
    else
    {
      if (a == 'b')
      {
        kirim = false;
      }
    }
    a = char();
  }
  else
  {
    if (kirim == true)
    {
      printdata();
    }

  }
  //--------------------------



}
