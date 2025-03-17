  #include <ESP8266WiFi.h>
  #include <DNSServer.h>
  #include <ESP8266WebServer.h>
  #include <WiFiManager.h>  
  #include <ESP8266HTTPClient.h>
  #include <EEPROM.h>

  WiFiServer server(80); 

const char* serverName = "aserver";
String apiKey = "key"; 

  int R,Y,B,A,C,D,r,y,b,i;
  
  int RP = 16; // 0;//       esp 01  &   esp 12
  int YP = 5; // 2;//
  int BP = 4; // 3;// 
  
  
  void setup() {
  Serial.begin(115200);
  EEPROM.begin(1); 
  
 
  pinMode(RP, INPUT);
  pinMode(YP, INPUT);
  pinMode(BP, INPUT);
  
 

  WiFiManager wifiManager;
  wifiManager.autoConnect("Novatron");                  
  Serial.println("<Controller is ready>");               
  server.begin(); 

    
    A=EEPROM.read(0); 
    EEPROM.commit();
     
    
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  void loop() { 

    r = digitalRead(RP);
    y = digitalRead(YP);
    b = digitalRead(BP);

    if(r==HIGH){R=1;}else{R=0;}
    if(y==HIGH){Y=1;}else{Y=0;}
    if(b==HIGH){B=1;}else{B=0;}
    
    if(R+Y+B==A)
    {}
    else
    {C=0;D++;if(D==3){D=1;}}
//Serial.print(C); Serial.print(A); Serial.println(R+Y+B); 


  if(C==0){
    i++; 
   sendRequest(R, Y, B, D); 
   if(i>=1){
    C=1;i=0;A=R+Y+B;EEPROM.write(0,A);EEPROM.commit();Serial.print(C); Serial.print(A); Serial.println(R+Y+B); 
}
  }delay(2000);
  }

  void sendRequest(int R, int Y, int B, int D) {
    HTTPClient http;
    WiFiClient client;

    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("apiKey", apiKey);

    String jsonPayload = "{\"R\": \"" + String(R) + "\", \"Y\": \"" + String(Y) + "\", \"B\": \"" + String(B) + "\", \"D\": \"" + String(D) + "\"}";
    Serial.print("Sending JSON: ");
    Serial.println(jsonPayload);
    // Notification variable is D
    int httpResponseCode = http.POST(jsonPayload);
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    http.end();
}