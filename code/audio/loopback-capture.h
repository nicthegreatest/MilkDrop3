// loopback-capture.h

#pragma once

#include <cstdint>

#ifdef _WIN32
#include <windows.h>
#include <mmdeviceapi.h>
#include <mmsystem.h>

// call CreateThread on this function
// feed it the address of a LoopbackCaptureThreadFunctionArguments
// it will capture via loopback from the IMMDevice
// and dump output to the HMMIO
// until the stop event is set
// any failures will be propagated back via hr

struct LoopbackCaptureThreadFunctionArguments {
    IMMDevice *pMMDevice;
    bool bInt16;
    HMMIO hFile;
    HANDLE hStartedEvent;
    HANDLE hStopEvent;
    UINT32 nFrames;
    HRESULT hr;
};

DWORD WINAPI LoopbackCaptureThreadFunction(LPVOID pContext);

#else

#include <thread>

struct LoopbackCaptureThreadFunctionArguments {
    // For PortAudio, we don't need most of these.
    // We'll use this to pass back the result.
    int hr; 
    // We can add a stop mechanism here later if needed, e.g., using std::atomic<bool>
};

void LoopbackCaptureThreadFunction(LoopbackCaptureThreadFunctionArguments *pContext);

#endif