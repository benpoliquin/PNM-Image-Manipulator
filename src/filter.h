#include "source.h"
#include "sink.h"
#include <stdio.h>

#ifndef FILTER_H
#define FILTER_H

class Filter: public Source, public Sink
{
	public:
		virtual void Update();
		virtual const char *FilterName() = 0;
		virtual const char *SourceName();
		virtual const char *SinkName();
};

#endif