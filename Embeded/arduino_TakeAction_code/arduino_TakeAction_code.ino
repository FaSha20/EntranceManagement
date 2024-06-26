#include <EtherCard.h>

const int RedlED = 5;
const int GreenlED = 4;
const int DCmotor1 = 7;
const int DCmotor2 = 6;

bool isOpen = false;
bool done = false;

// // Static IP configuration
static byte myip[] = { 192,168,2,2 }; // Arduino's static IP address
static byte gwip[] = { 192,168,2,1 }; // Gateway IP address

// Ethernet MAC address - must be unique on your network
static byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };

// LED pin
const int ledPin = 5;

byte Ethernet::buffer[700];  // TCP/IP send and receive buffer
int startTime;


void DoEnteryActions(){
  //turn LED on
  digitalWrite(GreenlED, HIGH);
  //open the door
  digitalWrite(DCmotor1, HIGH);
  delay(100);
  digitalWrite(DCmotor1, LOW);
  isOpen = true;
  startTime = millis();

  delay(500);

  //turn LED off
  digitalWrite(GreenlED, LOW);
}

void DoPreventiveActions(){
  //Close the door if it is open
  if(isOpen == true){
    closeTheDoor();
  }

  //turn LED off
  digitalWrite(RedlED, HIGH);
  delay(500);
  digitalWrite(RedlED, LOW);
}

void closeTheDoor(){
  digitalWrite(DCmotor2, HIGH);
  delay(100);
  digitalWrite(DCmotor2, LOW);
  isOpen = false;
}

void setup() {
  pinMode(RedlED, OUTPUT);
  pinMode(GreenlED, OUTPUT);
  pinMode(DCmotor1, OUTPUT);
  pinMode(DCmotor2, OUTPUT);
  // Initialize Ethernet connection
  ether.begin(sizeof Ethernet::buffer, mymac, SS);

  // Set static IP if defined
  ether.staticSetup(myip, gwip);

  // Set LED pin as output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Listen for incoming packets and respond
  if(millis() - startTime > 3000 and isOpen){
    closeTheDoor();
  }
  word pos = ether.packetLoop(ether.packetReceive());
  if (pos) {
    // Data received, process HTTP request
    char *data = (char *)Ethernet::buffer + pos;
    // Check if the request contains "GET /led/on"
    if (strstr(data, "200")) {
      if(!done){
        DoEnteryActions();
        done = true;
      }
    } 
    else {
      DoPreventiveActions();
      done = false;
    }
    
    // // Send HTML response
    sendHttpResponse();
    // ether.httpServerReplyAck();
  }
}

void sendHttpResponse() {
  // Create HTML response with LED state
  char htmlResponse[400];
  sprintf(htmlResponse,
          "HTTP/1.1 200 OK\r\n"
          "Content-Type: text/html\r\n"
          "Connection: close\r\n"
          "\r\n"
          );
  // Send response
  memcpy(ether.tcpOffset(), htmlResponse, strlen(htmlResponse));
  ether.httpServerReply(strlen(htmlResponse));
}

// "GET /led/off"