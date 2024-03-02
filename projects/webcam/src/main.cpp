#include "camera.hpp"
// #include ""

int main(int argc, const char *argv[])
{
    Camera c;
    c.cam_init();
    while(1)
    {
        c.get_fram();
    }
    return 0;
}
