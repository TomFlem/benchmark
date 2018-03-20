#include "Client.h"
#include "main.h"

namespace client
{
/* Constructor */
Client::Client(){}

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
   settings = new RTIMUSettings("RTIMULib");
   imu = RTIMU::createIMU(settings);
   pressure = RTPressure::createPressure(settings);
   humidity = RTHumidity::createHumidity(settings);

   imu->IMUInit();
   
   //  set up pressure sensor
   if (pressure != NULL)
   {
      pressure->pressureInit();
   }
   //  set up humidity sensor
   if (humidity != NULL)
   {
       humidity->humidityInit();
   }
   return true;
}

void Client::runSensorPoller()
{
   /* Runs one pass of the poller writing new values to the server */
     
      RTIMU_DATA imuData = imu->getIMUData();
      if (pressure != NULL)
      {
         pressure->pressureRead(imuData);
      }
      //  add the humidity data to the structur
      if (humidity != NULL)
      {
         humidity->humidityRead(imuData);
      }

      //Write Temperature
      UA_Variant *myVariant = UA_Variant_new();
      UA_Float tempIn = imuData.temperature;
      UA_Variant_setScalarCopy(myVariant, &tempIn, &UA_TYPES[UA_TYPES_FLOAT]);
      UA_NodeId tempNodeId = UA_NODEID_STRING(1,C_TEXT("Temperature"));
      UA_StatusCode status = UA_Client_writeValueAttribute(client,tempNodeId, myVariant);
      
      //Write Pressure
      UA_Float pressIn = imuData.pressure;
      UA_Variant_setScalarCopy(myVariant, &pressIn, &UA_TYPES[UA_TYPES_FLOAT]);
      UA_NodeId pressNodeId = UA_NODEID_STRING(1,C_TEXT("Pressure"));
      status = UA_Client_writeValueAttribute(client,pressNodeId, myVariant);
      
      //Write Humidity
      UA_Float humidIn = imuData.humidity;
      UA_Variant_setScalarCopy(myVariant, &humidIn, &UA_TYPES[UA_TYPES_FLOAT]);
      UA_NodeId humidNodeId = UA_NODEID_STRING(1,C_TEXT("Humidity"));
      status = UA_Client_writeValueAttribute(client,humidNodeId, myVariant);
}
/* Destructor */
Client::~Client (){}
}
