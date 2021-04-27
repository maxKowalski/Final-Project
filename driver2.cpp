#include <iostream>
#include <fstream>
#include <vector>
#include "miniGit.hpp"
#include <filesystem>

namespace fs = std::filesystem;

using namespace std;


int main()
{
    minigit system;
    system.addFile("test.txt");
    system.addFile("snack.txt");
    system.addFile("nashTown.txt");
    system.addFile("smash.txt");
    //system.removeFile("test.txt");
    system.commit();
    //system.checkout(1)
    return 0;
}
