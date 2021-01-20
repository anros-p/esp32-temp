#include "WiFiManager.h"

WiFiManager::WiFiManager()
{
    this->_isConfigured = false;
}

void WiFiManager::begin()
{
    log_d("Entering begin");
    WiFi.mode(WIFI_AP_STA);
    wifi_config_t config;
    esp_wifi_get_config(WIFI_IF_STA, &config);
    this->_ssid = reinterpret_cast<const char *>(config.sta.ssid);
    this->_password = reinterpret_cast<const char *>(config.sta.password);
    this->_preferences.begin("wifi", false);
    this->_prefssid = this->_preferences.getString("ssid", "notconfigured");
    this->_prefpassword = this->_preferences.getString("password", "notconfigured");
    this->_preferences.end();
    

    String nvssid = String(this->_ssid);
    String nvpassword = String(this->_password);

    //log_d("prefssid: %s\nprefpassword: %s\nnvssid: %s\nnvpassword: %s", this->_prefssid, this->_prefpassword, nvssid, nvpassword);
    Serial.print("prefssid: ");
    Serial.println(this->_prefssid);
    Serial.print("prefpassword: ");
    Serial.println(this->_prefpassword);
    Serial.print("nvssid: ");
    Serial.println(nvssid);
    Serial.print("nvpassword: ");
    Serial.println(nvpassword);

    if (nvssid.equals(this->_prefssid) && nvpassword.equals(this->_prefpassword)) {
        this->_isConfigured = true;
    }
}

bool WiFiManager::isConnected() 
{
    log_d("isConnected: %s", WiFi.isConnected());
    return WiFi.isConnected();
}

void WiFiManager::configure()
{
    WiFi.beginSmartConfig();

    while (!WiFi.smartConfigDone())
    {
        Serial.print(".");
        delay(50);
    }

    Serial.println("\nSmartConfig received, waiting for WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(50);
    }
    wifi_config_t config;
    esp_wifi_get_config(WIFI_IF_STA, &config);
    this->_ssid = reinterpret_cast<const char *>(config.sta.ssid);
    this->_password = reinterpret_cast<const char *>(config.sta.password);
    this->_preferences.begin("wifi", false);
    this->_preferences.putString("ssid", this->_ssid);
    this->_preferences.putString("password", this->_password);
    this->_preferences.end();
    WiFi.disconnect();
}

bool WiFiManager::isConfigured()
{
    return this->_isConfigured;
}

void WiFiManager::connect()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        WiFi.begin();
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(10);
        }
    }
}

void WiFiManager::disconnect()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        WiFi.disconnect();
    }
}