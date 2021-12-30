#include "helperfunctions.h"
#include <opencv2/calib3d/calib3d.hpp>
#include <iostream>
#include <stdio.h>
using namespace cv;

namespace acam {


bool calcRotTransOfCamera(camera &cam, objPlanar &object)
{
    Mat rvec, tvec;  //Output rotation vector and Output translation vector
    solvePnP(object.getObjectPoints(),object.getImagePoints(),cam.getInMatrix(),cam.getInDistCoeffs(),rvec,tvec);
    cam.setRotTransToWorldC(rvec,tvec);
    return true;    //FixMe: Feedback weather result succeeded should be implemented
}

/**
 * @brief setDefaultCameraParameters sets the default parameters of the exercise, avoids additional work implementing an additional loader (may be added later)
 * @param cam
 */
void setDefaultCameraParameters(camera &cam){
    cam.setCameraLensParameters(-1.2093325853347778, -1.041786551475525,
                              -0.004819112829864025,-0.0027203019708395004,
                              64.01393127441406,-0.5568028688430786,-3.6638600826263428,78.03067016601562);
    const double vals[4]={3751.937744140625d,3821.9775390625d,1280,960};
    cam.setIntrinsic(vals[2],vals[3],vals[0],vals[1]);
}

void printCameraParameters(camera &cam)
{
    std::cout<<"Camera Matrix:"<<std::endl;
    std::cout<<cam.getInMatrix()<<std::endl;
    std::cout<<"Camera Dist:"<<std::endl;
    std::cout<<cam.getInDistCoeffs()<<std::endl;
    std::cout<<"RVec:"<<std::endl;
    std::cout<<cam.getRvec()<<std::endl;
    std::cout<<"TVec:"<<std::endl;
    std::cout<<cam.getTvec()<<std::endl;
    std::cout<<"------------------"<<std::endl;
}

void printCalibrationObject(objPlanar &object)
{
    std::cout<<"Calibration Object Points"<<std::endl;
    std::cout<<"Points:"<<object.getNumberOfPoints()<<" ImagePxls:"<<object.getNumberOfImgPoints()<<std::endl;
    if(object.getNumberOfPoints()==object.getNumberOfImgPoints()){
        std::cout<<"Corresponding Points:"<<std::endl;
        for(std::size_t i = 0; i < object.getNumberOfImgPoints(); ++i){
            std::cout<<"Pxl:"<<object.getImagePoints()[i]<<" Point:"<<object.getObjectPoints()[i]<<std::endl;

        }
    }
}

}
