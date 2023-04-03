#include <ESP8266WiFi.h>
#include <Wire.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <time.h>

#define User_WiFi_Name "******"  // В " " введіть назву вашої WiFi мережі 
#define User_WiFi_Password_to_WiFi "*******" // В " " введіть пароль вашої WiFi мережі 
#define Pin_Info_Led 14 // Номер піна до якого підключено інформаційний світодіод 
#define Pin_Echo 13 //Номер піна до якого підключено Echo вихід датчика HC-SR04
#define Pin_Trig 15 //Номер піна до якого підключено Trig вихід датчика HC-SR04
#define Pin_Button 12 //Номер піна до яокго підключено кнопку 
#define BotToken "***********" // В " " токен бота в телеграм 
#define chat_id  "*******" //номер чату для телеграм каналу 
 

bool init_security_meaning = true;  
float security_meamimg;  
int  buttonPressedTime = 0; 
bool buttonState = false; 
bool Change ; 
bool currentButtonState ; 

bool condition_met = false; 
bool condition = true; 
int count ; //Лічильник 

WiFiClientSecure client; 
UniversalTelegramBot bot(BotToken, client);
// Налаштуйте NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ua.pool.ntp.org", 10800); //3600 - 1 Година 


void setup() {
  Serial.begin(9600);  
  
  WiFi.mode(WIFI_STA);

  WiFi.disconnect(); 

  pinMode(Pin_Info_Led,OUTPUT); 
  pinMode(Pin_Echo,INPUT); 
  pinMode(Pin_Trig,OUTPUT); 
  pinMode(Pin_Button,INPUT); 

  WiFi.begin(User_WiFi_Name, User_WiFi_Password_to_WiFi); 
  Serial.println("Підключення до Wi-Fi..."); 
  
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.println(".");
    digitalWrite(Pin_Info_Led, Change);
    Change = !Change;
  }
  Serial.println("Підключення до Wi-Fi успішне!");
  digitalWrite(Pin_Info_Led, false);
  client.setInsecure();
  timeClient.begin();
  Distance();
  timeClient.update();
  
  
}

void loop() {
  Distance();  
  if ((currentButtonState = digitalRead(Pin_Button)) == HIGH) {
    if (!buttonState) {
      buttonPressedTime = millis();
      buttonState = true;
    } else {
      unsigned long buttonHoldTime = millis() - buttonPressedTime;
      Serial.println(buttonHoldTime);
      if (buttonHoldTime >= 3000) {
          for (int i = 0 ;i < 8 ;i++){
           digitalWrite(Pin_Info_Led, Change);
           Change = !Change;
           delay(500);
         }
         digitalWrite(Pin_Info_Led, false);
         Serial.println("Режим сну");
         bot.sendMessage(chat_id, "Датчик в режимі сну ");
         ESP.deepSleep(0);
      }
    }
  } else {
    buttonState = false;
}
delay(500);
}

void Distance(){
  digitalWrite(Pin_Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Pin_Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Pin_Trig, LOW);
  
  long duration = pulseIn(Pin_Echo, HIGH);
  float distance = duration * 0.034 / 2; // Обчислення відстані 
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println("cm");  

  if(init_security_meaning) 
  {
  security_meamimg  = distance ;
  for(int h = 0 ;h<2;h++)
  {
    digitalWrite(Pin_Info_Led, Change);
    Change = !Change;
    delay(2000);
  }
  init_security_meaning = false;
  bot.sendMessage(chat_id, "Проініціалізовано відстані з сенсора до дверей ");
  }else{
    
   if(distance > (security_meamimg + 0.60)){
      if (condition_met && count == 3) {
       timeClient.update();
       
       time_t timestamp = timeClient.getEpochTime();
       struct tm* timeinfo = localtime(&timestamp);
       char timeString[25];
       strftime(timeString, 25, "%Y-%m-%d %H:%M:%S", timeinfo);
       bot.sendMessage(chat_id, timeString); 
       bot.sendMessage(chat_id, "Зафіксовано відчинення дверей "); 
       count = 0; 
       condition_met = false; 
        } 
        count = (condition) ? count + 1 : 0;
        condition_met = (count == 3) ? true : false;
   }
  }
  
}

