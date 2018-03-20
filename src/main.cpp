#include "main.h"
#include "Server.h"
#include "Client.h"

#include <csignal>
#include <thread>
#include <sense/fb.h>

UA_Boolean running = true;
static void stopHandler(int sign)
{
   UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
   running = false;
}

void pollSensors(client::Client * ua_client,bool * running)
{
   sleep(1);
     
   /* Connect with default address and port */
   ua_client.setupSensorPoller(C_TEXT("opc.tcp://localhost:4840"));
   
   while (*running)
   {
      std::cout<<"TEST"<<std::endl;
      sleep(1);
   }
}

int main()
{
   signal(SIGINT, stopHandler); /* catches ctrl-c */
   std::cout<<"Starting OPC-UA Benchmark Server"<<std::endl;
   
   server::Server ua_server = server::Server();
   
   /* Start the server */
   ua_server.setupServer(4840);
   
   /* Create the client */
   client::Client ua_client = client::Client();
    
   /* Start Sensor Polling Thread */
   std::thread t1(pollSensors,ua_client,&running);/* Start the pubPoller */
   
   /* Run the server, will continue running until 'running = false' from cntrl+c */
   ua_server.runServer(&running);
   

   
   /* Stop the server */
   ua_server.stopServer();
   return 0;
}
