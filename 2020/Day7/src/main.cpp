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

void checkBags(int argc, char* argv[]) {
    ifstream clusterFile;
	clusterFile.open(argv[1]);

	string readed;
    int n_bags = 0;
	int n_line = 1;

    string sgb = "shiny gold bag";

	while(getline(clusterFile, readed)) {
        char line[readed.length()];
        strcpy(line, readed.c_str());
        int len = strlen(line);


        if (len > 0 || clusterFile.eof()) {
            bool canContain = checkIfContain(readed, sgb, 1);

            if (canContain) {
                n_bags++;
            }
        }

        n_line++;
    }

	cout << "Readed " << n_line << " lines!" << endl;
    cout << "The number of bags that can contain shiny gold bags are: " << n_bags << "\n" << endl;

    clusterFile.close();
}

int main(int argc, char* argv[]) {
	cout << "Hey, im dope, give me some clusters!" << endl;

	if (argc != 2) {
		cout << "Give me a file with the cluster(s)'s points!" << endl;
	} else {
		cout << "Thanks! I will analyze the file: " << argv[1] << "\n" << endl;
	}

    size_t n_bags = bags->size;
    int n_loops = 1;
    do {
        cout << "Loop " << n_loops << ": ";
        n_bags = bags->size;
        checkBags(argc, argv);

        n_loops++;
    } while(n_bags != bags->size);

    cout << "The list has: " << bags->size << " bags!" << endl;
    bags->destruct();

    return 0;
}
