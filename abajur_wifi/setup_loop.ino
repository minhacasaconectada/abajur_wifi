void setup() {
  Serial.begin(115200);
  //Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    //Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("esp-d1mini-abajur");

  // No authentication by default
  ArduinoOTA.setPassword(senha_ota);

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  //// LRD ////
  pinMode(pinLdr, INPUT);
 
  //// PIR ////
  pinMode(pinPir, INPUT);
  
  //// Luz ////
  pinMode(pinRed, OUTPUT);
  analogWriteRange(255);
    
  //// MQTT ////
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  //// Botão ////
  pinMode(pinBotao1, INPUT_PULLUP);

}

void loop() {
  ArduinoOTA.handle();
  mqtt_loop();
  pir_loop();
  ldr_loop();
  led_loop();
  verifica_botao();
}
