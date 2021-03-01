#include <iostream>
#include "FileUtils.h"

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        std::cerr << "Usage: " << argv[0] << " <output_file> <num_lines> <num_columns> <min> <max>" << std::endl;
        return 1;
    }
    std::cout << "[DEBUG] size N: " << argv[2] << std::endl;
    std::cout << "[DEBUG] size M: " << argv[3] << std::endl;

    FileUtils::CreateNewFile(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
}