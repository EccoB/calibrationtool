#include "camera.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;



camera::camera()
{
    cameraMatrix = Mat::eye(3, 3, CV_64F);  //Identity Matrix 3x3 Mit 64_Bit Floating Point
    distCoeffs = Mat::zeros(8, 1, CV_64F);
    positionCamCoordinates=Mat::zeros(3,1,CV_64F);   //Per default: the camera itself is at zero position in its coordinates
    rotM = Mat(3,1,cv::DataType<double>::type);//rodrigues rotation matrix

}

void camera::setIntrinsic(double cx, double cy, double fx, double fy)
{
    cameraMatrix.at<double>(0,0)=fx;
    cameraMatrix.at<double>(1,1)=fy;
    cameraMatrix.at<double>(0,2)=cx;
    cameraMatrix.at<double>(1,2)=cy;

}

void camera::setCameraLensParameters(double k1, double k2, double p1, double p2, double k3, double k4, double k5, double k6)
{
    distCoeffs = (Mat_<double>(8,1) << k1, k2, p1, p2, k3, k4, k5, k6);

}

void camera::setRotTransToWorldC(Mat &rvec, Mat &tvec)
{
    this->rvec=rvec.clone();
    this->tvec=tvec.clone();
    Rodrigues(rvec,rotM);   //Convert rotation Vector to Matrix
}

Mat camera::getPositionInCamCoordinates() const
{
    return positionCamCoordinates;
}

Point3d camera::translateToWorldCoordinate(cv::Point3d PointCamCoordinates)
{
    Mat point(PointCamCoordinates);
    Mat cameraPosition =rotM.t()*point-(rotM.t()*tvec);
    return Point3d(cameraPosition);

}

Mat camera::getInMatrix() const
{
    return cameraMatrix;

}

Mat camera::getInDistCoeffs() const
{
    return distCoeffs;

}

Mat camera::getRvec() const
{
    return rvec;

}

Mat camera::getTvec() const
{
    return tvec;

}

Mat camera::getRotM() const
{
    return rotM;

}


