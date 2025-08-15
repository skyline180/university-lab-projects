/*  Project Name : Temperature Converter
*   Environment  : Code::Blocks 20.04 (GNU/GCC)
*   Language Used: C
*   Author       : Md. Shahat Akash
*   Date         : 26 January, 2023
*/

#include <stdio.h>
#include <stdlib.h>

// 1. Celsius to Fahrenheit
void celsius_to_fahrenheit() {
    double C, F;
    printf("Enter Celsius Temperature: ");
    scanf("%lf", &C);
    F = (C * 9.0 / 5.0) + 32.0;
    printf("\n%.2lf °C = %.2lf °F\n", C, F);
}

// 2. Celsius to Kelvin
void celsius_to_kelvin() {
    double C, K;
    printf("Enter Celsius Temperature: ");
    scanf("%lf", &C);
    K = C + 273.15;
    printf("\n%.2lf °C = %.2lf K\n", C, K);
}

// 3. Fahrenheit to Celsius
void fahrenheit_to_celsius() {
    double F, C;
    printf("Enter Fahrenheit Temperature: ");
    scanf("%lf", &F);
    C = (F - 32.0) * 5.0 / 9.0;
    printf("\n%.2lf °F = %.2lf °C\n", F, C);
}

// 4. Fahrenheit to Kelvin
void fahrenheit_to_kelvin() {
    double F, K;
    printf("Enter Fahrenheit Temperature: ");
    scanf("%lf", &F);
    K = (F - 32.0) * 5.0 / 9.0 + 273.15;
    printf("\n%.2lf °F = %.2lf K\n", F, K);
}

// 5. Kelvin to Celsius
void kelvin_to_celsius() {
    double K, C;
    printf("Enter Kelvin Temperature: ");
    scanf("%lf", &K);
    C = K - 273.15;
    printf("\n%.2lf K = %.2lf °C\n", K, C);
}

// 6. Kelvin to Fahrenheit
void kelvin_to_fahrenheit() {
    double K, F;
    printf("Enter Kelvin Temperature: ");
    scanf("%lf", &K);
    F = (K - 273.15) * 9.0 / 5.0 + 32.0;
    printf("\n%.2lf K = %.2lf °F\n", K, F);
}

// Main menu
int main() {
    printf("\t\t_____ TEMPERATURE CONVERTER _____\n");

    while (1) {
        printf("\n1. Celsius to Fahrenheit");
        printf("\n2. Celsius to Kelvin");
        printf("\n3. Fahrenheit to Celsius");
        printf("\n4. Fahrenheit to Kelvin");
        printf("\n5. Kelvin to Celsius");
        printf("\n6. Kelvin to Fahrenheit");
        printf("\n7. Exit");

        int choice;
        printf("\n\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: celsius_to_fahrenheit(); break;
            case 2: celsius_to_kelvin(); break;
            case 3: fahrenheit_to_celsius(); break;
            case 4: fahrenheit_to_kelvin(); break;
            case 5: kelvin_to_celsius(); break;
            case 6: kelvin_to_fahrenheit(); break;
            case 7: exit(0);
            default: printf("Enter a valid choice (1-7).\n");
        }
    }

    return 0;
}
