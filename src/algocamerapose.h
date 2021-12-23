#ifndef ALGOCAMERAPOSE_H
#define ALGOCAMERAPOSE_H
#include <opencv2/core/core.hpp>
#include <vector>
#include <camera.h>
#include <objplanar.h>

namespace acam {
    bool calcRotTransOfCamera(camera &cam, objPlanar &object);

}
#endif // ALGOCAMERAPOSE_H
