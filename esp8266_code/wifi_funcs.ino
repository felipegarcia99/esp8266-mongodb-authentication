void server_connect(){
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  client.connect(server, 8080);   // Connection to the server
}

void wifi_send(String text){
  client.println(text + "\r");
}

String wifi_receive(){
  String answer = client.readStringUntil('\r');   // receives the answer from the sever
  return answer;
}

char* wifi_receive2(){
  String str = client.readStringUntil('\r');
  int str_len = str.length() + 1;
  static char char_array[100];
  str.toCharArray(char_array, str_len);
  return char_array;
}
