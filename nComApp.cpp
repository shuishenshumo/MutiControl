// nComApp.cpp : Defines the entry point for the console application.

#include <tchar.h>
#include <Windows.h>

#include <sqxCommsConnection.h>
#include <sqxCommsConnectionLoader.h>
//#include <sqxCommsDataDescription.h>
#include <sqxCommsDataDescriptionLoader.h>
#include <sqxCommsLog.h>
#include <sqxCommsManager.h>
//#include <sqxCommsMessage.h>
#include <sqxCommsReceiver.h>
#include <sqxCommsSender.h>
//#include <sqxCommsUtil.h>
//#include <sqxString.h>
//#include <sqxStringW.h>

#include "anim.h"

using namespace std;

// nCom object declarations

#define COMM      //Activate first connection

// Message receiver, handles the messages from SM.
#ifdef COMM
class MyReceiver : public sqxCommsReceiver
{
public:
   virtual void HandleMessage(const sqxCommsMessage& a_rMessage)
   {
      // Cast incoming data based on structure of message
      const float* pIncomingData = static_cast<const float*>( a_rMessage.pGetData() );
      sqxCommsLog::s_pGetInstance()->vReportTrace(sqxCommsLog::TRACE_WARNING, "\nRx: value=%f\n", *pIncomingData);

      // Send incoming value to animation code
      anim_set_revs_per_minute(*pIncomingData);
   }
};
#endif

#ifdef COMM
sqxCommsManager   Manager;
sqxCommsSender    Sender;
#endif

static void RuntimenComReporter(const char* a_Message, va_list a_pList)
{
   int  nSize = 0;
   char buff[2048];
   nSize = _vsnprintf( buff, sizeof(buff), a_Message, a_pList);
   fprintf(stderr,buff);
}

#define TUTORIAL_PATH "D:\\X19_symbol_libaray3"

int InitnComLibraries(void)
{
   // Register static function with nCOM message reporter
   sqxCommsLog* pCommsLog = sqxCommsLog::s_pGetInstance();
   pCommsLog->vSetErrorReporter(RuntimenComReporter);
   pCommsLog->vSetWarningReporter(RuntimenComReporter);
   pCommsLog->vSetTraceReporter( RuntimenComReporter );
   pCommsLog->vSetTraceLvl(sqxCommsLog::TRACE_WARNING); // 5 is Show All Traces

#ifdef COMM
   // Build a path to the Connections.XML file 
   string Connection_File = TUTORIAL_PATH"\\DataIO\\Connections.xml";

   // Build a path to the DialPos.dd file 
   string Outgoing_Data_File = TUTORIAL_PATH"\\HUD\\DialPos.dd";

   // Build a path to the DialSpeed.dd file 
   string Incoming_Data_File = TUTORIAL_PATH"\\HUD\\DialSpeed.dd";
#endif

#ifdef COMM
   // Initialize nCOM
   Manager.SetAppName("nComApp");
   sqxCommsConnectionLoader ConnectionLoader;
   ConnectionLoader.Load(Connection_File);

   const sqxCommsProperties* pProperty = ConnectionLoader.pGetProperties("VapsXTtoAppConn");
   if ( NULL != pProperty )
   {
      sqxCommsConnection* pConnection = Manager.pCreateConnection(*pProperty);
      if ( NULL != pConnection )
      {
         sqxCommsDataDescriptionLoader DDLoader;
         if ( 0 != DDLoader.Load(Outgoing_Data_File) )
         { 
            return -1;
         }

         if ( DDLoader.pGetDataDescription() )
         {
            Sender.SetDataDescription(DDLoader.pGetDataDescription());
         }

         sqxCommsReceiver* pReceiver = new MyReceiver();
         DDLoader.Load(Incoming_Data_File);

         if ( DDLoader.pGetDataDescription() )
         {
            pReceiver->SetDataDescription(DDLoader.pGetDataDescription());
         }

         Sender.AddConnection(pConnection);
         Sender.SetAutoUpdateActive(true, true);
         Sender.SetName("PosBuff");

         pConnection->AddReceiver(pReceiver);
         pConnection->SetActive(true);

         // register the sender and receiver
         Manager.AddSender(&Sender);
         Manager.AddReceiver(pReceiver);

         return 1;
      }
   }
#endif

   return 0;  // return TRUE  unless you set the focus to a control
}

/*int _tmain(int argc, _TCHAR* argv[])
{
   printf("External Process using nCom Library\n");
   printf("For the tutorial we assume " TUTORIAL_PATH " as folder\n");

   // Initializes communications with VAPS
   InitnComLibraries();

   // Initializes animation library
   anim_init(0.0, 0.0);

#ifdef COMM
   //  Main Loop
   while(1)
   {
      // Asks the nCom mechanism to read incoming messages

      // update the data to be sent.
      float Angle = anim_get_angle_in_revs();
      Sender.SetData(&Angle, sizeof(Angle));

      // Send messages, tick the connections and process the received messages.
      Manager.Tick();

      Sleep(25);
   }
#endif

   return 0;
}*/