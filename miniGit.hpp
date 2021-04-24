//hello
#include<iostream>
#include <string>

using namespace std;

struct singlyNode
{
    std::string fileName;       // Name of local file
    std::string fileVersion; // Name of file in .minigit folder
    singlyNode* next;
};

struct doublyNode
{
    int commitNumber;
    singlyNode *head;
    doublyNode *previous;
    doublyNode *next;
}; 



class minigit
{
    public:
        minigit();
        ~minigit();
        void addFile();
        void removeFile(string fileName);
        void commit();
        void checkout();

    private:
        doublyNode* dHead;
        doublyNode* dEnd;
        int userVersion;
        int recentCommit;
};