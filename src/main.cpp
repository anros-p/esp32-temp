#include <WiFi.h>
#include "WiFiManager.h"

WiFiManager wifimgr;

void setup()
{
    Serial.begin(115200);
    delay(1000);

    wifimgr.begin();
    if (!wifimgr.isConfigured()) {
        Serial.println("WiFi not configured, starting configuration");
        wifimgr.configure();
    }

    Serial.println("Initialization done");
}

void loop()
{
    unsigned long time = millis();
    wifimgr.connect();
    unsigned long tt = millis() - time;
    Serial.print("time taken: ");
    Serial.print(tt);
    Serial.println("ms");
    Serial.println(WiFi.localIP());    
    delay(5000);
}
