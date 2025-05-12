    #include <iostream>
    #include <fstream>
    #include <string>
    #include <algorithm>
    #include <map>
    #include <cctype>

    using namespace std;

string cleanWord(const string& word) // Function to clean and convert a word to lowercase
{
    string cleanedWord;
    for (size_t i = 0; i < word.size(); ++i) 
    {
        char c = word[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            cleanedWord += (c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c;
        }
    }
    return cleanedWord;
}

struct WordInfo 
{
    int count;
    string word;
};

bool compareWords (const WordInfo& a, const WordInfo& b) {
    if (a.count != b.count) {
        return a.count > b.count;
    }
    return a.word < b.word;
}

void customSort(WordInfo arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (!compareWords(arr[i], arr[j])) {
                swap(arr[i], arr[j]);
            }
        }
    }
}

int main() {
    string filename;
    cout << "Enter the name of the text file: "; //user input for the file name
    
    cin >> filename;

    ifstream inputFile(filename);   //analysis the file 
    
    if (!inputFile) {
        cout << "Error opening file." << endl;
        return 1;
    }

    map<string, int> wordCount; //map string for store clean words

    string word;
    while (inputFile >> word) 
    {
        string cleanedWord = cleanWord(word);
        if (!cleanedWord.empty()) {
           
            wordCount[cleanedWord]++;
        }
    }

    const int maxWords = 50000; //maximum limitation 
   
    WordInfo words[maxWords];
    int numWords = 0;

    for (const auto& entry : wordCount) {
       
        words[numWords].count = entry.second;
        words[numWords].word = entry.first;
        numWords++;
    }

    customSort(words, numWords); //Sort in decreasing order of word counts and alphabetically

    cout << "Top 10 words:" << endl;  // Output the first ten words
    for (int i = 0; i < min(10, numWords); ++i) 
    {
        cout << words[i].word << " : " << words[i].count << endl;
    }

    cout << "\nBottom 10 words:" << endl;    // Output the last ten words
    for (int i = numWords - 1; i >= max(0, numWords - 10); --i) 
    {
        cout << words[i].word << " : " << words[i].count << endl;
    }

    cout << "\nUnique words:" << endl;     // Output all unique words 
    for (int i = 0; i < numWords; ++i) // word count is 1
    {
        if (words[i].count == 1) {
            cout << words[i].word << endl;
        }
    }

    return 0;
}
