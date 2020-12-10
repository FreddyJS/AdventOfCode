#include <LinkedList.hpp>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int getTrees(char* argv[], int moveX, int moveY) {
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

	while(getline(clusterFile, readed)) {
        char line[readed.length()];
        strcpy(line, readed.c_str());
        lim = strlen(line);

        if (n_line == 1 || checked) {
            posy += moveY;
            checked = false;
        }
        if (lim > 0) {
            if (n_line == posy) {
                checked = true;
                pos += moveX;
                if (pos < lim) {
                    if (*(line+pos) == '#' ) {
                        *(line+pos) = 'T';
                        trees++;
                    } else {
                        *(line+pos) = 'S';
                        saves++;
                    }
                } else {
                    int aux = (pos - lim);
                    pos = aux;

                    if (*(line+pos) == '#' ) {
                        *(line+pos) = 'T';
                        trees++;
                    } else {
                        *(line+pos) = 'S';
                        saves++;
                    }
                }
            }

            n_line++;
        }
    }

	cout << "\nReaded " << n_line << " lines!" << endl;
    cout << "There are " << trees << " trees! and " << saves << " save spots!" << endl;

    clusterFile.close();
    return trees;
}

int main(int argc, char* argv[]) {
	cout << "\nHey, im dope, give me some clusters!" << endl;

	if (argc != 2) {
		cout << "Give me a file with the cluster(s)'s points!" << endl;
	} else {
		cout << "Thanks! I will analyze the file: " << argv[1] << "\n" << endl;
	}

	int trees1 = getTrees(argv, 1, 1);
    int trees2 = getTrees(argv, 3, 1);
	int trees3 = getTrees(argv, 5, 1);
	int trees4 = getTrees(argv, 7, 1);
    int trees5 = getTrees(argv, 1, 2);

    cout << "\nThe final result is: " << trees1*trees2*trees3*trees4*trees5 << endl;

	return 0;
}