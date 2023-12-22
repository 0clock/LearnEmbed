#include <stdio.h>
int main() {
    float side1, side2, side3;
    printf("请输入三角形的三条边长：");
    scanf("%f %f %f", &side1, &side2, &side3);
    if (side1 + side2 > side3 && side1 + side3 > side2 && side2 + side3 > side1) {
        printf("能构成三角形\n");
        if (side1 == side2 || side1 == side3 || side2 == side3) {
            printf("是等腰三角形\n");
            if (side1 == side2 && side1 == side3) {
                printf("是等边三角形\n");
            }
        }
    } else {
        printf("不能构成三角形\n");
    }
    return 0;
}
