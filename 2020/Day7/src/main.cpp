#include <LinkedList.hpp>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

LinkedList<string>* bags = new LinkedList<string>();

bool bagSaved(string bag) {
    for (size_t i = 0; i < bags->size; i++) {
        if (bags->get(i).compare(bag) == 0) {
            return true;
        }
    }
    
    return false;
}

bool checkIfContain(string line, string search, int n) {
    size_t pos = line.find(search, 1);
    string result;

    if (pos <= line.length() && pos != 0) {
        pos = line.find(" contain ");
        result = line.substr(0, pos-1);
    
        if (!bagSaved(result)) {
            bags->addLast(result);
        }

        //cout << line << endl;
        //cout << "Founded the bag: " << result << "\n" << endl;
        return true;
    }

    for (size_t i = 0; i < bags->size; i++) {
        pos = line.find(bags->get(i), 1);

        if (pos <= line.length() && pos != 0) {

            pos = line.find(" contain ");
            result = line.substr(0, pos-1);
            
            //cout << line << endl;
            //cout << " --> Founded the bag: " << bags->get(i) << " in the bag " << result << "\n" << endl;

            if (!bagSaved(result)) {
                bags->addLast(result);
            }

            return true;
        }
    }

    return false;
}

void checkBags(LinkedList<string>* input) {
	string readed;
    int n_bags = 0;

    string sgb = "shiny gold bag";

	for (size_t i = 0; i < input->size; i++) {
        readed = input->get(i);
        bool canContain = checkIfContain(readed, sgb, 1);

        if (canContain) {
            n_bags++;
        }
    }

    

    cout << "The number of bags that can contain shiny gold bags are: " << n_bags << endl;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Give me a file with to use as the input data!" << endl;
	} else {
		cout << "The input data file is: " << argv[1] << endl;
	}

    LinkedList<string>* input = new LinkedList<string>();

    string readed;
	int n_line = 1;

    ifstream clusterFile;
	clusterFile.open(argv[1]);

	while(getline(clusterFile, readed)) {

        if (readed.length() > 0 || clusterFile.eof()) {
            input->addLast(readed);
        }
        
        n_line++;
    }

	cout << "Readed " << n_line << " lines from " << argv[1] << "\n" << endl;

    clusterFile.close();

    size_t n_bags = bags->size;
    int n_loops = 1;
    cout << "\t\t\033[1;34m---------- Day 7 Part 1 ----------\033[0m" << endl;
    do {
        cout << "Loop " << n_loops << ": ";
        n_bags = bags->size;
        checkBags(input);

        n_loops++;
    } while(n_bags != bags->size);

    cout << "\033[1;31mThe final number of bags that can contain shiny gold bags are: " << bags->size << " bags!\n\033[0m" << endl;

    cout << "\t\t\033[1;34m---------- Day 7 Part 2 ----------\033[0m" << endl;

    bags->destruct();

    return 0;
}
