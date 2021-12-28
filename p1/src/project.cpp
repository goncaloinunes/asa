#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <climits>
#include <algorithm>
#include <unordered_map>

#define ull unsigned long long

using namespace std;


void readSequenceToVector(vector<int>& vec) {
    int number;
    string line;

    getline(cin >> ws, line);
    istringstream iss(line);

    while(iss >> number) {   
        vec.push_back(number); 
    }
}


// Time Complexity: O(N)
void removeConsecutiveDuplicates(vector<int>& vet, unordered_map<int, int>& m) {
	int last = INT_MAX;
    ull k = 0;

	for (ull i = 0; i < vet.size(); i++) {
		// if m.find(x) == m.end() then it means that
		// x is not present in the map
		if(m.find(vet[i]) == m.end()) {
			m[vet[i]] = 1; // inserting vet[i] into the map
		}
        else if(vet[i] == last){
            continue;
        }
        vet[k++] = vet[i];
        last = vet[i];
	}
    //cout << "removeDuplicates: " << vet.size() <<' '<< k <<' '<< vet.size()-k << endl;
    vet.resize(k);
}


// Time Complexity: O(N), where N equals max(v1.size(), v2.size())
void removeUncommonElements(vector<int>& v1, vector<int>& v2, unordered_map<int, int>& m1, unordered_map<int, int>& m2) {
    ull k = 0;
    for(ull i = 0; i < v1.size(); i++) {
        if(m2.find(v1[i]) != m2.end()) {
            v1[k++] = v1[i];
		}        
    }
    //cout << "removeUncommonElements v1: " << v1.size() <<' '<< k <<' '<< v1.size()-k << endl;
    v1.resize(k);

    k = 0;
    for(ull i = 0; i < v2.size(); i++) {
        if(m1.find(v2[i]) != m1.end()) {
            v2[k++] = v2[i];
		}        
    }
    //cout << "removeUncommonElements v2: " << v2.size() <<' '<< k <<' '<< v2.size()-k << endl;
    v2.resize(k);
}


// Time Complexity: O(N)
// Space Complexity: O(N)
// Removes sequecial duplicates and uncommon elements in both sequences
void preprocessSequences(vector<int>& s1, vector<int>& s2) {
	unordered_map<int, int> m1, m2;

    // remove duplicates and builds the unordered_map
    removeConsecutiveDuplicates(s1, m1);   
    removeConsecutiveDuplicates(s2, m2);
    
    removeUncommonElements(s1, s2, m1, m2);
}


pair<ull, ull> findNumberAndLengthOfLIS(vector<int>& sequence) {
    ull maxLength = 0;
    ull subsequenceCount = 0;
    ull sequenceLength = sequence.size();

    // Initialize all the lengths with ones;
    vector<ull> lengths(sequenceLength, 1);
    // Initialize all the counts with ones
    vector<ull> counts(sequenceLength, 1);

    for(ull i = 0; i < sequenceLength; i++) {
        for(ull j = 0; j < i; j++) {
            if(sequence[i] <= sequence[j]) {
                continue;
            }

            if(lengths[j] + 1 > lengths[i]) {
                lengths[i] = lengths[j] + 1;
                counts[i] = counts[j];
            } 
            else if (lengths[j] + 1 == lengths[i]) {
                counts[i] += counts[j];
            }
        }
        
        if (maxLength == lengths[i]) {
            subsequenceCount += counts[i];
        } 
        else if (lengths[i] > maxLength) {
            maxLength = lengths[i];
            subsequenceCount = counts[i];
        }
    }

    return pair<ull, ull>(maxLength, subsequenceCount);
}


ull findLengthOfLCIS(vector<int>& seq1, vector<int>& seq2) {
    vector<ull> lengths(seq2.size(), 0);
    ull currentLength;
    ull maxLength = 0;

    for(ull i = 0; i < seq1.size(); i++) {
        currentLength = 0;

        for(ull j = 0; j < seq2.size(); j++) {
            if(seq1[i] > seq2[j] && lengths[j] > currentLength) {
                currentLength = lengths[j];
            }
            else if(seq1[i] == seq2[j]) {
                lengths[j] = currentLength + 1;

                // Update the maximum value of lengths
                if(lengths[j] > maxLength) {
                    maxLength = lengths[j];
                }
            } 
        }
    }

    return maxLength;
}


void handleFirstProblem() {
    vector<int> sequence;
    pair<ull, ull> result;

    readSequenceToVector(sequence);
    result = findNumberAndLengthOfLIS(sequence);

    cout << result.first << " " << result.second << endl;
}


void handleSecondProblem() {
    vector<int> sequence1, sequence2;

    readSequenceToVector(sequence1);
    readSequenceToVector(sequence2);
    preprocessSequences(sequence1, sequence2);

    cout << findLengthOfLCIS(sequence1, sequence2) << endl;
}


int main() {
    int problem;

    cin >> problem;

    if(problem == 1) {
        handleFirstProblem();
    } 
    else if (problem == 2) {
        handleSecondProblem();
    }
    return 0;
}
