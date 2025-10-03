#include "my_camera.hpp"

myCamera::myCamera() : handle_(nullptr), opened_(false) {
    MV_CC_DEVICE_INFO_LIST device_list;
    int ret = MV_CC_EnumDevices(MV_USB_DEVICE, &device_list);
    if (ret != MV_OK || device_list.nDeviceNum == 0) {
        throw std::runtime_error("No camera found");
    }

    ret = MV_CC_CreateHandle(&handle_, device_list.pDeviceInfo[0]);
    if (ret != MV_OK) throw std::runtime_error("Create handle failed");

    ret = MV_CC_OpenDevice(handle_);
    if (ret != MV_OK) throw std::runtime_error("Open device failed");

    // 设置相机参数
    MV_CC_SetEnumValue(handle_, "BalanceWhiteAuto", MV_BALANCEWHITE_AUTO_CONTINUOUS);
    MV_CC_SetEnumValue(handle_, "ExposureAuto", MV_EXPOSURE_AUTO_MODE_OFF);
    MV_CC_SetEnumValue(handle_, "GainAuto", MV_GAIN_MODE_OFF);
    MV_CC_SetFloatValue(handle_, "ExposureTime", 10000);
    MV_CC_SetFloatValue(handle_, "Gain", 20);
    MV_CC_SetFrameRate(handle_, 60);

    ret = MV_CC_StartGrabbing(handle_);
    if (ret != MV_OK) throw std::runtime_error("Start grabbing failed");

    opened_ = true;
}

myCamera::~myCamera() {
    if (opened_) {
        MV_CC_StopGrabbing(handle_);
        MV_CC_CloseDevice(handle_);
        MV_CC_DestroyHandle(handle_);
        opened_ = false;
    }
}

cv::Mat myCamera::transfer(MV_FRAME_OUT& raw) {
    cv::Mat img(cv::Size(raw.stFrameInfo.nWidth, raw.stFrameInfo.nHeight), CV_8U, raw.pBufAddr);

    const static std::unordered_map<MvGvspPixelType, cv::ColorConversionCodes> type_map = {
        {PixelType_Gvsp_BayerGR8, cv::COLOR_BayerGR2RGB},
        {PixelType_Gvsp_BayerRG8, cv::COLOR_BayerRG2RGB},
        {PixelType_Gvsp_BayerGB8, cv::COLOR_BayerGB2RGB},
        {PixelType_Gvsp_BayerBG8, cv::COLOR_BayerBG2RGB}
    };

    auto pixel_type = raw.stFrameInfo.enPixelType;
    cv::cvtColor(img, img, type_map.at(pixel_type));
    return img.clone();  // clone避免被释放
}

cv::Mat myCamera::read() {
    unsigned int nMsec = 100;
    int ret = MV_CC_GetImageBuffer(handle_, &raw_, nMsec);
    if (ret != MV_OK) {
        throw std::runtime_error("Get image buffer failed");
    }

    cv::Mat img = transfer(raw_);

    MV_CC_FreeImageBuffer(handle_, &raw_);
    return img;
}
