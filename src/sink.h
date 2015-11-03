#include "image.h"

#ifndef SINK_H
#define SINK_H

class Sink
{
	protected:
	    const Image *image1;
	   	const Image *image2;
	    
	public:
		virtual const char *SinkName() = 0;
	    void SetInput( Image *image1);
	    void SetInput2( Image *image2);
	    Sink();
};

#endif