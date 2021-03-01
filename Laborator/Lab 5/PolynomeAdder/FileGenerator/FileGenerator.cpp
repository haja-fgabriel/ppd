#include <iostream>

#include "FileUtils.h"

using namespace std;

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        cerr << "Usage: " << argv[0] << " <output_file> <degree> <number_monomes>" << endl;
        return 1;
    }
    FileUtils::CreateNewFile(argv[1], atoi(argv[2]), atoi(argv[3]), 0.1, 1e8);
    return 0;
}
