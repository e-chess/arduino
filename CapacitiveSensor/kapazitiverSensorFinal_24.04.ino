////////////////////////////////////////////////////////////////////////////////////
//
//  main code of smart chess ((working title)
//  
//  authors: Marcus Schoch, Jan Schneider
//
//  date: 22.04.2018
//  
//  description: This code detects a capacitive touch on one of 64 fields on a chessboard.
//
//  source: internet ;)
//
//  library: CapacitiveSensor by Paul Badge (http://playground.arduino.cc/Main/CapacitiveSensor)
//  
//  devices:
//  - Arduino Uno
//  - resistors 1Mohm
//  - capacitors 100pf
//
//  PINs: Pins for the Sensor, right now only 2, 4, 12.


#include <CapacitiveSensor.h>


//initializes the sensors and already defines the pins

CapacitiveSensor   row_A = CapacitiveSensor(22, 23);
CapacitiveSensor   row_B = CapacitiveSensor(22, 24);
CapacitiveSensor   row_C = CapacitiveSensor(22, 25);
CapacitiveSensor   row_D = CapacitiveSensor(22, 26);
CapacitiveSensor   row_E = CapacitiveSensor(22, 27);
CapacitiveSensor   row_F = CapacitiveSensor(22, 28);
CapacitiveSensor   row_G = CapacitiveSensor(22, 29);
CapacitiveSensor   row_H = CapacitiveSensor(22, 30);

CapacitiveSensor   row_1 = CapacitiveSensor(50, 49);
CapacitiveSensor   row_2 = CapacitiveSensor(50, 48);
CapacitiveSensor   row_3 = CapacitiveSensor(50, 47);
CapacitiveSensor   row_4 = CapacitiveSensor(50, 46);
CapacitiveSensor   row_5 = CapacitiveSensor(50, 45);
CapacitiveSensor   row_6 = CapacitiveSensor(50, 44);
CapacitiveSensor   row_7 = CapacitiveSensor(50, 43);
CapacitiveSensor   row_8 = CapacitiveSensor(50, 42);


class Sensor                                              //creates a new class of Sensor and defines variables later used in the methods
{  
  long time = 0;
  unsigned long currentMillis = millis();                 //is later used to calculate a time interval
  boolean touchedLetter;                                  //just to check if a state is high or low
  boolean touchedNumber;
  const int interval = 200;                               //interval to pace the code
                
    public:
    Sensor(){}
    
    int readOneField(int letter, int number, int borderLetter, int borderNumber){  
                
                                                          //senses one Field. For example the field A1 it is readOneField(0, 0, 30, 30)
                                                          //                  starting at 0 for the letter A (1-B, 2-C etc..) and 0 for the number 1
     //Calibrate the sensor
      row_A.set_CS_AutocaL_Millis(0xFFFFFFFF);
      row_B.set_CS_AutocaL_Millis(0xFFFFFFFF);
      row_C.set_CS_AutocaL_Millis(0xFFFFFFFF);
      row_D.set_CS_AutocaL_Millis(0xFFFFFFFF);
      row_E.set_CS_AutocaL_Millis(0xFFFFFFFF);
      row_F.set_CS_AutocaL_Millis(0xFFFFFFFF);
      row_G.set_CS_AutocaL_Millis(0xFFFFFFFF);
      row_H.set_CS_AutocaL_Millis(0xFFFFFFFF);
      
      row_1.set_CS_AutocaL_Millis(0xFFFFFFFF);
      row_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
      row_3.set_CS_AutocaL_Millis(0xFFFFFFFF);
      row_4.set_CS_AutocaL_Millis(0xFFFFFFFF);
      row_5.set_CS_AutocaL_Millis(0xFFFFFFFF);
      row_6.set_CS_AutocaL_Millis(0xFFFFFFFF);
      row_7.set_CS_AutocaL_Millis(0xFFFFFFFF);
      row_8.set_CS_AutocaL_Millis(0xFFFFFFFF);
      
    
      long valueA =  row_A.capacitiveSensor(80);
      long valueB =  row_B.capacitiveSensor(30);
      long valueC =  row_C.capacitiveSensor(30);
      long valueD =  row_D.capacitiveSensor(30);
      long valueE =  row_E.capacitiveSensor(30);
      long valueF =  row_F.capacitiveSensor(30);
      long valueG =  row_G.capacitiveSensor(30);
      long valueH =  row_H.capacitiveSensor(30);
      
      long value1 =  row_1.capacitiveSensor(80);
      long value2 =  row_2.capacitiveSensor(30);
      long value3 =  row_3.capacitiveSensor(30);
      long value4 =  row_4.capacitiveSensor(30);
      long value5 =  row_5.capacitiveSensor(30);
      long value6 =  row_6.capacitiveSensor(30);
      long value7 =  row_7.capacitiveSensor(30);
      long value8 =  row_8.capacitiveSensor(30);
      

      long * valuesLetter[8] = {&valueA, &valueB, &valueC, &valueD, &valueE, &valueF, &valueG, &valueH};
      long * valuesNumber[8] = {&value1, &value2, &value3, &value4, &value5, &value6, &value7, &value8};

      
       
      if (*valuesLetter[letter] > borderLetter){touchedLetter = true;}
      else {touchedLetter = false;}    
       if (*valuesNumber[number] > borderNumber){touchedNumber = true;}
      else {touchedNumber = false;}   
        
        // to toggle the state of state
        if(touchedLetter == true && touchedNumber == true && currentMillis - time > interval){
            time = currentMillis;
            return 1; 
                     
        }
        else if (touchedLetter == false || touchedNumber == false && currentMillis - time > interval){
            time = currentMillis;
            return 0;  
        }
        Serial.print("Letter: ");
        Serial.println(*valuesLetter[letter]);
        Serial.print("Number: ");
        Serial.println(*valuesNumber[number]);
        delay(100);
        
    }

    void doSomething(){
      Serial.println("do something");  
    }
};

Sensor neuerSensor;




void setup()
{
  Serial.begin(9600);
  Serial.print("Please play CHESSCLOCK!");
}


void loop()                    
{
neuerSensor.readOneField(0, 0, 30, 30); 
//neuerSensor.doSomething();

 //if(neuerSensor.readOneField(0, 0, 140, 90) == 1){
 //   Serial.println("touched A1"); 
 //}

 /*else if(neuerSensor.readOneField(0, 2, 30, 30) == 1){
    Serial.println("touched A3"); 
 }
 else if(neuerSensor.readOneField(0, 3, 30, 30) == 1){
    Serial.println("touched A4"); 
 }
 else if(neuerSensor.readOneField(0, 4, 30, 30) == 1){
    Serial.println("touched A5"); 
 }
 else if(neuerSensor.readOneField(0, 5, 30, 30) == 1){
    Serial.println("touched A6"); 
 }
 else if(neuerSensor.readOneField(0, 6, 30, 30) == 1){
    Serial.println("touched A7"); 
 }
 else if(neuerSensor.readOneField(0, 7, 30, 30) == 1){
    Serial.println("touched A8"); 
 }*/
}

