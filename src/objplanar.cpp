#include "objplanar.h"

/**
 * @brief objPlanar::objPlanar holds the data for an planar object used for calibration purposes
 */
objPlanar::objPlanar()
{

}

std::vector<cv::Point3f> objPlanar::getObjectPoints() const
{
    return objectPoints;

}

const std::vector<cv::Point2f> objPlanar::getImagePoints() const
{
    return imagePoints;

}

int objPlanar::getNumberOfPoints() const
{
    return objectPoints.size();

}

int objPlanar::getNumberOfImgPoints() const
{
    return imagePoints.size();

}

cv::Mat objPlanar::getImage() const
{
    return image;

}

void objPlanar::addObjectPoint(cv::Point3f point)
{
    objectPoints.push_back(point);

}

void objPlanar::addObjectPoint(cv::Point3f point, cv::Point2f correspondingPxl)
{
    objectPoints.push_back(point);
    imagePoints.push_back(correspondingPxl);
}

/**
 * @brief objPlanar::addimage clones the corresponding image to the object
 * @param img
 */
void objPlanar::addimage(cv::Mat img)
{
    this->image=img.clone();
}

void objPlanar::addimagePoint(cv::Point2f pxlXY)
{
    imagePoints.push_back(pxlXY);
}
