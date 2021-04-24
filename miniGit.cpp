#include "miniGit.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

void minigit::addFile(string fileName)
{
    fstream myFile;
    myFile.open(fileName);
    if (myFile.is_open())
    {
        if (search(fileName, dEnd) != NULL)
        {
            cout << "File already exists" << endl;
        }
        else
        {

            singlyNode *node = new singlyNode;
            node->fileName = fileName;
            node->fileVersion = fileName + "00";    //file verion
            node->next = NULL;
            doublyNode *dnode = new doublyNode; //create test dll node
            if (dnode->head = NULL)
            {
                dnode->head = node;
                node->next = NULL;
            }
            else
            {
                singlyNode *pres;
                pres = dnode->head;
                while (pres->next != NULL)
                {
                    pres = pres->next;
                }
                pres->next = node;
                node->next = NULL;
            }
        }
    }
    return;
}

minigit::minigit(){
    fs::create_directory(".minigit");  // create a new directory
    dEnd = nullptr;
    dHead = new doublyNode;
    userVersion = 0;
    recentCommit = 0;
}

void deleteSLL(singlyNode*& head){
    singlyNode* curr = head;
    singlyNode* prev = nullptr;
    while(curr != nullptr){
        prev = curr;
        curr = curr->next;
        delete prev;
    }
}

minigit::~minigit(){
    fs::remove_all(".minigit"); // removes a directory and its contents
    doublyNode* curr = dHead;
    doublyNode* prev = nullptr;
    if(curr->head = nullptr){
        delete curr;
        return;
    }
    while(curr != nullptr){
        deleteSLL(curr->head);
        prev = curr;
        curr = curr->next;
        delete prev;
    }
    
}

singlyNode* minigit::search(string fileName, doublyNode* commit)
{
    singlyNode* temp = commit->head;
    while(temp != nullptr){
        if(temp->fileName == fileName){
            return temp;
        }
        else{
            temp = temp -> next;
        }
    }
    return nullptr;
}

void minigit::removeFile(string fileName){
    doublyNode* commit =dHead; //set commit to head of DLL
    for(int i = 0; i < recentCommit; i++){
        commit = commit->next;
    }
    

    singlyNode* temp = commit->head;
    singlyNode* prev = commit->head;
    
    if(temp == nullptr){
        return;
    }
    else{
        temp = search(fileName,commit);
        if(temp == commit->head){
            commit->head = commit->head -> next;
            delete temp;
            return;
        }
        if(temp == nullptr){
            cout << "File does not exist." << endl;
            return;
        }
        while(prev -> next != temp){
            prev = prev -> next;
        }
        singlyNode* link = temp -> next;
        prev -> next = link;
        delete temp;
    }
    return;
}