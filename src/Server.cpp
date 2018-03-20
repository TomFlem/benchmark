#include "Server.h"
#include "main.h"
 
namespace server
{
/* Constructor */
Server::Server(){} 

static UA_StatusCode readCurrentTemp(UA_Server *server, const UA_NodeId *sessionId, void *sessionContext,
   const UA_NodeId *nodeId, void *nodeContext, UA_Boolean sourceTimeStamp, const UA_NumericRange *range, UA_DataValue *dataValue) 
{
   server::Server * ua_server = (server::Server*)nodeContext;
   RTIMU_DATA imuData = ua_server->getIMU()->getIMUData();
   if (ua_server->getRTPressure() != NULL)
   {
      ua_server->getRTPressure()->pressureRead(imuData);
   }
   UA_Float temp = imuData.temperature;
   UA_Variant_setScalarCopy(&dataValue->value, &temp, &UA_TYPES[UA_TYPES_FLOAT]);
   dataValue->hasValue = true;
   return UA_STATUSCODE_GOOD;
}

static UA_StatusCode readCurrentPress(UA_Server *server, const UA_NodeId *sessionId, void *sessionContext,
   const UA_NodeId *nodeId, void *nodeContext, UA_Boolean sourceTimeStamp, const UA_NumericRange *range, UA_DataValue *dataValue) 
{
   server::Server * ua_server = (server::Server*)nodeContext;
   RTIMU_DATA imuData = ua_server->getIMU()->getIMUData();
   if (ua_server->getRTPressure() != NULL)
   {
      ua_server->getRTPressure()->pressureRead(imuData);
   }
   UA_Float press = imuData.pressure;
   UA_Variant_setScalarCopy(&dataValue->value, &press, &UA_TYPES[UA_TYPES_FLOAT]);
   dataValue->hasValue = true;
   return UA_STATUSCODE_GOOD;
}

static UA_StatusCode readCurrentHumid(UA_Server *server, const UA_NodeId *sessionId, void *sessionContext,
   const UA_NodeId *nodeId, void *nodeContext, UA_Boolean sourceTimeStamp, const UA_NumericRange *range, UA_DataValue *dataValue) 
{
   server::Server * ua_server = (server::Server*)nodeContext;
   RTIMU_DATA imuData = ua_server->getIMU()->getIMUData();
   if (ua_server->getRTHumidity() != NULL)
   {
      ua_server->getRTHumidity()->humidityRead(imuData);
   }
   UA_Float humid = imuData.humidity;
   UA_Variant_setScalarCopy(&dataValue->value, &humid, &UA_TYPES[UA_TYPES_FLOAT]);
   dataValue->hasValue = true;
   return UA_STATUSCODE_GOOD;
}

/* Add the nodes */
void Server::addNodes()
{
   UA_VariableAttributes myVar = UA_VariableAttributes_default;
   myVar.description = UA_LOCALIZEDTEXT(C_TEXT("en-US"), C_TEXT("The temperature reading from the Pi Sense Hat"));
   myVar.displayName = UA_LOCALIZEDTEXT(C_TEXT("en-US"), C_TEXT("Temperature"));
   myVar.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
   myVar.dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;

   const UA_QualifiedName myTempName = UA_QUALIFIEDNAME(1, C_TEXT("Temperature"));
   const UA_NodeId myTempNodeId = UA_NODEID_STRING(1, C_TEXT("Temperature"));
   UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
   UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
   UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);
   
   UA_DataSource tempDataSource;
   tempDataSource.read = readCurrentTemp;
   UA_Server_addDataSourceVariableNode(server, myTempNodeId, parentNodeId,
                                     parentReferenceNodeId, myTempName,
                                     variableTypeNodeId, myVar,
                                     tempDataSource, this, NULL);
                                        
                                        
   
   myVar = UA_VariableAttributes_default;
   myVar.description = UA_LOCALIZEDTEXT(C_TEXT("en-US"), C_TEXT("The pressure reading from the Pi Sense Hat"));
   myVar.displayName = UA_LOCALIZEDTEXT(C_TEXT("en-US"), C_TEXT("Pressure"));
   myVar.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
   myVar.dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;

   const UA_QualifiedName myPressName = UA_QUALIFIEDNAME(1, C_TEXT("Pressure"));
   const UA_NodeId myPressNodeId = UA_NODEID_STRING(1, C_TEXT("Pressure"));
   UA_NodeId parentNodeIdPress = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
   UA_NodeId parentReferenceNodeIdPress = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
   UA_NodeId variableTypeNodeIdPress = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);
   
   UA_DataSource pressDataSource;
   pressDataSource.read = readCurrentPress;
   UA_Server_addDataSourceVariableNode(server, myPressNodeId, parentNodeIdPress,
                                     parentReferenceNodeIdPress, myPressName,
                                     variableTypeNodeIdPress, myVar,
                                     pressDataSource, this, NULL);
   
   myVar = UA_VariableAttributes_default;
   myVar.description = UA_LOCALIZEDTEXT(C_TEXT("en-US"), C_TEXT("The humidity reading from the Pi Sense Hat"));
   myVar.displayName = UA_LOCALIZEDTEXT(C_TEXT("en-US"), C_TEXT("Humidity"));
   myVar.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
   myVar.dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;

   const UA_QualifiedName myHumidName = UA_QUALIFIEDNAME(1, C_TEXT("Humidity"));
   const UA_NodeId myHumidNodeId = UA_NODEID_STRING(1, C_TEXT("Humidity"));
   UA_NodeId parentNodeIdHumid = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
   UA_NodeId parentReferenceNodeIdHumid = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
   UA_NodeId variableTypeNodeIdHumid = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);
   
   UA_DataSource humidDataSource;
   humidDataSource.read = readCurrentHumid;
   UA_Server_addDataSourceVariableNode(server, myHumidNodeId, parentNodeIdHumid,
                                     parentReferenceNodeIdHumid, myHumidName,
                                     variableTypeNodeIdHumid, myVar,
                                     humidDataSource, this, NULL);
   
   
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

   std::cout<<"Setup Sensors"<<std::endl;
   /* Setup sensor monitoring */
   settings = new RTIMUSettings("RTIMULib");
   imu = RTIMU::createIMU(settings);
  
   pressure = RTPressure::createPressure(settings);
   humidity = RTHumidity::createHumidity(settings);

   imu->IMUInit();
   imu->setSlerpPower(0.02);
   imu->setGyroEnable(true);
   imu->setAccelEnable(true);
   imu->setCompassEnable(true);

   //  set up pressure sensor
   if (pressure != NULL)
   {
      std::cout<<"Init Pressure"<<std::endl;
      pressure->pressureInit();
   }
   //  set up humidity sensor
   if (humidity != NULL)
   {
      std::cout<<"Init Humidity"<<std::endl;
      humidity->humidityInit();
   }
  
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

RTIMU * Server::getIMU()
{
   return imu;
}

RTPressure * Server::getRTPressure()
{
   return pressure;
}

RTHumidity * Server::getRTHumidity()
{
   return humidity;
}

/* Destructor */
Server::~Server (){}
}
