#include "Client.h"

namespace client
{
/* Constructor */
Client::Client(bool * state)
{
   running = state;
} 

bool Client::setupSensorPoller(std::string serverAddr)
{
   /* Create a client and connect */
   UA_Client *client = UA_Client_new(UA_ClientConfig_default);
   UA_StatusCode status = UA_Client_connect(client, serverAddr.c_str());
   
   std::cout<<"UA_Client_connect - StatusCode: "<<UA_StatusCode_name(status)<<std::endl;
   if (status!=UA_STATUSCODE_GOOD)
   {
      return false;
   }
   
   /* Setup sensor monitoring */
   
   
   return true;
}

void Client::runSensorPoller()
{
   /* Runs one pass of the poller writing new values to the server */
   
}
/* Destructor */
Client::~Client (){}
}
