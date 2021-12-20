#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

#define ul unsigned long

using namespace std;


void readSequenceToVector(vector<int>* vec) {
    int number;
    string line;

    getline(cin >> ws, line);
    istringstream iss(line);
    while(iss >> number) {
        vec->push_back(number);
    }
}


pair<ul, ul> findNumberAndLengthOfLIS(vector<int>* sequence) {

    ul maxLength = 0;
    ul subsequenceCount = 0;
    ul sequenceLength = sequence->size();

    // Initialize all the lengths with ones;
    vector<ul> lengths(sequenceLength, 1);
    // Initialize all the counts with ones
    vector<ul> counts(sequenceLength, 1);

    
    for(ul i = 1; i < sequenceLength; i++) {
        for(ul j = 0; j < i; j++) {

            if(sequence->at(i) <= sequence->at(j)) {
                continue;
            }

            if(lengths[j] + 1 > lengths[i]) {
                lengths[i] = lengths[j] + 1;
                counts[i] = counts[j];
            } else if (lengths[j] + 1 == lengths[i]) {
                counts[i] += counts[j];
            }
        }

        if (maxLength == lengths[i]) {
            subsequenceCount += counts[i];
        } else if (maxLength < lengths[i]) {
            maxLength = lengths[i];
            subsequenceCount = counts[i];
        }

        // Forma menos eficiente de calcular o maxLength e subsequencesCount
        /*
        for(int i = 0; i < sequenceLength; i++) {
            *maxLength = max(i, *maxLength);
        }

        for(int i = 0; i < sequenceLength; i++) {
            if(lengths[i] == *maxLength) {
                *subsequenceCount += counts[i];
            }
        }
        */
    }

    return pair<ul, ul>(maxLength, subsequenceCount);
}


ul findLengthOfLCIS(vector<int>* seq1, vector<int>* seq2) {
    vector<ul> lengths(min(seq1->size(), seq2->size()), 0);
    ul current;

    for(ul i = 0; i < seq1->size(); i++) {
        current = 0;

        for(ul j = 0; j < seq2->size(); j++) {
            if(seq1->at(i) == seq2->at(j) && current + 1 > lengths[j]) {
                lengths[j] = current + 1;
            } 
            else if(seq1->at(i) > seq2->at(j) && lengths[j] > current) {
                current = lengths[j];
            }
        }
    }

    return *max_element(lengths.begin(), lengths.end());
}


void handleFirstProblem() {
    vector<int> sequence;
    pair<ul, ul> result;

    readSequenceToVector(&sequence);

    result = findNumberAndLengthOfLIS(&sequence);

    cout << result.first << " " << result.second;

}



void handleSecondProblem() {
    vector<int> sequence1;
    vector<int> sequence2;

    readSequenceToVector(&sequence1);
    readSequenceToVector(&sequence2);

    cout << findLengthOfLCIS(&sequence1, &sequence2);
}


int main() {
    int problem;

    cin >> problem;

    if(problem == 1) {
        handleFirstProblem();
    } else if (problem == 2) {
        handleSecondProblem();
    }

    return 0;
}