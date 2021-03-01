#include <iostream>
#include <exception>
#include <cassert>
#include <filesystem>

#include "FileUtils.h"
#include "Logging.h"

void TestGenerate()
{

    FileUtils::CreateNewFile("witchdoctor.txt", 1000, -1000, 1000000);
    FileUtils::CreateNewFile("witchdoctor2.txt", 1000, -1000,  999999);
    FileUtils::CreateNewFile("witchdoctor3.txt", 999, -1000, 1000000);
    
    // C++17 is a sweeet language, also try C++20
    std::filesystem::copy_file("witchdoctor.txt", "drakeramoray.txt");
    assert(FileUtils::Compare<int>("witchdoctor.txt", "drakeramoray.txt"));
    assert(!FileUtils::Compare<int>("witchdoctor.txt", "witchdoctor2.txt"));
    assert(!FileUtils::Compare<int>("witchdoctor.txt", "witchdoctor3.txt"));
    std::filesystem::remove("witchdoctor.txt");
    std::filesystem::remove("witchdoctor2.txt");
    std::filesystem::remove("witchdoctor3.txt");
    std::filesystem::remove("drakeramoray.txt");
}

void Test()
{

}

int main()
{
    TestGenerate();
    try
    {
        SendLog(0.743);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    // TODO measure execution time
    return 0;
}