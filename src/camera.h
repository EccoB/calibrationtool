#ifndef CAMERA_H
#define CAMERA_H
#include <opencv2/core/core.hpp>

class camera
{
public:
    camera();

    void setIntrinsic(double cx, double cy, double fx, double fy);
    void setCameraLensParameters(double k1, double k2, double p1, double p2, double k3=0, double k4=0, double k5=0, double k6=0);  //(k1,k2,p1,p2[,k3[,k4,k5,k6 - not implemented: [,s1,s2,s3,s4[,τx,τy]]]])
    void setRotTransToWorldC(cv::Mat &rvec, cv::Mat &tvec);

    cv::Point3d translateToWorldCoordinate(cv::Point3d PointCamCoordinates);

    cv::Mat getInMatrix() const;
    cv::Mat getInDistCoeffs() const;
    cv::Mat getRvec() const;
    cv::Mat getTvec() const;
    cv::Mat getRotM() const;
protected:
    cv::Mat cameraMatrix, distCoeffs;
    cv::Point3f worldPosition;
    cv::Mat rvec, rotM, tvec;  //rotation vector and translation vector from CameraCoordinates to WorldCoordinates


};

#endif // CAMERA_H
