// audiobuf.h

#include <mutex>
#include <cstdint>

#ifndef _WIN32
typedef struct tWAVEFORMATEX
{
    uint16_t wFormatTag;
    uint16_t nChannels;
    uint32_t nSamplesPerSec;
    uint32_t nAvgBytesPerSec;
    uint16_t nBlockAlign;
    uint16_t wBitsPerSample;
    uint16_t cbSize;
} WAVEFORMATEX;
#endif

// Reset audio buffer discarding stored audio data
void ResetAudioBuf();

// Return previously saved audio data for visualizer
void GetAudioBuf(unsigned char *pWaveL, unsigned char *pWaveR, int SamplesCount);

// Save audio data for visualizer
void SetAudioBuf(const unsigned char *pData, const uint32_t nNumFramesToRead, const WAVEFORMATEX *pwfx, const bool bInt16);
