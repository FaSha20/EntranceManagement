// // include the library code:
// #include <EtherCard.h> //library for ethernet

int count = 0;
char c;
String id;
char id_input[50] = "hello";

// // Static IP configuration
static byte myip[] = { 192,168,2,2 }; // Arduino's static IP address
static byte gwip[] = { 192,168,2,1 }; // Gateway IP address

// // MAC address of the Arduino
// static byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };

// // Ethernet buffer size
// byte Ethernet::buffer[700];

// void sendHttpResponse(char* id) {
//   char htmlResponse[400];
//   sprintf(htmlResponse,
//           "HTTP/1.1 200 OK\r\n"
//           "Content-Type: text/html\r\n"
//           "Connection: close\r\n"
//           "\r\n"
//           "<!DOCTYPE html>\r\n"
//           "<html>\r\n"
//           "<head>\r\n"
//           "<title>Entrance Management</title>\r\n"
//           "<meta http-equiv='refresh' content='3'>\r\n"
//           "</head>\r\n"
//           "<body>\r\n"
//           "<h1>Welcome to Entrance Management Platform!</h1>\r\n"
//           "<p>ID is %s</p>\r\n"
//           "</body>\r\n"
//           "</html>\r\n",
//           id);
//   // Send response
//   memcpy(ether.tcpOffset(), htmlResponse, strlen(htmlResponse));
//   ether.httpServerReply(strlen(htmlResponse));
// }

// void setup()
// {
//   Serial.begin(9600);
//   Serial.println("Please scan your RFID Card");

//   // Begin Ethernet communication with buffer size and MAC address
//   ether.begin(sizeof Ethernet::buffer, mymac, SS);

//   // Configure static IP and gateway IP
//   ether.staticSetup(myip, gwip);

// }

// void loop()
// {
//   while (Serial.available() > 0){
//       c = Serial.read();
//       count++;
//       id += c;
//       if (count == 9 ){
//         id.toCharArray(id_input, 50);
//         break;
//       }
//   }  
//   count = 0;
//   id = "";
//   delay(500);

//   word pos = ether.packetLoop(ether.packetReceive());
//   if (pos) {

//     sendHttpResponse(id_input);

//   }  

// }


 

// // // Welcome page HTML content (stored in PROGMEM)
// // const char welcomePage[] PROGMEM =
// //   "<!DOCTYPE html>"
// //   "<html lang='en'>"
// //   "<head>"
// //   "<meta charset='UTF-8'>"
// //   "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
// //   "<title>Electronics Tree</title>"
// //   "<style>"
// //   "body {"
// //   "font-family: Arial, sans-serif;"
// //   "background-color: #f0f0f0;"
// //   "text-align: center;"
// //   "padding: 20px;"
// //   "}"
// //   "h1 {"
// //   "color: #333333;"
// //   "}"
// //   "p {"
// //   "color: #666666;"
// //   "}"
// //   "</style>"
// //   "</head>"
// //   "<body>"
// //   "<h1>Electronics Tree's Hands-On Journey</h1>"
// //   "<p>Welcome to Electronics Tree, where our name isn’t just a title—it’s a "
// //   "commitment to practical growth in your knowledge and skills."
// //   "Think of it like planting a seed.</p>"
// //   "Recived id is: %s"
// //   "</body>"
// //   "</html>";


#include <EtherCard.h>


static byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 }; // Arduino's MAC address
byte Ethernet::buffer[500]; // Ethernet buffer size

void setup() {
  pinMode(4, OUTPUT);
  ether.begin(sizeof Ethernet::buffer, mymac, SS); // Initialize Ethernet with buffer size and MAC address
  ether.staticSetup(myip, gwip); // Set static IP and gateway
}



void loop() {
  while (Serial.available() > 0){
      c = Serial.read();
      count++;
      id += c;
      digitalWrite(4, HIGH);
      delay(1000);
      digitalWrite(4, LOW);
      if (count != 9 ){
        id.toCharArray(id_input, 50);
        digitalWrite(4, HIGH);
        break;
      }
  }  
  count = 0;
  id = "";
  delay(500);

  char htmlResponse[250]; // Buffer for HTML response
  // Construct HTML response with potentiometer value
  sprintf(htmlResponse, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n"
                        "<html>\r\n"
                        "<head>\r\n"
                        "<meta http-equiv='refresh' content='3'>\r\n"
                        "</head>\r\n"
                        "<body>\r\n"
                        "Potentiometer value: %s\r\n"
                        "</body>\r\n"
                        "</html>\r\n", id_input);

  word pos = ether.packetLoop(ether.packetReceive());
  if (pos) {
    char *data = (char *)Ethernet::buffer + pos; // Pointer to packet data
    // Copy HTML response to Ethernet buffer
    memcpy(ether.tcpOffset(), htmlResponse, strlen(htmlResponse));
    // Send HTTP server reply with HTML response length
    ether.httpServerReply(strlen(htmlResponse));
  }
  
}
 