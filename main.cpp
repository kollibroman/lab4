#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>
#include <cmath>
#include "Arithmetic/operations_simd.h"
#include "Arithmetic/Operations_sisd.h"
#include "util/file_writer.h"
#include "Data/DataHandler.h"

double average(std::vector<double> const &v)
{
    if (v.empty())
    {
        return 0;
    }

    auto const count = static_cast<double>(v.size());
    return std::round(std::reduce(v.begin(), v.end()) / count * 1000) / 1000;
}

int main()
{
    std::vector<double> operation_times_add_vec;
    std::vector<double> operation_times_sub_vec;
    std::vector<double> operation_times_mul_vec;
    std::vector<double> operation_times_div_vec;

    std::vector<double> operation_times_add;
    std::vector<double> operation_times_sub;
    std::vector<double> operation_times_mul;
    std::vector<double> operation_times_div;

    DataHandler dataHandler[6];

    int elementCount[3] = {2048, 4096, 8192};

    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 10; i++)
        {
            operation_times_add_vec.push_back(gen_add_vectors(elementCount[j]));
            dataHandler[j].OperationTimes[0] = average(operation_times_add_vec);

            operation_times_sub_vec.push_back(gen_sub_vectors(elementCount[j]));
            dataHandler[j].OperationTimes[1] = average(operation_times_sub_vec);

            operation_times_mul_vec.push_back(gen_mul_vectors(elementCount[j]));
            dataHandler[j].OperationTimes[2] = average(operation_times_mul_vec);    

            operation_times_div_vec.push_back(gen_div_vectors(elementCount[j]));
            dataHandler[j].OperationTimes[3] = average(operation_times_div_vec);

            operation_times_add.push_back(gen_add(elementCount[j]));
            dataHandler[j+3].OperationTimes[0] = average(operation_times_add);

            operation_times_sub.push_back(gen_sub(elementCount[j]));
            dataHandler[j+3].OperationTimes[1] = average(operation_times_sub);

            operation_times_mul.push_back(gen_mul(elementCount[j]));
            dataHandler[j+3].OperationTimes[2] = average(operation_times_mul);

            operation_times_div.push_back(gen_div(elementCount[j]));
            dataHandler[j+3].OperationTimes[3] = average(operation_times_div);
        }
        
        dataHandler[j].NumCount = elementCount[j];
        dataHandler[j + 3].NumCount = elementCount[j];
    }
    
    write_vector_to_file("operation_times.txt", dataHandler, true);

    std::cout << "Operation times for 2048 elements:" << std::endl;

    std::cout << "Addition: " << std::endl;
    write_vector_to_console(operation_times_add);
    std::cout << std::endl;

    std::cout << "Subtraction: " << std::endl;
    write_vector_to_console(operation_times_sub);
    std::cout << std::endl;

    std::cout << "Multiplication: " << std::endl;
    write_vector_to_console(operation_times_mul);
    std::cout << std::endl;

    std::cout << "Division: " << std::endl;
    write_vector_to_console(operation_times_div);
    std::cout << std::endl;

    return 0;
}