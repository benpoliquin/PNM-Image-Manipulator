#include "image.h"

#ifndef SOURCE_H
#define SOURCE_H

class Source
{
	protected:
	    Image img;
	    virtual void Execute() = 0;

	public:
		virtual const char *SourceName() = 0;
		virtual void Update();
	    Image * GetOutput();
	    void SetSource();
	    Source();
};

#endif