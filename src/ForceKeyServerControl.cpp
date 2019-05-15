#include <ForceKeyServerControl.h>

ForceKeyServerControl::ForceKeyServerControl(const String & name, const String &url, ForceKey *forceKey, ESP8266WebServer *server):
    WiFiControl(name, url, "ForceKey", server)
{
    this->forceKey = forceKey;
}

void ForceKeyServerControl::setup()
{
    getServer()->on(getUrl(), std::bind(&ForceKeyServerControl::serverhandleInfo, this));
    getServer()->on(getUrl() + "/on", std::bind(&ForceKeyServerControl::serverHandleRelayOn, this));
    getServer()->on(getUrl() + "/off", std::bind(&ForceKeyServerControl::serverHandleRelayOff, this));
    getServer()->on(getUrl() + "/toggle", std::bind(&ForceKeyServerControl::serverHandleRelayToggle, this));
    getServer()->on(getUrl() + "/status", std::bind(&ForceKeyServerControl::serverHandleRelayStatus, this));
    getServer()->on(getUrl() + "/ratio", std::bind(&ForceKeyServerControl::serverHandleRelayRatio, this));
}

void ForceKeyServerControl::serverhandleInfo()
{
    String path = "<br><a href=\"" + getUrl();
    String message = getName() + ": " + getStatus();
    message += path + "/ratio\">ratio: "+ String(forceKey->getRatio()) + "</a>";
    message += path + "/on\">on</a>";
    message += path + "/off\">off</a>";
    message += path + "/toggle\">Toggle</a>";
    message += path + "/status\">Status</a>";
    getServer()->send(200, "text/html", message);
}

void ForceKeyServerControl::serverHandleRelayOn()
{
    relayEnable();
    getServer()->send(200, "text/plain", "OK");
}

void ForceKeyServerControl::serverHandleRelayOff()
{
    relayDisable();
    getServer()->send(200, "text/plain", "OK");
}

void ForceKeyServerControl::serverHandleRelayToggle()
{
    relayToggle();
    getServer()->send(200, "text/plain", getStatus());
}

void ForceKeyServerControl::serverHandleRelayStatus()
{
    getServer()->send(200, "text/plain", getStatus());
}

void ForceKeyServerControl::serverHandleRelayRatio()
{
    String strRatio = getServer()->arg("ratio");
    if (strRatio ==  "")
    {
        getServer()->send(200, "text/plain", String(forceKey->getRatio()));
        return;
    }
    float ratio = strRatio.toFloat();
    forceKey->setRatio(ratio);
    getServer()->send(200, "text/plain", "OK");
}

String ForceKeyServerControl::getStatus()
{
    return isEnabled() ? "ON" : "OFF";
}
