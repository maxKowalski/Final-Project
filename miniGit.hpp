//hello
#include <iostream>
#include <string>

using namespace std;

struct singlyNode
{
    std::string fileName;       // Name of local file
    std::string fileVersion; // Name of file in .minigit folder
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
        void checkout(int desiredCommit);
        singlyNode* search(string fileName, doublyNode* commit);

    private:
        doublyNode* dHead;
        doublyNode* dEnd;
        int userVersion;
        int recentCommit;
};