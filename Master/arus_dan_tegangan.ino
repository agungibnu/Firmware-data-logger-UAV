void tegangan()
{
  Va = analogRead(A1);
  Aa = analogRead(A2);
  V = ((Va*0.044412)+0.127786);
  Arus = ((0.080072 * Aa)-0.10204);
  dataprint [11] = String(V);
  dataprint [12] = String(Arus);
  
  //Serial.print(V);
 // Serial.println(".0");
  //delay(100);
}
