void mqtt_loop(){
  //// MQTT ////
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    //Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(client_id, mqtt_username, mqtt_password)) {
      //Serial.println("connected");
      client.subscribe(light_set_topic);
      char buffer[50];
      sprintf(buffer, "{\"client_id\":\"%s\",\"ip\":\"%s\"}", client_id, WiFi.localIP().toString().c_str());
      
      client.publish(start_state_topic, buffer);
      
    } else {
      //Serial.print("failed, rc=");
      //Serial.print(client.state());
      //Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  char message[length + 1];
  for (int i = 0; i < length; i++) {
    message[i] = (char)payload[i];
  }
  message[length] = '\0';
  setLight(message);
}

void setLight(char* message){
  if (!processJson(message)) {
    return;
  }

  if (stateOn) {
    // Update lights
    realRed = map(red, 0, 255, 0, brightness);
  }
  else {
    realRed = 0;
  }

  startFade = true;
  inFade = false; // Kill the current fade

  sendState();
}



