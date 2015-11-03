#include <stdio.h>
#include "sink.h"

#ifndef PNMWRITER_H
#define PNMWRITER_H

class PNMwriter: public Sink
{
	public:
	    void Write(char *filename);
	    const char * SinkName();
};

#endif