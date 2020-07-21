void mpu()
{
  if ( imu.dataReady() )
  {
    imu.update(UPDATE_ACCEL | UPDATE_GYRO | UPDATE_COMPASS);
    printIMUData(millis() - pre_ts);
    pre_ts = millis();
  }
}

void printIMUData(long int dt)
{

  float accelX = imu.calcAccel(imu.ax);
  float accelY = imu.calcAccel(imu.ay);
  float accelZ = imu.calcAccel(imu.az);
  float gyroX = imu.calcGyro(imu.gx) / 57.3;
  float gyroY = imu.calcGyro(imu.gy) / 57.3;
  float gyroZ = imu.calcGyro(imu.gz) / 57.3;
  float magX = imu.calcMag(imu.mx);
  float magY = imu.calcMag(imu.my);
  float magZ = imu.calcMag(imu.mz);

  // SerialPort.println("Accel: " + String(accelX) + ", " + String(accelY) + ", " + String(accelZ) + " g");
  // SerialPort.print(String(accelZ)+",");
  // SerialPort.println("Gyro: " + String(gyroX) + ", " + String(gyroY) + ", " + String(gyroZ) + " dps");
  // SerialPort.println("Mag: " + String(magX) + ", " + String(magY) + ", " + String(magZ) + " uT");
  // SerialPort.println("Time: " + String(imu.time) + " ms");

  //Euler angle from accel


  pitch = atan2 (accelY , ( sqrt ((accelX * accelX) + (accelZ * accelZ))));
  roll = atan2(-accelX , ( sqrt((accelY * accelY) + (accelZ * accelZ))));

  // yaw from mag

  float Yh = (magY * cos(roll)) - (magZ * sin(roll));
  float Xh = (magX * cos(pitch)) + (magY * sin(roll) * sin(pitch)) + (magZ * cos(roll) * sin(pitch));

  yaw =  atan2(Yh, Xh);


  roll = roll * 57.3;
  pitch = pitch * 57.3;
  yaw = yaw * 57.3;
//  Serial.print(String(accelX) + "," + String(accelY) + "," + String(accelZ) + ",");
//  Serial.print(String(gyroX) + "," + String(gyroY) + "," + String(gyroZ) + ",");
  dataprint[0] = String(accelX);
  dataprint[1] = String(accelY);
  dataprint[2] = String(accelZ);
  dataprint[3] = String(gyroX);
  dataprint[4] = String(gyroY);
  dataprint[5] = String(gyroZ);

  dataprint[6] = String(pitch);
  dataprint[7] = String(roll);
  dataprint[8] = String(yaw);
  //SerialPort.println("Mag: " + String(magX) + ", " + String(magY) + ", " + String(magZ) + " uT");
  //SerialPort.println("Time: " + String(imu.time) + " ms");
//  Serial.print(String( pitch) + ",");
//  Serial.print( String( roll) + ",");
//  Serial.print(String( yaw ) + ",");
}
