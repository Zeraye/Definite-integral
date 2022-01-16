#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "winbgi2.h"

double func(double x)
{

    return 3 + sin(x);
}

double draw(double a, double b, double max, int n)
{
    double rndx;
    double rndy;
    int f = 0;
    double k;
    srand(time(NULL));
    if (b > 0)
    {
        for (int i = 0; i < n; i++)
        {
            rndx = double(rand() % int(b + 0.00001)) + a + fabs((double(rand() % 10000)) / 10000 - fabs(b - int(b + 0.00001)));
            if (rndx > b) rndx = rndx - a;
            rndy = double(rand() % int(max + 0.00001)) + fabs((double(rand() % 10000)) / 10000 - fabs(max - int(max + 0.00001)));
            //printf("x=%lf\ty=%lf\n", rndx, rndy);
            if (rndy > func(rndx)) {}
            else
            {
                f++;
            }

        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            rndx = double(rand() % int(fabs(a) + 0.00001)) + fabs(b) + fabs((double(rand() % 10000)) / 10000 - fabs(fabs(a) - int(fabs(a) + 0.00001)));
            if (rndx > fabs(a)) rndx = rndx - fabs(b);
            rndx = -rndx;
            rndy = double(rand() % int(max + 0.00001)) + fabs((double(rand() % 10000)) / 10000 - fabs(max - int(max + 0.00001)));
            if (rndy > func(rndx)) {}
            else
            {
                f++;
            }
        }
    }

    k = double(f) / double(n);
    return k;
}

double rectangle(double a, double b, double max, double k)
{
    double area;
    double integral;
    area = (b - a) * max;
    integral = area * k;
    printf("Area of rectangle: %lf\n", area);
    return integral;
}

void grap(double a, double b, double max, int z, double n)
{
    graphics(1400, 1000);
    double rndx, rndy;
    double x;
    for (int i = 0; i < 1001; i++)
    {
        x = fabs(a) + (b - a) / 1000 * i;
        circle(x * z + 100, -func(x) * z + 800, 1);
        line(0, 800, 1400, 800);
    }
    line(z * fabs(a) + 100, 800, z * fabs(a) + 100, 800 - max * z);
    line(z * fabs(a) + 100, 800 - max * z, z * (fabs(a) + (b - a)) + 100, 800 - max * z);
    line(z * (fabs(a) + (b - a)) + 100, 800, z * (fabs(a) + (b - a)) + 100, 800 - max * z);

    if (b > 0)
    {
        for (int i = 0; i < n; i++)
        {
            rndx = double(rand() % int(b + 0.00001)) + a + fabs((double(rand() % 10000)) / 10000 - fabs(b - int(b + 0.00001)));
            if (rndx > b) rndx = rndx - a;
            rndy = double(rand() % int(max + 0.00001)) + fabs((double(rand() % 10000)) / 10000 - fabs(max - int(max + 0.00001)));
            if (rndy > func(rndx)) {}
            else
            {
                circle(rndx * z + 100, -rndy * z + 800, 2);
            }

        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            rndx = double(rand() % int(fabs(a) + 0.00001)) + fabs(b) + fabs((double(rand() % 10000)) / 10000 - fabs(fabs(a) - int(fabs(a) + 0.00001)));
            if (rndx > fabs(a)) rndx = rndx - fabs(b);
            rndx = -rndx;
            rndy = double(rand() % int(max + 0.00001)) + fabs((double(rand() % 10000)) / 10000 - fabs(max - int(max + 0.00001)));
            if (rndy > func(rndx)) {}
            else
            {
                circle(rndx * z + 100, -rndy * z + 800, 2);
            }
        }
    }

    wait();
}

double montecarlo2(double a, double b, double n)
{
    double sumofareas = 0;
    for (int i = 0; i < n + 1; i++)
    {
        sumofareas = sumofareas + (b - a) / n * func(a - (b - a) / 2 + (b - a) / n * i);
    }
    return sumofareas;
}

int main()
{
    int n;
    double a, b, c;
    printf("Podaj dolna granice calkowania: ");
    scanf("%lf", &a);
    printf("Podaj gorna granice calkowania: ");
    scanf("%lf", &b);
    printf("Podaj stopien dokladnosci: ");
    scanf("%d", &n);
    if (a > b)
    {
        c = b;
        b = a;
        a = c;
    }
    int prec = 10000, i;
    double max = func(a);
    double k;
    for (i = 0; i < prec + 1; i++)
    {
        if (func(a + (b - a) * i / prec) > max) max = func(a + (b - a) * i / prec);
    }
    k = draw(a, b, max, n);
    printf("Max function value: %lf\n", max);
    printf("Ratio: %lf\n", k);
    printf("Definite integral value: %lf\n", rectangle(a, b, max, k));
    printf("Sum of many small rectangles: %lf\n", montecarlo2(a, b, n));
    grap(a, b, max, 100, n);

    return 0;
}