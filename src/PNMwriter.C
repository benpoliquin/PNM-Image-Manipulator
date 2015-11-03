#include "PNMwriter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logging.h"

void PNMwriter::Write(char *filename)
{
    FILE *f = fopen(filename, "wb");
    
    if (f == NULL)
    {
        fprintf(stderr, "Unable to open file %s\n", filename);
    }
    
    fprintf(f, "P6\n%d %d\n%d\n", image1->GetWidth(), image1->GetHeight(), 255);

    fwrite(image1->GetBuffer(), sizeof(unsigned char), 3 * image1->GetWidth() * image1->GetHeight(), f);

    fclose(f);
}

const char * PNMwriter::SinkName()
{
    const char *msg;
    msg = "PNMwriter";
    return msg;
}