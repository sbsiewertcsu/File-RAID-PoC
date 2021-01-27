#include <stdio.h>
#include <stdlib.h>

#include "raidlib.h"

int main(int argc, char *argv[])
{
    int bytesWritten, bytesRestored;
    char rc;

    // zero default for no chunk erased
    int chunkToRebuild=0;

    if(argc < 3)
    {
        printf("useage: stripetest inputfile outputfile <sector to restore>\n");
        exit(-1);
    }
    
    if(argc >= 4)
    {
	sscanf(argv[3], "%d", &chunkToRebuild);
        printf("chunk to restore = %d\n", chunkToRebuild);
    }
   
    bytesWritten=stripeFile(argv[1], 0); 

    printf("%s input file was written as 4 data chunks + 1 XOR parity on 5 devices 1...5\n", argv[1]);

    printf("Enter chunk you have erased or 0 for none:");
    fscanf(stdin, "%d", &chunkToRebuild);
    printf("Got %d\n", chunkToRebuild);

    if(chunkToRebuild > 0)
    {
        printf("Will rebuild StripeChunk%1d.bin\n", chunkToRebuild);
        printf("working on restoring file ...\n");
        bytesRestored=restoreFile(argv[2], 0, bytesWritten, chunkToRebuild); 
    }
    else
    {
        printf("Nothing erased, so nothing to restore\n");
    }

    printf("FINISHED\n");
        
}
