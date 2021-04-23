#include <iostream>
#include <vector>
#include "miniGit.hpp"
#include <filesystem>

namespace fs = std::filesystem;

using namespace std;

int main(){
    fs::remove_all(".minigit"); // removes a directory and its contents
    fs::create_directory(".minigit");  // create a new directory
}