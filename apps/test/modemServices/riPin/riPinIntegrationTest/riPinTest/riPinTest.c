 /**
  * This module implements the le_riPin's test.
  *
  * Copyright (C) Sierra Wireless Inc. Use of this work is subject to license.
  *
  */

#include "legato.h"
#include "interfaces.h"


//--------------------------------------------------------------------------------------------------
/**
 * Helper.
 *
 */
//--------------------------------------------------------------------------------------------------
static void PrintUsage()
{
    int idx;
    bool sandboxed = (getuid() != 0);
    const char * usagePtr[] = {
            "Usage of the riPinTest app is:",
            "   execInApp riPinTest riPinTest <take/release/pulse> [pulse duration in ms]"};

    for(idx = 0; idx < NUM_ARRAY_MEMBERS(usagePtr); idx++)
    {
        if(sandboxed)
        {
            LE_INFO("%s", usagePtr[idx]);
        }
        else
        {
            fprintf(stderr, "%s\n", usagePtr[idx]);
        }
    }
}

//--------------------------------------------------------------------------------------------------
/**
 * Initialize the test component.
 */
//--------------------------------------------------------------------------------------------------
COMPONENT_INIT
{
    bool amIOwner;

    LE_INFO("Init");

    if (le_arg_NumArgs() >= 1)
    {
        LE_INFO("======== Ring Indicator signal Test ========");

        const char* testCase = le_arg_GetArg(0);
        LE_INFO("   Test case.%s", testCase);

        LE_ASSERT(le_riPin_AmIOwnerOfRingSignal(&amIOwner) == LE_OK);
        if (amIOwner)
        {
            LE_INFO("Legato is the owner of the Ring Indicator signal");
        }
        else
        {
            LE_INFO("Legato is NOT the owner of the Ring Indicator signal");
        }

        if (strncmp(testCase, "take", strlen("take")) == 0)
        {
            LE_ASSERT(le_riPin_TakeRingSignal() == LE_OK);
            LE_INFO("Legato is the owner of the Ring Indicator signal");
        }
        else if (strncmp(testCase, "release", strlen("release")) == 0)
        {
            LE_ASSERT(le_riPin_ReleaseRingSignal() == LE_OK);
            LE_INFO("Legato is no more the owner of the Ring Indicator signal");
        }
        else if (strncmp(testCase, "pulse", strlen("pulse")) == 0)
        {
            uint32_t duration = atoi(le_arg_GetArg(1));
            le_riPin_PulseRingSignal(duration);
            LE_INFO("Check the Ring indicator signal");
        }
        else
        {
            PrintUsage();
            LE_INFO("EXIT riPinTest");
            exit(EXIT_FAILURE);
        }

        LE_INFO("======== Ring Indicator signal test started successfully ========");
    }
    else
    {
        PrintUsage();
        LE_INFO("EXIT riPinTest");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

