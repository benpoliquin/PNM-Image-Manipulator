#include "sink.h"
#include <stdio.h>

Sink::Sink()
{
	image1 = NULL;
	image2 = NULL;
};

void Sink::SetInput(Image  *image1)
{
    this->image1 = image1;
}

void Sink::SetInput2(Image *image2)
{
    this->image2 = image2;
}