#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

typedef struct
{
    size_t sampleCount;
    float sampleRate;
    float sampleDuration;
    float* samples;
} audioInfo_s;

typedef struct
{
    size_t freqCount;
    float* amps;
} freqDomainST_s;

typedef struct
{
    freqDomainST_s* intervals;
    size_t intervalCount;
} freqDomain_s;

typedef struct
{
    uint8_t* notes; // ordered with respect to the timbre
    size_t noteCount; //number of different instruments
} notes_s;
