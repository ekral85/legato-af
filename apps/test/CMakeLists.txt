#*******************************************************************************
# Copyright (C) Sierra Wireless Inc. Use of this work is subject to license.
#*******************************************************************************

# Tests
enable_testing()

# Output
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/tests/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/tests/lib)
set(APP_OUTPUT_PATH ${CMAKE_BINARY_DIR}/tests/apps)

file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
file(MAKE_DIRECTORY ${LIBRARY_OUTPUT_PATH})
file(MAKE_DIRECTORY ${APP_OUTPUT_PATH})


# Framework
add_subdirectory(framework)

# Components

## Modem Services
add_subdirectory(modemServices/sms/smsIntegrationTest)
add_subdirectory(modemServices/sms/smsUnitTest)
add_subdirectory(modemServices/mcc/mccIntegrationTest)
add_subdirectory(modemServices/mcc/mccCallWaitingTest)
add_subdirectory(modemServices/mcc/mccUnitTest)
add_subdirectory(modemServices/mdc/mdcIntegrationTest)
add_subdirectory(modemServices/mdc/mdcUnitTest)
add_subdirectory(modemServices/mdc/mdcMultiPdpTest)
add_subdirectory(modemServices/mrc/mrcIntegrationTest)
add_subdirectory(modemServices/mrc/mrcUnitTest)
add_subdirectory(modemServices/sim/simIntegrationTest)
add_subdirectory(modemServices/sim/simUnitTest)
add_subdirectory(modemServices/sim/simProfileSwap)
add_subdirectory(modemServices/sim/simToolkit)
add_subdirectory(modemServices/info/infoIntegrationTest)
add_subdirectory(modemServices/info/infoUnitTest)
add_subdirectory(modemServices/ips/ipsIntegrationTest)
add_subdirectory(modemServices/ips/ipsUnitTest)
add_subdirectory(modemServices/temp/tempIntegrationTest)
add_subdirectory(modemServices/temp/tempUnitTest)
add_subdirectory(modemServices/antenna/antennaIntegrationTest)
add_subdirectory(modemServices/antenna/antennaUnitTest)
add_subdirectory(modemServices/adc/adcUnitTest)
add_subdirectory(modemServices/riPin/riPinIntegrationTest)
add_subdirectory(modemServices/riPin/riPinUnitTest)
add_subdirectory(modemServices/ecall/ecallUnitTest)
add_subdirectory(modemServices/rtc/rtcUnitTest)

if((INCLUDE_ECALL EQUAL 1) AND ((LEGATO_TARGET MATCHES "ar7") OR (LEGATO_TARGET MATCHES "ar86")))
    add_subdirectory(modemServices/ecall/ecallIntegrationTest)
    add_subdirectory(modemServices/ecall/ecallWPrompt)
    add_subdirectory(modemServices/ecall/ecallWVoice)
    add_subdirectory(modemServices/ecall/ecallStress)
endif()

## Positioning Services
add_subdirectory(positioning/gnssTest)
add_subdirectory(positioning/gnssXtraTest)
# To be implemented add_subdirectory(positioning/posDaemonTest)
add_subdirectory(positioning/positioningTest)

## Audio Services
add_subdirectory(audio/pa)
add_subdirectory(audio/service/audioTest)
add_subdirectory(audio/service/memoryTest)
add_subdirectory(audio/audioMcc)
add_subdirectory(audio/audioCallPbRec)
add_subdirectory(audio/dtmf)
add_subdirectory(audio/audioCfg)
add_subdirectory(audio/audioPlaybackRec)
add_subdirectory(audio/voicePromptMcc)
add_subdirectory(audio/voicePromptMcc2)
add_subdirectory(audio/audioUnitTest)

## Data Connection Service
add_subdirectory(dataConnectionService)

## Other Services ...
add_subdirectory(cellNetService)
add_subdirectory(voiceCallService/voiceCallServiceIntegrationTest)
add_subdirectory(smsInboxService)

# AirVantage Service
add_subdirectory(avcService)

# IfGen Tool
add_subdirectory(ifgen/test2)

# AT Services
add_subdirectory(atServices/atClientTest)
add_subdirectory(atServices/atServerIntegrationTest)
add_subdirectory(atServices/atServerUnitTest)
