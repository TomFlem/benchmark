#include "Server.h"
#include "main.h"
 
namespace server
{
/* Constructor */
Server::Server(){} 

/* Add the nodes */
void Server::addNodes()
{
   UA_VariableAttributes myVar = UA_VariableAttributes_default;
   myVar.description = UA_LOCALIZEDTEXT(C_TEXT("en-US"), C_TEXT("The temperature reading from the Pi Sense Hat"));
   myVar.displayName = UA_LOCALIZEDTEXT(C_TEXT("en-US"), C_TEXT("Temperature"));
   myVar.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
   myVar.dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;
   UA_Float myTemp = 0.5;
   UA_Variant_setScalarCopy(&myVar.value, &myTemp, &UA_TYPES[UA_TYPES_FLOAT]);
   const UA_QualifiedName myTempName = UA_QUALIFIEDNAME(1, C_TEXT("Temperature"));
   const UA_NodeId myTempNodeId = UA_NODEID_STRING(1, C_TEXT("Temperature"));
   UA_Server_addVariableNode(server, myTempNodeId, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 
   UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES), myTempName, UA_NODEID_NULL, myVar, NULL, NULL);
   
   myVar = UA_VariableAttributes_default;
   myVar.description = UA_LOCALIZEDTEXT(C_TEXT("en-US"), C_TEXT("The pressure reading from the Pi Sense Hat"));
   myVar.displayName = UA_LOCALIZEDTEXT(C_TEXT("en-US"), C_TEXT("Pressure"));
   myVar.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
   myVar.dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;
   UA_Float myPress = 0.5;
   UA_Variant_setScalarCopy(&myVar.value, &myPress, &UA_TYPES[UA_TYPES_FLOAT]);
   const UA_QualifiedName myPressName = UA_QUALIFIEDNAME(1, C_TEXT("Pressure"));
   const UA_NodeId myPressNodeId = UA_NODEID_STRING(1, C_TEXT("Pressure"));
   UA_Server_addVariableNode(server, myPressNodeId, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 
   UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES), myPressName, UA_NODEID_NULL, myVar, NULL, NULL);
   UA_Variant_deleteMembers(&myVar.value);
   
   myVar = UA_VariableAttributes_default;
   myVar.description = UA_LOCALIZEDTEXT(C_TEXT("en-US"), C_TEXT("The humidity reading from the Pi Sense Hat"));
   myVar.displayName = UA_LOCALIZEDTEXT(C_TEXT("en-US"), C_TEXT("Humidity"));
   myVar.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
   myVar.dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;
   UA_Float myHumid = 0.5;
   UA_Variant_setScalarCopy(&myVar.value, &myHumid, &UA_TYPES[UA_TYPES_FLOAT]);
   const UA_QualifiedName myHumidName = UA_QUALIFIEDNAME(1, C_TEXT("Humidity"));
   const UA_NodeId myHumidNodeId = UA_NODEID_STRING(1, C_TEXT("Humidity"));
   UA_Server_addVariableNode(server, myHumidNodeId, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER), 
   UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES), myHumidName, UA_NODEID_NULL, myVar, NULL, NULL);
   UA_Variant_deleteMembers(&myVar.value);

}

/* Start the server */
bool Server::setupServer(int port)
{
   /* Create Default Config */
   UA_ServerConfig *config = UA_ServerConfig_new_minimal(port, NULL);
   
   /* Create the server using the default config */
   server = UA_Server_new(config);
   
   /* Add the nodes we require */
   addNodes();

  
   return true;
}

bool Server::runServer(bool * running)
{     
   /* Run the server */
   UA_Server_run(server, running);
   return true;
}
bool Server::stopServer()
{
    UA_Server_delete(server);
    return true;
}



/* Destructor */
Server::~Server (){}
}
