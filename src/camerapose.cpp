#include "camerapose.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <helperfunctions.h>
#include <iterator>
using namespace cv;

CameraPose::CameraPose()
{
    //-------- Excercise specific, should be done later more flexible ----------
    planar4ptsObject.push_back(Point3f(0,0,0));
    planar4ptsObject.push_back(Point3f(defaultBoardSizeMM.width,0,0));
    planar4ptsObject.push_back(Point3f(defaultBoardSizeMM.width, defaultBoardSizeMM.height, 0));
    planar4ptsObject.push_back(Point3f(0,defaultBoardSizeMM.height,0));
    acam::setDefaultCameraParameters(cam);

}

/**
 * @brief CameraPose::addPoint matches a pixel-coordinate with the integrated planar object
 * @param x coordinate in pixels of one corner
 * @param y coordinate in pixels of one corner
 */
void CameraPose::addPoint(int x, int y)
{
    switch (obj.getNumberOfPoints()) {
    case 0:     //First we as we get the points in
    case 1:
    default:
        obj.addimagePoint(Point2f(x,y));
        break;
    }
    // Calculation of cameraPosition, if there are enough points and we do it the first time
    if(obj.getNumberOfImgPoints()==4 && obj.getObjectPoints().size()==0){
        //First, we add the corresponding points
        for(std::size_t i = 0; i < 4; ++i) {
            obj.addObjectPoint(planar4ptsObject[i]);    //FixMe: This is only valid for the specific Planar DinA4 sheet
        }
        acam::calcRotTransOfCamera(cam,obj);
        acam::printCameraParameters(cam);
        acam::printCalibrationObject(obj);
    }

    // If there are four points defined, we calculate the position of the camera

    refreshImage();

}


/**
 * @brief CameraPose::refreshImage creates the image from the the CalibrationObject and pushes updates to the defined callbackfunction
 */
void CameraPose::refreshImage(){
    Mat newImage=obj.getImage();
    const std::vector<cv::Point2f> imagePts=obj.getImagePoints();
    size_t elements=imagePts.size();


    //----- Drawing Lines and points of image ----------

    if(elements>=2){
        //Draw all lines, that the user puts in, regardless of what the rest is doing, found it nice, kept it in
        //Precondition: To draw a line, there have to be at least two points
        for(std::size_t i = 1; i < imagePts.size(); ++i) {
           cv::line(newImage, imagePts[i-1], imagePts[i], Scalar(255, 255, 255), 5);//FixMe: constants written in code
           cv::circle(newImage,imagePts[i-1],10,Scalar(128, 128, 255),2);
           // type of pos is vector<T>::const_iterator
           // *pos = 5; // Compile error - can't write via const iterator
        }
    }
    if(elements>0){
        //Draw the last circle extra
        cv::circle(newImage,imagePts[elements-1],10,Scalar(128, 128, 255),2);
    }
    if(getSolutionValid()&&elements>=4){
        //If we have a solution we draw a nice Frame axis and the corners of the sheet
        cv::drawFrameAxes(newImage, cam.getInMatrix(), cam.getInDistCoeffs(), cam.getRvec(), cam.getTvec(),defaultBoardSizeMM.height/2);  //Draws an Frame at the positio of rvec and Tvec
        for(std::size_t i = 1; i < 4; ++i) {
            cv::line(newImage, imagePts[i-1], imagePts[i], Scalar(0, 255, 0), 2);
        }
        cv::line(newImage, imagePts[0], imagePts[3], Scalar(0, 255, 0), 2);
    }


    // If a callback is defined, we inform other classes that the image changed
    if(imageUpdatedcallback)
        imageUpdatedcallback(newImage);

}

/**
 * @brief CameraPose::getCalibrationObject
 * @return
 */
objPlanar *CameraPose::getCalibrationObject()
{
    //Smart pointer not necessary here, this class owns this object alone
    return &obj;
}

camera *CameraPose::getCamera()
{
    return &cam;
}

/**
 * @brief CameraPose::getSolutionValid return wether the solution is already valid or not - atm. just checks number of points but can be improved later
 * @return
 */
bool CameraPose::getSolutionValid() const
{
    if(obj.getNumberOfImgPoints()>=4){
        return true;
    }
    return false;
}

/**
 * @brief CameraPose::setRefreshedImageCallback sets the function, that will be called if the image was updated
 * use with lambda as parameter: [&yourClass](cv::Mat& m) { return yourClass.Function(m); });
 * @param callback
 */
void CameraPose::setRefreshedImageCallback(ImgCallbackFct callback)
{
    this->imageUpdatedcallback=callback;
}

void CameraPose::setOriginalImage(const Mat &originalImage)
{
    obj.addimage(originalImage);
}

Point3d CameraPose::getPositionOfObject() const
{
    Point3d t;
    Mat camZero=cam.getPositionInCamCoordinates();
    Mat cameraPositionRealWorld =cam.getRotM().t()*camZero-(cam.getRotM().t()*cam.getTvec());
    return(Point3f(cameraPositionRealWorld));
}

