/* This program use the Kinematic() function with the Ultrasonic sensor HC-SR04 - by Oracid. 03/01/2019 */
#include <Servo.h>

Servo mySrv[8];                 // Indicate how many servos. Here 8 servos.
const int nbFeet = 11;          // Indicate here the number of feet of each line of the table bellow. Here 11.
int Speed = 1300;               // Indicate here, in microseconds the waiting time for velocity. Here 1300.

const int nbSrv = sizeof(mySrv)/sizeof(Servo);

// quadruped forward v3
int Forward[nbSrv][nbFeet]={  {110,100, 90, 80, 70, 60, 70, 80, 90,100,110},  // Indicate value angles of kinematic for each servo.
                              { 70, 80, 90,100,110,120,110,100, 90, 80, 70},  // one ligne for on servo. First and last value must be equal
                              {110,100, 90, 80, 70, 60, 70, 80, 90,100,110},  // Number of lignes must be equal to number of servos
                              { 70, 80, 90,100,110,120,110,100, 90, 80, 70},  // the foot must always be the same (here 10)
                              { 60, 60, 60, 60, 60, 80, 80, 80, 80, 80, 60},  // if servo don't move, duplicate value
                              {100,100,100,100,100,120,120,120,120,120,100},
                              {100,100,100,100,100,120,120,120,120,120,100},
                              { 60, 60, 60, 60, 60, 80, 80, 80, 80, 80, 60}};

// quadruped backward v3
int Backward[nbSrv][nbFeet]={ { 70, 80, 90,100,110,120,110,100, 90, 80, 70},
                              {110,100, 90, 80, 70, 60, 70, 80, 90,100,110},
                              { 70, 80, 90,100,110,120,110,100, 90, 80, 70},
                              {110,100, 90, 80, 70, 60, 70, 80, 90,100,110},
                              { 60, 60, 60, 60, 60, 80, 80, 80, 80, 80, 60},
                              {100,100,100,100,100,120,120,120,120,120,100},
                              {100,100,100,100,100,120,120,120,120,120,100},
                              { 60, 60, 60, 60, 60, 80, 80, 80, 80, 80, 60}};
  
// quadruped turn left v3
int TurnLeft[nbSrv][nbFeet]={ {110,100, 90, 80, 70, 60, 70, 80, 90,100,110},
                              { 70, 80, 90,100,110,120,110,100, 90, 80, 70},
                              { 70, 80, 90,100,110,120,110,100, 90, 80, 70},
                              {110,100, 90, 80, 70, 60, 70, 80, 90,100,110},
                              { 60, 60, 60, 60, 60, 80, 80, 80, 80, 80, 60},
                              {100,100,100,100,100,120,120,120,120,120,100},
                              {100,100,100,100,100,120,120,120,120,120,100},
                              { 60, 60, 60, 60, 60, 80, 80, 80, 80, 80, 60}};

// quadruped turn right v3
int TurnRight[nbSrv][nbFeet]={  { 70, 80, 90,100,110,120,110,100, 90, 80, 70},
                                {110,100, 90, 80, 70, 60, 70, 80, 90,100,110},
                                {110,100, 90, 80, 70, 60, 70, 80, 90,100,110},
                                { 70, 80, 90,100,110,120,110,100, 90, 80, 70},
                                { 60, 60, 60, 60, 60, 80, 80, 80, 80, 80, 60},
                                {100,100,100,100,100,120,120,120,120,120,100},
                                {100,100,100,100,100,120,120,120,120,120,100},
                                { 60, 60, 60, 60, 60, 80, 80, 80, 80, 80, 60}};
                                                                
int lgTab = sizeof(Forward[1])/sizeof(int);
int Foot = abs(Forward[0][0]-Forward[0][1]);
int SrvAdjust[nbSrv]={ 0, 5, 0, 9, 0, 2, -2, 8 };               // each servo need an adjustement position                        
int LeftRight=1;
const char DOUT_TRIGGER = 1;  const char DIN_ECHO = 2;  float distance = 1000;  //US sensor HC-SR04 connectors and variable

void  setup() {
//  Serial.begin(9600); // uncomment out if debug
//  Serial.print("nbSrv = ");Serial.print(nbSrv);Serial.print("  lgTabl = ");Serial.print(lgTabl);Serial.print("  Foot = ");Serial.print(Foot);Serial.print("  Speed = ");Serial.println(Speed);

//  Ultrasonic sensor HC-SR04
  pinMode(DOUT_TRIGGER, OUTPUT);
  digitalWrite(DOUT_TRIGGER, LOW);
  pinMode(DIN_ECHO, INPUT);

  // servos attachments to Arduino outputs
  mySrv[0].attach(8);
  mySrv[1].attach(9);
  mySrv[2].attach(10);
  mySrv[3].attach(3);
  mySrv[4].attach(4);
  mySrv[5].attach(5);
  mySrv[6].attach(6);
  mySrv[7].attach(7);
  
//  Kinematic(&lgTab, Tab1[0], &nbSrv, &Speed, &Foot, &SrvAdjust[0] );   // uncomment out to test only one cycle
}

void  loop() {
  detect();
  if (distance <= 25){
    LeftRight=LeftRight*(-1);
    if( LeftRight > 0 ) {         //once turn right, once turn left
      for(int i=0;i<2;i++)  Kinematic(&lgTab, TurnRight[0], &nbSrv, &Speed, &Foot, &SrvAdjust[0] ); 
    }else{
      for(int i=0;i<2;i++)  Kinematic(&lgTab, TurnLeft[0], &nbSrv, &Speed, &Foot, &SrvAdjust[0] );    
    }
  }else{
    Kinematic(&lgTab, Forward[0], &nbSrv, &Speed, &Foot, &SrvAdjust[0] );
  }   
}

void  Kinematic(int *lg, int *tb, int *nsrv, int *vel, int *foot, int *srvadjust){
int pos, srv, stp;
  for( int i=0; i < (*lg-1); i++){              // loop on the first line of the table
    for( stp = 0; stp < (*foot); stp++){        // loop on the step between two table values, here 10
      for(srv = 0; srv < (*nsrv); srv++){       // loop on the number of servos, here 8
        if ( *(tb+(srv*(*lg))+i) >= *(tb+(srv*(*lg))+i+1) ){ pos=(*(tb+(srv*(*lg))+i))*(-1)+stp; }  // if current value is bigger than the next 
          else { pos=(*(tb+(srv*(*lg))+i))+stp; }                                                   // then pos is multiply by -1 so it can be incremanted to the next value
        if ( *(tb+(srv*(*lg))+i) == *(tb+(srv*(*lg))+i+1) ){ pos=(*(tb+(srv*(*lg))+i)); }           // if current and next value are equal then pos keep value
        mySrv[srv].write(abs(pos+(*(srvadjust+srv))));                                              // abs(pos) because when negative value
//        Serial.print("Tabl=");Serial.print(i);Serial.print(" srv=");Serial.print(srv);Serial.print(" pos=");Serial.println(abs(pos+(*(srvadjust+srv))));
        delayMicroseconds((*vel));
      }
    }
  }
}

void detect(){
  digitalWrite(DOUT_TRIGGER, LOW);  delayMicroseconds(2);
  digitalWrite(DOUT_TRIGGER, HIGH); delayMicroseconds(10);
  digitalWrite(DOUT_TRIGGER, LOW);
  distance= pulseIn(DIN_ECHO, HIGH) / 58.0; 
}

