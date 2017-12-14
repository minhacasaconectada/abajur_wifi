void verifica_botao(){  
  long now = millis();  

  readingBotao1 = digitalRead(pinBotao1);
  if(readingBotao1 != botao1OldState){
      debounceTimeBotao1 = now;
  }
  if(now - debounceTimeBotao1 > 50){
    if(readingBotao1 != botao1State){
      botao1State = readingBotao1;
      if(botao1State == LOW){
        String str = "";
        if(stateOn == false){
           str = '{"state": "ON"}';
        } else {
           str = '{"state": "OFF"}';
        }
        int str_len = str.length() + 1; 
        char char_array[str_len];
        str.toCharArray(char_array, str_len);
        setLight(char_array);
      }
    }
  }
  botao1OldState = readingBotao1;
}



