/* 

---------------GARDEN CODE ------------------

Description: SIMPLE CODE FOR MONITORING THE WATERING OF MY GARDEN

FUNCTIONS

# The system will wake up by the always ON RTC DS3231 module of which alarms will be made.
Meanwhile the user can enable WiFi commands if he wants together with premade Blynk App in order to 
control the watering routine

# The thought is that when WiFi is enabled the system stops to be power efficient.

*/

#include "DS3232RTC.h"
//#include <ESP8266WiFi.h>
//#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#include <avr/sleep.h>//this AVR library contains the methods that controls the sleep modes
#define interruptPin 2 //Pin we are going to use to wake up the Arduino

//int serialRx = 3;   // software serial  RX  TX 
//int serialTx = 4;   // ESP-01 RX goes to this port, TX goes to Port 2
const int MosfetEsp = 7;
// ESP-01 CH_PD pin 7 Must go to 3.3v, not +5v to enable operation as UART (AP)
// UNO R3 has enough power to make it work.
const int pump1 = 4;
const int pump2 = 6;
const int buttonWifi = 5;
const int rottaryEn = 8;
//SoftwareSerial portOne(serialRx, serialTx); // communications port to ESP-01

//char auth[] = "";

// Your WiFi credentials.
// Set password to "" for open networks.
//char ssid[] = "##########";
//char pass[] = "##########";


void setup()
{
  pinMode(pump1, OUTPUT);
  pinMode(pump2, OUTPUT);
  pinMode(buttonWifi, INPUT_PULLUP);
  pinMode(MosfetEsp,OUTPUT);
  pinMode(rottaryEn, INPUT);
  digitalWrite(MosfetEsp,HIGH);
  digitalWrite(pump1, LOW);
  digitalWrite(pump2, LOW);
  //portOne.begin(115200);

    // initialize the alarms to known values, clear the alarm flags, clear the alarm interrupt flags
    RTC.setAlarm(ALM1_MATCH_DATE, 0, 0, 0, 1);
    RTC.setAlarm(ALM2_MATCH_DATE, 0, 0, 0, 1);
    RTC.alarm(ALARM_1);
    RTC.alarm(ALARM_2);
    RTC.alarmInterrupt(ALARM_1, false);
    RTC.alarmInterrupt(ALARM_2, false);
    RTC.squareWave(SQWAVE_NONE);

      /*Begin block
     tmElements_t tm;
    tm.Hour = 02;               // set the RTC to an arbitrary time
    tm.Minute = 45;
    tm.Second = 00;
    tm.Day = 28;
    tm.Month = 8;
    tm.Year = 2020 - 1970;      // tmElements_t.Year is the offset from 1970
    RTC.write(tm);              // set the RTC from the tm structure
//     Block end */
     //time_t t; //create a temporary time variable so we can set the time and read the time from the RTC
    //t=RTC.get();//Gets the current time of the RTC
    RTC.setAlarm(ALM1_MATCH_HOURS , 0, 0, 2, 0);// Setting alarm 1 to trigger at 02:00
    // clear the alarm flag
    RTC.alarm(ALARM_1);
    // configure the INT/SQW pin for "interrupt" operation (disable square wave output)
    RTC.squareWave(SQWAVE_NONE);
    // enable interrupt output for Alarm 1
    RTC.alarmInterrupt(ALARM_1, true);
}
    void loop() {
     delay(1000);
     Going_To_Sleep();
}

void Going_To_Sleep(){
    sleep_enable();//Enabling sleep mode
    attachInterrupt(0, wakeUp, LOW);//attaching a interrupt to pin d2
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);//Setting the sleep mode, in our case full sleep
    //time_t t;// creates temp time variable
    //t=RTC.get(); //gets current time from rtc
    delay(1000); //wait a second to allow the led to be turned off before going to sleep
    sleep_cpu();//activating sleep mode
    //t=RTC.get();
RTC.setAlarm(ALM1_MATCH_HOURS , 0, 0, 2, 0);
    RTC.alarm(ALARM_1);
  }

void wakeUp(){
  sleep_disable();//Disable sleep mode
  unsigned long currentMillis = millis();
     while (currentMillis<=100000){
     digitalWrite(pump1, HIGH);
     digitalWrite(pump2, LOW);
     }
     //delay(100000);
     while (currentMillis<=200000){
     digitalWrite(pump1, LOW);
     digitalWrite(pump2, HIGH);
     }
     //delay(100000);
  detachInterrupt(0); //Removes the interrupt from pin 2;
 
}