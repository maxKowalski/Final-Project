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
    dEnd = nullptr;
    dHead = new doublyNode;
    dHead->head = nullptr;
    userVersion = 0;
    recentCommit = 0;
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

bool minigit::addFile(string fileName)
{
    fstream myFile;
    doublyNode *swag = dEnd;
    if (dEnd == nullptr)
    {
        swag = dHead;
    }
    myFile.open(fileName);
    //cout << "1" << endl;
    if (myFile.is_open())
    {
        //cout << "2" << endl;

        if (search(fileName, swag) != NULL)
        {
            //cout << "3" << endl;
            cout << "File already exists" << endl;
            return false;
        }
        else
        {
            //cout << "4" << endl;
            singlyNode *node = new singlyNode;
            node->fileName = fileName;
            node->fileVersion = fileName + "00"; //file verion
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
        return false;
    }

    return true;
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