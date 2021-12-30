#ifndef OBJPLANAR_H
#define OBJPLANAR_H

#include <opencv2/core/core.hpp>
#include <vector>

/**
 * @brief The objPlanar class holds parameters and information for an object used for calibration purposes
 */
class objPlanar
{
public:
    objPlanar();
    //---- Getter
    std::vector<cv::Point3f> getObjectPoints() const;
    const std::vector<cv::Point2f> getImagePoints() const;
    int getNumberOfPoints() const;
    int getNumberOfImgPoints() const;
    cv::Mat getImage() const;

    void addObjectPoint(cv::Point3f point);
    void addimage(cv::Mat img);
    void addimagePoint(cv::Point2f pxlXY);
    void addObjectPoint(cv::Point3f point, cv::Point2f correspondingPxl);


    //----


private:
    std::vector<cv::Point3f> objectPoints;
    std::vector<cv::Point2f> imagePoints;
    cv::Mat image;
};

#endif // OBJPLANAR_H
