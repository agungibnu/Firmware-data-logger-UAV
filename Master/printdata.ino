void printdata() {
String semua = String();
semua = "LP,";
  for (int i = 0; i < 15; i++)
  {
   // Serial.print(dataprint[i]);
    semua += String(dataprint[i] + ",");
    //    Serial.print(","); delay(100);
  }
  delay(50);
  Serial.println(semua);
}
