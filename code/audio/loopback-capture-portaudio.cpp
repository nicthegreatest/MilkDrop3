#include "loopback-capture.h"
#include "portaudio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAMPLE_RATE         (44100)
#define FRAMES_PER_BUFFER   (512)
#define NUM_CHANNELS        (2)
#define SAMPLE_SILENCE      (0.0f)

typedef struct
{
    float* recordedSamples;
    int frameIndex;
    int maxFrameIndex;
} paTestData;

static int recordCallback(const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData)
{
    paTestData *data = (paTestData*)userData;
    const float *rptr = (const float*)inputBuffer;
    float *wptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
    long framesToCalc;
    long i;
    int finished;
    unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;

    (void) outputBuffer; /* Prevent unused variable warnings. */
    (void) timeInfo;
    (void) statusFlags;

    if (framesLeft < framesPerBuffer)
    {
        framesToCalc = framesLeft;
        finished = paComplete;
    }
    else
    {
        framesToCalc = framesPerBuffer;
        finished = paContinue;
    }

    if (inputBuffer == NULL)
    {
        for (i = 0; i < framesToCalc; i++)
        {
            *wptr++ = SAMPLE_SILENCE;  /* left */
            if (NUM_CHANNELS == 2) *wptr++ = SAMPLE_SILENCE;  /* right */
        }
    }
    else
    {
        for (i = 0; i < framesToCalc; i++)
        {
            *wptr++ = *rptr++;  /* left */
            if (NUM_CHANNELS == 2) *wptr++ = *rptr++;  /* right */
        }
    }
    data->frameIndex += framesToCalc;
    return finished;
}

void LoopbackCaptureThreadFunction(LoopbackCaptureThreadFunctionArguments *pArgs)
{
    pArgs->hr = 0; // S_OK

    PaStreamParameters inputParameters;
    PaStream *stream;
    PaError err;
    paTestData data;
    int numSamples;
    int numBytes;

    data.maxFrameIndex = numSamples = 10 * SAMPLE_RATE; // 10 seconds
    data.frameIndex = 0;
    numBytes = numSamples * NUM_CHANNELS * sizeof(float);
    data.recordedSamples = (float*)malloc(numBytes);
    if (data.recordedSamples == NULL)
    {
        pArgs->hr = -1; // E_OUTOFMEMORY
        return;
    }
    memset(data.recordedSamples, 0, numBytes);

    inputParameters.device = Pa_GetDefaultInputDevice();
    if (inputParameters.device == paNoDevice) {
        err = paNoDevice;
        goto error;
    }
    inputParameters.channelCount = NUM_CHANNELS;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    err = Pa_OpenStream(
        &stream,
        &inputParameters,
        NULL,
        SAMPLE_RATE,
        FRAMES_PER_BUFFER,
        paClipOff,
        recordCallback,
        &data);
    if (err != paNoError) goto error;

    err = Pa_StartStream(stream);
    if (err != paNoError) goto error;

    while ((err = Pa_IsStreamActive(stream)) == 1)
    {
        Pa_Sleep(100);
        // This is where you would process the audio data in `data.recordedSamples`
        // For now, we just sleep.
    }
    if (err < 0) goto error;

    err = Pa_CloseStream(stream);
    if (err != paNoError) goto error;

    free(data.recordedSamples);
    return;

error:
    if (data.recordedSamples) {
        free(data.recordedSamples);
    }
    pArgs->hr = err;
    return;
}
