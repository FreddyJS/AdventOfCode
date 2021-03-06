#include <LinkedList.hpp>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

bool checkField(char* start) {
    char* data;

    data = strtok(start, " ");
    data = strtok(data, ":");
    data = strtok(NULL, ":");
        
    int len = strlen(data);
    
    if (strncmp(start, "pid", 3) == 0) {

        if (len != 9) {
            return false;
        }

        for (int i = 0; i < len; i++){
            if (!isdigit(*(data+i))) {
                return false;
            }
        }
        
    } else if (strncmp(start, "byr", 3)  == 0) {

        if (len != 4) {
            return false;
        }
        try {
            int x = stoi(data);
            if (x > 2002 || x < 1920) {
                return false;
            }
        }
        catch(const std::exception& e){
            std::cerr << e.what() << '\n';
            return false;
        }
        
    } else if (strncmp(start, "iyr", 3)  == 0) {

        if (len != 4) {
            return false;
        }
        try {
            int x = stoi(data);
            if (x > 2020 || x < 2010) {
                return false;
            }
        }
        catch(const std::exception& e){
            std::cerr << e.what() << '\n';
            return false;
        }

    } else if (strncmp(start, "eyr", 3)  == 0) {

        if (len != 4) {
            return false;
        }
        try {
            int x = stoi(data);
            if (x > 2030 || x < 2020) {
                return false;
            }
        }
        catch(const std::exception& e){
            std::cerr << e.what() << '\n';
            return false;
        }

    } else if (strncmp(start, "hgt", 3)  == 0) {

        if (*(data+(len-1)) == 'm') {
            if (isdigit(*data)) {
                int x = stoi(data);
                if (x > 193 || x < 150) {
                    return false;
                }
            } else {
                return false;
            }

        } else if (*(data+(len-1)) == 'n') {
            if (isdigit(*data)) {
                int x = stoi(data);
                if (x > 76 || x < 59) {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }

    } else if (strncmp(start, "ecl", 3)  == 0) {

        if (strcmp(data, "amb") == 0) {
            return true;
        }

        if (strcmp(data, "blu") == 0) {
            return true;
        }

        if (strcmp(data, "brn") == 0) {
            return true;
        }

        if (strcmp(data, "gry") == 0) {
            return true;
        }

        if (strcmp(data, "grn") == 0) {
            return true;
        }

        if (strcmp(data, "hzl") == 0) {
            return true;
        }

        if (strcmp(data, "oth") == 0) {
            return true;
        }

        return false;
        
    } else if (strncmp(start, "hcl", 3)  == 0) {

        if (len != 7) {
            return false;
        }

        for (int i = 0; i < len; i++) {
            if (*(data+(len-1)) != '#') {
                if (!isdigit(*(data+(len-1)))) {
                    if (*(data+(len-1)) > 'f' || *(data+(len-1)) < 'a') {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

int checkValid(string data, LinkedList<string>* fields) {
    LinkedList<string>* fieldscpy = new LinkedList<string>(fields);
    
    char line[data.length()];
    strcpy(line, data.c_str());

    bool fin = false;
    char* start = line;
    size_t pos = 0;

    while (!fin) {
        size_t nspace = 0;
        size_t count = 0;

        for (string s: *fieldscpy) {
            int comp = strncmp(s.c_str(), start, s.length());

            if (comp == 0) {
                bool validField = checkField(start);
                if (validField) {
                    fieldscpy->remove(count);
                }
            }
            count++;
        }

        nspace = data.find(" ", pos);
        
        if (nspace < data.length()) {
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

    cout << "\033[1;33m\nPassport: \033[0m" << data << endl;
    cout << "\033[1;34mMissing " << fieldscpy->size << " field! \033[0m";
    if (fieldscpy->size == 0) {
        cout << "\033[1;31mValid passport!\033[0m" << endl;
        return 1;
    } else {
        if (fieldscpy->size == 1 && fieldscpy->get(0).compare("cid") == 0) {
            cout << "\033[1;31mValid passport!\033[0m" << endl;

            cout << "\033[1;35mMissing/Wrong: \033[0m";
            for (string s : *fieldscpy) {
                if (s.compare(fieldscpy->getLast()) == 0) {
                    cout << s << endl;
                } else {
                    cout << s << " - ";
                }
            }

            return 0;
        }

        cout << "\033[1;31mInvalid passport!\033[0m" << endl;
        cout << "\033[1;35mMissing/Wrong: \033[0m";

        for (string s : *fieldscpy) {
            if (s.compare(fieldscpy->getLast()) == 0) {
                cout << s << endl;
            } else {
                cout << s << " - ";
            }
        }
    
    }

    return -1;
}


int main(int argc, char* argv[]) {
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
	int n_line = 0;
    int lim = 0;

	while(getline(clusterFile, readed)) {
        n_line++;
        
        char line[readed.length()];
        strcpy(line, readed.c_str());
        lim = strlen(line);
        
        if (*line == '\0' || clusterFile.eof()) {
            if (clusterFile.eof()) {
                data.append(readed);
                data.append(" ");
            } 
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
        }

    }

	cout << "\nReaded " << n_line << " lines!" << endl;
    cout << "There are " << valids << " valids passports!" << endl;

    clusterFile.close();
    list->destruct();

	return 0;
}