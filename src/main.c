#include "types.h"
#include "config.h"
#include "fun.h"

#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>


int main()
{
    notes_s notes;
        {
            freqDomain_s fd;
            {
            audioInfo_s clipInfo = captureAudio(); //fills clipAudio with data along with allocating memory in heap
            fd = stft(clipInfo); //returns the frequency donian with a time window of ST
            free(clipInfo.samples); // won't be needed
            }
            notes = toNotes(fd);
            for (size_t i = 0; i < fd.intervalCount; i++) 
            {
                free(fd.intervals[i].amps);
            }
            free(fd.intervals);
        }
    
}