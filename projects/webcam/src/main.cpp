#include "camera.hpp"
#include "network.hpp"

int main(int argc, const char *argv[])
{
    CameraImageProcess cc;
    NetWork s;
    s.init();
    cc.cam_init();
    s.wait();
    while(1)
    {
        cc.get_fram();
        s.send_img(cc.jpeg_buffer);
        // cc.save_image();
    }
    return 0;
}
