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
    singlyNode *curr = head;
    singlyNode *prev = nullptr;
    while (curr != nullptr)
    {
        prev = curr;
        curr = curr->next;
        delete prev;
    }
}

minigit::~minigit()
{
    //fs::remove_all(".minigit"); // removes a directory and its contents
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

int minigit::addFile(string Name)   //0 means not version issues cannot add 1 file exists already 2 means addded
{
    if(userVersion != recentCommit){
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

        if (search(Name, swag) != NULL)
        {
            //cout << "3" << endl;
            cout << "File already exists" << endl;
            return 0;
        }
        else
        {
            //cout << "4" << endl;
            singlyNode *node = new singlyNode;
            string temp = Name;
            temp.erase(temp.end()-4, temp.end());
            Name.erase(Name.begin(),Name.end()-4);
            node->fileName = temp;
            node->fileType = Name;
            node->fileVersion =  "00"; //file verion
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
        cout << "File does not exist please enter a valid name." << endl;
        return 1;
    }

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
    if(userVersion != recentCommit){
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
                return;
            }
            cout << "4" << endl;
            while (prev->next != temp)
            {
                cout << "5" << endl;
                prev = prev->next;
            }
            prev->next = prev->next->next;
            delete temp;
        }
    }
    return;
}

void copyFiles(string input, string output){

}

void minigit::commit(){
    if(userVersion != recentCommit){
        cout << "User version is not up to date with most recent commit. Checkout to most recent commit to add or remove files." << endl;
        return;
    }
    singlyNode* n = dEnd->head;

    while(n != nullptr){
        ifstream outputFile(n->fileName+n->fileVersion+n->fileType);
        if(outputFile.is_open() == false){
            cout << "./minigit/" +n->fileName+n->fileVersion+n->fileType << endl;
            fstream outPut("./minigit/" +n->fileName+n->fileVersion+n->fileType);
        }
        n= n->next;
        
    }


    return;
    //userVersion++;
}



void minigit::checkout(int desiredCommit){
    string input = "";

    while(input != "Y" && input != "N"){
        cout << "You will lose your local changes if you checkout do you wish to continue Y or N" << endl;
        cin >> input;
    }

    if(input == "N"){
        return;
    }
    else if(input == "Y"){
        int n = recentCommit;
        if(desiredCommit == n){
            cout <<" Already in desired commit" << endl;
            return;
        }
        else if(desiredCommit >= n || desiredCommit < 0){
            cout <<"Invaild input!!" << endl;
            return;
        }
        else{
            doublyNode* crawler;
            crawler = dEnd;
            while(crawler->commitNumber != desiredCommit){
                crawler = crawler->previous;
            }
            singlyNode* Scrawler;
            Scrawler = crawler->head;
            while(Scrawler->next != NULL){
                //copy new schtuff over to the directory

                //overwrite the old files 
                // delete the ne


                Scrawler = Scrawler->next; 
            }

        }
    }
    else{
        cout << "Invalid input" << endl;
    }
}