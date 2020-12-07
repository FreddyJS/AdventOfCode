#include <LinkedList.hpp>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;


int checkValid(string data, LinkedList<string>* fields) {
    char line[data.length()];
    LinkedList<string>* fieldscpy = new LinkedList<string>(fields);
    strcpy(line, data.c_str());

    size_t pos = 0;
    size_t nspace = 0;
    size_t count = 0;
    bool fin = false;
    char* start = line;

    while (!fin) {
        count = 0;
        for (string s: *fieldscpy) {
            int comp = strncmp(s.c_str(), start, s.length());

            if (comp == 0) {
                fieldscpy->remove(count);
            }
            count++;
        }

        nspace = data.find(" ", pos);
        
        if (nspace != pos && nspace < data.length()) {
            start = line;
            if (data.length() > nspace) {
                start += nspace+1;
                pos = nspace+1;
            } else {
                start += nspace;
                pos = nspace;
            }
        } else {
            fin = true;
        }


    }

    cout << "\nWe miss " << fieldscpy->size << " thing!" << endl;
    if (fieldscpy->size == 0) {
        cout << "Valid passport! - " << data << endl;
        return 1;
    } else {
        for (string s : *fieldscpy) {
            cout << s << " - ";
        }
    
        if (fieldscpy->size == 1 && fieldscpy->get(0).compare("cid") == 0) {
            cout << "\"Valid passport\"! - " << data << endl;
            return 0;
        }
    }

    cout << "Invalid passport: " << data << endl;
    return -1;
}


int main(int argc, char* argv[]) {
    //char *fields[8] = {"ecl", "pid", "eyr", "hcl", "byr", "iyr", "hgt", "cid"};
    LinkedList<string>* fields = new LinkedList<string>();

    fields->addLast("ecl");
    fields->addLast("pid");
    fields->addLast("eyr");
    fields->addLast("hcl");
    fields->addLast("byr");
    fields->addLast("iyr");
    fields->addLast("hgt");
    fields->addLast("cid");

    int valids = 0;
    int semivalid = 0;

	cout << "\nHey, im dope, give me some clusters!" << endl;

	if (argc != 2) {
		cout << "Give me a file with the cluster(s)'s points!" << endl;
	} else {
		cout << "Thanks! I will analyze the file: " << argv[1] << "\n" << endl;
	}

    ifstream clusterFile;
	clusterFile.open(argv[1]);

    LinkedList<string>* list = new LinkedList<string>();

	string readed;
    string data;
	int n_line = 1;
    int lim = 0;

	while(getline(clusterFile, readed)) {
        char line[readed.length()];
        strcpy(line, readed.c_str());
        lim = strlen(line);
        
        if (*line == '\0') {
            if (clusterFile.eof()) data.append(readed);
            data.replace(data.length()-1, data.length(), "\0");
            list->addLast(data);
            int valid = checkValid(data, fields);
            if (valid != -1) {
                valids++;
            }
            data = "";
        } else if (lim > 0){
            data.append(readed);
            data.append(" ");
            if (clusterFile.eof()) {
                data.replace(data.length()-1, data.length(), "\0");
                list->addLast(data);
               int valid = checkValid(data, fields);
                if (valid != -1) {
                    valids++;
                }
            }
        }

        n_line++;
    }

	cout << "\nReaded " << n_line << " lines!" << endl;
    cout << "There are " << valids << " valids passports!" << endl;

    clusterFile.close();

	return 0;
}