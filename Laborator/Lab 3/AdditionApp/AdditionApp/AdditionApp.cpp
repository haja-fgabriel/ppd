#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "FileUtils.h"
#include "BigNumbers.h"
#include "Logging.h"

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> <input2_file> <output_file> [--log-to-socket]\n";
        return 1;
    }

    clock_t begin, end;
    int n;
    std::vector<int> number1;
    std::vector<int> number2;
    std::vector<int> result;

    begin = clock();
    FileUtils::ReadFile(argv[1], number1);
    FileUtils::ReadFile(argv[2], number2);

    BigNumbers::Add(number1, number2, result, 0);

    end = clock();
    double tim = 1.0 * (end - begin) / CLOCKS_PER_SEC;

    std::cout << "[DEBUG] Time: " << tim << std::endl;
    if (argc >= 5 && strcmp(argv[4], "--log-to-socket") == 0)
        SendLog(tim);

    FileUtils::Write(argv[3], result);

    return 0;
}
