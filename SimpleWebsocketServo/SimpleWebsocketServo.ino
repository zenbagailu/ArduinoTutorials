#include <SPI.h>
#include <Ethernet.h>
#include <cmath>
#include <Servo.h>
//#include "ServoData.h"

// Enabe debug tracing to Serial port.
#define DEBUG
// Here we define a maximum framelength to 64 bytes. Default is 256.
#define MAX_FRAME_LENGTH 64

#include <WebSocket.h>

//This is the mac address. It needs to be different for every connected device
//Ethernet shields have usually a mac Address given on a sticker attached to them.
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x0E, 0x61 }; 
//in case DHCP does not work, or we want to hardcode the IP
byte ip[] = {130, 237, 11,243};

// Create a Websocket server
WebSocket wsServer;

ServoManager servos;

//These are the websocket functions
void sendMessage(WebSocket &socket, char* message){
  socket.send(message, strlen(message));
}

//The followings websocket functions are callbacks
void onDisconnect(WebSocket &socket) {
#ifdef DEBUG
  Serial.println("onDisconnect called");
#endif
}

void onConnect(WebSocket &socket) {
#ifdef DEBUG
  Serial.println("onConnect called");
#endif
}

// You must have at least one function with the following signature.
// It will be called by the server when a data frame is received.
void onData(WebSocket &socket, char* dataString, byte frameLength) {
  
#ifdef DEBUG
  Serial.print("Got data: ");
  Serial.write((unsigned char*)dataString, frameLength);
  Serial.println();
#endif

  //dataString will be a number indicating degrees, from 0 to 180
  //we convert here from characters to a number. It will be  frameLength
  //or otherwise 3 characters max (3 decimal digits).
  
  int pos=0;
  
  for(int i=0;i< frameLength || i <3;++i){
    //in ASCII digits are characters with values between
    //48 (0) and 57 (9). Thus if the input is not between those 
    //values, it is not a number.
    if(dataString[i]<48 || data[pos]>57){
      sendMessage(socket,"INCORRECT MESSAGE");
      return; 
    }
    
    
    
  }
  

//
//  //we process the data:
//  dataString[frameLength]='\0'; //It is not properly formatted!!
//  ServoData sdata(dataString);
//
//  if(!sdata.isValid()){
//    sendMessage(socket,"INCORRECT MESSAGE");
//    return;
//  }
//  char message[100];
//  switch(sdata.getCommand()){
//      case 'a': //attach
//        servos.attach(sdata.getIndex());
//        sprintf(message,"%d attached.",sdata.getIndex());
//        break;
//      case 'd':
//        servos.detach(sdata.getIndex());
//        sprintf(message,"%d detached.",sdata.getIndex());
//      case 'm':
//        servos.setDestination(sdata.getIndex(),sdata.getVal());
//        sprintf(message,"%d move to %d",sdata.getIndex(),sdata.getVal());
//        break;
//      case 's':
//        servos.setSpeed(sdata.getIndex(),sdata.getVal());
//        sprintf(message,"%d speed to %d",sdata.getIndex(),sdata.getVal());
//        break;
//      default:
//        sprintf(message,"ERROR IN PROCESSING COMMAND");
//  }

  sendMessage(socket,message);

#ifdef DEBUG
  Serial.println(message);
#endif

}


void setup() {
#ifdef DEBUG  
  Serial.begin(57600);
#endif
  //Ethernet.begin(mac, ip);

// start the Ethernet connection:
if (Ethernet.begin(mac) == 0) {
  Serial.println("Failed to configure Ethernet using DHCP");
  // try to congifure using IP address instead of DHCP:
  Ethernet.begin(mac, ip);
}



#ifdef DEBUG  
  Serial.print("Server address: ");
  Serial.println(Ethernet.localIP());
#endif
  
  wsServer.registerConnectCallback(&onConnect);
  wsServer.registerDataCallback(&onData);
  wsServer.registerDisconnectCallback(&onDisconnect);  
  wsServer.begin();
  
  delay(100); // Give Ethernet time to get ready
}

void loop(){
  // Should be called for each loop.
  wsServer.listen();
  //this is the way we do if they have speed...
  servos.update();
}
