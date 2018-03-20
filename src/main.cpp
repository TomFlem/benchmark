#include "Server.h"

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
   
   while (true)
   {
   
   }
   
   /* Stop the server */
   ua_server.stopServer();
   return 0;
}
