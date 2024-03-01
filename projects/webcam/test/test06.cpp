#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 打开默认摄像头
    VideoCapture cap(0);
    
    // 检查摄像头是否成功打开
    if (!cap.isOpened()) {
        cerr << "Error: Unable to open camera." << endl;
        return -1;
    }
    
    // 设置摄像头分辨率
    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);

        // 检查参数是否被正确设置
    double width = cap.get(CAP_PROP_FRAME_WIDTH);
    double height = cap.get(CAP_PROP_FRAME_HEIGHT);
    double fps = cap.get(CAP_PROP_FPS);
    std::cout << "Frame width: " << width << ", Frame height: " << height << ", FPS: " << fps << std::endl;

    
    // 创建窗口
    namedWindow("Camera", WINDOW_NORMAL);
    
    // 持续读取并显示摄像头图像
    while (true) {
        Mat frame;
        
        // 从摄像头读取图像
        cap.read(frame);
        
        // 检查是否成功读取图像
        if (frame.empty()) {
            cerr << "Error: Unable to read frame from camera." << endl;
            break;
        }
        
        // 显示图像
        imshow("Camera", frame);
        
        // 按下 ESC 键退出循环
        if (waitKey(1) == 27) {
            break;
        }
    }
    
    // 关闭摄像头和窗口
    cap.release();
    destroyAllWindows();
    
    return 0;
}
