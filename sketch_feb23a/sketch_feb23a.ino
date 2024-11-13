#include <Ds1302.h>

#include <arduinoRTClibrary-master.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <virtuabotixRTC.h>

#include <Arduin.h>

#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>

// MAC address from Ethernet shield sticker under board
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(10, 0, 0, 20); // IP address, may need to change depending on network
EthernetServer server(80);  // create a server at port 80

File webFile;


/*
 * 
 *  SOURCE CODE FOR RELAY
* This is the Arduino code for Dual Channel 5V Relay
 * to control turn ON or OFF AC or DC load
 *  the video https://youtu.be/58XWVDnB7Ss
 *  * */
 /*
void setup() {
  pinMode(7, OUTPUT);// connected to S terminal of Relay

}

void loop() {

  digitalWrite(7,HIGH);// turn relay ON
  delay(3000);// keep it ON for 3 seconds

  digitalWrite(7, LOW);// turn relay OFF
 delay(5000);// keep it OFF for 5 seconds

}
*/
/*
 * 
 * CODE FOR SETTING THE RTC TIME
#include <virtuabotixRTC.h>                                                                              
virtuabotixRTC myRTC(6, 7, 8);

void setup()  {      
  Serial.begin(9600);

// Set the current date, and time in the following format:
// seconds, minutes, hours, day of the week, day of the month, month, year note: the week starts with monday so monday = 1, etc.
  myRTC.setDS1302Time(00, 59, 23, 6, 10, 1, 2020); // upload the sketch with the time you are at then reupload this sketch without this line just after uploading the first sketch.

}

void loop()  {                                                                                            
// This allows for the update of variables for time or accessing the individual elements.                
  myRTC.updateTime();                                                                                     
// Start printing elements as individuals                                                                   
  Serial.print("Current Date / Time: ");                                                                  
  Serial.print(myRTC.dayofmonth);                                                                         
  Serial.print("/");                                                                                      
  Serial.print(myRTC.month);                                                                              
  Serial.print("/");                                                                                      
  Serial.print(myRTC.year);                                                                               
  Serial.print("  ");                                                                                     
  Serial.print(myRTC.hours);                                                                              
  Serial.print(":");                                                                                      
  Serial.print(myRTC.minutes);                                                                            
  Serial.print(":");                                                                                      
  Serial.println(myRTC.seconds);                                                                          
// Delay so the program doesn't print non-stop                                                            
  delay(1000);*/





  /*
  CODE FOR  TURING ON RELAY ACCORDING TO SPECIFIED TIME
  */
  #include  <virtuabotixRTC.h>  // The RTC library

//Wiring     CLK -> 6 , DAT -> 7, Reset -> 8

virtuabotixRTC myRTC(6, 7, 8);

int relay = 9; // The signal pin of the relay connected to pin 9 in the Arduino
int led = 10; // Positive leg of the LED connected to pin 10 in the Arduino

void setup() {
// Set the current date, and time in the following format:
// seconds, minutes, hours, day of the week, day of the month, month, year note: the week starts with monday so monday = 1, etc.
  myRTC.setDS1302Time(00, 59, 23, 6, 10, 1, 2020); // upload the sketch with the time you are at then reupload this sketch without this line just after uploading the first sketch.

  //relay
Serial.begin(9600);

pinMode(relay, OUTPUT);
pinMode(led, OUTPUT);
pinMode(2, OUTPUT);       // LED on pin 2 fro initiallising via ethernjnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn
//relay

//ethernet shield
Ethernet.begin(mac, ip);  // initialize Ethernet device
    server.begin();           // start to listen for clients
    Serial.begin(9600);       // for debugging
    
    // initialize SD card
    Serial.println("Initializing SD card...");
    if (!SD.begin(4)) {
        Serial.println("ERROR - SD card initialization failed!");
        return;    // init failed
    }
    Serial.println("SUCCESS - SD card initialized.");
    // check for index.htm file
    if (!SD.exists("index.htm")) {
        Serial.println("ERROR - Can't find index.htm file!");
        return;  // can't find index file
    }
    Serial.println("SUCCESS - Found index.htm file.");
}

void loop() { 
  
  //http://startingelectronics.org reference 
  //The code below attains the index.html from the sd card pin 4 on the ethernet shield
  EthernetClient client = server.available();  // try to get client

    if (client) {  // got client?
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {   // client data available to read
                char c = client.read(); // read 1 byte (character) from client
                // last line of client request is blank and ends with \n
                // respond to client only after last line received
                if (c == '\n' && currentLineIsBlank) {
                    // send a standard http response header
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close");
                    client.println();
                    // send web page
                    webFile = SD.open("index.htm");        // open web page file
                    if (webFile) {
                        while(webFile.available()) {
                            client.write(webFile.read()); // send web page to client
                        }
                        webFile.close();
                    }
                    break;
                }
                // every line of text received from the client ends with \r\n
                if (c == '\n') {
                    // last character on line of received text
                    // starting new line with next character read
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    // a text character was received from client
                    currentLineIsBlank = false;
                }
            } // end if (client.available())
        } // end while (client.connected())
        delay(1);      // give the web browser time to receive the data
        client.stop(); // close the connection
    } // end if (client) 
    
myRTC.updateTime();

// Start printing elements as individuals
Serial.print("Current Date / Time: ");
Serial.print(myRTC.dayofmonth);
Serial.print("/");
Serial.print(myRTC.month);
Serial.print("/");
Serial.print(myRTC.year);
Serial.print("  ");
Serial.print(myRTC.hours);
Serial.print(":");
Serial.print(myRTC.minutes);
Serial.print(":");
Serial.println(myRTC.seconds);
// Delay so the program doesn't print non-stop
delay(1000);

myRTC.updateTime();

if (myRTC.dayofweek != 5 and myRTC.dayofweek != 6 and myRTC.dayofweek != 2 and myRTC.hours == 8 and myRTC.minutes == 00 and myRTC.seconds == 00  ){
digitalWrite(relay, HIGH);
digitalWrite(led, HIGH);
delay(20000);
digitalWrite(relay, LOW);
digitalWrite(led, LOW);
}

else if (myRTC.dayofweek != 5 and myRTC.dayofweek != 6 and myRTC.dayofweek != 2 and myRTC.hours == 9 and myRTC.minutes == 20 and myRTC.seconds == 00  ){
digitalWrite(relay, HIGH);
digitalWrite(led, HIGH);
delay(20000);
digitalWrite(relay, LOW);
digitalWrite(led, LOW);
}

else if (myRTC.dayofweek != 5 and myRTC.dayofweek != 6 and myRTC.dayofweek != 2 and myRTC.hours == 10 and myRTC.minutes == 40 and myRTC.seconds == 00  ){
digitalWrite(relay, HIGH);
digitalWrite(led, HIGH);
delay(20000);
digitalWrite(relay, LOW);
digitalWrite(led, LOW);
}

else if (myRTC.dayofweek != 5 and myRTC.dayofweek != 6 and myRTC.dayofweek != 2 and myRTC.hours == 11 and myRTC.minutes == 00 and myRTC.seconds == 00  ){
digitalWrite(relay, HIGH);
digitalWrite(led, HIGH);
delay(20000);
digitalWrite(relay, LOW);
digitalWrite(led, LOW);
}

else if (myRTC.dayofweek != 5 and myRTC.dayofweek != 6 and myRTC.dayofweek != 2 and myRTC.hours == 12 and myRTC.minutes == 00 and myRTC.seconds == 00  ){
digitalWrite(relay, HIGH);
digitalWrite(led, HIGH);
delay(20000);
digitalWrite(relay, LOW);
digitalWrite(led, LOW);
}

else if (myRTC.dayofweek != 5 and myRTC.dayofweek != 6 and myRTC.dayofweek != 2 and myRTC.hours == 1 and myRTC.minutes == 00 and myRTC.seconds == 00  ){
digitalWrite(relay, HIGH);
digitalWrite(led, HIGH);
delay(20000);
digitalWrite(relay, LOW);
digitalWrite(led, LOW);
}

else if (myRTC.dayofweek != 5 and myRTC.dayofweek != 6 and myRTC.dayofweek != 2 and myRTC.hours == 14 and myRTC.minutes == 00 and myRTC.seconds == 00  ){
digitalWrite(relay, HIGH);
digitalWrite(led, HIGH);
delay(20000);
digitalWrite(relay, LOW);
digitalWrite(led, LOW);
}

else if (myRTC.dayofweek != 5 and myRTC.dayofweek != 6 and myRTC.dayofweek != 2 and myRTC.hours == 15 and myRTC.minutes == 20 and myRTC.seconds == 00  ){
digitalWrite(relay, HIGH);
digitalWrite(led, HIGH);
delay(20000);
digitalWrite(relay, LOW);
digitalWrite(led, LOW);
}

else if (myRTC.dayofweek != 5 and myRTC.dayofweek != 6 and myRTC.dayofweek != 2 and myRTC.hours == 16 and myRTC.minutes == 40 and myRTC.seconds == 00  ){
digitalWrite(relay, HIGH);
digitalWrite(led, HIGH);
delay(20000);
digitalWrite(relay, LOW);
digitalWrite(led, LOW);
}

else if (myRTC.dayofweek != 5 and myRTC.dayofweek != 6 and myRTC.dayofweek != 2 and myRTC.hours == 5 and myRTC.minutes == 45 and myRTC.seconds == 00  ){
digitalWrite(relay, HIGH);
digitalWrite(led, HIGH);
delay(20000);
digitalWrite(relay, LOW);
digitalWrite(led, LOW);
}

else{
digitalWrite(relay, LOW);
digitalWrite(led, LOW);
}
}

/*--------------------------------------------------------------
  Program:      eth_websrv_SD

  Description:  Arduino web server that serves up a basic web
                page. The web page is stored on the SD card.
  
  Hardware:     Arduino Uno and official Arduino Ethernet
                shield. Should work with other Arduinos and
                compatible Ethernet shields.
                2Gb micro SD card formatted FAT16
                
  Software:     Developed using Arduino 1.0.3 software
                Should be compatible with Arduino 1.0 +
                SD card contains web page called index.htm
  
  References:   - WebServer example by David A. Mellis and 
                  modified by Tom Igoe
                - SD card examples by David A. Mellis and
                  Tom Igoe
                - Ethernet library documentation:
                  http://arduino.cc/en/Reference/Ethernet
                - SD Card library documentation:
                  http://arduino.cc/en/Reference/SD

  Date:         10 January 2013
 
  Author:       W.A. Smith, http://startingelectronics.org
--------------------------------------------------------------*/



void loop()
{

}
