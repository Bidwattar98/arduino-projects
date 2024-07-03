#include <WiFi.h>
#include <Servo.h>

// Replace with your network credentials
const char* ssid = "Redmi Note 10 Pro Max";
const char* password = "supersecretpassword";

WiFiServer server(80);

Servo servo1;
Servo servo2;

int servo1Pos = 0;
int servo2Pos = 0;
bool toggleState = false;

void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.begin();
  Serial.println("Server started.");

  // Attach the servos to pins
  servo1.attach(9); // Adjust pin as needed
  servo2.attach(10); // Adjust pin as needed

  // Initial servo positions
  servo1.write(servo1Pos);
  servo2.write(servo2Pos);
}

void loop() {
  WiFiClient client = server.available(); // Listen for incoming clients

  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          // If the current line is blank, you got two newline characters in a row.
          // That's the end of the client HTTP request, so send a response.
          if (currentLine.length() == 0) {
            // Send the HTTP response
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("<html><body><h1>Servo Control</h1>");
            client.println("<button onclick=\"toggleServo()\">Toggle Servo</button>");
            client.println("<script>");
            client.println("function toggleServo() {");
            client.println("  var xhr = new XMLHttpRequest();");
            client.println("  xhr.open('GET', '/toggle', true);");
            client.println("  xhr.send();");
            client.println("}");
            client.println("</script>");
            client.println("</body></html>");
            client.println();

            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
          // Check if the HTTP request is for /toggle
          if (currentLine.endsWith("GET /toggle ")) {
            toggleState = !toggleState; // Toggle the state
            if (toggleState) {
              servo1.write(180); // Move to 180 degrees
              servo2.write(180); // Move to 180 degrees
            } else {
              servo1.write(0); // Move back to 0 degrees
              servo2.write(0); // Move back to 0 degrees
            }
          }
        }
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}

// ip address of this arduino board: 192.168.217.124
// serial monitor has to be set at 115200 braud
