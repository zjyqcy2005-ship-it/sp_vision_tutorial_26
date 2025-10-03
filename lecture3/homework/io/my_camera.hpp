#pragma once
#include "hikrobot/include/MvCameraControl.h"
#include <opencv2/opencv.hpp>
#include <unordered_map>

class myCamera {
public:
    myCamera();                  // 构造函数：初始化相机
    ~myCamera();                 // 析构函数：释放资源
    cv::Mat read();              // 读取一帧图像

private:
    void* handle_;               // 相机句柄
    MV_FRAME_OUT raw_;           // 原始帧数据
    bool opened_;                // 相机是否打开

    cv::Mat transfer(MV_FRAME_OUT& raw);  // 转换函数
};
