#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filters.h"
#include "logging.h"

void Shrinker::Execute()
{
    int i, j;                                                       // Initialize i & j variables
    
    img.ResetSize(image1->GetWidth()/2, image1->GetHeight()/2);
    
    for(i = 0; i < img.GetHeight(); i++)
    {
        for(j = 0; j < img.GetWidth(); j++)
        {
            img.GetBuffer()[3*(i*img.GetWidth()+j)+0] = image1->GetBuffer()[3*(2*i*image1->GetWidth()+2*j)+0];
            img.GetBuffer()[3*(i*img.GetWidth()+j)+1] = image1->GetBuffer()[3*(2*i*image1->GetWidth()+2*j)+1];
            img.GetBuffer()[3*(i*img.GetWidth()+j)+2] = image1->GetBuffer()[3*(2*i*image1->GetWidth()+2*j)+2];
        }
    }
}

const char * Shrinker::FilterName()
{
    return "Shrinker";
}

void LRConcat::Execute()
{
    int i, j;                                                        // Initialize the i & j  variables 
    int width, height;

    if(image1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    if(image2 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    if(image1->GetWidth() != image2->GetWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: widths must match: %d, %d\n", SinkName(), image1->GetWidth(), image2->GetWidth());
        DataFlowException e(SinkName(), msg);
        throw e;
    }        

    width = image1->GetWidth() + image2->GetWidth();

    if(image1->GetHeight() > image2->GetHeight())                   // Find the max height of the two images 
    {
        height = image1->GetWidth();
    }
    else
    {
        height = image2->GetHeight();
    }

    img.ResetSize(width, height);

    for(i = 0; i < img.GetHeight(); i++)
    {
        for(j = 0; j < img.GetWidth(); j++)
        {           
            if(j < image1->GetWidth())
            {
                img.GetBuffer()[3*(i*img.GetWidth()+j)+0] = image1->GetBuffer()[3*(i*image1->GetWidth()+j)+0];
                img.GetBuffer()[3*(i*img.GetWidth()+j)+1] = image1->GetBuffer()[3*(i*image1->GetWidth()+j)+1];
                img.GetBuffer()[3*(i*img.GetWidth()+j)+2] = image1->GetBuffer()[3*(i*image1->GetWidth()+j)+2];
           
            }           
            else
            {
                img.GetBuffer()[3*(i*img.GetWidth()+j)+0] = image2->GetBuffer()[3*(i*image2->GetWidth()+j - image1->GetWidth()) + 0];
                img.GetBuffer()[3*(i*img.GetWidth()+j)+1] = image2->GetBuffer()[3*(i*image2->GetWidth()+j - image1->GetWidth()) + 1];
                img.GetBuffer()[3*(i*img.GetWidth()+j)+2] = image2->GetBuffer()[3*(i*image2->GetWidth()+j - image1->GetWidth()) + 2];
            }
        }
    }
}

const char * LRConcat::FilterName()
{
    return "LRConcat";
}

void TBConcat::Execute()
{
    int i, j;                                                   // Initialize the i & j  variables 
    int width, height;

    if(image1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    if(image2 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    if(image1->GetWidth() != image2->GetWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: widths must match: %d, %d\n", SinkName(), image1->GetWidth(), image2->GetWidth());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    else
    {
        height = image1->GetHeight() + image2->GetHeight();

        if(image1->GetWidth() > image2->GetWidth())            // Find the max width of the two images
        {
            width = image1->GetWidth();
        }
        else
        {
            width = image2->GetWidth();
        }

        img.ResetSize(width, height);

        for(i = 0; i < image1->GetHeight(); i++)
        {
            for(j = 0; j < img.GetWidth(); j++)
            {   
                img.GetBuffer()[3*(i*img.GetWidth()+j)+0] = image1->GetBuffer()[3*(i*image1->GetWidth()+j)+0];
                img.GetBuffer()[3*(i*img.GetWidth()+j)+1] = image1->GetBuffer()[3*(i*image1->GetWidth()+j)+1];
                img.GetBuffer()[3*(i*img.GetWidth()+j)+2] = image1->GetBuffer()[3*(i*image1->GetWidth()+j)+2];  
            }
        }

        for(i = 0; i < image2->GetHeight(); i++)
        {
            for(j = 0; j < img.GetWidth(); j++)
            {
                           
                img.GetBuffer()[3*((i+image1->GetHeight())*img.GetWidth()+j)+0] = image2->GetBuffer()[3*(i*image2->GetWidth()+j)+0];
                img.GetBuffer()[3*((i+image1->GetHeight())*img.GetWidth()+j)+1] = image2->GetBuffer()[3*(i*image2->GetWidth()+j)+1];
                img.GetBuffer()[3*((i+image1->GetHeight())*img.GetWidth()+j)+2] = image2->GetBuffer()[3*(i*image2->GetWidth()+j)+2];
            }
        }
    }
}

const char * TBConcat::FilterName()
{
    return "TBConcat";
}

void Blender::SetFactor(float factor)
{
    this->factor = factor;
}

void Blender::Execute()
{
    unsigned char *pixel;                                                                           // Initialize the pixal variable 
    int i, j;

    if(image1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    if(image2 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    if(factor < 0 || factor > 1)
    {
        char msg[1024];
        sprintf(msg, "%s: factor does not work: %f\n", SinkName(), factor);
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    else
    {
        img.ResetSize(image1->GetWidth(), image1->GetHeight());

        memcpy(img.GetBuffer(), image1->GetBuffer(), 3*image1->GetWidth()*image1->GetHeight());         // Copy the image memory and create a new one

        for(i = 0; i < img.GetHeight(); i++)                                                         // For loop to set the pixel color down the diagonal 
        {
            for(j = 0; j < img.GetWidth(); j++)
            {                  
                img.GetBuffer()[3*(i*img.GetWidth()+j)+0] = (image1->GetBuffer()[3*(i*image1->GetWidth()+j)+0]*factor) + (image2->GetBuffer()[3*(i*image2->GetWidth()+j)+0]*(1-factor));
                img.GetBuffer()[3*(i*img.GetWidth()+j)+1] = (image1->GetBuffer()[3*(i*image1->GetWidth()+j)+1]*factor) + (image2->GetBuffer()[3*(i*image2->GetWidth()+j)+1]*(1-factor));
                img.GetBuffer()[3*(i*img.GetWidth()+j)+2] = (image1->GetBuffer()[3*(i*image1->GetWidth()+j)+2]*factor) + (image2->GetBuffer()[3*(i*image2->GetWidth()+j)+2]*(1-factor));
            }
        }
    }
}

const char * Blender::FilterName()
{
    return "Blender";
}

void Crop::Execute()
{
    if (Istart < 0 || Istop < 0 || Jstart < 0 || Jstop < 0)
    {
        char msg[1024];
        sprintf(msg, "%s: uninitialized region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istart >= image1->GetWidth() || Istop >= image1->GetWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image width", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Jstart >= image1->GetHeight() || Jstop >= image1->GetHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image height", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istop < Istart || Jstop < Jstart)
    {
        char msg[1024];
        sprintf(msg, "%s: invalid region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }

    int height = Jstop-Jstart+1;
    int width  = Istop-Istart+1;
    int inputWidth = image1->GetWidth();

    img.ResetSize(width, height);

    unsigned char *buffer = img.GetBuffer();
    const unsigned char *buffer1 = image1->GetBuffer();

    for (int i = Istart ; i <= Istop ; i++)
    {
        for (int j = Jstart ; j <= Jstop ; j++)
        {
            int idx1 = j*inputWidth+i;
            int idx  = (j-Jstart)*width+(i-Istart);
            buffer[3*idx]   = buffer1[3*idx1];
            buffer[3*idx+1] = buffer1[3*idx1+1];
            buffer[3*idx+2] = buffer1[3*idx1+2];
        }
    }
}

void Crop::SetRegion(int Istart_, int Istop_, int Jstart_, int Jstop_)
{
    Istart = Istart_;
    Istop  = Istop_;
    Jstart = Jstart_;
    Jstop  = Jstop_;
}

const char *Crop::FilterName() 
{ 
    return "Crop"; 
}

void Transpose::Execute()
{
    int i, j, index, index1;

    if(image1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    img.ResetSize(image1->GetHeight(), image1->GetWidth());

    for(i = 0; i < img.GetHeight(); i++) 
    {
        for(j = 0; j < img.GetWidth(); j++) 
        {
            index = 3*(i*img.GetWidth()+j);
            index1 = 3*(j*image1->GetWidth()+i);

            img.GetBuffer()[index + 0] = image1->GetBuffer()[index1 + 0];
            img.GetBuffer()[index + 1] = image1->GetBuffer()[index1 + 1];
            img.GetBuffer()[index + 2] = image1->GetBuffer()[index1 + 2];
        }
    }
    
}

const char *Transpose::FilterName()
{
    return "Transpose";
}

void Invert::Execute()
{
    int i, j, index, index1;

    if(image1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    img.ResetSize(image1->GetWidth(), image1->GetHeight());
    
    for(i = 0; i < image1->GetWidth(); i++)
    {
        for(j = 0; j < image1->GetHeight(); j++)
        {
            index = 3*(i*img.GetWidth()+j);
            index1 = 3*(j*image1->GetWidth()+i);

            img.GetBuffer()[index + 0] = image1->GetBuffer()[index1 + 0];
            img.GetBuffer()[index + 1] = image1->GetBuffer()[index1 + 1];
            img.GetBuffer()[index + 2] = image1->GetBuffer()[index1 + 2];
        }
    }
}

const char *Invert::FilterName()
{
    return "Invert";
}

void Color::Execute()
{
    int i, j;

    img.ResetSize(width, height);

    for(i = 0; i < img.GetWidth(); i++)
    {
        for(j = 0; j < img.GetHeight(); j++)
        {
            img.GetBuffer()[3*(j*img.GetWidth()+i)+0] = red;
            img.GetBuffer()[3*(j*img.GetWidth()+i)+1] = green;
            img.GetBuffer()[3*(j*img.GetWidth()+i)+2] = blue;
        }
    }
}

void CheckSum::OutputCheckSum(const char *file)
{
	if(image1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    FILE* checksum = fopen(file, "w");

    int i, j;
    unsigned char red = 0;
    unsigned char green = 0;
    unsigned char blue = 0;

    for(i = 0; i < image1->GetWidth(); i++)
    {
        for(j = 0; j < image1->GetHeight(); j++)
        {
            red += image1->GetBuffer()[3*(j*image1->GetWidth()+i)+0];
            green += image1->GetBuffer()[3*(j*image1->GetWidth()+i)+1];
            blue += image1->GetBuffer()[3*(j*image1->GetWidth()+i)+2];
        }
    }
    fprintf(checksum, "CHECKSUM: %d, %d, %d\n", red, green, blue);
    fclose(checksum);
}