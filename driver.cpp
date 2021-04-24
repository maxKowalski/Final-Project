#include <iostream>
#include <fstream>
#include <vector>
#include "miniGit.hpp"
#include <filesystem>

namespace fs = std::filesystem;

using namespace std;

int main(){
    fstream File;
    minigit system;
    system.addFile("test.txt");
    system.addFile("snack.txt");
    system.addFile("nashTown.txt");
    system.removeFile("test.txt");
    

}