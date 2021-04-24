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
    File.open(".minigit/text.txt");
    if(File.is_open() == true){
        cout << "hello" << endl;
    }
    system.~minigit();

}