#include <SPI.h>
#include <Ethernet.h>

// Enabe debug tracing to Serial port.
#define DEBUG

// Here we define a maximum framelength to 64 bytes. Default is 256.
#define MAX_FRAME_LENGTH 64

#include <WebSocket.h>

//This is the mac address. It needs to be different for every connected device
//Ethernet shields have usually a mac Address given on a sticker attached to them.
byte mac[] = { 0x90, 0xA2, 0xDA, 0x=0F, 0x0E, 0x61 }; 
//in case DHCP does not work, or we want to hardcode the IP
byte ip[] = {130, 237, 11,243};

// Create a Websocket server
WebSocket wsServer;

void onConnect(WebSocket &socket) {
  Serial.println("onConnect called");
}


// You must have at least one function with the following signature.
// It will be called by the server when a data frame is received.
void onData(WebSocket &socket, char* dataString, byte frameLength) {
  
#ifdef DEBUG
  Serial.print("Got data: ");
  Serial.write((unsigned char*)dataString, frameLength);
  Serial.println();
#endif

  //we process the data here:
  char command=dataString[0];
  uint8_t val=dataString[1]-48;
  Serial.println(val);
  switch (command) {
      case 'O':
        pinMode(val, OUTPUT);
        sendMessage(socket,"OK");
        break;
      case 'I':
        pinMode(val, INPUT);
        sendMessage(socket,"OK");
        break;
      case 'L':
        digitalWrite(val, LOW);
        sendMessage(socket,"OK");
        break;
      case 'H':
        digitalWrite(val, HIGH);
        sendMessage(socket,"OK");
        break;
      default:
        sendMessage(socket,"UNKNOWN COMMAND");
  }

  // Just echo back data for fun.
  //socket.send(dataString, strlen(dataString));
}

void sendMessage(WebSocket &socket, char* message){
  socket.send(message, strlen(message));
}

void onDisconnect(WebSocket &socket) {
  Serial.println("onDisconnect called");
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

void loop() {
  // Should be called for each loop.
  wsServer.listen();
  
  // // Do other stuff here, but don't hang or cause long delays.
  // delay(100);
  // if (wsServer.isConnected()) {
  //   wsServer.send("abc123", 6);
  // }

}
