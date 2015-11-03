SimpleImageManipulator
======================

A simple image manipulator program written in C++.  
Features data flow execution, with logger and exception handling.  

**To run the program via terminal:**  
Download and then cd to the directory that you put it into  
'cd' into the folder called src  
Type 'make'  
Type './imageManipulator input.pnm output.pnm  

**SimpleImageManipulator has the following filters:**  
Shrinker -- halves the pixels of the image in size  
Left Right Concatenate -- takes two images and connects them left to right  
Top Bottom Concatenate -- takes two images and connects them top to bottom  
Blend -- makes the image more transparent, and puts it in front of a background  
Crop -- takes a range of pixels in width and height, and extracts the square within the range  
Transpose -- takes an image of MxN and makes it to be NxM  
Invert -- inverts the colors in an image  
Constant Color -- takes a size and color, then produces the image of that size with that color  
Check Sum --  sums the total value of each color channel and outputs it to a file  



