#include "ServoManager.h" //for static const member types
#include "StringProcess.h"

//ServoData declaration:
//this class defines a type for the servo commands
//--------------------------------------------------------------------------
class ServoData{
public:
   ServoData(char* data);
   bool isValid();
   void setInvalid();
   bool isPair();
   
   char getCommand();
   int getVal();
   int getIndex();
   
private:
  int index; //invalid data is set with a negative index
  char command;
  int val;
    
};

//ServoData implementation:
//--------------------------------------------------------------------------

  ServoData::ServoData(char* data){
    StringProcess sp(data);
    
  //get pin number
  if(!sp.moveToNext()){ //move to first character.
    setInvalid();
    return;
  }

  if(!sp.atDigit()){
    setInvalid();
    return;
  }

  index=sp.getInteger();
  //if not valid pin
  if(index>ServoManager::NumServos){
    setInvalid();
    return;
  }

  //get command
  if(!sp.moveToNext()){
    setInvalid();
    return;
  }

  //if not a letter
  if(!sp.atLetter()){
    setInvalid();
    return;
  }

  command=sp.get();
  if(isPair()){
    return;
  }

  //if it is speed or pos, get it
  if(!sp.moveToNext()){
    setInvalid();
    return;
  }
   val=sp.getInteger();

  //if not valid value
  if(command=='m' && 
     (val<ServoManager::MinVal || val>ServoManager::MaxVal)){
       setInvalid();
       return;
  }

  //accept any value for speed.
}

  bool  ServoData::isValid(){
    return index>=0;
  }
  void  ServoData::setInvalid(){
    index=-1;
  }
  bool  ServoData::isPair(){
    return command =='a' || command=='d';
  }
  
  char ServoData::getCommand(){
    return command;
  }
  
  int ServoData::getVal(){
    return val;
  }
  
  int ServoData::getIndex(){
    return index;
  }
  
  
  
   


