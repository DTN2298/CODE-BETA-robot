#define encoder0PinAL  2
#define encoder0PinBL  4
#define encoder0PinAR  18
#define encoder0PinBR  5
#include <Wire.h>
#include <SPI.h>
// RFID variable
const int SSPin = 53;  // Slave Select pin
const int IRQPin = 49;  // Sends wake-up pulse
byte TXBuffer[40];    // transmit buffer
byte RXBuffer[40];    // receive buffer
byte NFCReady = 0;  // used to track NFC state
byte Data=0;
String var_code ="";
byte Memory_Block = 0;
byte k1 = 0;
String tag_tam="";

const byte SlaveDeviceId = 1;
long encoder0PosL = 0;
long encoder0PosR = 0;
float SpeedLeft =0; 
float PulseLeft =0; 
float SpeedRight=0;
float PulseRight=0;
float xRobot=0;
float yRobot=0;
float xRobot1=0;
float yRobot1=0;
float Angle=0;
float goc=0;
float goc1=0;
float SpeedRobot=0;
byte a;
String s1;
char data[]="12345678901234567890123456789012";
char datareceive[]="12345678901234567890123456789012";
int tt=0;
byte k = 0;
byte k3 = 0;
String inputString3="";
String temp = "";
String temp3 = "";
String inputString = "";

uint8_t Data_uart[50];
uint8_t data_uart;
void setup() 
{
  pinMode(encoder0PinAL, INPUT); 
  digitalWrite(encoder0PinAL, HIGH);       // turn on pullup resistor
  pinMode(encoder0PinBL, INPUT); 
  digitalWrite(encoder0PinBL, HIGH);       // turn on pullup resistor
  pinMode(encoder0PinAR, INPUT); 
  digitalWrite(encoder0PinAR, HIGH);       // turn on pullup resistor
  pinMode(encoder0PinBR, INPUT); 
  digitalWrite(encoder0PinBR, HIGH);       // turn on pullup resistor
  attachInterrupt(0, doEncoderL, CHANGE);  // encoder pin on interrupt 0 - pin 2
  attachInterrupt(5, doEncoderR, CHANGE);  // encoder pin on interrupt 1 - pin 18
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 63036;            // preload timer 65536-16MHz/256/2Hz
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();              // enable all interrupts
  Serial.begin(115200);  
  Serial3.begin(9600);

  
// RFID init
    pinMode(IRQPin, OUTPUT);
    digitalWrite(IRQPin, HIGH); // Wake up pulse
    pinMode(SSPin, OUTPUT);
    digitalWrite(SSPin, HIGH);
    SPI.begin();
    SPI.setDataMode(SPI_MODE0);
    SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV32);
    delay(10);                      // send a wake up
    digitalWrite(IRQPin, LOW);      // pulse to put the 
    delayMicroseconds(100);         // BM019 into SPI
    digitalWrite(IRQPin, HIGH);     // mode 
    delay(10);
    pinMode(48, OUTPUT);

    //SetProtocol_Command(); // ISO 15693 settings
    //delay(1000);
  
}
void serialEvent3()
{
            char  data3="";
            data3 = (char)Serial3.read();
          if (data3 == 'J') // chuoi A & "van toc trai" & "chieu trai" & B // max 148+ 0 or 1
            { k3=1;inputString3="";}
          else if(data3 =='Q')
            {k3=0;   temp3= inputString3.substring(1);  xRobot=temp3.toInt();data3="";}
          else if (data3 == 'W') 
            {k3=0;   temp3= inputString3.substring(1);  yRobot=temp3.toInt();data3="";}
          else if (data3 == 'I') 
            {k3=0;   temp3= inputString3.substring(1);  Angle=(temp3.toInt())*PI/180;data3="";}
          if (k3==1)
           { inputString3 += data3; } 
}
void loop()
{
  //digitalWrite(48, LOW);
//  if(NFCReady == 0)
//  {
//    //IDN_Command();  // reads the CR95HF ID
//    //delay(2000);
////    SetProtocol_Command(); // ISO 15693 settings
////    delay(1000);
//  }
//  else
//  {
////     delay(10);                      // send a wake up
////    digitalWrite(IRQPin, LOW);      // pulse to put the 
////    delayMicroseconds(100);         // BM019 into SPI
////    digitalWrite(IRQPin, HIGH);     // mode 
////    delay(10);
//    Inventory_Command();
//    delay(10);
//
//    if (var_code =="4e1ec642d4")
//  {Serial.println("Tag 1");}
//    if (var_code =="b6f904960")
//  {Serial.println("Tag 2");}
//    if (var_code =="841ec8d684")
//  {Serial.println("Tag 3");}
//    if (var_code =="731e699094")
//  {Serial.println("Tag 4");xRobot = 1000; yRobot=1000;}
//    if (var_code =="91e3ae9c4")
//  {Serial.println("Tag 5");}
//  //Serial.println(var_code);
//  
//    for (k1 = 0; k1<40;k1++)
//    {RXBuffer[k1]=0;}
//  } 
  
//  if(tag_tam != var_code)
//  //if( var_code.length() > 8)
//  {   
//      Serial.println(var_code);
//      digitalWrite(48, HIGH);
//      tag_tam = var_code;
//      delay(50); 
//  }
  if(tt==7)
  {
    Serial3.println("A"+String(xRobot)+"QA"+String(yRobot)+"WA"+String((goc*180/PI)*100)+"Eo"); 
    //Serial.println(String(xRobot)+","+String(yRobot)+","+String((goc*180/PI)*100)); 
   //Serial3.println("o");
  tt=0;
    if(NFCReady == 1)
    {
      Inventory_Command();
        if (var_code =="4e1ec642d4")
      {xRobot = 1000; yRobot=1000;}
        else if (var_code =="b6f904960")
      {xRobot = 2000; yRobot=2000;}
        else if (var_code =="841ec8d684")
      {xRobot = 3000; yRobot=3000;}
        else if (var_code =="731e699094")
      {xRobot = 4000; yRobot=4000;}
        else if (var_code =="91e3ae9c4")
      {xRobot = 5000; yRobot=5000;}
       for (k1 = 0; k1<40;k1++){RXBuffer[k1]=0;}         
    }
  }
}
// Nhan data I2C
void doEncoderL() {
  
  if (digitalRead(encoder0PinAL) == digitalRead(encoder0PinBL)) {
    encoder0PosL--;
    PulseLeft--;   
  } 
  else {
    encoder0PosL++;
    PulseLeft++;
  }
}

void doEncoderR() {
  
  if (digitalRead(encoder0PinAR) == digitalRead(encoder0PinBR)) {
    encoder0PosR--;
    PulseRight--;
  } 
  else {
    encoder0PosR++;
    PulseRight++;
  }  
}

ISR(TIMER1_OVF_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
      TCNT1 = 63036;           // preload timer
      tt++;
//(PulseLeft *(2*PI*radiusWheel))/(rateTransmit*pulseEncoder);
//    SpeedLeft = (PulseLeft/2160.0)*PI*100.0;    
//    SpeedRight = (PulseRight/2160.0)*PI*100.0;
// Gear_ratio = 55; Pulse encoder = 13 => 715xung/vong=> 1 xung ~ 2*PI/715 = 0.0081 rad.
// t = 0.04s; => w = (Pulse * 0.0081)/t(rad/s)=> v = r.w = Pulse*0.0081*(72.5/1000)/0.04 = Pulse*((2*Pi)/(PusleEncoder*Gear_ratio))*r/t;
      SpeedLeft = PulseLeft*2*(PI/775.0)*72.5;
     SpeedRight = PulseRight*2*(PI/775.0)*72.5;  
     Angle=Angle+((SpeedRight-SpeedLeft)/270.0);
     
      if(Angle>2*PI)
      {Angle=Angle-2*PI;}
      if(Angle<0)
      { Angle=2*PI+Angle;}
      if(Angle<PI)
      {goc=Angle;}
      else
      {goc=Angle-2*PI; }
      SpeedRobot = (SpeedLeft + SpeedRight)/2;
      xRobot += SpeedRobot * cos(Angle);
      yRobot += SpeedRobot * sin(Angle);
      PulseLeft = 0;
      PulseRight = 0;
}

void IDN_Command()
 {
  
 byte i = 0;

// step 1 send the command
  digitalWrite(SSPin, LOW);
  SPI.transfer(0);  // SPI control byte to send command to CR95HF
  SPI.transfer(1);  // IDN command
  SPI.transfer(0);  // length of data that follows is 0
  digitalWrite(SSPin, HIGH);
  delay(1);
 
// step 2, poll for data ready
// data is ready when a read byte
// has bit 3 set (ex:  B'0000 1000')

  digitalWrite(SSPin, LOW);
  while(RXBuffer[0] != 8)
    {
    RXBuffer[0] = SPI.transfer(0x03);  // Write 3 until
    RXBuffer[0] = RXBuffer[0] & 0x08;  // bit 3 is set
    }
  digitalWrite(SSPin, HIGH);
  delay(1);


// step 3, read the data
  digitalWrite(SSPin, LOW);
  SPI.transfer(0x02);   // SPI control byte for read         
  RXBuffer[0] = SPI.transfer(0);  // response code
  RXBuffer[1] = SPI.transfer(0);  // length of data
  for (i=0;i<RXBuffer[1];i++)      
      RXBuffer[i+2]=SPI.transfer(0);  // data
  digitalWrite(SSPin, HIGH);
  delay(1);

  if ((RXBuffer[0] == 0) & (RXBuffer[1] == 15))
  {  
    Serial.println("IDN COMMAND-");  //
    Serial.print("RESPONSE CODE: ");
    Serial.print(RXBuffer[0]);
    Serial.print(" LENGTH: ");
    Serial.println(RXBuffer[1]);
    Serial.print("DEVICE ID: ");
    for(i=2;i<(RXBuffer[1]);i++)
    {
      Serial.print(RXBuffer[i],HEX);
      Serial.print(" ");
    }
    Serial.println(" ");
    Serial.print("ROM CRC: ");
    Serial.print(RXBuffer[RXBuffer[1]],HEX);
    Serial.print(RXBuffer[RXBuffer[1]+1],HEX);
    Serial.println(" ");
  }
  else
    Serial.println("BAD RESPONSE TO IDN COMMAND!");
  Serial.println(" ");
}

void SetProtocol_Command()
 {
 byte i = 0;
 
// step 1 send the command
  digitalWrite(SSPin, LOW);
  SPI.transfer(0x00);  // SPI control byte to send command to CR95HF
  SPI.transfer(0x02);  // Set protocol command
  SPI.transfer(0x02);  // length of data to follow
//  SPI.transfer(0x03);  // code for ISO/IEC 15693
  SPI.transfer(0x02);  // code for ISO/IEC 1443A
  SPI.transfer(0x00);// Parameter of ISO/IEC 1443A is 106kbps
//  SPI.transfer(0x0D);  // Wait for SOF, 10% modulation, append CRC
  digitalWrite(SSPin, HIGH);
  delay(1);
 
// step 2, poll for data ready

  digitalWrite(SSPin, LOW);
  while(RXBuffer[0] != 8)
    {
    RXBuffer[0] = SPI.transfer(0x03);  // Write 3 until
    RXBuffer[0] = RXBuffer[0] & 0x08;  // bit 3 is set
    }
  digitalWrite(SSPin, HIGH);
  delay(1);

// step 3, read the data
  digitalWrite(SSPin, LOW);
  SPI.transfer(0x02);   // SPI control byte for read         
  RXBuffer[0] = SPI.transfer(0);  // response code
  RXBuffer[1] = SPI.transfer(0);  // length of data
  digitalWrite(SSPin, HIGH);
//Serial.print(RXBuffer[0],HEX);
//Serial.print(" ");
//Serial.print(RXBuffer[1],HEX);
  if ((RXBuffer[0] == 0) & (RXBuffer[1] == 0))
  {
    NFCReady = 1; // NFC is ready
     Serial.println("PROTOCOL SET OK");  //  
  }
  else
  {
     Serial.println("BAD RESPONSE TO SET PROTOCOL");
     NFCReady = 0; // NFC not ready
  }
  Serial.println(" ");
}
void Inventory_Command()
 {
 byte i = 0;
// step 1 send the command
  digitalWrite(SSPin, LOW);
  SPI.transfer(0x00);  // SPI control byte to send command to CR95HF
  SPI.transfer(0x04);  // Send Receive CR95HF command
  SPI.transfer(0x02);  // length of data that follows is 2
  SPI.transfer(0x26); // Inventory Command for ISO/IEC 14443A
  SPI.transfer(0x07);
  digitalWrite(SSPin, HIGH);
  delay(1);
// step 2, poll for data ready
// data is ready when a read byte
// has bit 3 set (ex:  B'0000 1000')
  digitalWrite(SSPin, LOW);
  while(RXBuffer[0] != 8)
    {
    RXBuffer[0] = SPI.transfer(0x03);  // Write 3 until
    RXBuffer[0] = RXBuffer[0] & 0x08;  // bit 3 is set
    }
  digitalWrite(SSPin, HIGH);
  delay(1);
// step 3, read the data
  digitalWrite(SSPin, LOW);
  SPI.transfer(0x02);   // SPI control byte for read         
  RXBuffer[0] = SPI.transfer(0);  // response code
  RXBuffer[1] = SPI.transfer(0);  // length of data
  for (i=0;i<RXBuffer[1];i++)      
      RXBuffer[i+2]=SPI.transfer(0);  // data
  digitalWrite(SSPin, HIGH);
  delay(1);
  if (RXBuffer[0] == 128)
  {  
    for(i=16;i>=4;i--)
    {}
  }
  else
    {}
/////////
// step 1 send the command
  digitalWrite(SSPin, LOW);
  SPI.transfer(0x00);  // SPI control byte to send command to CR95HF
  SPI.transfer(0x04);  // Send Receive CR95HF command
  SPI.transfer(0x03);  // length of data that follows is 3
  SPI.transfer(0x93); // See data sheet CR95HF
  SPI.transfer(0x20);
  SPI.transfer(0x08);
  digitalWrite(SSPin, HIGH);
  delay(1);
// step 2, poll for data ready
// data is ready when a read byte
// has bit 3 set (ex:  B'0000 1000')
  digitalWrite(SSPin, LOW);
  while(RXBuffer[0] != 8)
    {
    RXBuffer[0] = SPI.transfer(0x03);  // Write 3 until
    RXBuffer[0] = RXBuffer[0] & 0x08;  // bit 3 is set
    }
  digitalWrite(SSPin, HIGH);
  delay(1);
// step 3, read the data
  digitalWrite(SSPin, LOW);
  SPI.transfer(0x02);   // SPI control byte for read         
  RXBuffer[0] = SPI.transfer(0);  // response code
  RXBuffer[1] = SPI.transfer(0);  // length of data
  for (i=0;i<RXBuffer[1];i++)      
      RXBuffer[i+2]=SPI.transfer(0);  // data
  digitalWrite(SSPin, HIGH);
  delay(1);
  if (RXBuffer[0] == 128)
  { for(i=6;i>=2;i--)
    { var_code = var_code + String(RXBuffer[i],HEX);}
  }
  else
    {var_code = ""; }
}














