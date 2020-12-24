#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <NetworkIdentify.h>
#include <WiFiConnector.h>
#include <SmartDelay.h>
#include <ForceKey.h>
#include <ForceKeyServerControl.h>
#include <LedRgbControl.h>

#define BUTTON_PIN D1
#define RELAY_PIN D2
#define RED_PIN D3
#define GREEN_PIN D5
#define BLUE_PIN D6

NetworkIdentify networkIdentify("TestEsp", "ControlsDevice", 54545);
WiFiConnector connector("ssid", "password");
SmartDelay relayDelay(10UL);
SmartDelay buttonDelay(50UL);
ForceKey relay(RELAY_PIN, 0, 1024, 10);
ESP8266WebServer server(80);
int buttonState;

LedRgbControl ledRgbControl("LedRgb", "/led_rgb", RED_PIN, GREEN_PIN, BLUE_PIN, 0, 1024, 10, &server);
ForceKeyServerControl relayControl("Light", "/relay", &relay, &server, &ledRgbControl);


void serverHandleRoot()
{
  String message = "<br><a href=\"" + relayControl.getUrl() + "\">" + relayControl.getName() + "</a>";
  message += "<br><a href=\"" + ledRgbControl.getUrl() + "\">" + ledRgbControl.getName() + "</a>";
  message += "<br><a href=\"/controls\">Controls</a>";
  server.send(200, "text/html", message);
}

void serverHandleControls()
{
  String message = "[";
  message += "{\"name\": \"" + relayControl.getName() + "\", \"type\": \"" + relayControl.getType() + "\", \"url\": \"" +  relayControl.getUrl() + "\"}, ";
  message += "{\"name\": \"" + ledRgbControl.getName() + "\", \"type\": \"" + ledRgbControl.getType() + "\", \"url\": \"" +  ledRgbControl.getUrl() + "\"}";
  message += "]";
  server.send(200, "application/json", message);
}

void serverHandleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++)
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";

  server.send(404, "text/plain", message);
}

void serverStart()
{
  if (MDNS.begin("esp8266")) 
  {
    Serial.println("MDNS responder started");
  }

  server.on("/", serverHandleRoot);
  server.on("/controls", serverHandleControls);
  server.onNotFound(serverHandleNotFound);
  server.begin();
  Serial.print("HTTP server started ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
}

void setup()
{
  Serial.begin(115200);

  relay.setup();
  ledRgbControl.setup();
  relayControl.setup();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  buttonState = digitalRead(BUTTON_PIN);

  connector.connect();
  serverStart();
  networkIdentify.setup();
}

void loop()
{
  if (connector.isConnected())
  {
    networkIdentify.handle();
    server.handleClient();
  }
  
  if (relayDelay.now())
  {
    relay.update();
    ledRgbControl.update();
  }

  if (buttonDelay.now())
  {
    int newButtonState = digitalRead(BUTTON_PIN);
    if (newButtonState != buttonState)
    {
      buttonState = newButtonState;
      relay.toggle();
      ledRgbControl.setEnabled(!relay.isLow());
    }
  }
  delay(10);
}
