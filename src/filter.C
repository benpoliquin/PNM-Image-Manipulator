#include "filter.h"
#include "logging.h"

int sumException;

void Filter::Update()
{	
	sumException++;

	if(sumException > 1000)
	{
		char msg[1024];
		sprintf(msg, "%s: greater than 1000\n", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	
	if(image1 != NULL)
	{
		char msg[128];
		sprintf(msg,"%s: about to update input1\n", SinkName() );
		Logger::LogEvent(msg);
		image1->Update();
		sprintf(msg,"%s: done updating input1\n", SinkName() );
		Logger::LogEvent(msg);
		sprintf(msg,"%s: about to execute\n", SinkName() );
		Logger::LogEvent(msg);
		sprintf(msg,"%s: done executing\n", SinkName() );
		Logger::LogEvent(msg);
	}

	if(image2 != NULL)
	{
		char msg[128];
		sprintf(msg,"%s: about to update input2\n", SinkName());
		Logger::LogEvent(msg);
		image2->Update();
		sprintf(msg,"%s: done to update input2\n", SinkName());
		Logger::LogEvent(msg);
		sprintf(msg,"%s: about to execute\n", SinkName() );
		Logger::LogEvent(msg);
		sprintf(msg,"%s: done executing\n", SinkName() );
		Logger::LogEvent(msg);
	}
	
	Execute();
}

const char *Filter::SourceName()
{
	return FilterName();
}

const char *Filter::SinkName()
{
	return FilterName();
}