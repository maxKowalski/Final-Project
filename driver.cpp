#include <iostream>
#include <fstream>
#include <vector>
#include "miniGit.hpp"

using namespace std;

int main()
{
    string answer;
    bool check = false;

    cout << "Welcome, would you like to initalize a repository. (Y/N)" << endl;
    getline(cin, answer);
    while (!check)
    {

        if (answer == "N")
        {
            cout << "Goodbye!" << endl;
            return 0;
        }
        else if (answer == "Y" || answer == "y")
        {
            check = true;
        }else{
            cout << "Not a valid response try again." << endl;
            getline(cin,answer);
        }
    }

    bool quit = false;
    minigit system;
    while (!quit)
    {
        int option;
        string inputLine;

        cout << "======Main Menu======" << endl;
        cout << "1. Add file" << endl;
        cout << "2. Remove file" << endl;
        cout << "3. Commit" << endl;
        cout << "4. Checkout" << endl;
        cout << "5. Quit" << endl;

        getline(cin, inputLine);

        if (inputLine.length() != 1 || inputLine[0] < '0' || inputLine[1] > '5')
        {
            cerr << "Invalid option: " << inputLine << endl;
            continue;
        }

        option = stoi(inputLine);

        switch (option)
        {

        case 1: //add
        {
            std::string filename;
            int check = 1; //0 means not version issues cannot add 1 file exists already 2 means addded
            while (check == 1)
            {
                cout << "Enter a valid file name:" << endl;
                getline(cin, filename);
                //cout << filename;
                check = system.addFile(filename);
            }
            break;
        }
        case 2: //remove
        {
            std::string filename;

            cout << "Enter a valid file name:" << endl;
            getline(cin, filename);
            system.removeFile(filename);

            break;
        }
        case 3: //commit
        {
            system.commit();
            break;
        }
        case 4: //checkout
        {
            system.checkout();
            break;
        }
        case 5:
        {
            quit = true;
        }
        }
    }

    cout << "Goodbye!" << endl;

    return 0;
}
