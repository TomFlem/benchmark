#ifndef CLIENT_H
#define CLIENT_H
#include <stdio.h>
#include <iostream>

#include "RTIMULib.h"
#include "open62541.h"
namespace client
{
class Client
{
public:
   Client ();
   ~Client ();
   
   bool setupSensorPoller(std::string);
   void runSensorPoller();
private:  
   UA_Client *client;
   RTIMUSettings *settings;
   RTIMU *imu;
   RTPressure *pressure;
   RTHumidity *humidity;
};
}
#endif
