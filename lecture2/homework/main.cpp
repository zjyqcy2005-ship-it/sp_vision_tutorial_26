#include <opencv2/opencv.hpp>
#include <fmt/core.h>
#include "tools.hpp"

int main() {
    std::string filename = "../img/test_1.jpg";  // 相对于 build/ 或 main.cpp 的路径

    cv::Mat img = cv::imread(filename);
    if (img.empty()) {
        fmt::print("Failed to load image '{}'\n", filename);
        return -1;
    }

    float scale;
    int offsetX, offsetY;
    cv::Mat canvas = resizeToCanvas(img, 640, scale, offsetX, offsetY);

    cv::imshow("Resized Image", canvas);
    cv::waitKey(0);

    return 0;
}
