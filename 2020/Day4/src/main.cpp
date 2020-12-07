#include <LinkedList.hpp>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main(int argc, char* argv[]) {
    char *fields[8] = {"ecl", "pid", "eyr", "hcl", "byr", "iyr", "hgt", "cid"};
	cout << "\nHey, im dope, give me some clusters!" << endl;

	if (argc != 2) {
		cout << "Give me a file with the cluster(s)'s points!" << endl;
	} else {
		cout << "Thanks! I will analyze the file: " << argv[1] << "\n" << endl;
	}

    ifstream clusterFile;
	clusterFile.open(argv[1]);

	string readed;
    bool checked = false;
	int n_line = 1;
    int pos = 0;
    int posy = 1;
    int lim = 0;
    int saves = 0;
    int trees = 0;

	//LinkedList<char[1024]>* list = new LinkedList<char[1024]>();

	while(getline(clusterFile, readed)) {
        char line[readed.length()];
        strcpy(line, readed.c_str());
        lim = strlen(line);

        if (lim > 0) {
            
        }

        n_line++;
    }

	cout << "\nReaded " << n_line << " lines!" << endl;

    clusterFile.close();

	return 0;
}