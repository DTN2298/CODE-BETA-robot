#include <SimpleTimer.h>
#include <IRremote.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#define button_pin  18
SoftwareSerial mySerial(12, 13);
//#include <TimerOne.h>
//#include <TimerThree.h>
const int receiverPin = 2; // chân digital 8 dùng để đọc tín hiệu
IRrecv irrecv(receiverPin); // tạo đối tượng IRrecv mới
decode_results results;// lưu giữ kết quả giải mã tín 
SimpleTimer timer;
int button_value = 0;
byte count_timer;
int timerId;
bool pose_flag;
int angle_dock;
byte kk = 0;byte kkk;byte iii;
byte count_point = 0; 
unsigned int count_not_obs;
char rece_uart[300];
uint16_t dem_uart=0;
int count_obs;
byte num_point=1;
String tempi2c="";String temp2uno="";
unsigned int tick;
String path_string="";
String inputStringi2c="";
int Dist_path;
bool IsI2C = true;bool isPath= false;bool Sensor_enable = false;bool reach_goal = false;bool isfinish_path = false;bool serial_flag = false;bool isObs;bool sent_f_one_time;
bool mode_autocharge;
String s1;
const byte SlaveDeviceId = 1;
int count;int ii;int jj;
//float vtt1;
//float vtp1;
int tempSe1;int tempSe2;int tempSe3;int tempSe4;int tempSe5;int tempSe6;int tempSe7;
int buff_sen1;int buff_sen2; int buff_sen3;int buff_sen4;
char data[]="12345678901234567890123456789012";char dataSent[]="12345678901234567890123456789012";
int path_array[100];
int x_path[20];
int y_path[20];
int theta_path[20];
char xx[100];
char data1;
int timer_stop;
String path;
byte k;byte k3;byte manual;bool enable =false;
String temp="";   String temp3="";     
int xRobot = 0;int yRobot = 0;
float AngleRobot;float AngleRobot_Goal ;  
int xObject = 0;int yObject=0 ;
int xValue;int yValue;
int Dist;
float AngleGoal = 0;// Direction if Robot at Goal location
float Angle;  
float DeltaStart; float DeltaGoal; float TangentialSpeed;
float AngularSpeed;
float LeftSpeed;float RightSpeed;
//float LinearVelocity;float TurnVelocity;
int tt;
String inputString="";String inputString3="";String inputString_path="";
// Variable of Fuzzy avoid Collision
const int trig1 = A0;const int trig2 = A1;const int trig3 = A2;const int trig4 = A3;const int trig5 = A5;const int trig6 = A4;const int echo = 7;const byte S0= 8;const byte S1=9;const byte S2= 10;
unsigned long duration;//biến đo thời gian
int distance;//biến lưu khoảng cách
int Se1; int Se2;int Se3;int Se4;
   // ******* Calculate Distance of Collison   
      int distance_func(int trig){    /* Creat Pulse for Trig Pin*/
            digitalWrite(trig,LOW);delayMicroseconds(2);
            digitalWrite(trig,HIGH);delayMicroseconds(10);
            digitalWrite(trig,LOW);
            // Calculate Distance
            duration = pulseIn(echo,HIGH,10000);//đo độ rộng xung HIGH ở chân echo.
            distance = int(duration/2/29.412);//tính khoảng cách đến vật.
            if (distance==0)
              {distance = 100;}
              else if (distance > 100)
              {distance = 100;}            
            return distance;
          } 
          
      void read_IR(){
  if (irrecv.decode(&results)) // nếu nhận được tín hiệu
  {  translateIR();
  Serial.println(String(angle_dock));
  irrecv.resume();}
  }
      void translateIR() {
        switch(results.value)
        {
          case 0x10:   
                      angle_dock = 2;//Mid Right
                      break;
          case 0x20: 
                      angle_dock = -1; // Mid left
                      break;
          case 0x30: 
                      angle_dock = -2; // Left
                      break;
         case 0x40: 
                      angle_dock = 1;//Mid Right
                      break;
          default:
                    break;                   
        }
      }
      void checkObstacle(){
            
          
          if(( buff_sen1>40)&&( buff_sen2>50)&&( buff_sen3>50)&&( buff_sen4>40))
          {
            enable = true;go();count_obs = 0;timer.disable(timerId);
            Serial.println("i,i");
          }
          else
          {
            enable = false; go();count_obs = 0;timer.restartTimer(timerId); timer.enable(timerId);
            Serial.println("o,o");
            }
//        timer.disable(timerId);
//        if(buff_sen1 <30)
//        {Serial.println("R,"+String(buff_sen1));delay(1);}
//        if(buff_sen2 <40)
//        {Serial.println("T,"+String(buff_sen2));delay(1);}
//        if(buff_sen3 <40)
//        {Serial.println("Y,"+String(buff_sen3));delay(1);}
//        if(buff_sen4 <30)
//        {Serial.println("U,"+String(buff_sen4));delay(1);}
//        if((buff_sen1 >40) && (buff_sen2 >50)&&(buff_sen3 >50)&&(buff_sen4 >40) )
//        {enable = true;go(); count_obs = 0;}
//        buff_sen1 =buff_sen2 =buff_sen3 =buff_sen4 =100;

//        fuzzy3->setInput(2,1);
//        fuzzy3->fuzzify();
//        LeftSpeed = fuzzy3->defuzzify(4);
//        RightSpeed = fuzzy3->defuzzify(5);
//        Serial.println(String(angle_dock)+"||"+String(LeftSpeed)+"||"+String(RightSpeed));
      }    
  void push_button()
  {
//    button_value ++;
//    Serial.println(String(button_value));
//    enable = false;
//    go();
    }
      // Set up Fuzzy
      #include "FuzzyRule.h";
      #include <FuzzyComposition.h>;
      #include <Fuzzy.h>;
      #include <FuzzyRuleConsequent.h>;
      #include <FuzzyOutput.h>;
      #include <FuzzyInput.h>;
      #include <FuzzyIO.h>;
      #include <FuzzySet.h>;
      #include <FuzzyRuleAntecedent.h>;
//      FuzzyInit();
      Fuzzy* fuzzy1 = new Fuzzy();
      Fuzzy* fuzzy2 = new Fuzzy();
      Fuzzy* fuzzy3 = new Fuzzy();
      // Input Fuzzy 1
      FuzzySet* Zero = new FuzzySet(0,70,70,120);
      FuzzySet* Near = new FuzzySet(70,100,100,150);
      FuzzySet* Far = new FuzzySet(130,300,20000,20000);
       
      FuzzySet* StartAngle_Left = new FuzzySet(-180,-180,-60,-30);
      FuzzySet* StartAngle_MidLeft = new FuzzySet(-60,-30,-30,0);
      FuzzySet* StartAngle_Zero = new FuzzySet(-10,0,0,10);
      FuzzySet* StartAngle_MidRight = new FuzzySet(0,30,30,60);
      FuzzySet* StartAngle_Right = new FuzzySet(30,60,180,180);
      
      FuzzySet* GoalAngle_Left = new FuzzySet(-180,-180,-60,-30);
      FuzzySet* GoalAngle_MidLeft = new FuzzySet(-60,-30,-30,0);
      FuzzySet* GoalAngle_Zero = new FuzzySet(-10,0,0,10);
      FuzzySet* GoalAngle_MidRight = new FuzzySet(0,30,30,60);
      FuzzySet* GoalAngle_Right = new FuzzySet(30,60,180,180);
      // Input Fuzzy 2
      FuzzySet* Left = new FuzzySet(-180,-180,-15,-7);
      FuzzySet* Mid = new FuzzySet(-10, 0, 0, 10);
      FuzzySet* Right = new FuzzySet(7,15,180,180);
      //Input Fuzzy 3
      FuzzySet*Dock_Left = new FuzzySet(-2,-2,-2,-1);
      FuzzySet*Dock_MidLeft = new FuzzySet(-2,-1,-1,0);
      FuzzySet*Dock_MidRight = new FuzzySet(0,1,1,2);
      FuzzySet*Dock_Right = new FuzzySet(1,2,2,2);      
      // Fuzzy1 Output variable         
      FuzzySet* SpeedLeft_BackFast = new FuzzySet(-45,-45,-35,-25); // mm/s
      FuzzySet* SpeedLeft_BackSlow = new FuzzySet(-35,-25,-25,-5);
      FuzzySet* SpeedLeft_Zero = new FuzzySet(-10,0,0,10);
      FuzzySet* SpeedLeft_FowSlow = new FuzzySet(5,25,25,35);
      FuzzySet* SpeedLeft_FowMidFast = new FuzzySet(25,35,35,45);
      FuzzySet* SpeedLeft_FowFast = new FuzzySet(35, 45,70,70);
      
      FuzzySet* SpeedRight_BackFast = new FuzzySet(-45,-45,-35,-25); // mm/s
      FuzzySet* SpeedRight_BackSlow = new FuzzySet(-35,-25,-25,-5);
      FuzzySet* SpeedRight_Zero = new FuzzySet(-10,0,0,10);
      FuzzySet* SpeedRight_FowSlow = new FuzzySet(5,25,25,35);
      FuzzySet* SpeedRight_FowMidFast = new FuzzySet(25,35,35,45);
      FuzzySet* SpeedRight_FowFast = new FuzzySet(35,45,70,70);
// Recover
//      FuzzySet* SpeedRight_BackFast = new FuzzySet(-35,-35,-25,-15); // mm/s
//      FuzzySet* SpeedRight_BackSlow = new FuzzySet(-25,-15,-15,-5);
//      FuzzySet* SpeedRight_Zero = new FuzzySet(-10,0,0,10);
//      FuzzySet* SpeedRight_FowSlow = new FuzzySet(5, 15,15, 25);
//      FuzzySet* SpeedRight_FowMidFast = new FuzzySet(15,25,25,35);
//      FuzzySet* SpeedRight_FowFast = new FuzzySet(25,35,70,70);
////------------------------------------------   
      // Fuzzy2 Output variable (degree/s)
        
      FuzzySet* TurnLeft2 = new FuzzySet(-20,-20,-10,0);
      FuzzySet* Turn_Zero2 = new FuzzySet(-8,0,0,8);
      FuzzySet* TurnRight2 = new FuzzySet(0,10,20,20);
      //Fuzzy3 Output Variable    
      FuzzySet* SpeedLeft_BackVeryFast_Dock = new FuzzySet(-35,-25,-25,-20);  
      FuzzySet* SpeedLeft_BackFast_Dock = new FuzzySet(-35,-25,-25,-20);
      FuzzySet* SpeedLeft_BackSlow_Dock = new FuzzySet(-10,-8,-8,0);
      FuzzySet* SpeedLeft_Zero_Dock = new FuzzySet(-5,0,0,5);
      FuzzySet* SpeedLeft_FowSlow_Dock = new FuzzySet(0,15,15,25);
      
      FuzzySet* SpeedRight_BackVeryFast_Dock = new FuzzySet(-35,-25,-25,-20);
      FuzzySet* SpeedRight_BackFast_Dock = new FuzzySet(-35,-25,-25,-20);
      FuzzySet* SpeedRight_BackSlow_Dock = new FuzzySet(-10,-8,-8,0);
      FuzzySet* SpeedRight_Zero_Dock = new FuzzySet(-5,0,0,-5);
      FuzzySet* SpeedRight_FowSlow_Dock = new FuzzySet(0,15,15,25);
      
      void serialEvent(){  
        while (Serial.available()) {                 
          char data = (char)Serial.read();  
          if (data == 'A') // chuoi A & "van toc trai" & "chieu trai" & B // max 148+ 0 or 1
            { k=1;inputString="";}
          if (data == 'B') // chuoi A & "van toc trai" & "chieu trai" & B // max 148+ 0 or 1
            { k=1; inputString="";}
          else if(data =='E')
            {k=0;   temp= inputString.substring(1);  xObject=temp.toInt();}
          else if (data == 'F') 
            {k=0;   temp= inputString.substring(1);  yObject=temp.toInt();}
          else if (data == 'G') 
            {k=0;   temp= inputString.substring(1);  AngleGoal=temp.toInt();}   
          else if (data =='c')
           { serial_flag = true; }
          else if (data =='v')
           { serial_flag = false; }
          else if (data =='b')
           { mode_autocharge = true; delay(100);}
          else if (data =='n')
           { mode_autocharge = false;pose_flag ==true;delay(100);}               
          else if (data =='r')
           { enable = true;go(); }
          else if (data=='s')
           { enable = false;go();}
          else if (data == 'w')
           {enable = false;manual =1;go();}
          else if (data == 'z')
           { enable = false; manual =2;go();}
          else if (data == 'a')
           { enable = false; manual =3;go();}
          else if (data == 'd')
           {enable = false; manual =4;go();}
          else if (data == 'q')
           {enable = false; manual =0;go();}
          else if (data =='O')
           { k = 1;      inputString = ""; }
          else if (data=='S')
           { k = 0;      temp2uno = inputString.substring(1);} 
          else if (data=='H')
           { k = 0; path_string = inputString.substring(1); isPath=true ;Sensor_enable = true; Dist_path=0; num_point=1;reach_goal =false;isfinish_path = false;sent_f_one_time = true;}
          else if (data == 'x')
           {             isPath=false ;Sensor_enable = false; Dist_path=0; num_point=1;reach_goal =false;isfinish_path = false;serial_flag == false; }
          else if  (data == 't')   { resetPosition(); xValue=0; yValue=0;yObject=0; xObject=0; Dist=0;}
          if (k==1)
           { inputString += data; }
         }
      }  

        void serialEvent3(){  
        while (Serial3.available()) 
                  {
           char data3 = (char)Serial3.read(); 
          if (data3 == 'A') // chuoi A & "van toc trai" & "chieu trai" & B // max 148+ 0 or 1
            { k3=1;inputString3="";}
          else if(data3 =='Q')
            {k3=0;   temp3= inputString3.substring(1);  xRobot=temp3.toInt();}
          else if (data3 == 'W') 
            {k3=0;   temp3= inputString3.substring(1);  yRobot=temp3.toInt();}
          else if (data3 == 'E') 
            {k3=0;   temp3= inputString3.substring(1);  AngleRobot=temp3.toFloat()/100;}
           else if(data3 =='o')
            {pose_flag = true; }
          if (k3==1)
           { inputString3 += data3; } 
                    }
                  }  
      void setup(){
                // Set up MCU
                irrecv.enableIRIn(); // start the IR receiver
                Serial.begin(115200);
                Serial3.begin(9600);
                mySerial.begin(19200);
                mySerial.println("#2R");
                pinMode(trig1,OUTPUT);//chân trig sẽ phát tín hiệu
                pinMode(trig2,OUTPUT);//chân trig sẽ phát tín hiệu
                pinMode(trig3,OUTPUT);//chân trig sẽ phát tín hiệu
                pinMode(trig4,OUTPUT);//chân trig sẽ phát tín hiệu
                pinMode(trig5,OUTPUT);//chân trig sẽ phát tín hiệu
                pinMode(trig6,OUTPUT);//chân trig sẽ phát tín hiệu
                pinMode(echo,INPUT);//chân echo sẽ nhận tín hiệu
                pinMode(button_pin, INPUT); 
                //digitalWrite(button_pin, HIGH); 
                //attachInterrupt(5, push_button, FALLING);
                //noInterrupts();
                //interrupts();  
                pinMode(S0,OUTPUT);
                pinMode(S1,OUTPUT);
                pinMode(S2,OUTPUT);
                timerId = timer.setInterval(3000,checkObstacle);
                //timer.enable(timerId); 
                timer.disable(timerId);  
                interrupts();           
//                Wire.begin(1); 
//                Wire.begin(SlaveDeviceId); 
//                Wire.onReceive(receiveEvent);
//                Wire.onRequest(requestCallback);
         // -------------------------------------------
         // Init Input Fuzzy1
         FuzzyInput* Dist = new FuzzyInput(7);
           Dist->addFuzzySet(Zero);
           Dist->addFuzzySet(Near); 
           Dist->addFuzzySet(Far); 
         fuzzy1->addFuzzyInput(Dist);
         
         FuzzyInput* StartAngle = new FuzzyInput(8);    
           StartAngle->addFuzzySet(StartAngle_Left);
           StartAngle->addFuzzySet(StartAngle_MidLeft);
           StartAngle->addFuzzySet(StartAngle_Zero);
           StartAngle->addFuzzySet(StartAngle_MidRight);
           StartAngle->addFuzzySet(StartAngle_Right);
         fuzzy1->addFuzzyInput(StartAngle);
         
         FuzzyInput* GoalAngle = new FuzzyInput(9);    
           GoalAngle->addFuzzySet(GoalAngle_Left);
           GoalAngle->addFuzzySet(GoalAngle_MidLeft);
           GoalAngle->addFuzzySet(GoalAngle_Zero);
           GoalAngle->addFuzzySet(GoalAngle_MidRight);
           GoalAngle->addFuzzySet(GoalAngle_Right);
         fuzzy1->addFuzzyInput(GoalAngle);
         
          // Init Input Fuzzy2
         FuzzyInput* Angle_robot = new FuzzyInput(1);
           Angle_robot->addFuzzySet(Left); 
           Angle_robot->addFuzzySet(Mid); 
           Angle_robot->addFuzzySet(Right);
         fuzzy2->addFuzzyInput(Angle_robot);      
         // Init Intput Fuzzy3
         FuzzyInput* Angle_Dock = new FuzzyInput(2);
         Angle_Dock -> addFuzzySet(Dock_Left);
         Angle_Dock -> addFuzzySet(Dock_MidLeft);
         Angle_Dock -> addFuzzySet(Dock_MidRight);
         Angle_Dock -> addFuzzySet(Dock_Right);
         fuzzy3->addFuzzyInput(Angle_Dock);
         
         //Creat Output Fuzzy 1
         FuzzyOutput* LeftSpeedFuzzy = new FuzzyOutput(1); 
           LeftSpeedFuzzy->addFuzzySet(SpeedLeft_BackFast);
           LeftSpeedFuzzy->addFuzzySet(SpeedLeft_BackSlow);
           LeftSpeedFuzzy->addFuzzySet(SpeedLeft_Zero);
           LeftSpeedFuzzy->addFuzzySet(SpeedLeft_FowSlow);
           LeftSpeedFuzzy->addFuzzySet(SpeedLeft_FowMidFast);
           LeftSpeedFuzzy->addFuzzySet(SpeedLeft_FowFast);
         fuzzy1->addFuzzyOutput(LeftSpeedFuzzy);
         
         FuzzyOutput* RightSpeedFuzzy = new FuzzyOutput(2); 
           RightSpeedFuzzy->addFuzzySet(SpeedRight_BackFast);
           RightSpeedFuzzy->addFuzzySet(SpeedRight_BackSlow);
           RightSpeedFuzzy->addFuzzySet(SpeedRight_Zero);
           RightSpeedFuzzy->addFuzzySet(SpeedRight_FowSlow);
           RightSpeedFuzzy->addFuzzySet(SpeedRight_FowMidFast);
           RightSpeedFuzzy->addFuzzySet(SpeedRight_FowFast);
         fuzzy1->addFuzzyOutput(RightSpeedFuzzy);
        // Creat output Fuzzy 2       
         FuzzyOutput* TurnSpeed2 = new FuzzyOutput(3); 
           TurnSpeed2->addFuzzySet(TurnLeft2);
           TurnSpeed2->addFuzzySet(Turn_Zero2);
           TurnSpeed2->addFuzzySet(TurnRight2);
          fuzzy2->addFuzzyOutput(TurnSpeed2);       
          
         //Creat Output Fuzzy 3
         FuzzyOutput* LeftSpeed_Dock_Fuzzy = new FuzzyOutput(4); 
           LeftSpeed_Dock_Fuzzy->addFuzzySet(SpeedLeft_BackFast_Dock);
           LeftSpeed_Dock_Fuzzy->addFuzzySet(SpeedLeft_BackSlow_Dock);
           LeftSpeed_Dock_Fuzzy->addFuzzySet(SpeedLeft_Zero_Dock);
           LeftSpeed_Dock_Fuzzy->addFuzzySet(SpeedLeft_FowSlow_Dock);
         fuzzy3->addFuzzyOutput(LeftSpeed_Dock_Fuzzy);
         
         FuzzyOutput* RightSpeed_Dock_Fuzzy = new FuzzyOutput(5); 
           RightSpeed_Dock_Fuzzy->addFuzzySet(SpeedRight_BackFast_Dock);
           RightSpeed_Dock_Fuzzy->addFuzzySet(SpeedRight_BackSlow_Dock);
           RightSpeed_Dock_Fuzzy->addFuzzySet(SpeedRight_Zero_Dock);
           RightSpeed_Dock_Fuzzy->addFuzzySet(SpeedRight_FowSlow_Dock);
         fuzzy3->addFuzzyOutput(RightSpeed_Dock_Fuzzy);
         
          // Building Fuzzy Rule ---------------------------------------------------
// Input case
            
           FuzzyRuleAntecedent* Dis_FarSt_Left = new FuzzyRuleAntecedent();
           Dis_FarSt_Left->joinWithAND(Far,StartAngle_Left);  
           FuzzyRuleAntecedent* Dis_FarSt_MidLeft = new FuzzyRuleAntecedent();
           Dis_FarSt_MidLeft->joinWithAND(Far,StartAngle_MidLeft);  
           FuzzyRuleAntecedent* Dis_FarSt_Zero = new FuzzyRuleAntecedent();
           Dis_FarSt_Zero->joinWithAND(Far,StartAngle_Zero);
           FuzzyRuleAntecedent* Dis_FarSt_MidRight = new FuzzyRuleAntecedent();
           Dis_FarSt_MidRight->joinWithAND(Far,StartAngle_MidRight);
           FuzzyRuleAntecedent* Dis_FarSt_Right = new FuzzyRuleAntecedent();
           Dis_FarSt_Right->joinWithAND(Far,StartAngle_Right);

           FuzzyRuleAntecedent* Dis_NearSt_Left = new FuzzyRuleAntecedent();
           Dis_NearSt_Left->joinWithAND(Near,StartAngle_Left);  
           FuzzyRuleAntecedent* Dis_NearSt_Right = new FuzzyRuleAntecedent();
           Dis_NearSt_Right->joinWithAND(Near,StartAngle_Right); 
////////Trial
           FuzzyRuleAntecedent* Dis_NearGo_Left = new FuzzyRuleAntecedent();
           Dis_NearGo_Left->joinWithAND(Near,GoalAngle_Left);  
           FuzzyRuleAntecedent* Dis_NearGo_Right = new FuzzyRuleAntecedent();
           Dis_NearGo_Right->joinWithAND(Near,GoalAngle_Right);
           FuzzyRuleAntecedent* Dis_NearGo_MidLeft = new FuzzyRuleAntecedent();
           Dis_NearGo_MidLeft->joinWithAND(Near,GoalAngle_MidLeft);  
           FuzzyRuleAntecedent* Dis_NearGo_MidRight = new FuzzyRuleAntecedent();
           Dis_NearGo_MidRight->joinWithAND(Near,GoalAngle_MidRight);           
//////
           FuzzyRuleAntecedent* Dis_NearSt_MidLeft = new FuzzyRuleAntecedent();
           Dis_NearSt_MidLeft->joinWithAND(Near,StartAngle_MidLeft);  
           FuzzyRuleAntecedent* Dis_NearSt_MidRight = new FuzzyRuleAntecedent();
           Dis_NearSt_MidRight->joinWithAND(Near,StartAngle_MidRight); 
           
           FuzzyRuleAntecedent* St_LeftGo_Left = new FuzzyRuleAntecedent();
           St_LeftGo_Left->joinWithAND(StartAngle_Left,GoalAngle_Left);
           FuzzyRuleAntecedent* St_LeftGo_MidLeft = new FuzzyRuleAntecedent();
           St_LeftGo_MidLeft->joinWithAND(StartAngle_Left,GoalAngle_MidLeft);
           FuzzyRuleAntecedent* St_LeftGo_Zero = new FuzzyRuleAntecedent();
           St_LeftGo_Zero->joinWithAND(StartAngle_Left,GoalAngle_Zero);
           FuzzyRuleAntecedent* St_LeftGo_MidRight = new FuzzyRuleAntecedent();
           St_LeftGo_MidRight->joinWithAND(StartAngle_Left,GoalAngle_MidRight);
           FuzzyRuleAntecedent* St_LeftGo_Right = new FuzzyRuleAntecedent();
           St_LeftGo_Right->joinWithAND(StartAngle_Left,GoalAngle_Right);

           FuzzyRuleAntecedent* St_MidLeftGo_Left = new FuzzyRuleAntecedent();
           St_MidLeftGo_Left->joinWithAND(StartAngle_MidLeft,GoalAngle_Left);
           FuzzyRuleAntecedent* St_MidLeftGo_MidLeft = new FuzzyRuleAntecedent();
           St_MidLeftGo_MidLeft->joinWithAND(StartAngle_MidLeft,GoalAngle_MidLeft);
           FuzzyRuleAntecedent* St_MidLeftGo_Zero = new FuzzyRuleAntecedent();
           St_MidLeftGo_Zero->joinWithAND(StartAngle_MidLeft,GoalAngle_Zero);
           FuzzyRuleAntecedent* St_MidLeftGo_MidRight = new FuzzyRuleAntecedent();
           St_MidLeftGo_MidRight->joinWithAND(StartAngle_MidLeft,GoalAngle_MidRight);
           FuzzyRuleAntecedent* St_MidLeftGo_Right = new FuzzyRuleAntecedent();
           St_MidLeftGo_Right->joinWithAND(StartAngle_MidLeft,GoalAngle_Right);

           FuzzyRuleAntecedent* St_ZeroGo_Left = new FuzzyRuleAntecedent();
           St_ZeroGo_Left->joinWithAND(StartAngle_Zero,GoalAngle_Left);
           FuzzyRuleAntecedent* St_ZeroGo_MidLeft = new FuzzyRuleAntecedent();
           St_ZeroGo_MidLeft->joinWithAND(StartAngle_Zero,GoalAngle_MidLeft);
           FuzzyRuleAntecedent* St_ZeroGo_Zero = new FuzzyRuleAntecedent();
           St_ZeroGo_Zero->joinWithAND(StartAngle_Zero,GoalAngle_Zero);
           FuzzyRuleAntecedent* St_ZeroGo_MidRight = new FuzzyRuleAntecedent();
           St_ZeroGo_MidRight->joinWithAND(StartAngle_Zero,GoalAngle_MidRight);
           FuzzyRuleAntecedent* St_ZeroGo_Right = new FuzzyRuleAntecedent();
           St_ZeroGo_Right->joinWithAND(StartAngle_Zero,GoalAngle_Right);

           FuzzyRuleAntecedent* St_MidRightGo_Left = new FuzzyRuleAntecedent();
           St_MidRightGo_Left->joinWithAND(StartAngle_MidRight,GoalAngle_Left);
           FuzzyRuleAntecedent* St_MidRightGo_MidLeft = new FuzzyRuleAntecedent();
           St_MidRightGo_MidLeft->joinWithAND(StartAngle_MidRight,GoalAngle_MidLeft);
           FuzzyRuleAntecedent* St_MidRightGo_Zero = new FuzzyRuleAntecedent();
           St_MidRightGo_Zero->joinWithAND(StartAngle_MidRight,GoalAngle_Zero);
           FuzzyRuleAntecedent* St_MidRightGo_MidRight = new FuzzyRuleAntecedent();
           St_MidRightGo_MidRight->joinWithAND(StartAngle_MidRight,GoalAngle_MidRight);
           FuzzyRuleAntecedent* St_MidRightGo_Right = new FuzzyRuleAntecedent();
           St_MidRightGo_Right->joinWithAND(StartAngle_MidRight,GoalAngle_Right);

           FuzzyRuleAntecedent* St_RightGo_Left = new FuzzyRuleAntecedent();
           St_RightGo_Left->joinWithAND(StartAngle_Right,GoalAngle_Left);
           FuzzyRuleAntecedent* St_RightGo_MidLeft = new FuzzyRuleAntecedent();
           St_RightGo_MidLeft->joinWithAND(StartAngle_Right,GoalAngle_MidLeft);
           FuzzyRuleAntecedent* St_RightGo_Zero = new FuzzyRuleAntecedent();
           St_RightGo_Zero->joinWithAND(StartAngle_Right,GoalAngle_Zero);
           FuzzyRuleAntecedent* St_RightGo_MidRight = new FuzzyRuleAntecedent();
           St_RightGo_MidRight->joinWithAND(StartAngle_Right,GoalAngle_MidRight);
           FuzzyRuleAntecedent* St_RightGo_Right = new FuzzyRuleAntecedent();
           St_RightGo_Right->joinWithAND(StartAngle_Right,GoalAngle_Right);
//////////////////////////////////////////////////

           FuzzyRuleAntecedent* Dis_NearSt_LeftGo_Left = new FuzzyRuleAntecedent();
           Dis_NearSt_LeftGo_Left->joinWithAND(Near,St_LeftGo_Left);
           FuzzyRuleAntecedent* Dis_NearSt_LeftGo_MidLeft = new FuzzyRuleAntecedent();
           Dis_NearSt_LeftGo_MidLeft->joinWithAND(Near,St_LeftGo_MidLeft);
           FuzzyRuleAntecedent* Dis_NearSt_LeftGo_Zero = new FuzzyRuleAntecedent();
           Dis_NearSt_LeftGo_Zero->joinWithAND(Near,St_LeftGo_Zero);
           FuzzyRuleAntecedent* Dis_NearSt_LeftGo_MidRight = new FuzzyRuleAntecedent();
           Dis_NearSt_LeftGo_MidRight->joinWithAND(Near,St_LeftGo_MidRight);
           FuzzyRuleAntecedent* Dis_NearSt_LeftGo_Right = new FuzzyRuleAntecedent();
           Dis_NearSt_LeftGo_Right->joinWithAND(Near,St_LeftGo_Right);

           FuzzyRuleAntecedent* Dis_NearSt_MidLeftGo_Left = new FuzzyRuleAntecedent();
           Dis_NearSt_MidLeftGo_Left->joinWithAND(Near,St_MidLeftGo_Left);
           FuzzyRuleAntecedent* Dis_NearSt_MidLeftGo_MidLeft = new FuzzyRuleAntecedent();
           Dis_NearSt_MidLeftGo_MidLeft->joinWithAND(Near,St_MidLeftGo_MidLeft);
           FuzzyRuleAntecedent* Dis_NearSt_MidLeftGo_Zero = new FuzzyRuleAntecedent();
           Dis_NearSt_MidLeftGo_Zero->joinWithAND(Near,St_MidLeftGo_Zero);
           FuzzyRuleAntecedent* Dis_NearSt_MidLeftGo_MidRight = new FuzzyRuleAntecedent();
           Dis_NearSt_MidLeftGo_MidRight->joinWithAND(Near,St_MidLeftGo_MidRight);
           FuzzyRuleAntecedent* Dis_NearSt_MidLeftGo_Right = new FuzzyRuleAntecedent();
           Dis_NearSt_MidLeftGo_Right->joinWithAND(Near,St_MidLeftGo_Right);

           FuzzyRuleAntecedent* Dis_NearSt_ZeroGo_Left = new FuzzyRuleAntecedent();
           Dis_NearSt_ZeroGo_Left->joinWithAND(Near,St_ZeroGo_Left);
           FuzzyRuleAntecedent* Dis_NearSt_ZeroGo_MidLeft = new FuzzyRuleAntecedent();
           Dis_NearSt_ZeroGo_MidLeft->joinWithAND(Near,St_ZeroGo_MidLeft);
           FuzzyRuleAntecedent* Dis_NearSt_ZeroGo_Zero = new FuzzyRuleAntecedent();
           Dis_NearSt_ZeroGo_Zero->joinWithAND(Near,St_ZeroGo_Zero);
           FuzzyRuleAntecedent* Dis_NearSt_ZeroGo_MidRight = new FuzzyRuleAntecedent();
           Dis_NearSt_ZeroGo_MidRight->joinWithAND(Near,St_ZeroGo_MidRight);
           FuzzyRuleAntecedent* Dis_NearSt_ZeroGo_Right = new FuzzyRuleAntecedent();
           Dis_NearSt_ZeroGo_Right->joinWithAND(Near,St_ZeroGo_Right);

           FuzzyRuleAntecedent* Dis_NearSt_MidRightGo_Left = new FuzzyRuleAntecedent();
           Dis_NearSt_MidRightGo_Left->joinWithAND(Near,St_MidRightGo_Left);
           FuzzyRuleAntecedent* Dis_NearSt_MidRightGo_MidLeft = new FuzzyRuleAntecedent();
           Dis_NearSt_MidRightGo_MidLeft->joinWithAND(Near,St_MidRightGo_MidLeft);
           FuzzyRuleAntecedent* Dis_NearSt_MidRightGo_Zero = new FuzzyRuleAntecedent();
           Dis_NearSt_MidRightGo_Zero->joinWithAND(Near,St_MidRightGo_Zero);
           FuzzyRuleAntecedent* Dis_NearSt_MidRightGo_MidRight = new FuzzyRuleAntecedent();
           Dis_NearSt_MidRightGo_MidRight->joinWithAND(Near,St_MidRightGo_MidRight);
           FuzzyRuleAntecedent* Dis_NearSt_MidRightGo_Right = new FuzzyRuleAntecedent();
           Dis_NearSt_MidRightGo_Right->joinWithAND(Near,St_MidRightGo_Right);

           FuzzyRuleAntecedent* Dis_NearSt_RightGo_Left = new FuzzyRuleAntecedent();
           Dis_NearSt_RightGo_Left->joinWithAND(Near,St_RightGo_Left);
           FuzzyRuleAntecedent* Dis_NearSt_RightGo_MidLeft = new FuzzyRuleAntecedent();
           Dis_NearSt_RightGo_MidLeft->joinWithAND(Near,St_RightGo_MidLeft);
           FuzzyRuleAntecedent* Dis_NearSt_RightGo_Zero = new FuzzyRuleAntecedent();
           Dis_NearSt_RightGo_Zero->joinWithAND(Near,St_RightGo_Zero);
           FuzzyRuleAntecedent* Dis_NearSt_RightGo_MidRight = new FuzzyRuleAntecedent();
           Dis_NearSt_RightGo_MidRight->joinWithAND(Near,St_RightGo_MidRight);
           FuzzyRuleAntecedent* Dis_NearSt_RightGo_Right = new FuzzyRuleAntecedent();
           Dis_NearSt_RightGo_Right->joinWithAND(Near,St_RightGo_Right);
////////////////////////////
           FuzzyRuleAntecedent* Dis_ZeroSt_LeftGo_Left = new FuzzyRuleAntecedent();
           Dis_ZeroSt_LeftGo_Left->joinWithAND(Zero,St_LeftGo_Left);
           FuzzyRuleAntecedent* Dis_ZeroSt_LeftGo_MidLeft = new FuzzyRuleAntecedent();
           Dis_ZeroSt_LeftGo_MidLeft->joinWithAND(Zero,St_LeftGo_MidLeft);
           FuzzyRuleAntecedent* Dis_ZeroSt_LeftGo_Zero = new FuzzyRuleAntecedent();
           Dis_ZeroSt_LeftGo_Zero->joinWithAND(Zero,St_LeftGo_Zero);
           FuzzyRuleAntecedent* Dis_ZeroSt_LeftGo_MidRight = new FuzzyRuleAntecedent();
           Dis_ZeroSt_LeftGo_MidRight->joinWithAND(Zero,St_LeftGo_MidRight);
           FuzzyRuleAntecedent* Dis_ZeroSt_LeftGo_Right = new FuzzyRuleAntecedent();
           Dis_ZeroSt_LeftGo_Right->joinWithAND(Zero,St_LeftGo_Right);

           FuzzyRuleAntecedent* Dis_ZeroSt_MidLeftGo_Left = new FuzzyRuleAntecedent();
           Dis_ZeroSt_MidLeftGo_Left->joinWithAND(Zero,St_MidLeftGo_Left);
           FuzzyRuleAntecedent* Dis_ZeroSt_MidLeftGo_MidLeft = new FuzzyRuleAntecedent();
           Dis_ZeroSt_MidLeftGo_MidLeft->joinWithAND(Zero,St_MidLeftGo_MidLeft);
           FuzzyRuleAntecedent* Dis_ZeroSt_MidLeftGo_Zero = new FuzzyRuleAntecedent();
           Dis_ZeroSt_MidLeftGo_Zero->joinWithAND(Zero,St_MidLeftGo_Zero);
           FuzzyRuleAntecedent* Dis_ZeroSt_MidLeftGo_MidRight = new FuzzyRuleAntecedent();
           Dis_ZeroSt_MidLeftGo_MidRight->joinWithAND(Zero,St_MidLeftGo_MidRight);
           FuzzyRuleAntecedent* Dis_ZeroSt_MidLeftGo_Right = new FuzzyRuleAntecedent();
           Dis_ZeroSt_MidLeftGo_Right->joinWithAND(Zero,St_MidLeftGo_Right);

           FuzzyRuleAntecedent* Dis_ZeroSt_ZeroGo_Left = new FuzzyRuleAntecedent();
           Dis_ZeroSt_ZeroGo_Left->joinWithAND(Zero,St_ZeroGo_Left);
           FuzzyRuleAntecedent* Dis_ZeroSt_ZeroGo_MidLeft = new FuzzyRuleAntecedent();
           Dis_ZeroSt_ZeroGo_MidLeft->joinWithAND(Zero,St_ZeroGo_MidLeft);
           FuzzyRuleAntecedent* Dis_ZeroSt_ZeroGo_Zero = new FuzzyRuleAntecedent();
           Dis_ZeroSt_ZeroGo_Zero->joinWithAND(Zero,St_ZeroGo_Zero);
           FuzzyRuleAntecedent* Dis_ZeroSt_ZeroGo_MidRight = new FuzzyRuleAntecedent();
           Dis_ZeroSt_ZeroGo_MidRight->joinWithAND(Zero,St_ZeroGo_MidRight);
           FuzzyRuleAntecedent* Dis_ZeroSt_ZeroGo_Right = new FuzzyRuleAntecedent();
           Dis_ZeroSt_ZeroGo_Right->joinWithAND(Zero,St_ZeroGo_Right);

           FuzzyRuleAntecedent* Dis_ZeroSt_MidRightGo_Left = new FuzzyRuleAntecedent();
           Dis_ZeroSt_MidRightGo_Left->joinWithAND(Zero,St_MidRightGo_Left);
           FuzzyRuleAntecedent* Dis_ZeroSt_MidRightGo_MidLeft = new FuzzyRuleAntecedent();
           Dis_ZeroSt_MidRightGo_MidLeft->joinWithAND(Zero,St_MidRightGo_MidLeft);
           FuzzyRuleAntecedent* Dis_ZeroSt_MidRightGo_Zero = new FuzzyRuleAntecedent();
           Dis_ZeroSt_MidRightGo_Zero->joinWithAND(Zero,St_MidRightGo_Zero);
           FuzzyRuleAntecedent* Dis_ZeroSt_MidRightGo_MidRight = new FuzzyRuleAntecedent();
           Dis_ZeroSt_MidRightGo_MidRight->joinWithAND(Zero,St_MidRightGo_MidRight);
           FuzzyRuleAntecedent* Dis_ZeroSt_MidRightGo_Right = new FuzzyRuleAntecedent();
           Dis_ZeroSt_MidRightGo_Right->joinWithAND(Zero,St_MidRightGo_Right);

           FuzzyRuleAntecedent* Dis_ZeroSt_RightGo_Left = new FuzzyRuleAntecedent();
           Dis_ZeroSt_RightGo_Left->joinWithAND(Zero,St_RightGo_Left);
           FuzzyRuleAntecedent* Dis_ZeroSt_RightGo_MidLeft = new FuzzyRuleAntecedent();
           Dis_ZeroSt_RightGo_MidLeft->joinWithAND(Zero,St_RightGo_MidLeft);
           FuzzyRuleAntecedent* Dis_ZeroSt_RightGo_Zero = new FuzzyRuleAntecedent();
           Dis_ZeroSt_RightGo_Zero->joinWithAND(Zero,St_RightGo_Zero);
           FuzzyRuleAntecedent* Dis_ZeroSt_RightGo_MidRight = new FuzzyRuleAntecedent();
           Dis_ZeroSt_RightGo_MidRight->joinWithAND(Zero,St_RightGo_MidRight);
           FuzzyRuleAntecedent* Dis_ZeroSt_RightGo_Right = new FuzzyRuleAntecedent();
           Dis_ZeroSt_RightGo_Right->joinWithAND(Zero,St_RightGo_Right);

         // Output case  
         FuzzyRuleConsequent* thenL_BackFastR_FowMidFast = new FuzzyRuleConsequent();    
           thenL_BackFastR_FowMidFast->addOutput(SpeedLeft_BackFast);
           thenL_BackFastR_FowMidFast->addOutput(SpeedRight_FowMidFast);

         FuzzyRuleConsequent* thenL_BackSlowR_FowMidFast = new FuzzyRuleConsequent();    
           thenL_BackSlowR_FowMidFast->addOutput(SpeedLeft_BackSlow);
           thenL_BackSlowR_FowMidFast->addOutput(SpeedRight_FowMidFast); 
         FuzzyRuleConsequent* thenL_FowMidFastR_BackSlow = new FuzzyRuleConsequent();    
           thenL_FowMidFastR_BackSlow->addOutput(SpeedLeft_FowMidFast);
           thenL_FowMidFastR_BackSlow->addOutput(SpeedRight_BackSlow); 
           
         FuzzyRuleConsequent* thenL_BackSlowR_FowSlow = new FuzzyRuleConsequent();    
           thenL_BackSlowR_FowSlow->addOutput(SpeedLeft_BackSlow);
           thenL_BackSlowR_FowSlow->addOutput(SpeedRight_FowSlow); 
         FuzzyRuleConsequent* thenL_ZeroR_Zero = new FuzzyRuleConsequent();    
           thenL_ZeroR_Zero->addOutput(SpeedLeft_Zero);
           thenL_ZeroR_Zero->addOutput(SpeedRight_Zero); 
         FuzzyRuleConsequent* thenL_ZeroR_FowMidFast = new FuzzyRuleConsequent();    
           thenL_ZeroR_FowMidFast->addOutput(SpeedLeft_Zero);
           thenL_ZeroR_FowMidFast->addOutput(SpeedRight_FowMidFast);
         FuzzyRuleConsequent* thenL_ZeroR_FowSlow = new FuzzyRuleConsequent();    
           thenL_ZeroR_FowSlow->addOutput(SpeedLeft_Zero);
           thenL_ZeroR_FowSlow->addOutput(SpeedRight_FowSlow);

          FuzzyRuleConsequent* thenL_FowSlowR_BackSlow = new FuzzyRuleConsequent();    
           thenL_FowSlowR_BackSlow->addOutput(SpeedLeft_FowSlow);
           thenL_FowSlowR_BackSlow->addOutput(SpeedRight_BackSlow);
          FuzzyRuleConsequent* thenL_FowSlowR_FowMidFast = new FuzzyRuleConsequent();    
           thenL_FowSlowR_FowMidFast->addOutput(SpeedLeft_FowSlow);
           thenL_FowSlowR_FowMidFast->addOutput(SpeedRight_FowMidFast);
          FuzzyRuleConsequent* thenL_FowSlowR_FowSlow = new FuzzyRuleConsequent();    
           thenL_FowSlowR_FowSlow->addOutput(SpeedLeft_FowSlow);
           thenL_FowSlowR_FowSlow->addOutput(SpeedRight_FowSlow);          
          FuzzyRuleConsequent* thenL_FowSlowR_Zero = new FuzzyRuleConsequent();    
           thenL_FowSlowR_Zero->addOutput(SpeedLeft_FowSlow);
           thenL_FowSlowR_Zero->addOutput(SpeedRight_Zero);          
          FuzzyRuleConsequent* thenL_FowMidFastR_BackFast = new FuzzyRuleConsequent();    
           thenL_FowMidFastR_BackFast->addOutput(SpeedLeft_FowMidFast);
           thenL_FowMidFastR_BackFast->addOutput(SpeedRight_BackFast);             
          FuzzyRuleConsequent* thenL_FowMidFastR_Zero = new FuzzyRuleConsequent();    
           thenL_FowMidFastR_Zero->addOutput(SpeedLeft_FowMidFast);
           thenL_FowMidFastR_Zero->addOutput(SpeedRight_Zero);  
          FuzzyRuleConsequent* thenL_FowMidFastR_FowSlow = new FuzzyRuleConsequent();    
           thenL_FowMidFastR_FowSlow->addOutput(SpeedLeft_FowMidFast);
           thenL_FowMidFastR_FowSlow->addOutput(SpeedRight_FowSlow);  
          FuzzyRuleConsequent* thenL_FowFastR_FowFast = new FuzzyRuleConsequent();    
           thenL_FowFastR_FowFast->addOutput(SpeedLeft_FowFast);
           thenL_FowFastR_FowFast->addOutput(SpeedRight_FowFast);
          //Output case for auto recharge
          FuzzyRuleConsequent* thenL_BackSlowDR_BackSlowD = new FuzzyRuleConsequent();    
           thenL_BackSlowDR_BackSlowD->addOutput(SpeedLeft_BackSlow_Dock);
           thenL_BackSlowDR_BackSlowD->addOutput(SpeedRight_BackSlow_Dock);
           
          FuzzyRuleConsequent* thenL_ZeroDR_BackSlowD = new FuzzyRuleConsequent();    
           thenL_ZeroDR_BackSlowD->addOutput(SpeedLeft_Zero_Dock);
           thenL_ZeroDR_BackSlowD->addOutput(SpeedRight_BackSlow_Dock);

          FuzzyRuleConsequent* thenL_BackSlowDR_ZeroD = new FuzzyRuleConsequent();    
           thenL_BackSlowDR_ZeroD->addOutput(SpeedLeft_BackSlow_Dock);
           thenL_BackSlowDR_ZeroD->addOutput(SpeedRight_Zero_Dock);
           
          FuzzyRuleConsequent* thenL_BackSlowDR_BackFastD = new FuzzyRuleConsequent();    
           thenL_BackSlowDR_BackFastD->addOutput(SpeedLeft_BackSlow_Dock);
           thenL_BackSlowDR_BackFastD->addOutput(SpeedRight_BackFast_Dock);

          FuzzyRuleConsequent* thenL_BackFastDR_BackSlowD = new FuzzyRuleConsequent();    
           thenL_BackFastDR_BackSlowD->addOutput(SpeedLeft_BackFast_Dock);
           thenL_BackFastDR_BackSlowD->addOutput(SpeedRight_BackSlow_Dock);
             
         FuzzyRuleConsequent* thenL_ZeroDR_BackFastD = new FuzzyRuleConsequent();    
           thenL_ZeroDR_BackFastD->addOutput(SpeedLeft_Zero_Dock);
           thenL_ZeroDR_BackFastD->addOutput(SpeedRight_BackFast_Dock);

          FuzzyRuleConsequent* thenL_BackFastDR_ZeroD = new FuzzyRuleConsequent();    
           thenL_BackFastDR_ZeroD->addOutput(SpeedLeft_BackFast_Dock);
           thenL_BackFastDR_ZeroD->addOutput(SpeedRight_Zero_Dock); 
                   
//           // Rule fuzzy 1

         FuzzyRule* fuzzyRule1 = new FuzzyRule(1, Dis_FarSt_Left, thenL_BackSlowR_FowMidFast);
         fuzzy1->addFuzzyRule(fuzzyRule1); 
         FuzzyRule* fuzzyRule2 = new FuzzyRule(2, Dis_FarSt_MidLeft, thenL_FowSlowR_FowMidFast);
         fuzzy1->addFuzzyRule(fuzzyRule2); 
         FuzzyRule* fuzzyRule3 = new FuzzyRule(3, Dis_FarSt_Zero, thenL_FowFastR_FowFast);
         fuzzy1->addFuzzyRule(fuzzyRule3); 
         FuzzyRule* fuzzyRule4 = new FuzzyRule(4, Dis_FarSt_MidRight, thenL_FowMidFastR_FowSlow);
         fuzzy1->addFuzzyRule(fuzzyRule4); 
         FuzzyRule* fuzzyRule5 = new FuzzyRule(5, Dis_FarSt_Right, thenL_FowMidFastR_BackSlow);
         fuzzy1->addFuzzyRule(fuzzyRule5);
         
//         FuzzyRule* fuzzyRule6 = new FuzzyRule(6, Dis_NearSt_Left, thenL_ZeroR_FowMidFast);
//         fuzzy1->addFuzzyRule(fuzzyRule6);
//         FuzzyRule* fuzzyRule7 = new FuzzyRule(7, Dis_NearSt_Right, thenL_FowMidFastR_Zero);
//         fuzzy1->addFuzzyRule(fuzzyRule7);  
/////////// Trial
         FuzzyRule* fuzzyRule6 = new FuzzyRule(6, Dis_NearGo_Left, thenL_FowMidFastR_Zero);
         fuzzy1->addFuzzyRule(fuzzyRule6);
         FuzzyRule* fuzzyRule7 = new FuzzyRule(7, Dis_NearGo_MidLeft, thenL_FowMidFastR_FowSlow);
         fuzzy1->addFuzzyRule(fuzzyRule7);
         FuzzyRule* fuzzyRule8 = new FuzzyRule(8, Dis_NearGo_MidRight, thenL_FowSlowR_FowMidFast);
         fuzzy1->addFuzzyRule(fuzzyRule8);  
         FuzzyRule* fuzzyRule9 = new FuzzyRule(9, Dis_NearGo_Right, thenL_ZeroR_FowMidFast);
         fuzzy1->addFuzzyRule(fuzzyRule9);
/////////
//         FuzzyRule* fuzzyRule8 = new FuzzyRule(8, Dis_NearSt_ZeroGo_Left, thenL_ZeroR_FowMidFast);
//         fuzzy1->addFuzzyRule(fuzzyRule8);
//         FuzzyRule* fuzzyRule9 = new FuzzyRule(9, Dis_NearSt_ZeroGo_MidLeft, thenL_FowSlowR_FowSlow);
//         fuzzy1->addFuzzyRule(fuzzyRule9);
         FuzzyRule* fuzzyRule10 = new FuzzyRule(10, Dis_NearSt_ZeroGo_Zero, thenL_FowSlowR_FowSlow);
         fuzzy1->addFuzzyRule(fuzzyRule10);
//         FuzzyRule* fuzzyRule11 = new FuzzyRule(11, Dis_NearSt_ZeroGo_MidRight, thenL_FowSlowR_FowSlow);
//         fuzzy1->addFuzzyRule(fuzzyRule11);
//         FuzzyRule* fuzzyRule12 = new FuzzyRule(12, Dis_NearSt_ZeroGo_Right, thenL_FowMidFastR_Zero);
//         fuzzy1->addFuzzyRule(fuzzyRule12);

//         FuzzyRule* fuzzyRule13 = new FuzzyRule(13, Dis_NearSt_MidLeft, thenL_ZeroR_FowSlow);
//         fuzzy1->addFuzzyRule(fuzzyRule13);

//         FuzzyRule* fuzzyRule13 = new FuzzyRule(13, Dis_NearSt_MidLeftGo_Left, thenL_ZeroR_FowMidFast);
//         fuzzy1->addFuzzyRule(fuzzyRule13);
//         FuzzyRule* fuzzyRule14 = new FuzzyRule(14, Dis_NearSt_MidLeftGo_MidLeft, thenL_ZeroR_FowMidFast);
//         fuzzy1->addFuzzyRule(fuzzyRule14);
//         FuzzyRule* fuzzyRule15 = new FuzzyRule(15, Dis_NearSt_MidLeftGo_Zero, thenL_ZeroR_FowSlow);
//         fuzzy1->addFuzzyRule(fuzzyRule15);        
//         FuzzyRule* fuzzyRule16 = new FuzzyRule(16, Dis_NearSt_MidLeftGo_MidRight, thenL_ZeroR_FowMidFast);
//         fuzzy1->addFuzzyRule(fuzzyRule16);
//         FuzzyRule* fuzzyRule17 = new FuzzyRule(17, Dis_NearSt_MidLeftGo_Right, thenL_FowSlowR_FowSlow);
//         fuzzy1->addFuzzyRule(fuzzyRule17);                  

//         FuzzyRule* fuzzyRule18 = new FuzzyRule(18, Dis_NearSt_MidRight, thenL_FowSlowR_Zero);
//         fuzzy1->addFuzzyRule(fuzzyRule18);

//         FuzzyRule* fuzzyRule18 = new FuzzyRule(18, Dis_NearSt_MidRightGo_Left, thenL_FowSlowR_FowSlow);
//         fuzzy1->addFuzzyRule(fuzzyRule18);
//         FuzzyRule* fuzzyRule19 = new FuzzyRule(19, Dis_NearSt_MidRightGo_MidLeft, thenL_FowMidFastR_Zero);
//         fuzzy1->addFuzzyRule(fuzzyRule19);
//         FuzzyRule* fuzzyRule20 = new FuzzyRule(20, Dis_NearSt_MidRightGo_Zero, thenL_FowSlowR_Zero);
//         fuzzy1->addFuzzyRule(fuzzyRule20);        
//         FuzzyRule* fuzzyRule21 = new FuzzyRule(21, Dis_NearSt_MidRightGo_MidRight, thenL_FowSlowR_Zero);
//         fuzzy1->addFuzzyRule(fuzzyRule21);
//         FuzzyRule* fuzzyRule22 = new FuzzyRule(22, Dis_NearSt_MidRightGo_Right, thenL_FowMidFastR_Zero);
//         fuzzy1->addFuzzyRule(fuzzyRule22);  

         FuzzyRule* fuzzyRule23 = new FuzzyRule(23, Dis_ZeroSt_LeftGo_Left, thenL_ZeroR_Zero);
         fuzzy1->addFuzzyRule(fuzzyRule23);
         FuzzyRule* fuzzyRule24 = new FuzzyRule(24, Dis_ZeroSt_LeftGo_MidLeft, thenL_BackSlowR_FowSlow);
         fuzzy1->addFuzzyRule(fuzzyRule24);
         FuzzyRule* fuzzyRule25 = new FuzzyRule(25, Dis_ZeroSt_LeftGo_Zero, thenL_BackFastR_FowMidFast);
         fuzzy1->addFuzzyRule(fuzzyRule25);        
         FuzzyRule* fuzzyRule26 = new FuzzyRule(26, Dis_ZeroSt_LeftGo_MidRight, thenL_FowMidFastR_BackFast);
         fuzzy1->addFuzzyRule(fuzzyRule26);
         FuzzyRule* fuzzyRule27 = new FuzzyRule(27, Dis_ZeroSt_LeftGo_Right, thenL_BackFastR_FowMidFast);
         fuzzy1->addFuzzyRule(fuzzyRule27);  

         FuzzyRule* fuzzyRule28 = new FuzzyRule(28, Dis_ZeroSt_RightGo_Left, thenL_FowMidFastR_BackFast);
         fuzzy1->addFuzzyRule(fuzzyRule28);
         FuzzyRule* fuzzyRule29 = new FuzzyRule(29, Dis_ZeroSt_RightGo_MidLeft, thenL_BackFastR_FowMidFast);
         fuzzy1->addFuzzyRule(fuzzyRule29);
         FuzzyRule* fuzzyRule30 = new FuzzyRule(30, Dis_ZeroSt_RightGo_Zero, thenL_FowMidFastR_BackFast);
         fuzzy1->addFuzzyRule(fuzzyRule30);        
         FuzzyRule* fuzzyRule31 = new FuzzyRule(31, Dis_ZeroSt_RightGo_MidRight, thenL_FowSlowR_BackSlow);
         fuzzy1->addFuzzyRule(fuzzyRule31);
         FuzzyRule* fuzzyRule32 = new FuzzyRule(32, Dis_ZeroSt_RightGo_Right, thenL_ZeroR_Zero);
         fuzzy1->addFuzzyRule(fuzzyRule32);  

         FuzzyRule* fuzzyRule33 = new FuzzyRule(33, Dis_ZeroSt_MidLeftGo_Left, thenL_FowSlowR_BackSlow);
         fuzzy1->addFuzzyRule(fuzzyRule33);
         FuzzyRule* fuzzyRule34 = new FuzzyRule(34, Dis_ZeroSt_MidLeftGo_MidLeft, thenL_ZeroR_Zero);
         fuzzy1->addFuzzyRule(fuzzyRule34);
         FuzzyRule* fuzzyRule35 = new FuzzyRule(35, Dis_ZeroSt_MidLeftGo_Zero, thenL_BackSlowR_FowSlow);
         fuzzy1->addFuzzyRule(fuzzyRule35);        
         FuzzyRule* fuzzyRule36 = new FuzzyRule(36, Dis_ZeroSt_MidLeftGo_MidRight, thenL_BackSlowR_FowSlow);
         fuzzy1->addFuzzyRule(fuzzyRule36);
         FuzzyRule* fuzzyRule37 = new FuzzyRule(37, Dis_ZeroSt_MidLeftGo_Right, thenL_BackFastR_FowMidFast);
         fuzzy1->addFuzzyRule(fuzzyRule37);   
                 
         FuzzyRule* fuzzyRule38 = new FuzzyRule(38, Dis_ZeroSt_RightGo_Left, thenL_FowMidFastR_BackFast);
         fuzzy1->addFuzzyRule(fuzzyRule38);
         FuzzyRule* fuzzyRule39 = new FuzzyRule(39, Dis_ZeroSt_RightGo_MidLeft, thenL_FowSlowR_BackSlow);
         fuzzy1->addFuzzyRule(fuzzyRule39);
         FuzzyRule* fuzzyRule40 = new FuzzyRule(40, Dis_ZeroSt_RightGo_Zero, thenL_FowSlowR_BackSlow);
         fuzzy1->addFuzzyRule(fuzzyRule40);        
         FuzzyRule* fuzzyRule41 = new FuzzyRule(41, Dis_ZeroSt_RightGo_MidRight, thenL_ZeroR_Zero);
         fuzzy1->addFuzzyRule(fuzzyRule41);
         FuzzyRule* fuzzyRule42 = new FuzzyRule(42, Dis_ZeroSt_RightGo_Right, thenL_BackSlowR_FowSlow);
         fuzzy1->addFuzzyRule(fuzzyRule42);  

         FuzzyRule* fuzzyRule43 = new FuzzyRule(43, Dis_ZeroSt_ZeroGo_Left, thenL_FowMidFastR_BackFast);
         fuzzy1->addFuzzyRule(fuzzyRule43);
         FuzzyRule* fuzzyRule44 = new FuzzyRule(44, Dis_ZeroSt_ZeroGo_MidLeft, thenL_FowSlowR_BackSlow);
         fuzzy1->addFuzzyRule(fuzzyRule44);
         FuzzyRule* fuzzyRule45 = new FuzzyRule(45, Dis_ZeroSt_ZeroGo_Zero, thenL_ZeroR_Zero);
         fuzzy1->addFuzzyRule(fuzzyRule45);        
         FuzzyRule* fuzzyRule46 = new FuzzyRule(46, Dis_ZeroSt_ZeroGo_MidRight, thenL_BackSlowR_FowSlow);
         fuzzy1->addFuzzyRule(fuzzyRule46);
         FuzzyRule* fuzzyRule47 = new FuzzyRule(47, Dis_ZeroSt_ZeroGo_Right, thenL_BackFastR_FowMidFast);
         fuzzy1->addFuzzyRule(fuzzyRule47); 
                            
//         //-------------------------   Fuzzy2 Rule     -----------------------------------
          //Input case Fuzzy2
         FuzzyRuleAntecedent* AngleRobot_Mid= new FuzzyRuleAntecedent();
           AngleRobot_Mid->joinSingle(Mid); 
         FuzzyRuleConsequent* thenTurn_Zero2 = new FuzzyRuleConsequent();  
           thenTurn_Zero2->addOutput(Turn_Zero2);           
         FuzzyRule* fuzzyRule48 = new FuzzyRule(48, AngleRobot_Mid, thenTurn_Zero2);
        fuzzy2->addFuzzyRule(fuzzyRule48);    

         FuzzyRuleAntecedent* AngleRobot_Left= new FuzzyRuleAntecedent();
           AngleRobot_Left->joinSingle(Left); 
         FuzzyRuleConsequent* thenTurnLeft2 = new FuzzyRuleConsequent();  
           thenTurnLeft2->addOutput(TurnLeft2);           
         FuzzyRule* fuzzyRule49 = new FuzzyRule(49, AngleRobot_Left, thenTurnLeft2);
        fuzzy2->addFuzzyRule(fuzzyRule49); 
        
         FuzzyRuleAntecedent* AngleRobot_Right= new FuzzyRuleAntecedent();
          AngleRobot_Right->joinSingle(Right); 
         FuzzyRuleConsequent* thenTurnRight2 = new FuzzyRuleConsequent();  
           thenTurnRight2->addOutput(TurnRight2);           
         FuzzyRule* fuzzyRule50 = new FuzzyRule(50, AngleRobot_Right, thenTurnRight2);
        fuzzy2->addFuzzyRule(fuzzyRule50); 

          //-------------------------   Fuzzy3 Rule     -----------------------------------
         FuzzyRuleAntecedent* Angle_Dock_Left= new FuzzyRuleAntecedent();
           Angle_Dock_Left->joinSingle(Dock_Left);
         FuzzyRule* fuzzyRule51 = new FuzzyRule(51, Angle_Dock_Left, thenL_BackFastDR_BackSlowD);
         fuzzy3->addFuzzyRule(fuzzyRule51);
         FuzzyRuleAntecedent* Angle_Dock_Right= new FuzzyRuleAntecedent();
          Angle_Dock_Right->joinSingle(Dock_Right);
         FuzzyRule* fuzzyRule52 = new FuzzyRule(52, Angle_Dock_Right, thenL_BackSlowDR_BackFastD);
         fuzzy3->addFuzzyRule(fuzzyRule52);
         FuzzyRuleAntecedent* Angle_Dock_MidRight= new FuzzyRuleAntecedent();
          Angle_Dock_MidRight->joinSingle(Dock_MidRight);
         FuzzyRule* fuzzyRule53 = new FuzzyRule(53, Angle_Dock_MidRight, thenL_BackSlowDR_BackFastD);
         fuzzy3->addFuzzyRule(fuzzyRule53);
         FuzzyRuleAntecedent* Angle_Dock_MidLeft= new FuzzyRuleAntecedent();
           Angle_Dock_MidLeft->joinSingle(Dock_MidLeft);
         FuzzyRule* fuzzyRule54 = new FuzzyRule(54, Angle_Dock_MidLeft, thenL_BackFastDR_BackSlowD);
         fuzzy3->addFuzzyRule(fuzzyRule54);
           
        } 
 //******* RUN **********      
      void go(){
              if(enable ==true)//auto run
              {
//                 digitalWrite(DirL,dirl);digitalWrite(DirR,dirr);  
//                  analogWrite(PWMR,abs((int)(vtp))); analogWrite(PWML,abs((int)(vtt)));
                  mySerial.println("{N2 P0 V"+String(-LeftSpeed)+" A150}");
                  delay(3);
                  mySerial.println("{N3 P0 V"+String(RightSpeed)+" A150}");
              }              
            else if(enable ==false)//stop auto run
              {            
                if(manual==0)
                { //vtt=vtp=0; analogWrite(PWMR,vtp); analogWrite(PWML,vtt);
                  mySerial.println("{N2 P0 V0 A100}");delay(3);mySerial.println("{N3 P0 V0 A100}");
                }
                else if(manual ==1)// Tien
                { //vtt=vtp=40; digitalWrite(DirL,0); digitalWrite(DirR,1); analogWrite(PWMR,vtp); analogWrite(PWML,vtt); delay(1);
                mySerial.println("{N2 P0 V-80 A100}");delay(3);mySerial.println("{N3 P0 V80 A100}");
                }
                else if(manual ==2)// Lui
                { //vtt=vtp=40; digitalWrite(DirL,1); digitalWrite(DirR,0); analogWrite(PWMR,vtp); analogWrite(PWML,vtt); delay(1);
                mySerial.println("{N2 P0 V80 A100}");delay(3); mySerial.println("{N3 P0 V-80 A100}");
                }
                else if(manual ==3)// Trái
                { //vtt=vtp=30; digitalWrite(DirL,0); digitalWrite(DirR,0); analogWrite(PWMR,vtp); analogWrite(PWML,vtt); delay(1);
                mySerial.println("{N2 P0 V40 A100}");delay(3);mySerial.println("{N3 P0 V40 A100}"); 
                }
                else if(manual ==4)// Phai
                {// vtt=vtp=30; digitalWrite(DirL,1); digitalWrite(DirR,1); analogWrite(PWMR,vtp); analogWrite(PWML,vtt); delay(1);
                mySerial.println("{N2 P0 V-40 A100}"); delay(3); mySerial.println("{N3 P0 V-40 A100}");
                 }      
              }     
        }  
    
  // *********** RECIEVE POSITION *******  
// //*********SENT DATA TO ARDUINO UNO**********   
  void resetPosition()
  {Serial3.println(temp2uno);}
      
 void loop()
 {
 //read_IR();
  
 timer.run();
//         while(Serial3.available())
//         {
//          char data3 = (char)Serial3.read(); 
//          if (data3 == 'A') // chuoi A & "van toc trai" & "chieu trai" & B // max 148+ 0 or 1
//            { k3=1;inputString3="";}
//          else if(data3 =='Q')
//            {k3=0;   temp3= inputString3.substring(1);  xRobot=temp3.toInt();}
//          else if (data3 == 'W') 
//            {k3=0;   temp3= inputString3.substring(1);  yRobot=temp3.toInt();}
//          else if (data3 == 'E') 
//            {k3=0;   temp3= inputString3.substring(1);  AngleRobot=temp3.toFloat()/100;}
//           else if(data3 =='o')
//            {pose_flag = true;}
//          if (k3==1)
//           { inputString3 += data3; } 
//          }

if(mode_autocharge==true)
{

//read_IR();
//      void read_IR(){
//  if (irrecv.decode(&results)) // nếu nhận được tín hiệu
//  {  translateIR();
//  Serial.println(String(angle_dock));
//  irrecv.resume();}
//  }
  
  button_value = digitalRead(button_pin);
if (irrecv.decode(&results)) // nếu nhận được tín hiệu
  {  translateIR();//Serial.println(String(angle_dock));
      fuzzy3->setInput(2,angle_dock);
  fuzzy3->fuzzify();
  LeftSpeed = fuzzy3->defuzzify(4);
  RightSpeed = fuzzy3->defuzzify(5);
  Serial.println(String(angle_dock)+"||"+String(LeftSpeed)+"||"+String(RightSpeed));
  if(button_value==0)
  {enable = false;mode_autocharge = false;}
  go();
  irrecv.resume();
}
if(button_value==0)
{mode_autocharge = false;}
}
 else
   {    
     
         //******** Split the path data
         if (isPath ==true)
         {
          String path_string_input = path_string;          
          //path_string ="";
          byte count_path =1;
               count_point=0;
//               Serial.println(path_string);
          for (ii = 0;ii<=path_string_input.length()-1;ii++)
              {
              inputString_path += char(path_string_input[ii]);
              jj ++;        
              if (path_string_input[ii]==',')
                   {path= inputString_path.substring(0,jj-1);
                    path_array[count_path]= inputString_path.substring(0,jj-1).toInt();
                    count_path++;
                    inputString_path="";jj=0;} 
              }       
           for (kkk = 1;kkk<count_path;kkk = kkk+3)
             {count_point= count_point +1;
               x_path[count_point]=path_array[kkk];
               y_path[count_point]=path_array[kkk+1];
               theta_path[count_point]=path_array[kkk+2];}  
                //Tinh chieu dai duong di  
//            for (iii = 1;iii<=count_point-1;iii++)
//             {Dist_path = Dist_path + sqrt(float((x_path[iii+1]- x_path[iii]))*float((x_path[iii+1]- x_path[iii]))+ float((y_path[iii+1]- y_path[iii]))*float((y_path[iii+1]- y_path[iii])));}
//             Serial.println(String(Dist_path));  
//             Serial.println(String(count_point));
              isPath = false;
           }  
 // ******* Computing Distance and Direction of Robot
         if (num_point <=count_point)
         {
               xValue = (x_path[num_point] - xRobot);
               yValue = (y_path[num_point] - yRobot);
               AngleGoal = theta_path[num_point];
               Dist = sqrt(((float)xValue*(float)xValue)+((float)yValue*(float)yValue));
             //  Serial.println(String(num_point)+"||"+String(Dist));
                  if ((xValue==0) && (yValue==0))
                   { Angle = 0;}
                  else if ((xValue==0) && (yValue < 0))
                  {Angle = -90;}
                   else if ((xValue==0) && (yValue > 0))
                  {Angle = 90;}
                   else if ((xValue<0) && (yValue==0))
                  {Angle = 180;}
                  else
                  { if ((xValue <0)&&(yValue>0))
                      {Angle = 180 + ((atan((float)yValue/(float)xValue))*180/PI); }
                      else if ((xValue <0)&&(yValue<0))
                      {Angle = ((atan((float)yValue/(float)xValue))*180/PI)-180; }
                      else
                      {Angle = (atan((float)yValue/(float)xValue))*180/PI;}
                  }            
                DeltaStart = AngleRobot - Angle;
                DeltaGoal = AngleGoal - Angle;
                  if (DeltaStart > 180)
                  {DeltaStart = DeltaStart - 360;}
                  else if (DeltaStart < -180)
                  {DeltaStart = DeltaStart + 360;}
                  if (DeltaGoal > 180)
                  {DeltaGoal = DeltaGoal - 360;}
                  else if (DeltaGoal < -180)
                  {DeltaGoal = DeltaGoal + 360;}
                  if (num_point == count_point)
                    {if(Dist<120)
                      {reach_goal = true;}
                    }
                 if (Dist <120)
                { num_point ++;}  
             }
         if (serial_flag == false)
         {           
//     Select Data Thread Sensor 1
      digitalWrite(S0,0);
      digitalWrite(S1,0);
      digitalWrite(S2,0);
      delay(1);
      int Se1 = distance_func(trig1);    
//     Select Data Thread Sensor 2
      digitalWrite(S0,1);
      digitalWrite(S1,0);
      digitalWrite(S2,0);
      delay(1);
     int Se2 = distance_func(trig2);
//        // Select Data Thread Sensor 3
      digitalWrite(S0,0);
      digitalWrite(S1,1);
      digitalWrite(S2,0);
      delay(1);
     int Se3 = distance_func(trig3);
      // Select Data Thread Sensor 4
      digitalWrite(S0,1);
      digitalWrite(S1,1);
      digitalWrite(S2,0);
      delay(1);
     int Se4 = distance_func(trig4);
      digitalWrite(S0,1);
      digitalWrite(S1,0);
      digitalWrite(S2,1);
      delay(1);
     int Se5 = distance_func(trig5);
    
      digitalWrite(S0,0);
      digitalWrite(S1,0);
      digitalWrite(S2,1);
      delay(1);
     int Se6 = distance_func(trig6);
//     Serial.println(String(Se1)+"||"+String(Se2)+"||"+String(Se3)+"||"+String(Se4)+"||"+String(Se6)+"||"+String(Se5));
     if (count <5)
     {
     count = count + 1;
     tempSe1 = tempSe1 + Se1;
     tempSe2 = tempSe2 + Se2;
     tempSe3 = tempSe3 + Se3;
     tempSe4 = tempSe4 + Se4;    
     tempSe5 = tempSe5 + Se5;  
     }
     else
     { 
       count =0;
       tempSe1 = tempSe1/5;
       tempSe2 = tempSe2/5;
       tempSe3 = tempSe3/5;
       tempSe4 = tempSe4/5;   
       tempSe5 = tempSe5/5; 
       //{Serial.println("A"+String(tempSe1)+","+String(tempSe2)+","+String(tempSe3)+","+String(tempSe4));}    
//     if ((Sensor_enable ==true)&&(reach_goal == false)&&((abs(DeltaStart)) <8))
//      {Serial.println("A"+String(tempSe1)+","+String(tempSe2)+","+String(tempSe3)+","+String(tempSe4));}
//      buff_sen1= tempSe1;buff_sen2= tempSe2;buff_sen3= tempSe3;buff_sen4= tempSe4;
            //if (((buff_sen1<30)||(buff_sen1<40)||(buff_sen1<40)||(buff_sen1<30))

            buff_sen1= tempSe1;buff_sen2= tempSe2;buff_sen3= tempSe3;buff_sen4= tempSe4;
      if (((tempSe1<35)||(tempSe2<50)||(tempSe3<50)||(tempSe4<35))&&(abs(DeltaStart)<8)&&(reach_goal ==false)&& (Dist > 300)&&(enable == true))
        {  count_obs ++;            
        //Serial.println("A"+String(tempSe1)+","+String(tempSe2)+","+String(tempSe3)+","+String(tempSe4));
        }
      if (count_obs > 3)
        { enable = false; go();count_obs = 0; timer.restartTimer(timerId); timer.enable(timerId);}   //&&(timer.isEnabled(timerId)==false)

//// Phuong phap 2
//          buff_sen1= tempSe1;buff_sen2= tempSe2;buff_sen3= tempSe3;buff_sen4= tempSe4;
//          if (((tempSe1<40)||(tempSe2<60)||(tempSe3<60)||(tempSe4<40))&&(abs(DeltaStart)<8)&&(reach_goal ==false)&& (Dist > 200)&&(enable == true))
//          {  count_obs ++;}
//          if (count_obs > 5)
//          {
//              Serial.println("R,"+String(tempSe1));delay(1);
//              Serial.println("T,"+String(tempSe2));delay(1);
//              Serial.println("Y,"+String(tempSe3));delay(1);
//              Serial.println("U,"+String(tempSe4));delay(1);
//              count_obs = 0;
//          }        
        tempSe1 =tempSe2 = tempSe3 = tempSe4 = 0; 
        //delay(20);
      }
 }
        if(pose_flag ==true)
        {
        Serial.println("P,"+String(xRobot)+","+String(yRobot)+","+String(AngleRobot));         
            if (reach_goal ==true)
            {            
                AngleRobot_Goal = AngleRobot-theta_path[num_point-1];
                if (AngleRobot_Goal > 180)
                    {AngleRobot_Goal = AngleRobot_Goal - 360;}
                    else if (AngleRobot_Goal < -180)
                    {AngleRobot_Goal = AngleRobot_Goal + 360;}
                fuzzy2->setInput(1,AngleRobot_Goal);
                fuzzy2->fuzzify();
                AngularSpeed= fuzzy2->defuzzify(3);
              // Serial.println(String(AngleRobot_Goal)+"--"+String(AngularSpeed));         
             // ******* Calculate Speed of Wheel
                 TangentialSpeed=0;
                 LeftSpeed = (((AngularSpeed*PI/180)*260 + (2*TangentialSpeed))*180)/(145*PI);  // Degree/second
                 RightSpeed = (((2*TangentialSpeed) - (AngularSpeed*PI/180)*260)*180)/(145*PI); // Degree/second
                 if (abs(AngleRobot_Goal)<5)
                 {isfinish_path = true;
                 //Serial.println("f,f");
                 }           
            }
            else
            {
              
                fuzzy1->setInput(7,Dist);
                fuzzy1->setInput(8,DeltaStart);
                fuzzy1->setInput(9,DeltaGoal);
                fuzzy1->fuzzify();
                LeftSpeed = fuzzy1->defuzzify(1);
                RightSpeed = fuzzy1->defuzzify(2);

                //Serial.println(String(LeftSpeed)+"||"+String(RightSpeed));
                //TangentialSpeed= fuzzy1->defuzzify(1);
                //AngularSpeed = fuzzy1->defuzzify(2);
                          // Serial.println(String(num_point)+"||"+String(Dist)+"||"+String(DeltaStart)+"||"+String(DeltaGoal)+"||"+String(LeftSpeed)+"||"+String(RightSpeed));         
                //// ******* Calculate Speed of Wheel
                //LeftSpeed = (((AngularSpeed*PI/180)*260 + (2*TangentialSpeed))*180)/(145*PI);  // Degree/second
                //RightSpeed = (((2*TangentialSpeed) - (AngularSpeed*PI/180)*260)*180)/(145*PI); // Degree/second
            }
            if ((reach_goal==true)&&(isfinish_path == true))
            {
              enable = false;
              isPath =false;
              Sensor_enable = false; 
              Serial.println("f,f");             
              //if(sent_f_one_time == true)
              //{sent_f_one_time = false;}
            }
          go();
          pose_flag = false;
       }     
     }          
 }


