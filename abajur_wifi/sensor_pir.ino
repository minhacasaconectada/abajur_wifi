
void pir_loop(){
  int pirState = digitalRead(pinPir);  
  
  if (pirState != pirOldState){
    client.publish(pir_state_topic, pirState==HIGH?on_cmd:off_cmd,true);
    pirOldState = pirState;
  }
}

void ldr_loop(){
  long now = millis(); 
  if((now - timeLdr) > 3000){
    valueLdr = analogRead(pinLdr);  
    //Serial.println(valueLdr);  
    String str = String(valueLdr); 
    int str_len = str.length() + 1; 
    char char_array[str_len];
    str.toCharArray(char_array, str_len);
    client.publish(ldr_state_topic, char_array);
    timeLdr = now;
  }
  
}
