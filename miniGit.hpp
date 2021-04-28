#include <iostream>
#include <string>

using namespace std;

struct singlyNode
{
    string fileName;       // Name of local file
    string fileVersion; // Name of file in .minigit folder
    string fileType;
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
        int addFile(string fileName);
        void removeFile(string fileName);
        void commit();
        void checkout();
        singlyNode* search(string fileName, doublyNode* commit);
        void print();

    private:
        doublyNode* dHead;
        doublyNode* dEnd;
        int userVersion;
        int recentCommit;
};