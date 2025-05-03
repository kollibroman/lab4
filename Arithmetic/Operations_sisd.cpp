#include <iostream>
#include "Operations_sisd.h"
#include <random>
#include <chrono>

double gen_add(int n)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> distribution(0, 1000);
    auto startTime = std::chrono::high_resolution_clock::now();

    float vec1[n];
    float vec2[n];

    for (int j = 0; j < n; j++)
    {
        vec1[j] = distribution(gen);
        vec2[j] = distribution(gen);
    }

    for(int j = 0; j < n; j++)
    {
        vec1[j] += vec2[j];
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(endTime - startTime).count();

    return duration;
}

double gen_sub(int n)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> distribution(0, 1000);
    auto startTime = std::chrono::high_resolution_clock::now();

    float vec1[n];
    float vec2[n];

    for (int j = 0; j < n; j++)
    {
        vec1[j] = distribution(gen);
        vec2[j] = distribution(gen);
    }

    for (int j = 0; j < n; j++)
    {
        vec1[j] -= vec2[j];
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(endTime - startTime).count();

    return duration;
}

double gen_mul(int n)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> distribution(0, 1000);
    auto startTime = std::chrono::high_resolution_clock::now();

    float vec1[n];
    float vec2[n];

    for (int j = 0; j < n; j++)
    {
        vec1[j] = distribution(gen);
        vec2[j] = distribution(gen);
    }

    for (int j = 0; j < n; j++)
    {
        vec1[j] *= vec2[j];
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(endTime - startTime).count();

    return duration;
}

double gen_div(int n)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> distribution(0, 1000);
    auto startTime = std::chrono::high_resolution_clock::now();

    float vec1[n];
    float vec2[n];

    for (int j = 0; j < n; j++)
    {
        vec1[j] = distribution(gen);
        vec2[j] = distribution(gen);
    }

    for (int j = 0; j < n; j++)
    {
        vec1[j] /= vec2[j];
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(endTime - startTime).count();

    return duration;
}