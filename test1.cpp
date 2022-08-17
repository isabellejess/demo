#include <bits/stdc++.h>
#include <opencv2/opencv.hpp> 

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    VideoCapture vid("video/demo.mp4");
    Mat frame,tresh,frame_resize,frame_hsv;
    int L_H = 0;
    int U_H = 7;
    int L_S = 40;
    int U_S = 255;
    int L_V = 70;
    int U_V = 255;
    // namedWindow("atur", WINDOW_AUTOSIZE);
    // createTrackbar ("L_H", "atur", &L_H, 179);
    // createTrackbar ("U_H", "atur", &U_H, 179);
    // createTrackbar ("L_S", "atur", &L_S, 255);
    // createTrackbar ("U_S", "atur", &U_S, 255);
    // createTrackbar ("L_V", "atur", &L_V, 255);
    // createTrackbar ("U_V", "atur", &U_V, 255);

    while (true){
        vid.read(frame);
        resize(frame,frame_resize,Size(),0.5,0.5);
        rotate(frame_resize,frame_resize,ROTATE_90_CLOCKWISE);
        cvtColor(frame_resize,frame_hsv, COLOR_BGR2HSV);        
        inRange(frame_hsv, Scalar (L_H, L_S, L_V), Scalar(U_H, U_S, U_V), tresh);

        vector<vector<Point>> contours;
        findContours(tresh,contours,RETR_TREE,CHAIN_APPROX_NONE);

        for (int i=0;i<contours.size();i++){
            vector<Point>contours_lagi;
            Point2f center;
            float radius;
            contours_lagi = contours[i];
            minEnclosingCircle (contours_lagi,center,radius);
            if (radius>40 && radius <100){
                circle(frame_resize,center,radius,Scalar(0,225,0),5);
                printf ("x= %.2f, y= %.2f, rad= %.2f\n\n", center.x, center.y, radius);
            }
        }
        imshow("HASIL",frame_resize);
        

        if ((char)27 == (char) waitKey(20))
        break;
    }
    return 0;
}