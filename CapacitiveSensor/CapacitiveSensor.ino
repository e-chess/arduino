#include <CapacitiveSensor.h>

CapacitiveSensor   row_A = CapacitiveSensor(4, 2);
//CapacitiveSensor   row_B = CapacitiveSensor();
//CapacitiveSensor   row_C = CapacitiveSensor();
//CapacitiveSensor   row_D = CapacitiveSensor();
//CapacitiveSensor   row_E = CapacitiveSensor();
//CapacitiveSensor   row_F = CapacitiveSensor();
//CapacitiveSensor   row_G = CapacitiveSensor();
//CapacitiveSensor   row_H = CapacitiveSensor();
CapacitiveSensor   row_1 = CapacitiveSensor(4, 12);
//CapacitiveSensor   row_2 = CapacitiveSensor();
//CapacitiveSensor   row_3 = CapacitiveSensor();
//CapacitiveSensor   row_4 = CapacitiveSensor();
//CapacitiveSensor   row_5 = CapacitiveSensor();
//CapacitiveSensor   row_6 = CapacitiveSensor();
//CapacitiveSensor   row_7 = CapacitiveSensor();
//CapacitiveSensor   row_8 = CapacitiveSensor();


class Sensor
{  
  long time = 0;
  boolean yes;
  boolean yes2;
  const int DEBOUNCE = 200;
                
    public:
    Sensor(){}
    
    void readOneField(int letter, int number){
       
     //Calibrate the sensor
      row_A.set_CS_AutocaL_Millis(0xFFFFFFFF);
      //row_B.set_CS_AutocaL_Millis(0xFFFFFFFF);
      //row_C.set_CS_AutocaL_Millis(0xFFFFFFFF);
      //row_D.set_CS_AutocaL_Millis(0xFFFFFFFF);
      //row_E.set_CS_AutocaL_Millis(0xFFFFFFFF);
      //row_F.set_CS_AutocaL_Millis(0xFFFFFFFF);
      //row_G.set_CS_AutocaL_Millis(0xFFFFFFFF);
      //row_H.set_CS_AutocaL_Millis(0xFFFFFFFF);
      row_1.set_CS_AutocaL_Millis(0xFFFFFFFF);
      //row_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
      //row_3.set_CS_AutocaL_Millis(0xFFFFFFFF);
      //row_4.set_CS_AutocaL_Millis(0xFFFFFFFF);
      //row_5.set_CS_AutocaL_Millis(0xFFFFFFFF);
      //row_6.set_CS_AutocaL_Millis(0xFFFFFFFF);
      //row_7.set_CS_AutocaL_Millis(0xFFFFFFFF);
      //row_8.set_CS_AutocaL_Millis(0xFFFFFFFF);
      
    
      long valueA =  row_A.capacitiveSensor(30);
      long value1 =  row_1.capacitiveSensor(30);

      long * valuesLetter[1] = {&valueA};
      long * valuesNumber[1] = {&value1};

      
       
      if (valuesLetter[letter] > 30){yes = true;}
      else {yes = false;}    
       if (valuesNumber[number] > 30){yes2 = true;}
      else {yes2 = false;}   
        
        // to toggle the state of state
        if(yes == true && yes2 == true && millis() - time>DEBOUNCE){
             time = millis();  
                     
        }
        else if (yes == false || yes2 == false){}

        Serial.print("Reihe A: ");
        Serial.println(*valuesLetter[letter]);
        Serial.print("Reihe 1: ");
        Serial.println(*valuesNumber[number]);
        delay(100);
    }
};

Sensor neuerSensorA1;

void setup()
{
  Serial.begin(9600);
  Serial.print("Please play CHESSCLOCK!");
}


void loop()                    
{
 neuerSensorA1.readOneField(0, 0);
}


