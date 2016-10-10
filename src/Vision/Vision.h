#ifndef VISION_H_
#define VISION_H_

#include <iostream>
#include <stdio.h>
#include "unistd.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "Color.h"

using namespace cv;
using namespace std;


class Vision{
private:
	VideoCapture cam;  
    Mat image;
    Mat calibImage;
    Mat filteredImage;
    int variationR;
    float variation;
    bool calibrate;

public:
  //  static bool click;
    //static Mat imageRGB;
    //static int points[3];
    
	Vision();
    int time();
    static void pixelColor(int evt, int x, int y, int flags, void* param);
    void fixImage(Mat image, Color color);    
    void calibrateColor(); 
    Color saveColor();
};
#endif
