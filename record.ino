#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <Wire.h>
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
double lon,la,la1=26.934339999999999999,la2=26.93337000000000000,lon1=75.923279999999999999,lon2=75.921820000000000000;
int rag,f,e=0,mi=0,y,l,ans=0,v=0,fy,x=300,raghav12=0;
int flag;
const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum
int dif,count,i=0,a[200],j,sum=0,b;
void setup()
{
  pinMode(A0,INPUT);   //VIBRATION
   pinMode(A1,INPUT);   // FIRE
  Serial1.begin(9600); 
  Serial.begin(9600); 
   Serial2.begin(GPSBaud);  
   Wire.begin();
  delay(100);
  rag=5;
  for(f=0 ; f<10 ; f++)
  {
    Serial1.print("AT+CMGD=");
    Serial1.println(f);
    delay(250);
  }
}
void loop()
{
  {
      ans=fy=0;
      fy=RecieveMessage(); 
      if(fy==-1)
      {
        while(1){
          v=0;
         while (Serial2.available() > 0)
         if (gps.encode(Serial2.read()))
          v=displayInfo();
         if(v==-1)
         break;
        if (millis() > 5000 && gps.charsProcessed() < 10) {
         Serial.println(F("No GPS detected: check wiring."));
          while(true);}
             }
             v=0; 
      }
      else if(fy==-2){
        SendMessage();
         while(1){
          v=0;
         while (Serial2.available() > 0)
         if (gps.encode(Serial2.read()))
          v=displayInfo();
         if(v==-1)
         break;
        if (millis() > 5000 && gps.charsProcessed() < 10) {
         Serial.println(F("No GPS detected: check wiring."));
          while(true);}
             }
             v=0; }
        else if(fy==-5)
        SendMessage5();
        else if(fy==-7)
        {
          v=0;
        }
       else
    bluetooth(fy);
  }
 if (Serial1.available()>0)
   Serial.write(Serial1.read());
}
 void SendMessage()
{
  Serial1.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  
  Serial1.println("AT+CMGS=\"+919202222029\"\r"); 
  delay(1000);
  Serial1.println("FIRE ACCIDENT HAPPEN");
  delay(100);
   Serial1.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
void SendMessage5()
{
  Serial1.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  
  Serial1.println("AT+CMGS=\"+919202222029\"\r"); 
  delay(1000);
  Serial1.println("ROAD ACCIDENT HAPPEN");
  delay(100);
   Serial1.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
 int RecieveMessage()
{
   Serial1.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  Serial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);  
  Serial1.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  while(Serial1.peek()!='#')
  {
    int rgh=0,raghav12=0;
    ans=0;
    char b=Serial1.read();
   /* Serial.println("badchar");
    Serial.println(b);*/
    //delay(500);
   rgh=accident();
    if(rgh==-2)
    return -2; 
  }
  char we1=Serial1.read();
  char we=Serial1.read();
  if(we=='L' || we=='l')
     {
      return -1;
     }
      if(we=='G' || we=='g')
     {
         char c=Serial1.read();
     l=(int)c;
     l=l-48;
  ans=(ans*10)+l;
  char df=Serial1.read();
     l=(int)df;
     l=l-48;
  ans=(ans*10)+l;
 /* Serial.print("ans is : ");
  Serial.println(ans);
  delay(6000); */
  int zx=raghav(ans);
  return -7;
     }
     l=(int)we;
     l=l-48;
  ans=(ans*10)+l;
  char df=Serial1.read();
     l=(int)df;
     l=l-48;
  ans=(ans*10)+l;
  Serial.print("ans is : ");
  Serial.println(ans);
  return ans;
 }
 int displayInfo() {
  Serial.print(F("Location: ")); 
  if (gps.location.isValid()) {
    la=gps.location.lat();
    Serial.print(la);
    Serial.print(F(","));
    lon=gps.location.lng();
    sendlat(la,lon);
     Serial.print(lon);
    delay(1000);
     return -1;
  } else {
    Serial.println(F("INVALID"));
    return 0;
  }
  Serial.println();
}
void sendlat(double la,double lon)
{
  Serial1.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  
  Serial1.println("AT+CMGS=\"+919202222029\"\r"); 
  delay(1000);
  Serial1.print(la,18);
   Serial1.print(F(","));
   Serial1.print(lon,18);
  delay(100);
   Serial1.println((char)26);// ASCII code of CTRL+Z
  //delay(1000);
}
int accident()
{
  b = analogRead(A0);
Serial.println(b);
 a[i]=b;
  i++;
  if(i==200){
    for(j=0 ; j<100 ; j++)
    {
      dif=a[j]-a[j+1];
      if(dif>500 || dif<(-500))
        {
          if(dif!=-1)
           sum++;
        } 
    }
    i=0;
  }
  if(sum>100){
  //Serial.println("accident");
  return -5;}
  sum=0;    */
  int sensorReading = analogRead(A1);
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);
 // Serial.println(range);
  switch (range) {
  case 0:
  {
    Serial.println("** Close Fire **");
    return -2;
    break;}
  case 1:    // A fire between 1-3 feet away.
    Serial.println("** Distant Fire **");
    break;
  case 2:    // No fire detected.
    Serial.println("No Fire");
    break;
  }  
 // delay(1);  // delay between reads
  return 0;
}
void bluetooth(int fy)
{
  if(fy>=0 && fy<=20){
  Wire.beginTransmission(9); 
  Wire.write(0);              
  Wire.endTransmission();     
  delay(100);}   
  else if(fy>20 && fy<=60){
  Wire.beginTransmission(9); 
  Wire.write(160);             
  Wire.endTransmission(); 
  delay(100);} 
  else{
  Wire.beginTransmission(9);
  Wire.write(250);              
  Wire.endTransmission(); 
  delay(100);}    
}
int displayInfo1(int limit) {
 // Serial.println("yeah baby ");
  Serial.print(F("Location: ")); 
  if (gps.location.isValid()) {
    la=gps.location.lat();
    Serial.print(la,10);
    Serial.print(F(","));
    lon=gps.location.lng();
     Serial.print(lon,10);
     if((la<=la1 && lon<=lon1) && (la>=la2 && lon>=lon2))
     {
      Wire.beginTransmission(9);
      Wire.write(limit);              
      Wire.endTransmission();
     }
    else {
       Wire.beginTransmission(9);
      Wire.write(250);              
      Wire.endTransmission();
    return 0;}
  } else {
    Serial.println(F("INVALID"));
    return 0;
  }
  Serial.println();
}
int raghav(int limit)
{
  if(limit>=0 && limit<=20)
   limit=0;   
  if(limit>20 && limit<=60)
   limit=160; 
  else
  limit=250;          
   while(1){
          v=0;
         while (Serial2.available() > 0)
         if (gps.encode(Serial2.read()))
          v=displayInfo1(limit);
         if(v==-1)
         break;
        if (millis() > 5000 && gps.charsProcessed() < 10) {
         Serial.println(F("No GPS detected: check wiring."));
          while(true);}
             }
            return -7;
}
