#include "algocamerapose.h"
#include <opencv2/calib3d/calib3d.hpp>
using namespace cv;

namespace acam {


bool calcRotTransOfCamera(camera &cam, objPlanar &object)
{
    Mat rvec, tvec;  //Output rotation vector and Output translation vector
    solvePnP(object.getObjectPoints(),object.getImagePoints(),cam.getInMatrix(),cam.getInDistCoeffs(),rvec,tvec);
    cam.setRotTransToWorldC(rvec,tvec);
    return true;    //FixMe: Feedback weather result succeeded should be implemented
}

}
