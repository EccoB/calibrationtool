#include "objplanar.h"

/**
 * @brief objPlanar::objPlanar holds the data for an planar object used for calibration purposes
 */
objPlanar::objPlanar()
{

}

/**
 * @brief objPlanar::getObjectPoints
 * @return The Points ob the object in the 3D-World coordinates
 */
std::vector<cv::Point3f> objPlanar::getObjectPoints() const
{
    return objectPoints;

}

/**
 * @brief objPlanar::getImagePoints
 * @return ImagePoints in Pixel-Coordinates
 */
const std::vector<cv::Point2f> objPlanar::getImagePoints() const
{
    return imagePoints;

}

/**
 * @brief objPlanar::getNumberOfPoints
 * @return Number of 3D-World-coordinates stored for this object
 */
int objPlanar::getNumberOfPoints() const
{
    return objectPoints.size();

}

/**
 * @brief objPlanar::getNumberOfImgPoints
 * @return Number of ImagePoints in pixels stored for this object
 */
int objPlanar::getNumberOfImgPoints() const
{
    return imagePoints.size();

}

/**
 * @brief objPlanar::getImage
 * @return Image, for that the Pixel-Points and corresponding Object-Points are given
 */
cv::Mat objPlanar::getImage() const
{
    return image;

}

/**
 * @brief objPlanar::addObjectPoint adds an Point in 3D-World-coordinates to the point
 * @param point
 */
void objPlanar::addObjectPoint(cv::Point3f point)
{
    objectPoints.push_back(point);

}

/**
 * @brief objPlanar::addObjectPoint adds a 3D-World-coordinate and the corresponding pixel in the image
 * @param point
 * @param correspondingPxl
 */
void objPlanar::addObjectPoint(cv::Point3f point, cv::Point2f correspondingPxl)
{
    objectPoints.push_back(point);
    imagePoints.push_back(correspondingPxl);
}

/**
 * @brief objPlanar::resetPoints deletes all objectPoints and ImagePoints, but leaves the image untouched
 */
void objPlanar::resetPoints()
{
    objectPoints.clear();
    imagePoints.clear();

}

/**
 * @brief objPlanar::addimage clones the corresponding image to the object
 * @param img
 */
void objPlanar::addimage(cv::Mat img)
{
    this->image=img.clone();
}

/**
 * @brief objPlanar::addimagePoint adds an Image-Point in Pixel-Coordinates to the Object
 * @param pxlXY
 */
void objPlanar::addimagePoint(cv::Point2f pxlXY)
{
    imagePoints.push_back(pxlXY);
}

