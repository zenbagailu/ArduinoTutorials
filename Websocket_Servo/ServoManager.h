
#include <Servo.h>

//Servos:
//--------------------------------------------------------------------------
class ServoManager{
public:
  ServoManager();
  void attach(int n);
  void detach(int n);
  void setDestination(int servoN,int dest);
  void setSpeed(int servoN,int ns);
  void update();
  

  //Type members:
public:
  static const int NumServos=3;
  static const int MinVal=1000;
  static const int MaxVal=2000;
  static const double SpeedScale=0.01;

private:
  int pins[NumServos]; 
  double speed[NumServos];
  double pos[NumServos];
  int destination[NumServos];
  Servo svs[NumServos];

};


 ServoManager::ServoManager(){
    //pins to use hard-coded
    //if serial is used pins 0 and 1 are used in Arduino Uno
    //with Ethernet pins 4,10,11,12,13 are used in Arduino Uno
    //with other Arduinos check specifications of board and ethernet shield
    pins[0]=7;pins[1]=8;pins[2]=9;
    for(int i=0;i<NumServos;++i){
      speed[i]=0;
      destination[i]=MinVal;
      pos[i]=MinVal;
    }  
  }

  void ServoManager::attach(int n){
    svs[n].attach(pins[n]);
    pos[n]=destination[n]=MinVal;
    svs[n].writeMicroseconds(pos[n]); 
  }

  void ServoManager::detach(int n){
    svs[n].detach();
  }

  void ServoManager::setDestination(int servoN,int dest){
    destination[servoN]=dest;
  }

  void ServoManager::setSpeed(int servoN,int ns){
    speed[servoN]=ns*SpeedScale;

  }

  void ServoManager::update(){
    
    for(int i=0;i<NumServos; ++i){
      
      if(pos[i]!=destination[i]){

        if(speed[i]==0){ //if speed is not set, or max
          pos[i]=destination[i];
        }else if(abs(pos[i]-destination[i])<=speed[i]){ //if it has reached its destination
          pos[i]=destination[i];
        }else{
          pos[i]+=pos[i]>destination[i]? -speed[i] : speed[i];
        }
        //update the servos position
        svs[i].writeMicroseconds(pos[i]);
      }
      //do nothing if it has reached its position
      
      //svs[i].write(pos[i]);
    }
  }

