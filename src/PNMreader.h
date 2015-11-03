#include <stdio.h>
#include "source.h"

#ifndef PNMREADER_H
#define PNMREADER_H

class PNMreader: public Source
{
	protected:
	    char *filename;
	    
	public:
	    virtual void Execute();
	    const char *SourceName();
	    PNMreader(char *filename);
};

#endif