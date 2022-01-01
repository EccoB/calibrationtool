#ifndef CAMERAPOSE_H
#define CAMERAPOSE_H

#include <objplanar.h>
#include <camera.h>

#include <opencv2/core/core.hpp>
#include <vector>
#include <opencv2/core/types.hpp>
typedef std::function<void(const cv::Mat&)> ImgCallbackFct;

/**
 * @brief The CameraPose class contains all needed information to solve the exercise.
 * It takes an Image, Image-Points added by the user, a Calibration-Object and the Information about the Width and Height of a DINA4-sheet
 * to calculate the position of the camera.
 */
class CameraPose
{
public:
    CameraPose();
    void addPoint(int x, int y);
    void refreshImage();
    objPlanar* getCalibrationObject();
    camera* getCamera();

    bool getSolutionValid() const;
    void setRefreshedImageCallback(ImgCallbackFct callback);
    void setOriginalImage(const cv::Mat& originalImage);
    cv::Point3d getPositionOfCamera() const;
    void reset();

protected:
    objPlanar obj;
    std::vector<cv::Point3d> planar4ptsObject;
    cv::Size2f defaultBoardSizeMM={297,210};            // The size of the board in mm
    ImgCallbackFct imageUpdatedcallback;                //Callbackfunction informs other classes that Image has changed
    camera cam;                                         //Camera used to take the picture
    bool matchObjectPointsAndUserInput();
};

#endif // CAMERAPOSE_H
