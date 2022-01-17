#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <climits>
#include <unordered_map>
#include <algorithm>

#define ull unsigned long long
#define ll long long

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

		if(m.find(vet[i]) == m.end())   // if m.find(x) == m.end() then x is not in the map yet
			m[vet[i]] = 1;  // inserting vet[i] into the map

        else if(vet[i] == last) // if vet[i] == last it's a consecutive duplicate
            continue;
        
        vet[k++] = vet[i];  // add element and increase number of elements
        last = vet[i];  // update last element seen
    }
    
    vet.resize(k);  // resize vet with number of elements not duplicated
}


// Time Complexity: O(N), where N equals max(v1.size(), v2.size())
void removeUncommonElements(vector<int>& v1, vector<int>& v2, unordered_map<int, int>& m1, unordered_map<int, int>& m2) {
    ull k = 0;
    
    for(ull i = 0; i < v1.size(); i++)   // for every element in v1
        if(m2.find(v1[i]) != m2.end())  // check if element is in m2
            v1[k++] = v1[i];    // add element and increase number of elements
    v1.resize(k);   // resize v1 with number of v1 elements in m2

    k = 0;
    for(ull i = 0; i < v2.size(); i++)
        if(m1.find(v2[i]) != m1.end())
            v2[k++] = v2[i];
    v2.resize(k);
}


// Time Complexity: O(N)
// Space Complexity: O(N)
// Removes sequecial duplicates and uncommon elements in both sequences
void preprocessSequences(vector<int>& s1, vector<int>& s2) {
	unordered_map<int, int> m1, m2;

    // builds the unordered_map while removing consecutive duplicates
    removeConsecutiveDuplicates(s1, m1);   
    removeConsecutiveDuplicates(s2, m2);
    
    removeUncommonElements(s1, s2, m1, m2);
}


pair<ll, ll> findNumberAndLengthOfLIS(int* sequence, ll size) {
    ll maxLength = 0, subsequenceCount = 0;
    
    vector<ll> lengths(size, 1);
    vector<ll> counts(size, 1);
    vector<int> sorted(size);

    copy(sequence, sequence + size, begin(sorted));
    sort(begin(sorted), end(sorted));

    for(ll i = 0; i < size; i++) {
        ll j = i - 1;

        // ignore all the first previous elements bigger or equal to sequence[i]
        for(; j >= 0; j--) {
            if(sequence[j] < sequence[i])
                break;
        }

        // find the previous element of sequence[i] in sorted sequence
        ll current_idx = lower_bound(sorted.begin(), sorted.end(), sequence[i]) - sorted.begin();
        int previous = sorted[current_idx - 1];
        
        // update current length, length[i]
        for(ll k = j; k >= 0; k--) {
            if(lengths[k] >= lengths[i] && sequence[k] < sequence[i]) {
                lengths[i] = lengths[k] + 1;
                counts[i] = counts[k];
                j = k;  // update position
                // if current == previous we don't need to continue searching
                if(sequence[k] == previous)
                    break;
            }
        }

        // find how many paths we can take to reach the current length
        for(j--; j >= 0; j--) {
            if(lengths[j] == lengths[i] - 1 && sequence[j] < sequence[i])
                counts[i] += counts[j];
        }

        // update maxLength and subsequenceCount
        if (maxLength < lengths[i]) {
            maxLength = lengths[i];
            subsequenceCount = counts[i];
        }
        else if (maxLength == lengths[i])
            subsequenceCount += counts[i];
    }

    return pair<ll, ll>(maxLength, subsequenceCount);
}


ull findLengthOfLCIS(vector<int>& seq1, vector<int>& seq2) {
    vector<ull> lengths(seq2.size(), 0);
    ull currentLength, maxLength = 0;
    
    for(ull i = 0; i < seq1.size(); i++) {
        currentLength = 0;

        for(ull j = 0; j < seq2.size(); j++) {
            if(seq1[i] > seq2[j] && lengths[j] > currentLength)
                currentLength = lengths[j];
            
            else if(seq1[i] == seq2[j]) {
                lengths[j] = currentLength + 1;

                // update maxLength
                if(lengths[j] > maxLength)
                    maxLength = lengths[j];
            }
        }
    }

    return maxLength;
}


void handleFirstProblem() {
    vector<int> sequence;
    pair<ll, ll> result;

    readSequenceToVector(sequence);
    result = findNumberAndLengthOfLIS(&(sequence[0]), sequence.size());
    
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

    if(problem == 1) 
        handleFirstProblem();
    else if (problem == 2)
        handleSecondProblem();
    
    return 0;
}
