#include <stdio.h>
#include "image.h"
#include "source.h"
#include "logging.h"

Image * Source::GetOutput()
{
	return &img;
}

void Source::Update()
{
	char msg[128];
	sprintf(msg, "%s: about executing\n", SourceName());
	Logger::LogEvent(msg);
	Execute();
	sprintf(msg, "%s: done executing\n", SourceName());
	Logger::LogEvent(msg);
}

Source::Source()
{
	img.SetSource(this);
};