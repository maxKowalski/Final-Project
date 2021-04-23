#include "miniGit.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


singlyNode* search(string fileName, doublyNode* commit)
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
    doublyNode* commit =dHead; //find head of DLL
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