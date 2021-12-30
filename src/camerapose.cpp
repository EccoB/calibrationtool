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
    //Draw the lines between all points
    const std::vector<cv::Point2f> imagePts=obj.getImagePoints();
    size_t elements=imagePts.size();
    switch (elements) {
    case 0:
        return;
        break;
    case 1:

    default:
        break;
    }



    //----- Drawing Lines and points of image ----------
    //Precondition: To draw a line, there have to be at least two points
    if(elements>=2){
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
    if(elements>=4){
        Mat img_draw_poses;
        cv::drawFrameAxes(newImage, cam.getInMatrix(), cam.getInDistCoeffs(), cam.getTvec(), cam.getRvec(),6*defaultBoardSizeMM.width);  //Draws an Frame at the positio of rvec and Tvec
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

