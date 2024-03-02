#include "camera.hpp"
#include "network.hpp"
#include <thread>
#include <mutex>
#include <condition_variable>

int main(int argc, const char *argv[])
{
    CameraImageProcess cc;
    NetWork s;
    s.init();
    cc.cam_init();
    s.wait();

    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;

    std::thread t1([&cc, &s, &mtx, &cv, &ready]() {
        while (true) {
            cc.get_fram();
            {
                std::lock_guard<std::mutex> lock(mtx);
                ready = true;
            }
            cv.notify_one();
        }
    });

    std::thread t2([&cc, &s, &mtx, &cv, &ready]() {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [&ready]() { return ready; });
            s.send_img(cc.jpeg_buffer);
            ready = false;
        }
    });

    t1.join(); // 等待第一个线程结束
    t2.join(); // 等待第二个线程结束

    return 0;
}
