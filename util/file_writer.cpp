#include "file_writer.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <string>
#include "Data/DataHandler.h"

void write_vector_to_file(const std::string filename, DataHandler input[3], bool isSimd)
{
    std::string fullPath = "./" + filename;
    std::ofstream file(fullPath);

    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << fullPath << std::endl;
        return;
    }

    for (int i = 0; i < 6; i++)
    {
        if(i > 2)
        {
            isSimd = false;
        }

        file << "Typ Obliczen: " << (isSimd ? "SIMD\n" : "SISD\n");
        file << "Liczba liczb: " << input[i].NumCount << "\n";
        file << "Sredni czas [x]ms:\n";

        file << "+ " << input[i].OperationTimes[0] << "\n";
        file << "- " << input[i].OperationTimes[1] << "\n";
        file << "* " << input[i].OperationTimes[2] << "\n";
        file << "/ " << input[i].OperationTimes[3] << "\n";
    }

        file.close();
    std::cout << "Saved: " << fullPath << std::endl;
}

void write_vector_to_console(const std::vector<double> vec)
{
    int i = 0;

    for (const auto &element : vec)
    {
        std::cout << element << " ";
        i++;

        if(i == 10)
        {
            std::cout << std::endl;
            i = 0;
        }
    }
}