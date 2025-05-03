#ifndef FILE_WRITER_H
#define FILE_WRITER_H

#include <iostream>
#include <vector>
#include "../Data/DataHandler.h"

void write_vector_to_file(const std::string filename, DataHandler input[3], bool isSimd);
void write_vector_to_console(const std::vector<double> vec);

#endif