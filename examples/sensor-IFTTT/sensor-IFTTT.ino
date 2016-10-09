#include <SPI.h>
#include <Adafruit_WINC1500.h>


// Define the WINC1500 board connections below.
// If you're following the Adafruit WINC1500 board
// guide you don't need to modify these:
#define WINC_CS   8
#define WINC_IRQ  7
#define WINC_RST  4
#define WINC_EN   2     // or, tie EN to VCC and comment this out
// The SPI pins of the WINC1500 (SCK, MOSI, MISO) should be
// connected to the hardware SPI port of the Arduino.
// On an Uno or compatible these are SCK = #13, MISO = #12, MOSI = #11.
// On an Arduino Zero use the 6-pin ICSP header, see:
//   https://www.arduino.cc/en/Reference/SPI

// Setup the WINC1500 connection with the pins above and the default hardware SPI.
Adafruit_WINC1500 WiFi(WINC_CS, WINC_IRQ, WINC_RST);

// Or just use hardware SPI (SCK/MOSI/MISO) and defaults, SS -> #10, INT -> #7, RST -> #5, EN -> 3-5V
//Adafruit_WINC1500 WiFi;



//char ssid[] = "RISD-MiscDevices";     //  your network SSID (name)
//char pass[] = "T3chn0l0gy!";  // your network password
char ssid[] = "usagi";     //  your network SSID (name)
char pass[] = "2008505505";  // your network password

int keyIndex = 0;                // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(141,101,112,175);  // numeric IP for test page (no DNS)
char server[] = "maker.ifttt.com";    // domain name for test page (using DNS)
#define webpage "/trigger/switch_detected/with/key/dY61k0AtTbt2D293AhfiAm"  // path to test page


// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP, 443 for HTTPS):
Adafruit_WINC1500SSLClient client;

// define your sensor pin 
int buttonPin = 12;
int buttonState = 1;
int sensorPin = A0;
int sensorState = 0;


void setup() {
/************ Sensor Setup ***************/
//Put your sensor setup her:
pinMode(buttonPin, INPUT_PULLUP);


/************ Initialize serial and wait for port to open *****/
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

/************ establishing connection to internet ***********/

//Enabling the wifi module
#ifdef WINC_EN
  pinMode(WINC_EN, OUTPUT);
  digitalWrite(WINC_EN, HIGH);
#endif

  Serial.println("WINC1500 Web client test");

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }
  
// attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    uint8_t timeout = 10;
    while (timeout && (WiFi.status() != WL_CONNECTED)) {
      timeout--;
      delay(1000);
    }
  }

  Serial.println("Connected to wifi");
  printWifiStatus();

}

void loop() {

  /************* Reading sensor Data ***********/
  buttonState = digitalRead (buttonPin);
//  Serial.print("buttonState: ");
//  Serial.println(buttonState);
  
  /************* update data to ifttt when the switch is triggered ***********/
  
  
  if (buttonState == 0){

    Serial.println("sensor triggered.");
    updateIFTTT(buttonState);
  }



/************ Check wifi connection status *******/
  while (WiFi.status() != WL_CONNECTED) {
    
    Serial.print("Lost wifi connection, ");
    Serial.println("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    uint8_t timeout = 10;
    while (timeout && (WiFi.status() != WL_CONNECTED)) {
      timeout--;
      delay(1000);
    }
  }

  
}

void updateIFTTT(int sensorVal){
  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, 443)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.print("POST ");
    client.print(webpage);
    client.println(" HTTP/1.1");

    client.print("Host: "); 
    client.println(server);

    client.println("Connection: close");
    
    client.println("Content-Type: application/json");

    String val1 = String(sensorVal);
    
    String json = "{\"value1\":\""+val1+"\"}";
    Serial.println(json);
    Serial.println(json.length());
    
    client.print("Content-Length: "); 
    client.println(json.length());
    client.println();

    client.println(json);
  }

  delay(1000);

  Serial.println("waiting for confirmation...");

  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
