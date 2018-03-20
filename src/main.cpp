#include "main.h"
#include "Server.h"
#include "Client.h"

#include <csignal>

UA_Boolean running = true;
static void stopHandler(int sign)
{
   UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
   running = false;
}

int main()
{
   signal(SIGINT, stopHandler); /* catches ctrl-c */
   std::cout<<"Starting OPC-UA Benchmark Server"<<std::endl;
   
   server::Server ua_server = server::Server();
   
   /* Start the server */
   ua_server.startServer(4840,&running);
   
   client::Client ua_client = client::Client();
   /* Connect with default address and port */
   ua_client.setupSensorPoller(C_TEXT("opc.tcp://localhost:4840"));
   while (running)
   {
   
   }
   
   /* Stop the server */
   ua_server.stopServer();
   return 0;
}
