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

std::vector<cv::Point2f> objPlanar::getImagePoints() const
{
    return imagePoints;

}

int objPlanar::getNumberOfPoints() const
{
    return objectPoints.size();

}

void objPlanar::addObjectPoint(cv::Point3f &point, cv::Point2f &correspondingPxl)
{
    objectPoints.push_back(point);
    imagePoints.push_back(correspondingPxl);

}
