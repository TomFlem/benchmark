#include "main.h"
#include "Server.h"

#include <csignal>
#include <thread>
#include <sense/fb.h>

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
   ua_server.setupServer(4840);
   
   /* Run the server, will continue running until 'running = false' from cntrl+c */
   ua_server.runServer(&running);
   

   
   /* Stop the server */
   ua_server.stopServer();
   return 0;
}
