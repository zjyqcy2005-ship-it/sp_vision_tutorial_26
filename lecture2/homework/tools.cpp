#include "tools.hpp"

cv::Mat resizeToCanvas(const cv::Mat& src, int canvasSize, float& scale, int& offsetX, int& offsetY) {
    int srcW = src.cols;
    int srcH = src.rows;

    // 计算缩放比例
    scale = std::min(static_cast<float>(canvasSize) / srcW, static_cast<float>(canvasSize) / srcH);
    int newW = static_cast<int>(srcW * scale);
    int newH = static_cast<int>(srcH * scale);

    // 计算偏移量，让图片居中
    offsetX = (canvasSize - newW) / 2;
    offsetY = (canvasSize - newH) / 2;

    // 缩放图片
    cv::Mat resized;
    cv::resize(src, resized, cv::Size(newW, newH));

    // 创建画布并放置缩放后的图片
    cv::Mat canvas(canvasSize, canvasSize, src.type(), cv::Scalar(0,0,0)); // 黑色背景
    resized.copyTo(canvas(cv::Rect(offsetX, offsetY, newW, newH)));

    // 输出参数
    fmt::print("scale = {}, offsetX = {}, offsetY = {}\n", scale, offsetX, offsetY);

    return canvas;
}
