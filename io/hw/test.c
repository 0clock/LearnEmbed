#include <stdint.h>
#include <stdio.h>

// 假设color是一个包含红、绿、蓝三个分量的结构体
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} Color;

int main() {
    // 打开或创建一个bmp文件，假设文件指针是fp
    FILE *fp = fopen("output.bmp", "wb");

    // 定义黄色的Color结构体，可以根据实际需要调整RGB值
    Color yellow = {255, 255, 0};

    // 图像宽度和高度，根据实际需求调整
    int width = 800;
    int height = 600;

    // 写BMP文件头
    // 请注意，以下代码仅适用于24位色深度的BMP图像，如果你的图像深度不同，需要调整文件头的大小和格式
    uint16_t bfType = 0x4D42; // "BM"
    uint32_t bfSize = 54 + (width * height * 3); // 文件大小
    uint16_t bfReserved1 = 0;
    uint16_t bfReserved2 = 0;
    uint32_t bfOffBits = 54; // 数据偏移量

    fwrite(&bfType, sizeof(uint16_t), 1, fp);
    fwrite(&bfSize, sizeof(uint32_t), 1, fp);
    fwrite(&bfReserved1, sizeof(uint16_t), 1, fp);
    fwrite(&bfReserved2, sizeof(uint16_t), 1, fp);
    fwrite(&bfOffBits, sizeof(uint32_t), 1, fp);

    // 写BMP信息头
    uint32_t biSize = 40; // 信息头大小
    uint32_t biWidth = width; // 图像宽度
    uint32_t biHeight = height; // 图像高度
    uint16_t biPlanes = 1; // 颜色平面数
    uint16_t biBitCount = 24; // 每个像素的位数
    uint32_t biCompression = 0; // 压缩类型，0表示不压缩
    uint32_t biSizeImage = 0; // 图像数据大小，可设置为0
    uint32_t biXPelsPerMeter = 0; // 水平分辨率，可设置为0
    uint32_t biYPelsPerMeter = 0; // 垂直分辨率，可设置为0
    uint32_t biClrUsed = 0; // 使用的颜色索引数，可设置为0
    uint32_t biClrImportant = 0; // 重要颜色索引数，可设置为0

    fwrite(&biSize, sizeof(uint32_t), 1, fp);
    fwrite(&biWidth, sizeof(uint32_t), 1, fp);
    fwrite(&biHeight, sizeof(uint32_t), 1, fp);
    fwrite(&biPlanes, sizeof(uint16_t), 1, fp);
    fwrite(&biBitCount, sizeof(uint16_t), 1, fp);
    fwrite(&biCompression, sizeof(uint32_t), 1, fp);
    fwrite(&biSizeImage, sizeof(uint32_t), 1, fp);
    fwrite(&biXPelsPerMeter, sizeof(uint32_t), 1, fp);
    fwrite(&biYPelsPerMeter, sizeof(uint32_t), 1, fp);
    fwrite(&biClrUsed, sizeof(uint32_t), 1, fp);
    fwrite(&biClrImportant, sizeof(uint32_t), 1, fp);

    // 写入黄色的框
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fwrite(&yellow, sizeof(Color), 1, fp);
        }
    }

    // 关闭文件
    fclose(fp);

    return 0;
}
