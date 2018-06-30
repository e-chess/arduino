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
  int smoothedLetter;
  int smoothedNumber;
                
    public:
    Sensor(){}
    
    int readOneField(char letter, int number, int borderLetter, int borderNumber){  
                
                                                          //senses one Field. For example the field A1 it is readOneField(0, 0, 30, 30)
                                                          //                  starting at 0 for the letter A (1-B, 2-C etc..) and 0 for the number 1
     

     long valueLetter;
     long valueNumber;
     
     switch (letter){
      case 'A':
      row_A.set_CS_AutocaL_Millis(0xFFFFFFFF);
      valueLetter =  row_A.capacitiveSensor(90);
      break;
      case 'B':
      row_B.set_CS_AutocaL_Millis(0xFFFFFFFF);
      valueLetter =  row_B.capacitiveSensor(90);
      break;
      case 'C':
      row_C.set_CS_AutocaL_Millis(0xFFFFFFFF);
      valueLetter =  row_C.capacitiveSensor(90);
      break;
      case 'D':
      row_D.set_CS_AutocaL_Millis(0xFFFFFFFF);
      valueLetter =  row_D.capacitiveSensor(90);
      break;
      case 'E':
      row_E.set_CS_AutocaL_Millis(0xFFFFFFFF);
      valueLetter =  row_E.capacitiveSensor(90);
      break;
      case 'F':
      row_F.set_CS_AutocaL_Millis(0xFFFFFFFF);
      valueLetter =  row_F.capacitiveSensor(60);
      break;
      case 'G':
      row_G.set_CS_AutocaL_Millis(0xFFFFFFFF);
      valueLetter =  row_G.capacitiveSensor(90);
      break;
      case 'H':
      row_H.set_CS_AutocaL_Millis(0xFFFFFFFF);
      valueLetter =  row_H.capacitiveSensor(90);
      break;
     }

      switch (number){
      case 1:
      row_1.set_CS_AutocaL_Millis(0xFFFFFFFF);
      valueNumber =  row_1.capacitiveSensor(60);
      break;
      case 2:
      row_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
      valueNumber =  row_2.capacitiveSensor(60);
      break;
      case 3:
      row_3.set_CS_AutocaL_Millis(0xFFFFFFFF);
      valueNumber =  row_3.capacitiveSensor(60);
      break;
      case 4:
      row_4.set_CS_AutocaL_Millis(0xFFFFFFFF);
      valueNumber =  row_4.capacitiveSensor(60);
      break;
      case 5:
      row_5.set_CS_AutocaL_Millis(0xFFFFFFFF);
      valueNumber =  row_5.capacitiveSensor(60);
      break;
      case 6:
      row_6.set_CS_AutocaL_Millis(0xFFFFFFFF);
      valueNumber =  row_6.capacitiveSensor(60);
      break;
      case 7:
      row_7.set_CS_AutocaL_Millis(0xFFFFFFFF);
      valueNumber =  row_7.capacitiveSensor(60);
      break;
      case 8:
      row_8.set_CS_AutocaL_Millis(0xFFFFFFFF);
      valueNumber =  row_8.capacitiveSensor(60);
      break;
     }    

      smoothedNumber = smooth(valueNumber, 0.95, smoothedNumber);
      smoothedLetter = smooth(valueLetter, 0.95, smoothedLetter);

      Serial.print("Letter: ");
      Serial.println(smoothedLetter);
      Serial.print("Number: ");
      Serial.println(smoothedNumber);
       
      if (smoothedLetter > borderLetter){touchedLetter = true;}
      else {touchedLetter = false;}    
       if (smoothedNumber > borderNumber){touchedNumber = true;}
      else {touchedNumber = false;}
        
        // to toggle the state of state
        if(touchedLetter == true && touchedNumber == true){
            return 1; 
                     
        }
        else if (touchedLetter == false || touchedNumber == false){
            return 0;  
        }        
    } 

    float smooth(float data, float filterVal, float smoothedVal){
  
    if (filterVal > 1){      // check to make sure param's are within range
      filterVal = .99;
    }
    else if (filterVal <= 0){
      filterVal = 0;
    }
  
    smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);
  
    return int(smoothedVal);
}
       
};



Sensor f1;
Sensor g1;



void setup()
{
  Serial.begin(9600);
  Serial.print("Have Fun!");
}


void loop()                    
{


if(f1.readOneField('F', 1, 115, 70) == 1){
   // Serial.println("touched Formula1"); 
 }
/*else if(g1.readOneField('G', 1, 125, 60) == 1){
    Serial.println("touched E1"); 
 }
 /*else if(neuerSensor.readOneField(0, 3, 30, 30) == 1){
    Serial.println("touched A4"); 
 }
 /*else if(neuerSensor.readOneField(0, 4, 30, 30) == 1){
    Serial.println("touched A5"); 
 }
 /*else if(neuerSensor.readOneField(0, 5, 30, 30) == 1){
    Serial.println("touched A6"); 
 }
 /*else if(neuerSensor.readOneField(0, 6, 30, 30) == 1){
    Serial.println("touched A7"); 
 }
 else if(neuerSensor.readOneField(0, 7, 30, 30) == 1){
    Serial.println("touched A8"); 
 }*/
}







