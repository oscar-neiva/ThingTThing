#include "Vision.h"

Mat imageRGB;
int points[3];
bool click = false;

Vision::Vision(){    
    cam = VideoCapture(1);
    variation = 0.2;
    variationR = 4;
    calibrate = false;
}    

int Vision::time(){
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (t.tv_sec * 1000) + (t.tv_nsec * 1e-6);
}

void Vision::fixImage(Mat image, Color color){
    inRange(imageRGB, Scalar(color.colorR - variationR, color.colorG*(1 - variation), color.colorB*(1-variation)),
     Scalar(color.colorR + variationR, color.colorG * (1 + variation), color.colorB * (1 + variation)), calibImage);
}

void Vision::pixelColor(int evt, int x, int y, int flags, void* param){    
    if (evt == CV_EVENT_LBUTTONDOWN){
        Vec3b p = imageRGB.at<Vec3b>(y,x);
        printf("(%d, %d, %d)\n", p[0], p[1], p[2]);
        points[0] = (int)p[0];
        points[1] = (int)p[1];
        points[2] = (int)p[2];
        click = true;
    }   
}

Color Vision::saveColor(){        
    Color color = Color();

    while (true){ 
        clock_t start = time();  

        cam >> image;
        cvtColor(image, imageRGB, COLOR_BGR2RGB);

        //Filters
        blur(image, filteredImage, Size(10,5));
        //GaussianBlur(image, filteredImage, Size(10, 5), 0, 0 );

        imshow("Camera", filteredImage); 
        moveWindow("Camera", 0, 0);  

        inRange(imageRGB, Scalar(points[0] - variationR, points[1] * (1 - variation), points[2] * (1 - variation)),
         Scalar(points[0] + variationR, points[1] * (1 + variation), points[2] * (1 + variation)), calibImage);  

        imshow("Color Calibration", calibImage); 
        moveWindow("Color Calibration", 640, 0);

        setMouseCallback("Camera", pixelColor, 0);

        char key =  waitKey(1);    
        if (key == 27){
            for (int i=0; i<10; i++){
                destroyAllWindows();
                waitKey(1);  
            }
            break; 
        }
        if (click == true){
            color.colorR = points[0];
            color.colorG = points[1];
            color.colorB = points[2];

            if (key == 32){ 
                for (int i=0; i<10; i++){
                    destroyAllWindows();
                    waitKey(1);  
                }
                cout << "Color calibrate" << endl;
                click = false;
                points[0] = 0; points[1] = 0; points[2] = 0; 
                break;
            }            
        }        
    }
    return color;
}
