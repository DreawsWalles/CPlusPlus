#include <stdlib.h> 
#include <stdio.h> 
#include <math.h> 
#include <locale.h> 

#define PI 3.14159 

#pragma warning( disable : 4101)

double Yfunc(double x); //первая функция 
double Vfunc(double x); //вторая функция 
double SfuncN(double x, int N); //третья функция с количеством членов 
double SfuncE(double x, double E); //с заданной точностью 


void main()
{
    setlocale(LC_ALL, "RUS");

    int choice = 3, N = 0; //E-точность N-кол-во членов Choice - переменная для меню 
    double xmin, xmax, dx, E = 0;

    while (1)
    {
        // навигация по меню 
            printf("\nВыберите функцию:\n");
        printf("1.Y(x)= -0.5 * log(1 - 2 * x * cos(PI / 3) + x * x)\n");
        printf("2.V(x)= 0.17 * fi - log(x + 2.5) + 0.9 * (exp(x) - exp(-x))\n");
        printf("3.S(x)= pow(x, k) * cos(PI * k / 3) / k\n");
        do //будет спрашивать пока не получит правильный ответ 
        {
            scanf("%d", &choice);
            getchar();

        } while (choice < 1 || choice > 3);
        printf("\nВведите интервал (min:max) > ");
        scanf("%lf:%lf", &xmin, &xmax);
        getchar();
        printf("\nВведите шаг > ");
        scanf("%lf", &dx);
        getchar();
        switch (choice)
        {
        case 1:
            printf("___________\n");
            printf("|%13s|%13s|\n", "X", "Y(X)");
            for (double i = xmin; i <= xmax; i += dx)
                printf("|%13lf|%13lf|\n", i, Yfunc(i));

            break;
        case 2:
            if (xmin < -2.5) xmin = -2.5 + dx; //проверка выхода за область допустимых значений 
            if (xmax < -2.5) xmax = -2.5 + dx;
            printf("___________\n");
            printf("|%13s|%13s|\n", "X", "V(X)");
            for (double i = xmin; i <= xmax; i += dx)
                printf("|%13lf|%13lf|\n", i, Vfunc(i));
            break;
        case 3:
            if (xmin < -1 || xmin >= 1) xmin = -1; //проверка выхода за область допустимых значений 
            if (xmax < -1 || xmax >= 1) xmax = 1 - dx;

            printf("1.Функция с заданным кол-вом членов\n");
            printf("2.Функция с заданной точностью\n");
            printf("3.Отмена\n");
            do //будет спрашивать пока не получит правильный ответ 
            {
                scanf("%d", &choice);
                getchar();
            } while (choice < 1 || choice > 3);
            if (choice == 3) continue;
            switch (choice)
            {
            case 1:
                printf("Введите количество членов > ");
                scanf("%d", &N);
                getchar();
                printf("____________\n");
                printf("|%13s|%20s|\n", "X", "S(X)");
                for (double i = xmin; i <= xmax; i += dx)
                    printf("|%13.3lf|%20.6lf|\n", i, SfuncN(i, N));
                break;
            case 2:
                printf("Введите точность > ");
                scanf("%lf", &E);
                getchar();
                printf("____________\n");
                printf("|%13s|%20s|\n", "X", "S(X)");
                for (double i = xmin; i <= xmax; i += dx)
                    printf("|%13.3lf|%20.6lf|\n", i, SfuncE(i, E));
                break;
            default:;
            }
        }
    }
}

// первая функция 
double Yfunc(double x)
{
    return -0.5 * log(1 - 2 * x * cos(PI / 3) + x * x);
}

// вторая функция 
double Vfunc(double x)
{
    double fi;
    if (x < -1) fi = -x / 3; //если число логарифма меньше нуля,то ошибка 
    else fi = fabs(x);
    return 0.17 * fi - log(x + 2.5) + 0.9 * (exp(x) - exp(-x));
}

// третья функция с кол - вом членов 
double SfuncN(double x, int N)
{
    double sum = 0;
    for (int k = 1; k <= N; k++)
        sum += pow(x, k) * cos(PI * k / 3) / k;
    return sum;
}

// третья функция с заданной точностью 
double SfuncE(double x, double E)
{
    double k = 1;
    double sum = 0;
    for (int i = 1; fabs(k) > E; i++)
    {
        k = pow(x, i) * cos(PI * i / 3) / i;
        sum += k;
    }
    return sum;
}