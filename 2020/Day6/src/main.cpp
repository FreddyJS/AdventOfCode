#include <LinkedList.hpp>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

struct letter {
    char l;
    int n;
};

int checkAnswers(char* line, LinkedList<letter>* letters) {
    int len = strlen(line);
    int answers = 0;

    for (int i = 0; i < len; i++) {
        for (size_t j = 0; j < letters->size; j++) {
            char c = letters->get(j).l;
            if (*(line+i) == c) {
                //cout << " --> " << *(line+i) << " Letter: " << letters->get(j).l << endl;

                letter let = letters->get(j);
                if (let.n == 0) {
                    answers++;
                }
                let.n++;

                letters->set(j, let);
            }
        }
    }
    

    return answers;
}

int getGeneralAnswers(LinkedList<letter>* letters, int n_group) {
    int count = 0;

    for (size_t i = 0; i < letters->size; i++) {
        if (letters->get(i).n == n_group) {
            count++;
        }
    }

    return count;
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

    LinkedList<letter>* letters = new LinkedList<letter>();

    for (char c = 'a'; c < 'z'+1; c++) {
        letter let;
        let.l = c;
        let.n = 0;
        letters->addLast(let);
    }

    LinkedList<letter>* letterscpy = new LinkedList<letter>(letters);    

	string readed;
	int n_line = 1;
    int g_answers = 0;
    int n_group = 0;
    int n_allAnswered = 0;

	while(getline(clusterFile, readed)) {
        char line[readed.length()];
        strcpy(line, readed.c_str());
        int len = strlen(line);

        if (len == 0 || clusterFile.eof()) {
            n_allAnswered += getGeneralAnswers(letters, n_group);

            letters->destruct();
            letters = new LinkedList<letter>(letterscpy);

            cout << "The group answered: " << g_answers << " times!\n" << endl;
            n_group = 0;
        } else {
            cout << readed << endl;

            int answers = checkAnswers(line, letters);
            n_group++;
            g_answers += answers;
        }

        n_line++;
    }

	cout << "\nReaded " << n_line << " lines!" << endl;

    cout << "The result of the part1 is: " << g_answers << "!" << endl;
    cout << "The result of the part2 is: " << n_allAnswered << "!" << endl;

    clusterFile.close();

    letters->destruct();
    letterscpy->destruct();

    return 0;
}
