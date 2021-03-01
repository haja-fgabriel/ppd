#include <iostream>
#include "FileUtils.h"

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <output_file> <num_size>" << std::endl;
        return 1;
    }
    std::cout << "[DEBUG] size N: " << argv[2] << std::endl;

    FileUtils::CreateNewFile(argv[1], atoi(argv[2]), 0, 9);
}