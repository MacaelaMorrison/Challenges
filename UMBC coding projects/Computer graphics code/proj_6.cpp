#define cimg_display 0
#include <iostream>
#include "CImg.h"
#include <Eigen/Dense>
using namespace cimg_library;
using namespace std;

//#define gl

int main(int argc, char *argv[]) {

#ifdef gl

	string inFile = argv[1];
	string outFile = argv[2];
	double width = atoi(argv[3]);
	double height = atoi(argv[4]);

#else

	char inFile[] = "lena.png";
	char outFile[] = "out.png";
	

#endif


  CImg<double> input(inFile);
  double width = input.width();
  double height = input.height();

  CImg<double> lab = input.RGBtoLab();
  Eigen::Vector3d *image = new Eigen::Vector3d[input.width()*input.height()];
  CImg<double> tempImage = lab;//Setting equal to lab to preserve image dimensions
  Eigen::Vector3d *energyValues = new Eigen::Vector3d[input.width() * input.height()];
  Eigen::Vector3d* newImage = new Eigen::Vector3d[input.width() * input.height()];
  double max = 0.0;
  
  for (int i = 0; i < input.width(); i++) {
	  for (int j = 0; j < input.height(); j++) {
		  image[i * input.height() + j][0] = lab(i, j, 0);
		  image[i * input.height() + j][1] = 0.0;
		  image[i * input.height() + j][2] = 0.0;

		  
	  }
  }
  for (int i = 0; i < input.width(); i++) {
	  for (int j = 0; j < input.height(); j++)
	  {
		  double top = 0.0;
		  double bottom = 0.0;
		  double right = 0.0;
		  double left = 0.0;



		  if (i - 1 >= 0) { // Neighbor left
			  /*cout << "First value " << image[i * input.height() + j][0] << endl;
			  cout << "Second value " << image[(i - 1) * input.height() + j][0] << endl;*/
			  left = abs(image[i * input.height() + j][0] - image[(i - 1) * input.height() + j][0]);
			  //cout << "Top: " << top << endl;
		  }
		  if (i + 1 < input.width()) { // Neighbor right
			  /*cout << "First value " << image[i * input.height() + j][0] << endl;
			  cout << "Second value " << image[(i + 1) * input.height() + j][0] << endl;
			  cout << "Difference" << (image[i * input.height() + j][0]) - (image[(i + 1) * input.height() + j][0]) << endl;
			  cout << "Absolute value" << abs(image[i * input.height() + j][0] - image[(i + 1) * input.height() + j][0]) << endl;
			  cout << "i " << i << " j " << j << endl;*/
			  right = abs(image[i * input.height() + j][0] - image[(i + 1) * input.height() + j][0]);
		  }
		  if (j - 1 >= 0) { // Neighbor top
			  top = abs(image[i * input.height() + j][0] - image[i * input.height() + j - 1][0]);
		  }
		  if (j + 1 < input.height()) { // Neighbor bottom
			  bottom = abs(image[i * input.height() + j][0] - image[i * input.height() + j + 1][0]);
		  }

		  /*cout << "Top: " << top << endl;
		  cout << "Bottom: " << bottom << endl;
		  cout << "Right: " << right << endl;
		  cout << "Left: " << left << endl;*/

		  double totalEnergy = 0.0;
		  totalEnergy = top + bottom + right + left;
		  if (max < totalEnergy)
		  {
			  max = totalEnergy;
		  }

		  energyValues[i * input.height() + j][0] = totalEnergy;
		  /*cout << "energy value: " << energyValues[i * input.height() + j][0] << endl;
		  cout << "Max: " << max << endl;*/
	  }
  }
  for (int i = 0; i < input.width(); i++) {
	  for (int j = 0; j < input.height(); j++)
	  {
		  
		  double energy = pow(energyValues[i * input.height() + j][0] / max, 1.0 / 3.0) * 255;
		  newImage[i * input.height() + j][0] = energy;
		  newImage[i * input.height() + j][1] = 0.0;
		  newImage[i * input.height() + j][2] = 0.0;
	  }
  }

  CImg<double> energyOutput(width, height, 1, 3, 0);
  for (int i = 0; i < energyOutput.width(); i++) {
	  for (int j = 0; j < energyOutput.height(); j++) {
		  energyOutput(i, j, 0) = newImage[i * energyOutput.height() + j][0];
		  energyOutput(i, j, 1) = newImage[i * energyOutput.height() + j][1];
		  energyOutput(i, j, 2) = newImage[i * energyOutput.height() + j][2];
	  }
  }

  CImg<double> output(width, height, input.depth(), input.spectrum(), 0);
  for (int i=0; i<output.width(); i++) {
	for (int j=0; j<output.height(); j++) {
	  output(i, j, 0) = newImage[i*output.height()+j][0]; 
	  output(i, j, 1) = newImage[i*output.height()+j][1];
	  output(i, j, 2) = newImage[i*output.height()+j][2];
	}
  }

  CImg<double> rgb = output.LabtoRGB();
  if (strstr(outFile, "png"))
	rgb.save_png(outFile);
  else if (strstr(outFile, "jpg"))
	rgb.save_jpeg(outFile);

  delete [] image;
  return 0;
}

