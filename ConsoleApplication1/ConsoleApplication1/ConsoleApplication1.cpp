// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "func.h"
#include <vector>

int main()
{
    double RAD_DEG = 180 / 3.14;
    double DEG_RAD = 3.14 / 180;


    std::vector<double> p1 = { 67.85602632628772 * DEG_RAD, -139.78658419419955 * DEG_RAD };
    std::vector<double> p2 = { 19.26225699268021 * DEG_RAD, 4.178247318013565 * DEG_RAD };
    std::vector<double> p3 = { 71.94934558251 * DEG_RAD, -17.442844594077023 * DEG_RAD };
    std::vector<double> p4 = { -13.290356075967138 * DEG_RAD, -99.88424383611364 * DEG_RAD };

    std::vector<double> v = intersection_ortodrom(p1, p2, p3, p4);

    if (v.size() == 1)
    {
        std::cout << "Net peresecheniya\n";
    }
    else
    {
        std::cout << v[0] * RAD_DEG;
        std::cout << "\n";
        std::cout << v[1] * RAD_DEG;
        std::cout << "\n";
        std::cout << "********************************\n";
    }




    p1 = { 55.760436596101535 * DEG_RAD, 37.596834268267 * DEG_RAD };
    p2 = { 57.4941433302542 * DEG_RAD, 31.737946408548172 * DEG_RAD };
    p3 = { 55.760436596101535 * DEG_RAD, 37.596834268267 * DEG_RAD };
    p4 = { 56.97220892371373 * DEG_RAD, 39.992237977284795 * DEG_RAD };

    v = intersection_ortodrom(p1, p2, p3, p4);

    if (v.size() == 1) 
    {
        std::cout << "Net peresecheniya\n";
    }
    else 
    {
        std::cout << v[0] * RAD_DEG;
        std::cout << "\n";
        std::cout << v[1] * RAD_DEG;
        std::cout << "\n";
        std::cout << "********************************\n";
    }


    p1 = { -85.0 * DEG_RAD, 0.0 * DEG_RAD };
    p2 = { -85.0 * DEG_RAD, 180.0 * DEG_RAD };
    p3 = { -85.0 * DEG_RAD, 30.0 * DEG_RAD };
    p4 = { -85.0 * DEG_RAD, -150 * DEG_RAD };

    v = intersection_ortodrom(p1, p2, p3, p4);

    if (v.size() == 1)
    {
        std::cout << "Net peresecheniya\n";
    }
    else
    {
        std::cout << v[0] * RAD_DEG;
        std::cout << "\n";
        std::cout << v[1] * RAD_DEG;
        std::cout << "\n";
        std::cout << "********************************\n";
    }


    p1 = { 39.25752072616424 * DEG_RAD, -111.74149012317523 * DEG_RAD };
    p2 = { 36.482873364916806 * DEG_RAD, 55.07490194653163 * DEG_RAD };
    p3 = { 39.25752072616424 * DEG_RAD, -102.95242837029288 * DEG_RAD };
    p4 = { 36.341410313321056 * DEG_RAD, 47.51630883905283 * DEG_RAD };

    v = intersection_ortodrom(p1, p2, p3, p4);

    if (v.size() == 1)
    {
        std::cout << "Net peresecheniya\n";
    }
    else
    {
        std::cout << v[0] * RAD_DEG;
        std::cout << "\n";
        std::cout << v[1] * RAD_DEG;
        std::cout << "\n";
        std::cout << "********************************\n";
    }
    
}
