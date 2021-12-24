#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#define ull unsigned long long

using namespace std;


void readSequenceToVector(vector<int>& vec) {
    int number;
    string line;

    getline(cin >> ws, line);
    /*
    if(line.empty()) {
        return;
    }
    */

    istringstream iss(line);
    while(iss >> number) {   
        vec.push_back(number); 
    }
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

    //Forma menos eficiente de calcular o maxLength e subsequencesCount
    /*
    for(ull i = 0; i < sequenceLength; i++) {
        maxLength = max(i, maxLength);
    }

    for(ull i = 0; i < sequenceLength; i++) {
        if(lengths[i] == maxLength) {
            subsequenceCount += counts[i];
        }
    }
    */

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
    vector<int> sequence1;
    vector<int> sequence2;

    readSequenceToVector(sequence1);
    readSequenceToVector(sequence2);

    cout << findLengthOfLCIS(sequence1, sequence2) << endl;
}


int main() {
    int problem;

    cin >> problem;
    //cin.ignore(1, '\n');

    if(problem == 1) {
        handleFirstProblem();
    } else if (problem == 2) {
        handleSecondProblem();
    }

    return 0;
}
