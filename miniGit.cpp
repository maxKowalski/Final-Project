#include "miniGit.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream> //libraries
#include <filesystem>

using namespace std; //namespace
namespace fs = filesystem; //creates an object from the filesystem in document

minigit::minigit() //object
{
    fs::create_directory(".minigit"); // create a new directory
    //constructor initializing variables
    dHead = new doublyNode;
    dHead->head = nullptr; //create new node
    userVersion = 0;
    recentCommit = 0;
    dEnd = dHead;
}

void deleteSLL(singlyNode *&head)
{
    singlyNode *prev = nullptr;
    while (head != nullptr) //deletes a singlylist 
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
    if (curr->head == nullptr) //deconstructor
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
    if (userVersion != recentCommit) //see if user version is = to the most recent commit
    {
        cout << "User version is not up to date with most recent commit. Checkout to most recent commit to add or remove files." << endl;
        return 0;
    }
    fstream myFile; //file stream
    doublyNode *swag = dEnd; //adding to the last doubly node
    if (dEnd == nullptr)
    {
        swag = dHead;
    }

    myFile.open(Name); //open the file
    //cout << "1" << endl;
    if (myFile.is_open())
    {
        //cout << "2" << endl;
        string temp = Name;
        temp.erase(temp.end() - 4, temp.end()); //erasing the .txt/extension part of the file
        if (search(temp, swag) != NULL) // checks to see if the file already exists 
        {
            //cout << "3" << endl;
            cout << "File already exists" << endl;
            return 0;
        }
        else //if the file doesnt exist continue
        {
            //cout << "4" << endl;
            singlyNode *node = new singlyNode; //create new singly node

            Name.erase(Name.begin(), Name.end() - 4); //erase the file name only get extension
            node->fileName = temp;
            node->fileType = Name;
            node->fileVersion = "00"; //file version
            node->next = nullptr;
            if (swag->head == nullptr) //check to see if the head is empty
            {
                //cout << "5" << endl;
                swag->head = node;
            }
            else
            {
                //cout << "6" << endl;
                singlyNode *pres;
                pres = swag->head;
                while (pres->next != nullptr) //traverse the linked list to find the last node to add a file
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
        cout << "File does not exist please try again." << endl; //file doesn't exist in the directory
        return 1;
    }
    cout << "Sucessfully added the file." << endl; //added file
    return 2;
}

singlyNode *minigit::search(string fileName, doublyNode *commit) //searches for the node with the filename
{
    singlyNode *temp = commit->head;
    while (temp != nullptr)
    {
        if (temp->fileName == fileName) //traversing the commit doubly node to find the singly node with the desired name
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

void minigit::removeFile(string fileName) //remove a file from the singly linked list

{
    if (userVersion != recentCommit) //making sure that the repository is up to date
    {
        cout << "User version is not up to date with most recent commit. Checkout to most recent commit to add or remove files." << endl;
        return;
    }
    doublyNode *commit = dHead; //set commit to head of DLL
    for (int i = 0; i < recentCommit; i++) //traversing the doubly linked list
    {
        commit = commit->next;
    }
    singlyNode *temp = commit->head; 
    singlyNode *prev = commit->head;

    if (temp == nullptr) //checks to see if the head is empty
    {
        return;
    }
    else
    {
        fileName.erase(fileName.end() - 4, fileName.end()); //ignoring the txt part
        temp = search(fileName, commit); //checking the file
        if (temp == nullptr)
        {
            cout << "File does not exist." << endl; //checks to see if the file exists 
            return;
        }
        else
        {

            if (temp == commit->head) //deleting the node at the head
            {

                commit->head = commit->head->next;
                delete temp;
                cout << "Sucessfully removed the file." << endl;
                return;
            }
            //cout << "4" << endl;
            while (prev->next != temp) //traversing to find the node to delete 
            {
                //cout << "5" << endl;
                prev = prev->next;
            }
            prev->next = prev->next->next;
            delete temp; //delete found node 
            cout << "Sucessfully removed the file." << endl;
        }
    }
    return;
}

void copyFiles(string input, string output)
{
    //cout << input << " " << output << endl;
    ofstream out(output); //creates a file with the output name
    ifstream in(input); //reads a file with the input name
    string line; 

    while (getline(in, line)) //reads everyline in the in file
    {
        //cout << line << endl;
        if (in.eof() == true) //if the end of file has been reached 
        {
            out << line; //doesn't add the extra endl
        }
        else
        {
            out << line << endl; //line for line 
        }
    }
}

bool compare(string input, string output)
{
    ifstream out(output); //creates a file with the output name
    ifstream in(input); //creates a file with the input name
    //compared the characters size(line)
    //cout << output << " " << input << endl;
    while (true)
    {
        char one = out.get(); //returns the character of out
        char two = in.get();// returns the character of in 
        //cout << int(one) << " " << int(two) << endl;
        if (one != two) //if the characters aren't equal to eachother return false
        {
            //cout << "hello" << endl;
            out.close();
            in.close();
            return false;
        }
        if ((out.eof() == true) && (in.eof() == true)) //if both files end at the same time return true
        {
            out.close();
            in.close();
            return true;
        }
        else if ((out.eof() == true) || (in.eof() == true)) //if one of the files ends first and the othe doesnt return false
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

    userVersion++;      //updates commit versions
    recentCommit++;

    doublyNode *prev = dEnd;                //pointer to the end 
    doublyNode *newNode = new doublyNode;   //creates new double node
    newNode->next = nullptr;        //initalize the next and prev of the newNode, commit number of new node, and prev node
    dEnd = newNode;
    newNode->previous = prev;
    prev->next = newNode;
    newNode->commitNumber = prev->commitNumber + 1;    
    singlyNode *sTemp = prev->head;     //creates pointer to head of prev
    singlyNode *prevSN = nullptr;       //creates empty pointer

    //cout << prev->commitNumber << " " << newNode->commitNumber << endl;

    while (sTemp != nullptr)        //goes through the signlyList of the prev node
    {

        singlyNode *newSN = new singlyNode;     //creates new signly node and give it the data needed   
        newSN->fileName = sTemp->fileName;
        newSN->fileType = sTemp->fileType;
        newSN->fileVersion = sTemp->fileVersion;
        if (prev->head == sTemp)                //if we are at the head of the prev node 
        {
            newNode->head = newSN;          //set the new singly node as the head of the new double 
            prevSN = newSN;                 //set empty pointer as new singly node
            sTemp = sTemp->next;            //move the prev node along the signly list
            continue;
        }
        prevSN->next = newSN;               //set the prev new signly's next as the current new node
        prevSN = newSN;                     //moves the prev pointer
        sTemp = sTemp->next;                //move the prev node along the signly list
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
            int desiredCommit = 0;
            int n = userVersion;
            cout << "Enter the commit number you want to checkout too." << endl; //the desired commit
            //cout <<  << endl;
            //getline(cin, desiredCommit);
            cin >> desiredCommit;
            while (cin.fail())
            {
                cout << "Error not a number try again." << endl; //make sure the user enters a number
                cin.clear();
                cin.ignore(256, '\n');
                cin >> desiredCommit;
            }
            //cout << desiredCommit << " " << recentCommit << endl;

            if (desiredCommit == n)
            {
                cout << " Already in desired commit" << endl; //if already in the desired commit
                return;
            }
            else if (desiredCommit > recentCommit || desiredCommit < 0) //make sure the input falls within the bounds of a desired commit
            {
                cout << "Invaild input!!" << endl;
                continue;
            }
            else
            {
                cout << "1" << endl;
                singlyNode *deletor; //function to remove the whole list of files within the directory
                deletor = dEnd->head; //deletor starts at the head
                while (deletor != NULL)
                {
                    string name = deletor->fileName + deletor->fileType; //usage of the remove function to remove the files 
                    remove(name.c_str()); //removing files might need to make string
                    deletor = deletor->next;
                }

                doublyNode *crawler; //crawler to go along the doubly linked list to find the desired commit number 
                crawler = dEnd;
                while (crawler->commitNumber != desiredCommit)
                {
                    crawler = crawler->previous;
                }
                singlyNode *Scrawler; //singly linked list crawler to go along the singly linked list of the desired commit
                Scrawler = crawler->head;

                while (Scrawler != NULL)
                {
                    string name = "./.minigit/" + Scrawler->fileName + (Scrawler->fileVersion) + Scrawler->fileType; 
                    ifstream outputFile(name); //gather the file names stored

                    if (outputFile.is_open() == true) //opens the files and copies it
                    {
                        copyFiles(name, Scrawler->fileName + Scrawler->fileType);
                    }
                    Scrawler = Scrawler->next; //traversal
                }

                check = false;
                userVersion = desiredCommit;
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
    doublyNode *temp = dHead;       //sets temp to doubly 
    for (int i = 0; i < recentCommit; i++)      //goes through the doubly node
    {
        singlyNode *sTemp = temp->head;
        cout << "Commit number:" << temp->commitNumber << "-->";        //print statement
        while (sTemp != nullptr)        //goes through the signly list
        {
            cout << "FN:" << sTemp->fileName << " FV:" << sTemp->fileVersion << " -->";         //print statement 
            sTemp = sTemp->next;
        }
        cout << endl;           
        temp = temp->next;     
    }
}
