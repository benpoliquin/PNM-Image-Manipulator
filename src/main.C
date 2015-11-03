#include <PNMreader.h>
#include <PNMwriter.h>
#include <filters.h>

int main(int argc, char *argv[])
{
    PNMreader reader(argv[1]);
    PNMwriter   writer;
    Shrinker    shrinker1;
    Shrinker    shrinker2;
    Shrinker    shrinker3;
    LRConcat    lrconcat1;
    LRConcat    lrconcat2;
    LRConcat    lrconcat3;
    TBConcat    tbconcat1;
    TBConcat    tbconcat2;
    TBConcat    tbconcat3;
    Blender     blender;
    Crop        crop;
    Transpose   transpose;
    Invert      invert;
    CheckSum    checkSum;

    Color color(675, 700, 0, 0, 128);

    blender.SetFactor(0.8);
    crop.SetRegion(300, 1400, 50, 400);

    shrinker1.SetInput(reader.GetOutput());

    lrconcat1.SetInput(shrinker1.GetOutput());
    lrconcat1.SetInput2(shrinker1.GetOutput());

    tbconcat1.SetInput(lrconcat1.GetOutput());
    tbconcat1.SetInput2(lrconcat1.GetOutput());

    shrinker2.SetInput(tbconcat1.GetOutput());

    lrconcat2.SetInput(shrinker2.GetOutput());
    lrconcat2.SetInput2(shrinker1.GetOutput());

    tbconcat2.SetInput(lrconcat2.GetOutput());
    tbconcat2.SetInput2(lrconcat1.GetOutput());

    blender.SetInput(tbconcat2.GetOutput());
    blender.SetInput2(reader.GetOutput());
    
    blender.GetOutput()->Update();

    writer.SetInput(blender.GetOutput());
    
    writer.Write(argv[2]);

    // Since use floating point in blender it does not work well yet for check sum, so check before blender
    checkSum.SetInput(tbconcat2.GetOutput()); 
    checkSum.OutputCheckSum("image_checksum");
}