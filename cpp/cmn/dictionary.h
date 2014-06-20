#include <fstream>
#include <string>
#include <map>

using namespace std;

class dictionary {
    set<string> words;
    public:
    dictionary() {
        ifstream input("/usr/share/dict/words");
        for (string line; getline(input, line);) words.insert(line);
    }

    bool isValidWord (string word) {
        return words.count(word) ? true : false;
    }
};

