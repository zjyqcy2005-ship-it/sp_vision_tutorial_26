#include "io/my_camera.hpp"
#include "tasks/yolo.hpp"
#include "opencv2/opencv.hpp"
#include "tools/img_tools.hpp"

int main()
{
    try {
        // 初始化相机
        myCamera camera;

        // 初始化yolo类（传入配置文件路径）
        YoloDetector yolo("./configs/yolo.yaml");

        while (true) {
            // 读取图像
            cv::Mat img = camera.read();

            // YOLO识别装甲板
            std::vector<Armor> armors = yolo.detect(img);

            // 画红色矩形
            for (auto& armor : armors) {
                draw_points(img, armor.pts, cv::Scalar(0, 0, 255));  // 红色
            }

            // 显示图像
            cv::resize(img, img , cv::Size(640, 480));
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
