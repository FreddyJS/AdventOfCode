#include <LinkedList.hpp>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;


LinkedList<string>* bags = new LinkedList<string>();
LinkedList<string>* subBags = new LinkedList<string>();
LinkedList<int>* nSubBags = new LinkedList<int>();

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

        return true;
    }

    for (size_t i = 0; i < bags->size; i++) {
        pos = line.find(bags->get(i), 1);

        if (pos <= line.length() && pos != 0) {

            pos = line.find(" contain ");
            result = line.substr(0, pos-1);
            
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

bool subBagSaved(string bag) {

    if (bag.at(0) == ' ') {
        return true;
    }

    for (size_t i = 0; i < subBags->size; i++) {
        if (subBags->get(i).compare(bag) == 0) {
            return true;
        }
    }
    

    return false;
}

void checkBag(LinkedList<string>* input) {
    string readed;
    int n_bags = 0;

    for (size_t i = 0; i < subBags->size; i++) {
	    for (size_t j = 0; j < input->size; j++) {
        readed = input->get(j);
        //cout << j << ". " << readed << ". List size: " << subBags->size << endl;

            if (strncmp(readed.c_str(), subBags->get(i).c_str(), subBags->get(i).length()) == 0) {
                size_t pos = readed.find(" contain ");
                pos += strlen(" contain ");
                string result = readed.substr(pos);

                size_t aux = result.find(", ");
                size_t posR = 0;

                if (aux <= result.length()) {
                    int n = 0;

                    while (aux <= result.length()) {
                        string s = result.substr(posR, aux-posR);
                        size_t aux2 = aux;

                        if (s.at(s.length()-1) == 's') {
                            s.at(s.length()-1) = '\0';
                        }
                        
                        char c_n = *(s.c_str());    
                        n = 0;

                        s = s.substr(2);

                        if (isdigit(c_n)) {
                            n = stoi(&c_n);
                            n_bags++;
                        }         

                        if (!subBagSaved(s)) {
                            subBags->addLast(s);
                            nSubBags->addLast(n);

                        }

                        aux = result.find(", ", aux+1);
                        posR = aux2+2;
                    }

                    string s = result.substr(posR, result.length()-posR-1);

                    if (s.at(s.length()-1) == 's') {
                            s.at(s.length()-1) = '\0';
                    }
                        
                    
                    char c_n = *(s.c_str());    
                    n = 0;

                    s = s.substr(2);

                    if (isdigit(c_n)) {
                        n = stoi(&c_n);
                        n_bags++;
                    }       


                    if (!subBagSaved(s)) {
                            subBags->addLast(s);
                            nSubBags->addLast(n);
                    }

                } else {
                    pos = readed.find(" contain ");
                    pos += strlen(" contain ");
                    result = readed.substr(pos);

                    char c_n = *(result.c_str());    
                    int n = 0;

                    if (isdigit(c_n)) {
                        n = stoi(&c_n);
                        n_bags++;
                    }         

                    result = readed.substr(pos+2, readed.length() - (pos+3) );
                    if (!subBagSaved(result)) {
                        subBags->addLast(result);
                        nSubBags->addLast(n);
                    }
                }
            }
        }
    }
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

    bags->clear();

    subBags->addLast("shiny gold bag");
    nSubBags->addLast(0);



    n_bags = subBags->size;
    n_loops = 1;
    cout << "\t\t\033[1;34m---------- Day 7 Part 2 ----------\033[0m" << endl;
    do {
        cout << "Loop " << n_loops << "!" << endl;
        n_bags = subBags->size;
        checkBag(input);

        n_loops++;
        cout << "The list has: " << subBags->size << endl;
    } while(n_bags != subBags->size);


    for (size_t i = 0; i < subBags->size; i++) {
        cout << "\tWe have " << nSubBags->get(i) << " " << subBags->get(i) << endl;
    }
    

    bags->destruct();
    input->destruct();
    subBags->destruct();
    nSubBags->destruct();
    return 0;
}
