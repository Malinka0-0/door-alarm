---
# door-alarm
---
## About
This project was created to track open doors and display the result in a telegram bot 
The project was realized for the microcontroller ESP8266 and ultrasonic sensor HR-SO04;
## Working principle 
The basic principle of operation is to read the distance from the sensor and then compare it with the initial 
distance to determine if the door is open. When an open door is detected, the microcontroller sends a message to the Telegram bot. 
In addition, the microcontroller contains sleep modes that reduce power consumption.

# How to create the project 
---
* Сonnecting components
* Install and configurate Arduino IDE
* Steps to configure telegram 
* Finale settings
## Step 1 :Сonnecting components
---
Connect the components to the controller ESP8266 like on the [connection diagram](https://github.com/Malinka0-0/door-alarm/blob/main/%D1%81%D1%85%D0%B5%D0%BC%D0%B0.png). <br>
Make sure the connection is reliable.
## Step 2 :Install and configurate Arduino IDE
---
1. Install [Arduino IDE 2.0.4](https://www.arduino.cc/en/software) or another version.
2. Configure Arduino IDE to work with ESP8266 
3. Open the Arduino IDE app 
Setting up Arduino :
-  File -> Preferences -> Additional boards manager URLs:-> copy and paste (https://arduino.esp8266.com/stable/package_esp8266com_index.json)
-  Tools -> Board -> Boards Manager -> esp8266 -> esp8266 by ESP8266 Community
-  Tools -> Board -> esp8266 -> NodeMCU 1.0(ESP-12E Module);

4. To check that everything is fine, connect the ESP8266 to the computer  and open : 
- Tools->Get board info 
If you have window ([Board Info](https://s4scoding.com/images/arduino-genuino-uno-board-info-800x400.jpg)) like this,everthing is fine. <br> 
5. You need to download libraries for the program, they can be downloaded in two ways. 
   - Install the libraries in Arduino IDE, for this open: <br>
Sketch -> Include Library -> Manager Library -> (enter name of library) -> install <br>
Example:<br>
Sketch -> Include Library -> Manager Library -> ArduinoJson -> install <br>
All nead library ;<br>
       - ArduinoJson (by Benoit Blanchon)
       - NTPClient (by Fabrice Weinberg)
       - UniversalTelegramBot (by Brian Lough)
   
    - Downloads file Libraries.zip <br>
Unzip the contents of the zip file and get the Libraries file.<br>
Move the contents of the Libraries file to the folder ../Arduino/libraries

6. Then need to create a new sketch,for this open:<br>
File -> New Sketch <br>
and copy in a new sketch , code from file [edfgd.ico](https://github.com/Malinka0-0/door-alarm/blob/main/edfgd.ino)<br>

## Step 3:Steps to configure telegram 
---
1. Open the telegram app 
2. Search BotFather.You will see a BotFather with a blue tick.
3. Start a chat with BotFather by typing /start. You can see the response with many command lists.
4. Create a new bot by typing /newbot
5. BotFather asks you to choose a username for a bot. Type a name for your bot.
6. Now let's choose a username for your bot.It must end in 'bot' .
7. Now you will get message like:Done! Congratulations on your new bot. you will find a link for your telegrambot and token .
8. Start Conversation to t.me/username by typing hello  
9. Go to https://api.telegram.org/bot"bot token"/getUpdates and take chat id and find a message like this
{"id":********,"first_name":"**************","username":"********","type":"private"},"date":***********,"text":"hello"}}]} (***** - some text)
you need "id":chatid for example "id":12491247 . 12491247 - it's your chat id
  
## Step 4 :Finale settings:
---
 1. Enter your informantion in the code's fields :<br>
 User_WiFi_Name "******"  // In " " enter the name of your WiFi network<br>
 User_WiFi_Password_to_WiFi "*******" //  In " " enter the password of your WiFi network <br>
 BotToken "***********" // Enter " " bot token in Telegram <br>
 chat_id  "*******" //chat id number for the Telegram channel
2. Connect the board to the computer and compile sketch then upload to esp8266. 
