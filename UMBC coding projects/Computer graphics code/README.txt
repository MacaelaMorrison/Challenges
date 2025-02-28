This project was completed as part of my Computer Graphics class

This program reads in an image and uses an energy function to determine which parts of the image will attract a viewers attention. This is based on how our eyes perceive color. The output is a black image with white outlines where the energy is highest. It creates some really interesting results. 

Eigen is used for easy vector and matrix manipulation and ImageMagick and the CImg libraries are used to read in and edit the image to allow for multiple input file formats.
The input file name can be changed on line 21, but this project is also set up to run using command line arguments for the input image. 

Note: Uncomment the #define gl in order to run on command line. A makefile is included, but would require you to have g++ and Eigen installed.

The results can be seen by opening the "out.png" file