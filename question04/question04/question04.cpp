//Question 4 - Filesystem & args  

// Task: Implement the code as described in the main body, make sure to handle cases when the requested file is not found or the "files" directory doesn't exists and you have to create it
// Prefer modern solutions over classic C style solutions and keep in mind that this code should be able to run in other windows, linux and other platforms (hint: '/' and '\' in file paths)


#include <iostream>
#include <string>
#include <direct.h>
#include <fstream>
#include <filesystem>
#include <vector>
using namespace std;


// namespace fs = std::filesystem;

bool IsPathExist(const std::string& s)
{
	struct stat buffer;
	return (stat(s.c_str(), &buffer) == 0);
}
char checkWhatSlash(string directory) {//finds specific slash in directory to find out what slash to op system is using
	if (directory.find('\\') != std::string::npos)
		return '\\';
	else
		return '/';
}


int main(int argc, char** argv)
{
	string directory = argv[0];//program full path + name of binary file
	char slash = checkWhatSlash(directory);//returns what backslash the opperating system uses for its directories

	directory.erase(directory.find_last_of(slash) + 1);//remove name of binary file
	directory += "files";
	directory += slash;//adds the correct slash according to op system

	string action = argv[1];
	string fileName = argv[2];
	fileName += ".txt";
	if (action == "create") {
		if (!IsPathExist(directory))//creates file only if it doesnt exist already
		{
			if (_mkdir(directory.c_str()) != 0) {
				cerr << "Problem creating directory 'files'\n" << endl;
				exit(1);
			}
			else
				cout  << """files"" successfully created in directory: "<< directory << endl;
		}
		else {
			cout << """files"" already exists in directory: " << directory << endl;
		}
		directory += fileName;
		string contentToAdd = argv[3];
		string content = "Hello from ";
		content += contentToAdd;
		ofstream outfile;
		outfile.open(directory);
		if (outfile.is_open()) {
			outfile << content;
			cout << fileName << " holds wanted content." <<endl;
			outfile.close();
		}
		else {
			cerr << "Error: file could not be opened" << endl;
			exit(1);
		}
	}
	else if (action == "read") {
		directory += fileName;
		if (!IsPathExist(directory)) {
			cerr << "Error: file could not be opened to be read, path does not exist" << endl;
			exit(1);
		}
		ifstream infile(directory);
		string data;
		while (getline(infile, data,'\0')) {
			cout << data<< endl;
		}
		infile.close();

	}
		//If user passed "create" argument 
		//		Create (or overwrite) a file named *argument2.txt*  with the text "Hello from *argument3*" in a folder named "files" under the current working directory  
		//else if user passed "read" argument 
		//		read a file named* argument2* from a folder named "files" under the current working directory and print it to the console

		//Execution example (assuming working directory c:\code): question04.exe create test1 Nir - should create the file c:\code\files\test1.txt with the content "Hello from Nir"
		//Execution example (assuming working directory c:\code): question04.exe read test1  - should print "Hello from Nir" in the console (assuming the previous command was executed) 

		std::cout << "Press enter to exit" << std::endl;
		getchar();
		return 0;
}