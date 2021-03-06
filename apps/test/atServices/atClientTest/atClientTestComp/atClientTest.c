/**
 * This module implements the integration tests for AT commands client API.
 *
 * Copyright (C) Sierra Wireless Inc. Use of this work is subject to license.
 *
 */

#include "legato.h"
#include "interfaces.h"

le_atClient_DeviceRef_t DevRef;
le_atClient_UnsolicitedResponseHandlerRef_t UnsolCmtiRef;

//--------------------------------------------------------------------------------------------------
/**
 * Unsolicited handler.
 *
 */
//--------------------------------------------------------------------------------------------------
void UnsolicitedResponseHandler
(
    const char* unsolicitedRsp,
    void* contextPtr
)
{
    LE_INFO("Unsolicited received: %s", unsolicitedRsp);

    if (strncmp(unsolicitedRsp, "+COPS:", 6) == 0)
    {
        LE_INFO("Please send a sms to the module");

    }
    else if (strncmp(unsolicitedRsp, "+CMTI:", 6) == 0)
    {
        le_atClient_RemoveUnsolicitedResponseHandler(UnsolCmtiRef);
        LE_INFO("Please send again a sms to the module");
        LE_INFO("No indication should be displayed this time");
    }
}

//--------------------------------------------------------------------------------------------------
/**
 * Thread used to received unsolicited response.
 *
 */
//--------------------------------------------------------------------------------------------------
static void* TestThread
(
    void* context
)
{
    le_atClient_ConnectService();

    UnsolCmtiRef = le_atClient_AddUnsolicitedResponseHandler(  "+CMTI:",
                                                DevRef,
                                                UnsolicitedResponseHandler,
                                                NULL,
                                                1
                                            );

    le_atClient_AddUnsolicitedResponseHandler(  "+COPS:",
                                                DevRef,
                                                UnsolicitedResponseHandler,
                                                NULL,
                                                1
                                            );
    le_event_RunLoop();

    return NULL;
}

//--------------------------------------------------------------------------------------------------
/**
 * main of the test
 *
 */
//--------------------------------------------------------------------------------------------------
COMPONENT_INIT
{
    const char* phoneNumber=NULL;
    le_thread_Ref_t newThreadPtr;

    // Get phone number
    if (le_arg_NumArgs() == 1)
    {
        phoneNumber = le_arg_GetArg(0);
    }
    else
    {
        LE_INFO("Usage:");
        LE_INFO("execInApp atClientTest atClientTest <phoneNumber>");
        exit(EXIT_FAILURE);
    }


    newThreadPtr = le_thread_Create("TestThread",TestThread,NULL);

    le_thread_Start(newThreadPtr);
    //! [binding]
    DevRef = le_atClient_Start("/dev/ttyAT");
    //! [binding]
    // A device is opened only once, we should received the same reference
    LE_ASSERT(le_atClient_Start("/dev/ttyAT") == DevRef);

    // Try to stop the device
    LE_ASSERT(le_atClient_Stop(DevRef) == LE_OK);
    LE_ASSERT(le_atClient_Stop(DevRef) == LE_OK);

    // OPen again for tests
    DevRef = le_atClient_Start("/dev/ttyAT");

    char buffer[LE_ATCLIENT_CMD_RSP_MAX_BYTES];
    le_atClient_CmdRef_t cmdRef;

    // Get S/N
    cmdRef = le_atClient_Create();
    LE_ASSERT(le_atClient_SetDevice(cmdRef, DevRef) == LE_OK);
    LE_ASSERT(le_atClient_SetCommand(cmdRef, "AT+CGSN") == LE_OK);
    LE_ASSERT(le_atClient_SetFinalResponse(cmdRef, "OK|ERROR|+CME ERROR") == LE_OK);
    LE_ASSERT(le_atClient_Send(cmdRef) == LE_OK);
    LE_ASSERT(le_atClient_GetFinalResponse( cmdRef,buffer, LE_ATCLIENT_CMD_RSP_MAX_BYTES) == LE_OK);
    LE_DEBUG("final rsp: %s", buffer);
    memset(buffer,0,50);
    LE_ASSERT(le_atClient_GetFirstIntermediateResponse(cmdRef,buffer, LE_ATCLIENT_CMD_RSP_MAX_BYTES)
                                                                                          == LE_OK);
    LE_DEBUG("inter rsp: %s", buffer);
    LE_ASSERT(le_atClient_GetNextIntermediateResponse(cmdRef,buffer, LE_ATCLIENT_CMD_RSP_MAX_BYTES)
                                                                                   == LE_NOT_FOUND);
    LE_ASSERT(le_atClient_Delete(cmdRef) == LE_OK);

    // Same command with le_atClient_SetCommandAndSend
    LE_ASSERT(le_atClient_SetCommandAndSend (   &cmdRef,
                                                DevRef,
                                                "AT+CGSN",
                                                "",
                                                "OK|ERROR|+CME ERROR",
                                                LE_ATCLIENT_CMD_DEFAULT_TIMEOUT  ) == LE_OK);
    LE_ASSERT(le_atClient_GetFinalResponse( cmdRef,buffer, LE_ATCLIENT_CMD_RSP_MAX_BYTES) == LE_OK);
    LE_DEBUG("final rsp: %s", buffer);
    memset(buffer,0,50);
    LE_ASSERT(le_atClient_GetFirstIntermediateResponse(cmdRef,buffer, LE_ATCLIENT_CMD_RSP_MAX_BYTES)
                                                                                          == LE_OK);
    LE_DEBUG("inter rsp: %s", buffer);
    LE_ASSERT(le_atClient_GetNextIntermediateResponse(cmdRef,buffer, LE_ATCLIENT_CMD_RSP_MAX_BYTES)
                                                                                   == LE_NOT_FOUND);
    LE_ASSERT(le_atClient_Delete(cmdRef) == LE_OK);

    // Send AT+CREG? command, and treat response
    //! [declarationFull]
    cmdRef = le_atClient_Create();
    LE_ASSERT(cmdRef != NULL);
    LE_ASSERT(le_atClient_SetDevice(cmdRef, DevRef) == LE_OK);
    LE_ASSERT(le_atClient_SetCommand(cmdRef, "AT+CREG?") == LE_OK);
    LE_ASSERT(le_atClient_SetFinalResponse(cmdRef, "OK|ERROR|+CME ERROR") == LE_OK);
    LE_ASSERT(le_atClient_SetIntermediateResponse(cmdRef, "+CREG:") == LE_OK);
    LE_ASSERT(le_atClient_Send(cmdRef) == LE_OK);
    //! [declarationFull]
    memset(buffer,0,50);
    LE_ASSERT(le_atClient_GetFinalResponse( cmdRef,buffer, LE_ATCLIENT_CMD_RSP_MAX_BYTES) == LE_OK);
    LE_DEBUG("final rsp: %s", buffer);
    memset(buffer,0,50);
    LE_ASSERT(le_atClient_GetFirstIntermediateResponse(cmdRef,buffer, LE_ATCLIENT_CMD_RSP_MAX_BYTES)
                                                                                          == LE_OK);
    LE_DEBUG("inter rsp: %s", buffer);
    LE_ASSERT(le_atClient_GetNextIntermediateResponse(cmdRef,buffer, LE_ATCLIENT_CMD_RSP_MAX_BYTES)
                                                                                   == LE_NOT_FOUND);
    LE_ASSERT(le_atClient_Delete(cmdRef) == LE_OK);

    // Get the list of SMS
    LE_ASSERT(le_atClient_SetCommandAndSend(&cmdRef,
                                        DevRef,
                                        "AT+CMGF=1",
                                        "",
                                        "OK|ERROR|+CME ERROR:|+CMS ERROR:",
                                        LE_ATCLIENT_CMD_DEFAULT_TIMEOUT) == LE_OK);
    LE_ASSERT(le_atClient_Delete(cmdRef) == LE_OK);

    //! [declarationSimple]
    LE_ASSERT(le_atClient_SetCommandAndSend(&cmdRef,
                                        DevRef,
                                        "AT+CMGL=\"REC READ\"",
                                        "+CMGL:",
                                        "OK|ERROR|+CME ERROR:|+CMS ERROR:",
                                        LE_ATCLIENT_CMD_DEFAULT_TIMEOUT) == LE_OK);
    //! [declarationSimple]

    LE_ASSERT( le_atClient_GetFinalResponse(cmdRef,
                                       buffer,
                                       LE_ATCLIENT_CMD_RSP_MAX_BYTES) == LE_OK );

    LE_ASSERT( strcmp(buffer,"OK") == 0);

    //! [responses]
    int intNumber = 1;
    le_result_t res = le_atClient_GetFirstIntermediateResponse(cmdRef,
                                                   buffer,
                                                   LE_ATCLIENT_CMD_RSP_MAX_BYTES);

    while(res == LE_OK)
    {
        LE_INFO("rsp interm %d: %s", intNumber, buffer);
        intNumber++;

        res = le_atClient_GetNextIntermediateResponse(cmdRef,
                                                    buffer,
                                                    LE_ATCLIENT_CMD_RSP_MAX_BYTES);
    }
    //! [responses]

    le_atClient_Delete(cmdRef);

    //! [declarationText]
    // Send a SMS
    char cmgs[100];
    memset(cmgs,0,100);
    snprintf(cmgs,100,"AT+CMGS=\"%s\"", phoneNumber);

    cmdRef = le_atClient_Create();
    LE_ASSERT(cmdRef != NULL);
    LE_ASSERT(le_atClient_SetCommand(cmdRef, cmgs) == LE_OK);
    char sms[]="Hello Legato";
    LE_ASSERT(le_atClient_SetText(cmdRef, sms) == LE_OK);
    LE_ASSERT(le_atClient_SetDevice(cmdRef, DevRef) == LE_OK);
    LE_ASSERT(le_atClient_SetTimeout(cmdRef, 0) == LE_OK);
    LE_ASSERT(le_atClient_SetFinalResponse(cmdRef, "OK|ERROR|+CMS ERROR") == LE_OK);
    LE_ASSERT(le_atClient_Send(cmdRef)==LE_OK);
    //! [declarationText]
    //! [delete]
    LE_ASSERT(le_atClient_Delete(cmdRef) == LE_OK);
    //! [delete]

    // Test timeout command
    cmdRef = le_atClient_Create();
    LE_ASSERT(cmdRef != NULL);
    LE_ASSERT(le_atClient_SetCommand(cmdRef, "AT+COPS=?") == LE_OK);
    LE_ASSERT(le_atClient_SetTimeout(cmdRef, 1) == LE_OK);
    LE_ASSERT(le_atClient_SetDevice(cmdRef, DevRef) == LE_OK);
    LE_ASSERT(le_atClient_SetFinalResponse(cmdRef, "OK|ERROR|+CME ERROR") == LE_OK);
    LE_ASSERT(le_atClient_Send(cmdRef)==LE_TIMEOUT);
    LE_ASSERT(le_atClient_Delete(cmdRef) == LE_OK);
}
