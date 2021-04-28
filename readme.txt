Project description

We wrote a program that represents a mini version control system that tracks changes
made to the files and stores past versions of the files in a repository. The programs 
starts with asking the user to initiate a repository which creates a minigit directory
system represented by a doubly linked list representing each commit where files can be 
added or deleted. The first option in the menu is add a file to the current commit where
a file is added to the current repository waiting to be committed based on the users input. 
A file must be in the  directory in order for the user to add the file into the repository. 
After a file is added, the file version and file type is tracked as well. The user 
is unable to add a file more than once in the same commit version. The second option in 
the menu is to remove a file from the current repository. This function removes a file in the 
singly linked list out of the repository based on the users input. The file must 
exist in the repository in order for the file to be removed. The third option is to 
commit the changes made to the local files onto the repository. This option pushes the 
changes made to the files onto the repository and saves that version on the repository. 
New file versions are updated and files added or removed are saved. The fourth option in 
the menu is checkout. This fuction allows the user to move between commit versions and 
moves the files from the version into the directory so they can view the past versions. 
The fifth option is simply a print where all the past versions and all the files they 
contain and their version. The last option is quit where the user can quit the program.