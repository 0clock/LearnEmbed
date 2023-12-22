#include <stdio.h>
int main() {
    int score;
    printf("请输入学生成绩：");
    scanf("%d", &score);
    int scoreRange = score / 10;
    switch (scoreRange) {
        case 10:
        case 9:
            printf("成绩等级：A\n");
            break;
        case 8:
            printf("成绩等级：B\n");
            break;
        case 7:
            printf("成绩等级：C\n");
            break;
        case 6:
            printf("成绩等级：D\n");
            break;
        default:
            if (score > 100 || score < 0) {
                printf("输入不合理\n");
            } else {
                printf("成绩等级：不及格\n");
            }
            break;
    }
    return 0;
}
