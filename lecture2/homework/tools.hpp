#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <opencv2/opencv.hpp>
#include <fmt/core.h>

// 缩放图片到 canvasSize*canvasSize 画布，居中放置
cv::Mat resizeToCanvas(const cv::Mat& src, int canvasSize, float& scale, int& offsetX, int& offsetY);

#endif // TOOLS_HPP
