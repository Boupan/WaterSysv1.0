#WaterSysv1.0
 Watering programmer based on ESP
## **To do**

 - [] Installing a button with interrupt routine. 
```
//ISR subroutine
program_mode(){
 while(buttonpin == HIGH){
  //rotary encoder + lcd menu(?)
  //...
  //"button re-press to exit programming mode
  }
  ```
 - [] WiFi enable/disable
 
  So the user has to enter WiFi credentials. Based on code from [AirCon](https://github.com/Boupan/AirCON)
  Plus we have to use JSON file inside SPIFFS or EEPROM. What if we premade a site with QR.
