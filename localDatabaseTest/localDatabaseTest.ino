

String source = "d7";
String target = "d6";



void setup(void) 
{
  Serial.begin(9600);
}

void loop(void) 
{  
  sendTestData();
  delay(15000);
}

void sendTestData()
{
   Serial.print(source);
   Serial.print(",");
   Serial.println(target);
}
