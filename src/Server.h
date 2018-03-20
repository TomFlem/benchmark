#ifndef SERVER_H
#define SERVER_H
#include <stdio.h>
#include <iostream>

#include "RTIMULib.h"
#include "open62541.h"
namespace server
{
class Server
{
public:
   Server ();
   ~Server ();

   bool setupServer(int);
   bool stopServer();
   bool runServer(bool *);
   
   RTIMU * getIMU();
   RTPressure * getRTPressure();
   RTHumidity * getRTHumidity();
private:  

   UA_Server *server;
   RTIMUSettings *settings;
   RTIMU *imu;
   RTPressure *pressure;
   RTHumidity *humidity;
   
   void addNodes();
};
}
#endif
