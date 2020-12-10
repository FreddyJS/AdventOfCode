#include <LinkedList.hpp>
#include <iostream>
#include <fstream>
#include <string.h>

#define MAXROW 127
#define MINROW 0
#define MAXCOLUMN 7
#define MINCOLUMN 0

using namespace std;

int getID(char* line) {
    int len = strlen(line);

    int maxR = MAXROW;
    int minR = MINROW;

    int maxC = MAXCOLUMN;
    int minC = MINCOLUMN;
    int spaceC = 127;
    int spaceR = 7;
    
    for (int i = 0; i < len; i++) {
        spaceC = (maxC - minC);
        spaceR = (maxR - minR);
        if (i >= len-3) {
            if (*(line+i) == 'R') {
                minC = minC + spaceC/2 +1;
            } else if (*(line+i) == 'L') {
                maxC = maxC - spaceC/2 -1;
            }
        } else {
            if (*(line+i) == 'F') {
                maxR = maxR - spaceR/2 -1;
            } else if (*(line+i) == 'B') {
                minR = minR + spaceR/2 +1;
            }
        }
    }

    int result = maxR*8 +maxC;

    return result;    
}

int main(int argc, char* argv[]) {
	cout << "Hey, im dope, give me some clusters!" << endl;

	if (argc != 2) {
		cout << "Give me a file with the cluster(s)'s points!" << endl;
	} else {
		cout << "Thanks! I will analyze the file: " << argv[1] << "\n" << endl;
	}

    ifstream clusterFile;
	clusterFile.open(argv[1]);

    LinkedList<int>* list = new LinkedList<int>();
    int maxID = 0;
	string readed;
	int n_line = 1;

	while(getline(clusterFile, readed)) {
        char line[readed.length()];
        strcpy(line, readed.c_str());

        int id = getID(line);
        list->addLast(id);
        if (id > maxID) {
            maxID = id;
        }

        n_line++;
    }

	cout << "Readed " << n_line << " lines!" << endl;
    cout << "\nThe maximum ID found was: " << maxID << endl;
    
    int i;
    for (i = 100; i <= 894; i++) {
        int founded = 0;
        bool error = false;
        for (size_t j = 0; j < list->size; j++) {
            if (list->get(j) == i+1 || list->get(j) == i-1) {
                founded++;
            }

            if (list->get(j) == i) {
                error = true;
            }
        }        

        if (founded == 2 && !error) {
            break;
        }
    }
    
    cout << "My seat ID is: " << i << endl;

    clusterFile.close();
    list->destruct();

	return 0;
}