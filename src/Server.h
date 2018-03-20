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

   bool setupServer(int);
   bool stopServer();
   bool runServer(bool *);
private:  
   UA_Server *server;
   
   void addNodes();
};
}
#endif
