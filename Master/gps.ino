void gps_ublox()
{
  bool newData = true;
  unsigned long chars;
  unsigned short sentences, failed;

  for (unsigned long start = millis(); millis() - start < 100;)
  {
    while (ss.available())
    {
      char c = ss.read();
      // Serial.write(c); // uncomment jika ingin melihat data asli dari gps
      if (gps.encode(c)) // Parsing semua data
        newData = true;
    }
  }

  if (newData)
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    //Serial.print(",");// ini LAT
//    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
//    Serial.print(",");// ini LON
//    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
//    Serial.print(","); // ini satelit
//    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    //Serial.print(" PREC=");
    //Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());

    dataprint[10] = String(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    dataprint[9] = String(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    //dataprint[11] = String (gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
  }
  //Serial.println();
  gps.stats(&chars, &sentences, &failed);
  //Serial.print(" CHARS=");
  //Serial.print(chars);
  //Serial.print(" SENTENCES=");
  //Serial.print(sentences);
  //Serial.print(" CSUM ERR=");
  //Serial.println(failed);
  //if (chars == 0)
    //Serial.println("--NO DATA, Check Wiring--");

}
