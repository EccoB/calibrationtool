#include "testing.h"
#include <camera.h>
#include <stdio.h>
#include <iostream>
using namespace std;
namespace tst {

/**
 * @brief checkIntrinsics does check if matrices put in are stored in the right way
 * @return
 */
bool checkIntrinsics()
{
    camera c;
    c.setCameraLensParameters(-1.2093325853347778, -1.041786551475525,
                              -0.004819112829864025,-0.0027203019708395004,
                              64.01393127441406,-0.5568028688430786,-3.6638600826263428,78.03067016601562);
    bool passed=true;
    passed &= (c.getInDistCoeffs().rows==8);
    passed &= (c.getInDistCoeffs().cols==1);
    std::cout<< (passed ? "Dist PASSED": "Dist FAILED")<<endl;

    bool passed2=true;
    const double vals[4]={3751.937744140625d,3821.9775390625d,1280,960};
    c.setIntrinsic(vals[2],vals[3],vals[0],vals[1]);
    for(int i=0;i<4;i++){
        passed2 &= (c.getInMatrix().at<double>(i%2,(i>2 ? 2:i))==vals[i]);
        std::cout<< i%2<<"."<<(i>2 ? 2:i)<<": "<<vals[i]<<" vs "<<c.getInMatrix().at<double>(i%2,(i>2 ? 2:i))<<std::endl;
    }
    std::cout<< (passed2 ? "InMatrx PASSED": "Dist FAILED");

    return passed & passed2;

}



}


