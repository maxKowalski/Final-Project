#include <iostream>
#include <fstream>
#include <vector> // declaration of libraries
#include "miniGit.hpp"

using namespace std;

int main() //main
{
    string answer; //input argument from the user
    bool check = false; //keeps the user in the loop

    cout << "Welcome, would you like to initalize a repository. (Y/N)" << endl; //would the user like to initialize a repo
    getline(cin, answer); //get the user input
    while (!check) //check
    {

        if (answer == "N")
        {
            cout << "Goodbye!" << endl; //end program if no
            return 0;
        }
        else if (answer == "Y" || answer == "y") // contiue to the menu
        {
            check = true;
        }else{
            cout << "Not a valid response try again." << endl; //invaild option
            cin >> answer;
        }
    }

    bool quit = false; //bool to make the loop continue
    minigit system; //the object that is created by the program
    while (!quit)
    {
        int option;
        string inputLine; // user input 
        cout << "======Main Menu======" << endl; //main menu
        cout << "1. Add file" << endl;
        cout << "2. Remove file" << endl;
        cout << "3. Commit" << endl;
        cout << "4. Checkout" << endl;
        cout << "5. Print"  << endl;
        cout << "6. Quit" << endl;
        cin  >> inputLine;
        if (inputLine.length() != 1 || inputLine[0] < '0' || inputLine[1] > '5') //incorrect argument fro the user in the menu
        {
            cerr << "Invalid option: " << inputLine << endl;
            continue;
        }

        option = stoi(inputLine);

        switch (option) //switch case menu
        {

        case 1: //add
        {
            std::string filename;
            int check = 1; //0 means not version issues cannot add 1 file exists already 2 means addded
            while (check == 1)
            {
                cout << "Enter a valid file name:" << endl;
                cin >> filename;
                //cout << filename;
                check = system.addFile(filename);
            }
            break;
        }
        case 2: //remove
        {
            std::string filename;

            cout << "Enter a valid file name:" << endl;
            cin >> filename;
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
            system.print();
            break;
        }
        case 6:
        {
            quit = true;
        }
        }
    }

    cout << "Goodbye!" << endl;

    return 0;
}


