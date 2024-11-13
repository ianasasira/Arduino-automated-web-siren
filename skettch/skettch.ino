#include <Ds1302.h>

#include <arduinoRTClibrary-master.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <virtuabotixRTC.h>

#include <Arduin.h>

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
Serial.begin(9600);

pinMode(relay, OUTPUT);
pinMode(led, OUTPUT);
}

void loop() {
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

if (myRTC.dayofweek != 5 and myRTC.dayofweek != 6 and myRTC.hours == 7 and myRTC.minutes == 45 and myRTC.seconds == 00  ){
digitalWrite(relay, HIGH);
digitalWrite(led, HIGH);
delay(20000);
digitalWrite(relay, LOW);
digitalWrite(led, LOW);
}

else if (myRTC.dayofweek != 5 and myRTC.dayofweek != 6 and myRTC.hours == 8 and myRTC.minutes == 45 and myRTC.seconds == 00  ){
digitalWrite(relay, HIGH);
digitalWrite(led, HIGH);
delay(20000);
digitalWrite(relay, LOW);
digitalWrite(led, LOW);
}

else if (myRTC.dayofweek != 5 and myRTC.dayofweek != 6 and myRTC.hours == 9 and myRTC.minutes == 30 and myRTC.seconds == 00  ){
digitalWrite(relay, HIGH);
digitalWrite(led, HIGH);
delay(20000);
digitalWrite(relay, LOW);
digitalWrite(led, LOW);
}

else if (myRTC.dayofweek != 5 and myRTC.dayofweek != 6 and myRTC.hours == 10 and myRTC.minutes == 15 and myRTC.seconds == 00  ){
digitalWrite(relay, HIGH);
digitalWrite(led, HIGH);
delay(20000);
digitalWrite(relay, LOW);
digitalWrite(led, LOW);
}

else if (myRTC.dayofweek != 5 and myRTC.dayofweek != 6 and myRTC.hours == 11 and myRTC.minutes == 00 and myRTC.seconds == 00  ){
digitalWrite(relay, HIGH);
digitalWrite(led, HIGH);
delay(20000);
digitalWrite(relay, LOW);
digitalWrite(led, LOW);
}

else if (myRTC.dayofweek != 5 and myRTC.dayofweek != 6 and myRTC.hours == 11 and myRTC.minutes == 45 and myRTC.seconds == 00  ){
digitalWrite(relay, HIGH);
digitalWrite(led, HIGH);
delay(20000);
digitalWrite(relay, LOW);
digitalWrite(led, LOW);
}

else if (myRTC.dayofweek != 5 and myRTC.dayofweek != 6 and myRTC.hours == 12 and myRTC.minutes == 30 and myRTC.seconds == 00  ){
digitalWrite(relay, HIGH);
digitalWrite(led, HIGH);
delay(20000);
digitalWrite(relay, LOW);
digitalWrite(led, LOW);
}

else if (myRTC.dayofweek != 5 and myRTC.dayofweek != 6 and myRTC.hours == 13 and myRTC.minutes == 00 and myRTC.seconds == 00  ){
digitalWrite(relay, HIGH);
digitalWrite(led, HIGH);
delay(20000);
digitalWrite(relay, LOW);
digitalWrite(led, LOW);
}

else if (myRTC.dayofweek != 5 and myRTC.dayofweek != 6 and myRTC.hours == 13 and myRTC.minutes == 30 and myRTC.seconds == 00  ){
digitalWrite(relay, HIGH);
digitalWrite(led, HIGH);
delay(20000);
digitalWrite(relay, LOW);
digitalWrite(led, LOW);
}

else if (myRTC.dayofweek != 5 and myRTC.dayofweek != 6 and myRTC.hours == 14 and myRTC.minutes == 00 and myRTC.seconds == 00  ){
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
