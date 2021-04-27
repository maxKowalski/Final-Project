#include <iostream>
#include <fstream>
#include <vector>
#include "miniGit.hpp"
#include <filesystem>

namespace fs = std::filesystem;

using namespace std;

bool compare(string input, string output)
{
    ifstream out(output);
    ifstream in(input);
    in.seekg(0, ios::end);
    out.seekg(0,ios::end);
    int inpu = in.tellg();
    int outpu=  out.tellg();
    if(inpu != outpu) {
        return false;
    }

    while(true){
        if(out.get() != in.get()){
            out.close();
            in.close();
            return false;
        }
        if((out.eof() == true) && (in.eof() == true)){
            out.close();
            in.close();
            return true; 
        }else if((out.eof() == true) || (in.eof() == true)){
            out.close();
            in.close();
            return false;
        }
    }
}

int main()
{
    cout << compare("nashTown2.txt","nashTown.txt") << endl;
    return 0;
}
