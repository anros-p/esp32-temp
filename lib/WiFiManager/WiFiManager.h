#pragma once

#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include "FS.h"
#include "esp_system.h"
#include <string.h>
#include <esp_wifi.h>
#include <WiFi.h>
#include <Preferences.h>

// typedef enum
// {
//     WIFI_MGR_UNKNOWN,
//     WIFI_MGR_CONNECTED,
//     WIFI_MGR
// } wifi_manager_connection_status_t;

class WiFiManager 
{
    public:
        WiFiManager();
        void begin();
        bool isConnected();
        bool isConfigured();
        void configure();
        void connect();        
        void disconnect();

    private:
        const char *_ssid;
        const char *_password;
        Preferences _preferences;
        String _prefssid;
        String _prefpassword;
        bool _isConfigured;                
};

#endif