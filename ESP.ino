// ======================================================
//        ESP8266 IoT Circuit Breaker Code
// ======================================================

#include <ESP8266WiFi.h>

// ---------------- WIFI DETAILS ----------------
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// ---------------- SERVER ----------------
WiFiServer server(80);

// ---------------- RELAY PIN ----------------
int relayPin = D1;

// ======================================================
// SETUP
// ======================================================

void setup() {

  // Serial Start
  Serial.begin(9600);

  // Relay Output
  pinMode(relayPin, OUTPUT);

  // Relay OFF Initially
  digitalWrite(relayPin, LOW);

  // ==================================================
  // WIFI CONNECT
  // ==================================================

  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  // ==================================================
  // CONNECTED
  // ==================================================

  Serial.println();
  Serial.println("WiFi Connected");

  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());

  // Start Server
  server.begin();

  Serial.println("Server Started");
}

// ======================================================
// LOOP
// ======================================================

void loop() {

  // Check Client
  WiFiClient client = server.available();

  if (!client) {
    return;
  }

  Serial.println("New Client");

  // Read Browser Request
  String request = client.readStringUntil('\r');

  Serial.println(request);

  client.flush();

  // ==================================================
  // RELAY CONTROL
  // ==================================================

  // Turn ON
  if (request.indexOf("/ON") != -1) {

    digitalWrite(relayPin, HIGH);

    Serial.println("Breaker ON");
  }

  // Turn OFF
  if (request.indexOf("/OFF") != -1) {

    digitalWrite(relayPin, LOW);

    Serial.println("Breaker OFF");
  }

  // ==================================================
  // WEBPAGE
  // ==================================================

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");

  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.println("<head>");
  client.println("<title>IoT Circuit Breaker</title>");
  client.println("</head>");

  client.println("<body style='text-align:center; font-family:Arial;'>");

  client.println("<h1>IoT Based Circuit Breaker</h1>");

  client.println("<h2>Khushi Raikwar</h2>");

  client.println("<h3>Govt Polytechnic College Satna</h3>");

  client.println("<br>");

  // ON Button
  client.println("<a href=\"/ON\">");
  client.println("<button style='height:60px; width:120px; font-size:20px;'>ON</button>");
  client.println("</a>");

  client.println("<br><br>");

  // OFF Button
  client.println("<a href=\"/OFF\">");
  client.println("<button style='height:60px; width:120px; font-size:20px;'>OFF</button>");
  client.println("</a>");

  client.println("</body>");
  client.println("</html>");

  delay(1);

  Serial.println("Client Disconnected");
}
