//String Processing:
//--------------------------------------------------------------------------
struct StringProcess{
  char* data;
  int pos;

  StringProcess(char* data_):
  data(data_),
  pos(0){};

  //UTF-8, ASCII
  bool atEnd(){return data[pos]=='\0';}
  bool atDigit(){return data[pos]>47 && data[pos]<58;}
  bool atUpper(){return data[pos]>64 && data[pos]<91;}
  bool atLower(){return data[pos]>96 && data[pos]<123;}
  bool atLetter(){return atUpper() || atLower();}

  bool moveToNext(){
    while (!atDigit() && !atLetter()){
      if(atEnd()){
        return false;
      }
      ++pos;
    }
    return true;
  }

  //get automatically moves to the next relevant char
  //and converts it to digit or from upper to lower case
  //(we need to check what type it is before calling...)
  char get(){ 
    return
    atDigit() ? data[pos++]-48 : 
    atUpper() ? data[pos++]+35 :
    data[pos++]; //this may return either a lower or terminating character
  }
  
  int getInteger(){
  //while char is a digit
  int num=0;
  while(atDigit()){
     num=num*10+get();
    //int val=static_cast<int>(sp.get());
    //num=num*10+val;
  }

  return num;
}
  
};

