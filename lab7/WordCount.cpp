// WordCount.cpp

#include "WordCount.h"

using namespace std;
void merge(vector<std::pair<std::string, int>>& arr, int left, 
                     int mid, int right, bool byCount)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    vector<std::pair<std::string, int>> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;
	if(byCount == 1){
    		while (i < n1 && j < n2) {
        		if (L[i].second > R[j].second) {
            			arr[k] = L[i];
            			i++;
        		}
			else if(L[i].second == R[j].second){
				if (L[i].first <= R[j].first) {
                                	arr[k] = L[i];
                                	i++;
                		}	
				else{
					arr[k] = R[j];
                                	j++;
				}
			}
        		else {
            			arr[k] = R[j];
            			j++;
        		}
        		k++;
	
    		}
	}
	else{
    		while (i < n1 && j < n2) {
        		if (L[i].first > R[j].first) {
            			arr[k] = L[i];
            			i++;
        	}
        	else {
            		arr[k] = R[j];
            		j++;
        	}
        	k++;
	
    		}
	}
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void mergeSort(vector<std::pair<std::string, int>>& arr, int left, int right, bool byCount)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, byCount);
    mergeSort(arr, mid + 1, right, byCount);
    merge(arr, left, mid, right, byCount);
}

// Default constructor
WordCount::WordCount() {}

// Simple hash function. Do not modify.
size_t WordCount::hash(std::string word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
	int count = 0;
	for(size_t i = 0; i < CAPACITY;  i++){
                for(auto it = table[i].begin(); it != table[i].end(); ++it){
                        count += it->second;
                }
        }
        return count;
}

int WordCount::getNumUniqueWords() const {
	int count = 0;
	for(size_t i = 0; i < CAPACITY;  i++){
		for(auto it = table[i].begin(); it != table[i].end(); ++it){
			count++;
		}
	}
	return count;
}

int WordCount::getWordCount(std::string word) const {
	std::string str = makeValidWord(word);
	if(str == ""){
                return 0;
        }
        size_t key = hash(str);
        for(auto i = table[key].begin(); i != table[key].end(); ++i){
                if(i->first == str){
                        return i->second;
                }
        }
	return 0;
}
	
int WordCount::incrWordCount(std::string word) {
	std::string str = makeValidWord(word);
	if(str == ""){
                return 0;
        }
	size_t key = hash(str);
	for(auto i = table[key].begin(); i != table[key].end(); ++i){
		if(i->first == str){
			(i->second)++;
			return i->second;
		}
	}	
	std::pair<std::string, int> p = std::make_pair(str, 1);
	table[key].push_back(p);
	return 1;
}

int WordCount::decrWordCount(std::string word) {
	std::string str = makeValidWord(word);
	if(str == ""){
		return 0;
	}
        size_t key = hash(str);
        for(auto i = table[key].begin(); i != table[key].end(); ++i){
                if(i->first == str){
                        if(i->second > 1){
                        	i->second--;
				return i->second;
			}
			else{
				table[key].erase(i);
				return 0;
			}
                }
        }
        return -1;
}

bool WordCount::isWordChar(char c) {
	if(isalpha(c)){
		return true;
	}
	return false;
}

std::string WordCount::makeValidWord(std::string word) {
	std::string str = word;
	for(size_t i = 0; i < str.size(); i++){
		if(isWordChar(str[i]) || ((i >= 1 && i < str.size()-1) && (str[i] == '\'' || str[i] == '-') && isWordChar(str[i-1]) && isWordChar(str[i+1]))){
			if(isupper(str[i])){
				str[i] = tolower(str[i]);
			}
		}
		else{
			str.erase(str.begin() + i);
			i--;
		}
	}
	return str;
}

void WordCount::dumpWordsSortedByWord(std::ostream &out) const {
	std::vector<std::pair<std::string, int> > output;	
	for(size_t i = 0; i < CAPACITY;  i++){
                for(auto it = table[i].begin(); it != table[i].end(); ++it){
                        output.push_back(*it);
                }
        }
	
	mergeSort(output, 0, output.size() - 1,0);

	for(size_t i = 0; i < output.size();  i++){
		out <<  output[i].first << "," << output[i].second << "\n";
	}
	return;
}

void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {
	std::vector<std::pair<std::string, int> > output;
        for(size_t i = 0; i < CAPACITY;  i++){
                for(auto it = table[i].begin(); it != table[i].end(); ++it){
                        output.push_back(*it);
                }
        }

        mergeSort(output, 0, output.size() - 1, 1);

        for(size_t i = 0; i < output.size();  i++){
                out <<  output[i].first << "," << output[i].second << "\n";
        }
        return;
}

void WordCount::addAllWords(std::string text) {
	std::string currentWord = "";
	for(size_t i = 0; i < text.size(); i++){
		if(text[i] == ' ' || text[i] == '\t' || text[i] == '\n'){
			if(currentWord != ""){
				incrWordCount(currentWord);
				currentWord = "";
			}
		}
		else{
			currentWord += text[i];
		}
	}

	if(currentWord != ""){
        	incrWordCount(currentWord);
        }
	return;
}
