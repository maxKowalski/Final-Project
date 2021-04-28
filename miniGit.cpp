#include "miniGit.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

minigit::minigit()
{
    fs::create_directory(".minigit"); // create a new directory

    dHead = new doublyNode;
    dHead->head = nullptr;
    userVersion = 0;
    recentCommit = 0;
    dEnd = dHead;
}

void deleteSLL(singlyNode *&head)
{
    singlyNode *prev = nullptr;
    while (head != nullptr)
    {
        prev = head;
        head = head->next;
        delete prev;
    }
}

minigit::~minigit()
{
    fs::remove_all(".minigit"); // removes a directory and its contents
    doublyNode *curr = dHead;
    doublyNode *prev = nullptr;
    if (curr->head == nullptr)
    {
        delete curr;
        return;
    }
    while (curr != nullptr)
    {
        deleteSLL(curr->head);
        prev = curr;
        curr = curr->next;
        delete prev;
    }
}

int minigit::addFile(string Name) //0 means not version issues cannot add 1 file exists already 2 means addded
{
    if (userVersion != recentCommit)
    {
        cout << "User version is not up to date with most recent commit. Checkout to most recent commit to add or remove files." << endl;
        return 0;
    }
    fstream myFile;
    doublyNode *swag = dEnd;
    if (dEnd == nullptr)
    {
        swag = dHead;
    }

    myFile.open(Name);
    //cout << "1" << endl;
    if (myFile.is_open())
    {
        //cout << "2" << endl;
        string temp = Name;
        temp.erase(temp.end() - 4, temp.end());
        if (search(temp, swag) != NULL)
        {
            //cout << "3" << endl;
            cout << "File already exists" << endl;
            return 0;
        }
        else
        {
            //cout << "4" << endl;
            singlyNode *node = new singlyNode;

            Name.erase(Name.begin(), Name.end() - 4);
            node->fileName = temp;
            node->fileType = Name;
            node->fileVersion = "00"; //file verion
            node->next = nullptr;
            if (swag->head == nullptr)
            {
                //cout << "5" << endl;
                swag->head = node;
            }
            else
            {
                //cout << "6" << endl;
                singlyNode *pres;
                pres = swag->head;
                while (pres->next != nullptr)
                {
                    pres = pres->next;
                }
                pres->next = node;
                node->next = nullptr;
            }
        }
    }
    else
    {
        cout << "File does not exist please try again." << endl;
        return 1;
    }
    cout << "Sucessfully added the file." << endl;
    return 2;
}

singlyNode *minigit::search(string fileName, doublyNode *commit)
{
    singlyNode *temp = commit->head;
    while (temp != nullptr)
    {
        if (temp->fileName == fileName)
        {
            return temp;
        }
        else
        {
            temp = temp->next;
        }
    }
    return nullptr;
}

void minigit::removeFile(string fileName)

{
    if (userVersion != recentCommit)
    {
        cout << "User version is not up to date with most recent commit. Checkout to most recent commit to add or remove files." << endl;
        return;
    }
    doublyNode *commit = dHead; //set commit to head of DLL
    for (int i = 0; i < recentCommit; i++)
    {
        commit = commit->next;
    }
    singlyNode *temp = commit->head;
    singlyNode *prev = commit->head;

    if (temp == nullptr)
    {
        return;
    }
    else
    {
        fileName.erase(fileName.end() - 4, fileName.end());
        temp = search(fileName, commit);
        if (temp == nullptr)
        {
            cout << "File does not exist." << endl;
            return;
        }
        else
        {

            if (temp == commit->head)
            {

                commit->head = commit->head->next;
                delete temp;
                cout << "Sucessfully removed the file." << endl;
                return;
            }
            //cout << "4" << endl;
            while (prev->next != temp)
            {
                //cout << "5" << endl;
                prev = prev->next;
            }
            prev->next = prev->next->next;
            delete temp;
            cout << "Sucessfully removed the file." << endl;
        }
    }
    return;
}

void copyFiles(string input, string output)
{
    //cout << input << " " << output << endl;
    ofstream out(output);
    ifstream in(input);
    string line;

    while (getline(in, line))
    {
        //cout << line << endl;
        if (in.eof() == true)
        {
            out << line;
        }
        else
        {
            out << line << endl;
        }
    }
}

bool compare(string input, string output)
{
    ifstream out(output);
    ifstream in(input);
    //compared the characters size(line)
    //cout << output << " " << input << endl;
    while (true)
    {
        char one = out.get();
        char two = in.get();
        //cout << int(one) << " " << int(two) << endl;
        if (one != two)
        {
            //cout << "hello" << endl;
            out.close();
            in.close();
            return false;
        }
        if ((out.eof() == true) && (in.eof() == true))
        {
            out.close();
            in.close();
            return true;
        }
        else if ((out.eof() == true) || (in.eof() == true))
        {
            //cout << "hello2" << endl;
            out.close();
            in.close();
            return false;
        }
    }
}

void minigit::commit()
{
    if (userVersion != recentCommit) //checks if the user is in the right commit for checkout
    {
        cout << "User version is not up to date with most recent commit. Checkout to most recent commit to add or remove files." << endl;
        return;
    }
    singlyNode *n = dEnd->head; //this is the head of the DL that need to be commited

    while (n != nullptr) //cycle between all the nodes in the singly list
    {
        string name = "./.minigit/" + n->fileName + (n->fileVersion) + n->fileType; //this is the file name of the repository files
        ifstream outputFile(name);                                                  //tries to read open the file name

        if (outputFile.is_open() == false) //if it doesnt open
        {
            ofstream outPut(name);                      //creates new file with file version
            copyFiles(n->fileName + n->fileType, name); //copies the old files to the new repository file
        }
        else //if the file does open
        {
            if (compare(name, n->fileName + n->fileType) == false) //compares the two files and if they are not the same
            {
                //not the same files
                //copy file from directory into .minigit
                //increase version

    

                int num = stoi(n->fileVersion) + 1; //increases the version number

                if (num < 10)
                { //if the num is less than 10 keep the 0 before the num
                    n->fileVersion = "0" + to_string(num);
                    string updated = "./.minigit/" + n->fileName + (n->fileVersion) + n->fileType;
                    ofstream outPut(updated);
                }
                else
                {
                    n->fileVersion = to_string(num);
                    string updated = "./.minigit/" + n->fileName + (n->fileVersion) + n->fileType;
                    ofstream outPut(updated);
                }
                string updated = "./.minigit/" + n->fileName + (n->fileVersion) + n->fileType;
                //cout << updated << endl;
                copyFiles(n->fileName + n->fileType, updated); //copies the file from the directory to the new repository file
            }
            else //same file
            {
                n = n->next;
                continue;
            }
        }
        n = n->next;
    }
    cout << "Sucessfully commited files." << endl;
    
    userVersion++;
    recentCommit++;

    doublyNode *prev = dEnd;
    doublyNode *newNode = new doublyNode;
    newNode->next = nullptr;
    dEnd = newNode;
    newNode->previous = prev;
    prev->next = newNode;
    newNode->commitNumber = prev->commitNumber + 1;
    singlyNode *sTemp = prev->head;
    singlyNode *prevSN = nullptr;
    
    //cout << prev->commitNumber << " " << newNode->commitNumber << endl;

    while (sTemp != nullptr)
    {

        singlyNode *newSN = new singlyNode;
        newSN->fileName = sTemp->fileName;
        newSN->fileType = sTemp->fileType;
        newSN->fileVersion = sTemp->fileVersion;
        if (prev->head == sTemp)
        {
            newNode->head = newSN;
            prevSN = newSN;
            sTemp = sTemp->next;
            continue;
        }
        prevSN->next = newSN;
        prevSN = newSN;
        sTemp = sTemp->next;
    }

    return;
    //userVersion++;
}

void minigit::checkout()
{
    string input = ""; // creating a string value with an input

    while (input != "Y" && input != "N") //run the question over and over until the user selects either yes or no
    {
        cout << "You will lose your local changes if you checkout do you wish to continue Y or N" << endl; //question prompt
        cin >> input;                                                                                      //user input
    }

    if (input == "N") //finish if the user doesn't want to lose changes
    {
        return;
    }
    else if (input == "Y") //run checkout
    {
        bool check = true;
        while (check)
        {
            string desiredCommit = "a";
            int n = userVersion;
            cout << "Enter the commit number you want to checkout too." << endl;
            //cout <<  << endl;
            //getline(cin, desiredCommit);
            cin >> desiredCommit;
            cout << desiredCommit << " " << recentCommit << endl;
            if (stoi(desiredCommit) == n)
            {
                cout << " Already in desired commit" << endl;
                return;
            }
            else if (stoi(desiredCommit) > recentCommit || stoi(desiredCommit) < 0)
            {
                cout << "Invaild input!!" << endl;
                continue;
            }
            else
            {
                cout << "1" << endl;
                singlyNode *deletor;
                deletor = dEnd->head;
                while (deletor != NULL)
                {
                    string name = deletor->fileName + deletor->fileType;
                    remove(name.c_str()); //removing files might need to make string
                    deletor = deletor->next;
                }
            
                doublyNode *crawler;
                crawler = dEnd;
                while (crawler->commitNumber != stoi(desiredCommit))
                {
                    crawler = crawler->previous;
                }
                singlyNode *Scrawler;
                Scrawler = crawler->head;
                
                while (Scrawler != NULL)
                {
                    string name = "./.minigit/" + Scrawler->fileName + (Scrawler->fileVersion) + Scrawler->fileType;
                    ifstream outputFile(name);
                
                    if (outputFile.is_open() == true)
                    {
                        copyFiles(name, Scrawler->fileName + Scrawler->fileType);
        
                    }
                    Scrawler = Scrawler->next;
                }
                
                check = false;
                userVersion = stoi(desiredCommit);
            }
        }
    }
    else
    {
        cout << "Invalid input" << endl;
    }
}

void minigit::print()
{
    doublyNode *temp = dHead;
    for (int i = 0; i < recentCommit; i++)
    {
        singlyNode *sTemp = temp->head;
        cout << "Commit number:" << temp->commitNumber << "-->";
        while (sTemp != nullptr)
        {
            cout << "FN:" << sTemp->fileName << " FV:" << sTemp->fileVersion << " -->";
            sTemp = sTemp->next;
        }
        cout << endl;
        temp = temp->next;
    }
}
