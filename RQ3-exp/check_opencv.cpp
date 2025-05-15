#include <opencv2/core.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
    std::cout << "OpenCV version: " << CV_VERSION << std::endl;
    // ...
    cout << "OpenCV Build Information:" << endl;
    cout << cv::getBuildInformation() << endl
         << endl;

    // cout << "OpenCV is using parallel backend: " << (cv::currentParallelFramework() ? cv::currentParallelFramework() : "None (Sequential or unknown)") << endl;
    // ... rest of your main function ...
    return 0;
}
