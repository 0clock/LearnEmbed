#include <stdio.h>
int main() {
    char operation;
    double num1, num2, result;
    printf("Enter an operation (+, -, *, /, %%): ");
    scanf(" %c", &operation);
    printf("Enter two numbers: ");
    scanf("%lf %lf", &num1, &num2);
    switch (operation) {
        case '+':
            result = num1 + num2;
            printf("%.2lf + %.2lf = %.2lf\n", num1, num2, result);
            break;
        case '-':
            result = num1 - num2;
            printf("%.2lf - %.2lf = %.2lf\n", num1, num2, result);
            break;
        case '*':
            result = num1 * num2;
            printf("%.2lf * %.2lf = %.2lf\n", num1, num2, result);
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
                printf("%.2lf / %.2lf = %.2lf\n", num1, num2, result);
            } else {
                printf("Error: Division by zero\n");
            }
            break;
        case '%':
            if (num2 != 0) {
                result = (int)num1 % (int)num2;
                printf("%.2lf %% %.2lf = %.2lf\n", num1, num2, result);
            } else {
                printf("Error: Modulo by zero\n");
            }
            break;
        default:
            printf("Error: Invalid operation\n");
    }
    return 0;
}
