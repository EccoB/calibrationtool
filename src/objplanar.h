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
    std::vector<cv::Point3f> getObjectPoints() const;
    std::vector<cv::Point2f> getImagePoints() const;
    int getNumberOfPoints() const;
    void addObjectPoint(cv::Point3f &point, cv::Point2f &correspondingPxl);


private:
    std::vector<cv::Point3f> objectPoints;
    std::vector<cv::Point2f> imagePoints;
};

#endif // OBJPLANAR_H
