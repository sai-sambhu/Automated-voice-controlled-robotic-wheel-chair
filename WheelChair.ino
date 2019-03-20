
#include <SoftwareSerial.h>

#include <TinyGPS.h>

#include <Sim800l.h>

#define SIM800_TX_PIN 12
#define SIM800_RX_PIN 13

SoftwareSerial mySerial(SIM800_TX_PIN, SIM800_RX_PIN);


String response;
boolean activeCall = false; 
String alertNumber = "+917780107612";
String alertNumber1 = "+917780107612";
long callActiveSince = 0;// indicates that there is an active call going
boolean setUpModeActive = false;
int calibrationTime = 0.1;
int commandDelay=1000;


TinyGPS gps;
SoftwareSerial ss(4, 3);

const int x_axis=A0;
const int y_axis=A1;
const int z_axis=A2;
const int Buzz=11;
float flat=0, flon=0;



void setup() {
Serial.begin(9600);
ss.begin(9600);
mySerial.begin(9600);
delay(1000);
 pinMode(Buzz, OUTPUT);
 digitalWrite(Buzz,LOW);  
  Serial.print("Simple TinyGPS library v. "); Serial.println(TinyGPS::library_version());
  Serial.println();

}

String getAtResponse(String command, long commandDelay)
{

  Serial.print("before ");
  Serial.print(command);
  Serial.print(":");
  Serial.print(getSim800Response());
  Serial.println(":");
  mySerial.println(command);
 
 delay(commandDelay);

  return getSim800Response();
}



int x=0;

String getSim800Response()
  {
    Serial.println("hi");

  int recvCharInt;
  String resp="";
  char recvChar,str[1023],ReturnStr[1023];

  int counter=0;
  

  while (mySerial.available()  ){       //while there is data and not prompt
    recvChar = mySerial.read();  
   //read from elm
    recvCharInt = recvChar;
   
    if (recvCharInt == 0)
     
        if (recvCharInt == 65)
      recvChar = '|';
    resp = resp + recvChar;
    //Serial.print("char at ");
    //Serial.print(counter);
    //Serial.print(":");
    //Serial.print(recvChar);
    //Serial.print(":");
    //Serial.print(recvCharInt);
    //Serial.println(":");
    if (counter > 512) 
      break;
      
  }

//  Serial.print("resp=");
//  Serial.print(resp);
//  Serial.println("=");
Serial.println(resp);
  return resp;
  String Response=getSim800Response();
  Serial.println(Response);
}
 




void makeAcall(String phoneNumber){
  char charRead;
  String callAtCommand;

  Serial.print("ATD");
  Serial.print(phoneNumber);
  Serial.print(";\r");
  callAtCommand = "ATD";
  callAtCommand += phoneNumber;
  callAtCommand += ';';
  getAtResponse(callAtCommand,2000);
  activeCall = true;
  callActiveSince = millis();

}


int sms(String phone_num,String message)
{
  Serial.println("Setup Complete!");

  Serial.println("Sending SMS...");
  
  //Set SMS format to ASCII
  mySerial.write("AT+CMGF=1\r\n");
  delay(1000);
  String string1="AT+CMGS=\"+91";
  string1+=phone_num;
  string1+="\"\r\n\"";
  char string1char[100];
  string1.toCharArray(string1char,100);
  
  Serial.println(string1char);
  //Send new SMS command and message number
  mySerial.write(string1char);
  delay(2000);
  String message1= message;
  char messagechar[100];
  message1.toCharArray(messagechar,100);
  //Send SMS content
  mySerial.write(messagechar);
  delay(2000);
  
  //Send Ctrl+Z / ESC to denote SMS message is complete
  mySerial.write((char)26);
  delay(1000);
    
  Serial.println("SMS Sent!");
mySerial.write("AT+CMGD=4\r\n");

  Serial.println("The message intruder presence sent");
  Serial.println("SMS Sent!done\n");
  delay(1000);
  
}




void loop() {
  // put your main code here, to run repeatedly:
  int x=analogRead(x_axis);
  delay(1);
  int y=analogRead(y_axis);
  delay(1);
  int z=analogRead(y_axis);
  delay(1);
  Serial.print("X-axis ");
  Serial.print(x);
  Serial.print("\t");
  Serial.print("Y-axis ");
  Serial.print(y);
  Serial.print("\t");
  Serial.print("Z-axis ");
  Serial.print(z);
  Serial.print("\n");


    bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      char c = ss.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("LAT=");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" LON=");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial.print(" SAT=");
    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial.print(" PREC=");
    Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
  }

String response;
boolean activeCall = true;


  if(x<300||x>400||y<300||y>400||z<300||z>400)
  {
digitalWrite(Buzz,HIGH);


 activeCall=true; 
       if (activeCall){
      
      if (millis() - callActiveSince > 1000){
      
          makeAcall(alertNumber);
          makeAcall(alertNumber);
           makeAcall(alertNumber);
           makeAcall(alertNumber);
          Serial.println("hi ra");
        
         
          

  }
       }
//if(!newData)
//{
  String phone_num1 ="7780107612";
       
       char phone_num1char[14];
       phone_num1.toCharArray(phone_num1char,13);
    String message1="Hey kanchana,\nhttps://www.google.co.in/maps/@17.3908,78.3196113,17z\nregards WheelChair";
   
        char message1char[100];
        
        message1.toCharArray(message1char,100);
        
      sms(phone_num1,message1char);
        
        delay(2000);
 message1="https://www.google.co.in/maps/@17.3908,78.3196113,17z";
 message1.toCharArray(message1char,100);
sms(phone_num1,message1char);
delay(2000);
//}
//  
 
//       else
//       {
//        String phone_num1 ="7780107612";
//       
//       char phone_num1char[14];
//       phone_num1.toCharArray(phone_num1char,13);
//    String message1="Hey kanchana,\nI The person in the wheel chair is in EMERGENCY , his locations is in https://www.google.co.in/maps/place/";
//    message1+=TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6;
//    message1+=',';
//    message1+=TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6;
//        char message1char[100];
//        
//        message1.toCharArray(message1char,100);
//        
//        sms(phone_num1,message1char);
//        
//        delay(2000);
//newData=false;
//       } 
      
  

        for(int i=1;i<10;i++)
       {
 
      
        digitalWrite(Buzz,HIGH);
        delay(1000);
        digitalWrite(Buzz,LOW);
        delay(1000);
       }
       

  
  }

  else
  {
    digitalWrite(Buzz,LOW);
  }
}
 
