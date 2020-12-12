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
	int n_line = 0;
    int pos = 0;
    int posy = 1;
    int lim = 0;
    int saves = 0;
    int trees = 0;

	while(getline(clusterFile, readed)) {
        n_line++;

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
        }
    }

    cout << "Readed " << n_line << " lines!" << endl;
    cout << "There are " << trees << " trees! - There are " << saves << " save spots!\n" << endl;

    clusterFile.close();
    return trees;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Give me a file with to use as the input data!" << endl;
	} else {
		cout << "The input data file is: " << argv[1] << "\n" << endl;
	}

    cout << "\t\t\033[1;34m---------- Day 3 Both Parts ----------\033[0m\n" << endl;

	cout << "\033[1;31mMoving 1 right 1 down!\033[0m" << endl;
	int trees1 = getTrees(argv, 1, 1);
    
	cout << "\033[1;31mMoving 3 right 1 down!\033[0m" << endl;
    int trees2 = getTrees(argv, 3, 1);

	cout << "\033[1;31mMoving 5 right 1 down!\033[0m" << endl;
	int trees3 = getTrees(argv, 5, 1);

	cout << "\033[1;31mMoving 7 right 1 down!\033[0m" << endl;
	int trees4 = getTrees(argv, 7, 1);

	cout << "\033[1;31mMoving 1 right 2 down!\033[0m" << endl;
    int trees5 = getTrees(argv, 1, 2);

    cout << "\nThe final result is: " << trees1*trees2*trees3*trees4*trees5 << endl;

	return 0;
}