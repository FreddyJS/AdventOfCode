#include <LinkedList.hpp>
#include <iostream>
#include <fstream>
#include <string.h>


using namespace std;

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

	LinkedList<int>* list = new LinkedList<int>();


	while(getline(clusterFile, readed)) {
		n_line++;
		int x = stoi(readed);
		list->addLast(x);
	}
    
	cout << "Readed " << n_line << " points!\n" << endl;
    int result;
    
    for (size_t i = 0; i < list->size-1; i++) {
        for (size_t j = i+1; j < list->size-1; j++) {
            /* code */
            int x = list->get(i);
            int y = list->get(j);

            int sum = x+y;
            //cout << x << "+" << y << "=" << sum << endl;
            if (sum == 2020) {
                result = x*y;
                cout << x << "+" << y << "=" << sum << endl;
            }
            
        }
    }
    cout << "The result is: " << result << endl  << endl;


    for (size_t i = 0; i < list->size-1; i++) {
        for (size_t j = i+1; j < list->size-1; j++) {
            for (size_t k = j+1; k < list->size-1; k++) {
                /* code */
                int x = list->get(i);
                int y = list->get(j);
                int z = list->get(k);

                int sum = x+y+z;
                //cout << x << "+" << y << "=" << sum << endl;
                if (sum == 2020) {
                    result = x*y*z;
                    cout << x << "+" << y << "+" << z << "=" << sum << endl;
                }
            }
        }
    }
    cout << "The result is: " << result << endl;
	list->destruct();

	return 0;
}