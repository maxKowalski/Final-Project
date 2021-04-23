//hello
#include<vector>
#include<iostream>
using namespace std;


struct doublyNode
{
    int commitNumber;
    singlyNode *head;
    doublyNode *previous;
    doublyNode *next;
}; 
struct singlyNode
{
    std::string fileName;       // Name of local file
    std::string fileVersion; // Name of file in .minigit folder
    singlyNode *next;
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
        doublyNode dHead;
        singlyNode sHead;
        int userVersion;
        int recentCommit;
};