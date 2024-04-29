// include the library code:
#include <EtherCard.h> //library for ethernet

const int RedlED = 5;
const int GreenlED = 4;
const int DCmotor1 = 7;
const int DCmotor2 = 6;

bool isOpen = false;
int count = 0;
char c;
String id;
char id_input[50] = "hello";

// Static IP configuration
static byte myip[] = { 192,168,2,2 }; // Arduino's static IP address
static byte gwip[] = { 192,168,2,1 }; // Gateway IP address

// MAC address of the Arduino
static byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };

// Ethernet buffer size
byte Ethernet::buffer[700];

// Welcome page HTML content (stored in PROGMEM)
const char welcomePage[] PROGMEM =
  "<!DOCTYPE html>"
  "<html lang='en'>"
  "<head>"
  "<meta charset='UTF-8'>"
  "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
  "<title>Electronics Tree</title>"
  "<style>"
  "body {"
  "font-family: Arial, sans-serif;"
  "background-color: #f0f0f0;"
  "text-align: center;"
  "padding: 20px;"
  "}"
  "h1 {"
  "color: #333333;"
  "}"
  "p {"
  "color: #666666;"
  "}"
  "</style>"
  "</head>"
  "<body>"
  "<h1>Electronics Tree's Hands-On Journey</h1>"
  "<p>Welcome to Electronics Tree, where our name isn’t just a title—it’s a "
  "commitment to practical growth in your knowledge and skills."
  "Think of it like planting a seed.</p>"
  "Recived id is: %s"
  "</body>"
  "</html>";



void sendHttpResponse(char* id) {
  char htmlResponse[400];
  sprintf(htmlResponse,
          "HTTP/1.1 200 OK\r\n"
          "Content-Type: text/html\r\n"
          "Connection: close\r\n"
          "\r\n"
          "<!DOCTYPE html>\r\n"
          "<html>\r\n"
          "<head>\r\n"
          "<title>Entrance Management</title>\r\n"
          "</head>\r\n"
          "<body>\r\n"
          "<h1>Welcome to Entrance Management Platform!</h1>\r\n"
          "<p>ID is %s</p>\r\n"
          "<p><a href=\"/led/on\">Turn On</a> | <a href=\"/led/off\">Turn Off</a></p>\r\n"
          "</body>\r\n"
          "</html>\r\n",
          id);
  // Send response
  memcpy(ether.tcpOffset(), htmlResponse, strlen(htmlResponse));
  ether.httpServerReply(strlen(htmlResponse));
}

void setup()
{
  Serial.begin(9600);
  pinMode(RedlED, OUTPUT);
  pinMode(GreenlED, OUTPUT);
  pinMode(DCmotor1, OUTPUT);
  pinMode(DCmotor2, OUTPUT);
  Serial.println("Please scan your RFID Card");

  // Begin Ethernet communication with buffer size and MAC address
  ether.begin(sizeof Ethernet::buffer, mymac, SS);

  // Configure static IP and gateway IP
  ether.staticSetup(myip, gwip);

}

void loop()
{
  while (Serial.available() > 0){
      c = Serial.read();
      count++;
      id += c;
      if (count == 9 ){
        // if(id == "810199440"){
        //    digitalWrite(GreenlED, HIGH);
        // }
        id.toCharArray(id_input, 50);
        break;
      }
  }  
  count = 0;
  id = "";
  delay(500);

  word pos = ether.packetLoop(ether.packetReceive());
  if (pos) {
    // Extract data from Ethernet buffer
    char *data = (char *)Ethernet::buffer + pos;
    
    sendHttpResponse(id_input);
    
  }  
 

}


  // while (Serial.available() > 0)
  // {
  //   c = Serial.read();
  //   count++;
  //   id += c;
  //   if (count == 9)
  //   {
  //     Serial.print(id);
  //     //break;

  //     if (id == "810199440")
  //     {
  //       sprintf(htmlResponse, 
  //             "<!DOCTYPE html>"
  //             "<html lang='en'>"
  //             "<head>"
  //             "<meta charset='UTF-8'>"
  //             "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
  //             "<title>Electronics Tree</title>"
  //             "<style>"
  //             "body {"
  //             "font-family: Arial, sans-serif;"
  //             "background-color: #f0f0f0;"
  //             "text-align: center;"
  //             "padding: 20px;"
  //             "}"
  //             "h1 {"
  //             "color: #333333;"
  //             "}"
  //             "p {"
  //             "color: #666666;"
  //             "}"
  //             "</style>"
  //             "</head>"
  //             "<body>"
  //             "<h1>Electronics Tree's Hands-On Journey</h1>"
  //             "<p>Welcome to Electronics Tree, where our name isn’t just a title—it’s a "
  //             "commitment to practical growth in your knowledge and skills."
  //             "Think of it like planting a seed.</p>"
  //             "Recived id is: %s"
  //             "</body>"
  //             "</html>", id);

  //       digitalWrite(GreenlED, HIGH);

  //       //open the door
  //       digitalWrite(DCmotor1, HIGH);
  //       delay(100);
  //       digitalWrite(DCmotor1, LOW);
  //       isOpen = true;

  //       delay(1000);
  //       digitalWrite(GreenlED, LOW);
        
  //       // close the door
  //       digitalWrite(DCmotor2, HIGH);
  //       delay(100);
  //       digitalWrite(DCmotor2, LOW);
  //       isOpen = false;

  //     }

  //     else
  //     {
  //       if(isOpen == true){
  //         digitalWrite(DCmotor2, HIGH);
  //         delay(100);
  //         digitalWrite(DCmotor2, LOW);
  //       }
      
  //       digitalWrite(RedlED, HIGH);
  //       delay(1000);
  //       digitalWrite(RedlED, LOW);
      
  //     }
  //   }
  // }
  // count = 0;
  // id = "";
  // delay(500);



// void loop() {
//   // Handle incoming Ethernet packets and get the position of the data
//   word pos = ether.packetLoop(ether.packetReceive());

//   // If data is received
//   if (pos) {
//     // Extract data from Ethernet buffer
//     char *data = (char *)Ethernet::buffer + pos;

//     // Copy the welcome page content to the Ethernet buffer
//     memcpy_P(ether.tcpOffset(), welcomePage, sizeof welcomePage);

//     // Send HTTP response with the welcome page to the client
//     ether.httpServerReply(sizeof welcomePage - 1);
//   }
// }

 