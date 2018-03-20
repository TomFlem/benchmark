#ifndef CLIENT_H
#define CLIENT_H
#include <stdio.h>
#include <iostream>

#include "open62541.h"
namespace client
{
class Client
{
public:
   Client (bool *);
   ~Client ();
   
   bool setupSensorPoller(std::string);
   void runSensorPoller();
private:  
   UA_Client *client;
   bool * running;
};
}
#endif
