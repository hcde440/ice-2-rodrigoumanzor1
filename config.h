/************************ Adafruit IO Config *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME    "rodrigoumanzor"
#define IO_KEY         "55575ec8c52b4f9ea65554e909e8f4cc"

/******************************* WIFI **************************************/

#define WIFI_SSID       "STC2"
#define WIFI_PASS       "bahtsang"

// comment out the following two lines if you are using fona or ethernet
#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
