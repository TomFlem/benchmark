#ifndef SERVER_H
#define SERVER_H
#include <stdio.h>
#include <iostream>

#include "open62541.h"
namespace server
{
class Server
{
public:
   Server ();
   ~Server ();

   bool startServer(int,bool *);
   bool stopServer();
private:  
   UA_Server *server;
   
   void addNodes();
};
}
#endif
