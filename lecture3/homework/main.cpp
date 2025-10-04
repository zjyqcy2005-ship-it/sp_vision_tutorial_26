#include "io/my_camera.hpp"
#include "tasks/yolo.hpp"
#include "opencv2/opencv.hpp"
#include "tools/img_tools.hpp"
#include <iostream>

int main()
{
    try {
        // 初始化相机
        myCamera camera;

        // 初始化 YOLO 类
        auto_aim::YOLO yolo("./configs/yolo.yaml");

        while (true) {
            // 读取图像
            cv::Mat img = camera.read();
            if (img.empty()) {
                std::cerr << "Warning: empty frame grabbed from camera!" << std::endl;
                continue;
            }

            // YOLO 识别装甲板
            std::list<auto_aim::Armor> armors = yolo.detect(img);

            // 遍历装甲板并画红色点/框
            for (auto& armor : armors) {
                tools::draw_points(img, armor.points, cv::Scalar(0, 0, 255));  // 注意：pts 要确认
            }

            // 显示图像
            cv::resize(img, img, cv::Size(640, 480));
            cv::imshow("img", img);
            if (cv::waitKey(1) == 'q') {
                break;
            }
        }
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
