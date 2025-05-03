#include "operations_simd.h"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

// ile wektorów: 2048/8 = 256  4096/8 = 512  8192/8 = 1024
//  https://net-informations.com/asm/adv/vector.htm
// https://docs.oracle.com/cd/E26502_01/html/E28388/eojde.html

double gen_add_vectors(int n)
{
    // data generation
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> distribution(0, 1000);
    auto startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n / 8; i++)
    {
        float vec1[4];
        float vec2[4];

        for (int j = 0; j < 4; j++)
        {
            vec1[j] = distribution(gen);
            vec2[j] = distribution(gen);
        }

        __asm__ volatile(
            "movaps (%0), %%xmm0\n"
            "movaps (%1), %%xmm1\n"
            "addps %%xmm1, %%xmm0\n" 
            :                       
            : "r"(vec1), "r" (vec2)
            : "xmm0", "xmm1" 
        );
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(endTime - startTime).count();

    return duration;
}

double gen_sub_vectors(int n)
{
    // data generation
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> distribution(0, 1000);
    auto startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n / 8; i++)
    {
        float vec1[4];
        float vec2[4];

        for (int j = 0; j < 4; j++)
        {
            vec1[j] = distribution(gen);
            vec2[j] = distribution(gen);
        }

        __asm__ volatile(
            "movaps (%0), %%xmm0\n"
            "movaps (%1), %%xmm1\n"
            "subps %%xmm1, %%xmm0\n"
            :
            : "r"(vec1), "r"(vec2)
            : "xmm0", "xmm1");
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(endTime - startTime).count();

    return duration;
}

double gen_mul_vectors(int n)
{
    // data generation
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> distribution(0, 1000);
    auto startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n / 8; i++)
    {
        float vec1[4];
        float vec2[4];

        for (int j = 0; j < 4; j++)
        {
            vec1[j] = distribution(gen);
            vec2[j] = distribution(gen);
        }

        __asm__ volatile(
            "movaps (%0), %%xmm0\n"
            "movaps (%1), %%xmm1\n"
            "mulps %%xmm1, %%xmm0\n"
            :
            : "r"(vec1), "r"(vec2)
            : "xmm0", "xmm1");
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(endTime - startTime).count();

    return duration;
}

double gen_div_vectors(int n)
{
    // data generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(0, 1000);

    auto startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n / 8; i++)
    {
        float vec1[4];
        float vec2[4];

        for (int j = 0; j < 4; j++)
        {
            vec1[j] = distribution(gen);
            vec2[j] = distribution(gen);
        }

        __asm__ volatile(
            "movaps (%0), %%xmm0\n"
            "movaps (%1), %%xmm1\n"
            "divps %%xmm1, %%xmm0\n"
            :
            : "r"(vec1), "r"(vec2)
            : "xmm0", "xmm1");
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(endTime - startTime).count();

    return duration;
}