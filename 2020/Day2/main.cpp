#include <LinkedList.hpp>
#include <iostream>
#include <fstream>
#include <string.h>


using namespace std;

struct password {
    char psswd[1024];
    int minL;
    int maxL;
    char letter;
};

bool checkPass(struct password p) {
    char* paux = p.psswd;
    int count = 0;
    while (paux != NULL) {
        if (*paux == p.letter) {
            count++;
        } else if (*paux == '\0') {
            break;
        }
        paux++;
    }

    if ( count >= p.minL && count <= p.maxL ) {
        return true;
    }

    return false;
}

bool checkPass2(struct password p) {
    char* paux = p.psswd;
    p.minL--;
    p.maxL--;
    
    char* firstP = paux + p.minL;
    char* lastP = paux + p.maxL;
    if(*firstP == p.letter && *lastP != p.letter) {
        return true;
    } else if (*lastP == p.letter && *firstP != p.letter) {
        return true;
    }

    return false;
}


int main(int argc, char* argv[]) {
	cout << "\nHey, im dope, give me some clusters!" << endl;

	if (argc != 2) {
		cout << "Give me a file with the cluster(s)'s points!" << endl;
	} else {
		cout << "Thanks! I will analyze the file: " << argv[1] << "\n" << endl;
	}

	ifstream clusterFile;
	clusterFile.open(argv[1]);

	string readed;
	int n_line = 0;

	LinkedList<password>* listCorrect = new LinkedList<password>();
	LinkedList<password>* listWrong = new LinkedList<password>();
    LinkedList<password>* listAll = new LinkedList<password>();

	while(getline(clusterFile, readed)) {
		n_line++;

		char line[readed.length()];
		strcpy(line, readed.c_str());

		char* pol = strtok(line, " ");
        char* passL = strtok(NULL, ":");
        char* psswd = strtok(NULL, ": ");

        int minL = stoi(strtok(pol, "-"));
		int maxL = stod(strtok (NULL, "-"));
		
        struct password p;
        p.letter = *passL;
        p.maxL = maxL;
        p.minL = minL;
        strcpy(p.psswd, psswd);

        bool correct = checkPass(p);

        if (correct) {
            listCorrect->addLast(p);

        } else {
            listWrong->addLast(p);
        }
        listAll->addLast(p);
	}

	cout << "\nReaded " << n_line << " lines!" << endl;

    cout << "\nPart 1!" << endl;
    cout << "There are " << listCorrect->size << " correct paswords." << endl;
    cout << "There are " << listWrong->size << " incorrect paswords." << endl;

    listCorrect->clear();
    listWrong->clear();

    for (size_t i = 0; i < listAll->size; i++) {
        struct password p = listAll->get(i);
        bool correct = checkPass2(p);

        if (correct) {
            listCorrect->addLast(p);
        } else {
            listWrong->addLast(p);
        }
    }
    
    cout << "\nPart 2!" << endl;
    cout << "There are " << listCorrect->size << " correct paswords." << endl;
    cout << "There are " << listWrong->size << " incorrect paswords." << endl;

	listCorrect->destruct();
    listWrong->destruct();
    listAll->destruct();

	return 0;
}