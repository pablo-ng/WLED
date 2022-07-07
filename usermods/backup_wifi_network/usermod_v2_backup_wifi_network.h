#pragma once

#include "wled.h"

class UsermodBackupWifiNetwork : public Usermod {

  private:

    bool updatedWifiConfig = false;

    bool enableBackupWifiNetwork;
    String clientSSID2;
    String clientPass2;
    unsigned long mainNetworkTimeoutMs;

  public:

    void setup() {
    }

    void connected() {
    }

    void loop() {
      if (enableBackupWifiNetwork && !updatedWifiConfig && !WLED_CONNECTED && millis() > mainNetworkTimeoutMs) {
        strncpy(clientSSID, clientSSID2.c_str(), sizeof(clientSSID));
        clientSSID[sizeof(clientSSID) - 1] = 0;

        strncpy(clientPass, clientPass2.c_str(), sizeof(clientPass));
        clientPass[sizeof(clientPass) - 1] = 0;

        updatedWifiConfig = true;
      }
    }

    void addToConfig(JsonObject& root)
    {
      JsonObject top = root.createNestedObject("usermodBackupWifiNetwork");
      top["enableBackupWifiNetwork"] = enableBackupWifiNetwork;
      top["clientSSID2"] = clientSSID2;
      top["clientPass2"] = clientPass2;
      top["mainNetworkTimeoutMs"] = mainNetworkTimeoutMs;
    }

    bool readFromConfig(JsonObject& root)
    {
      JsonObject top = root["usermodBackupWifiNetwork"];
      bool configComplete = !top.isNull();
      configComplete &= getJsonValue(top["enableBackupWifiNetwork"], enableBackupWifiNetwork, false);  
      configComplete &= getJsonValue(top["clientSSID2"], clientSSID2, "");  
      configComplete &= getJsonValue(top["clientPass2"], clientPass2, "");
      configComplete &= getJsonValue(top["mainNetworkTimeoutMs"], mainNetworkTimeoutMs, 10000);
      return configComplete;
    }

};
