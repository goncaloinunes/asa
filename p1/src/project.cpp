#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <climits>
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
    for(ull i = 0; i < v1.size(); i++)
        if(m2.find(v1[i]) != m2.end())
            v1[k++] = v1[i];
    v1.resize(k);

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

    // remove duplicates and builds the unordered_map
    removeConsecutiveDuplicates(s1, m1);   
    removeConsecutiveDuplicates(s2, m2);
    
    removeUncommonElements(s1, s2, m1, m2);
}


// O(nlogn)
ull findLengthOfLIS(vector<int>& vet, ull size) {
    if(size == 0) return 0;
    
    vector<int> lis;
    lis.push_back(vet[0]);

    for(ull i = 1; i < size; i++)
        if(lis.back() < vet[i])
            lis.push_back(vet[i]);
        else {
            ull aux = lower_bound(lis.begin(), lis.end(), vet[i]) - lis.begin();
            lis[aux] = vet[i];
        }

    return lis.size();
}


pair<ull, ull> findNumberAndLengthOfLIS(int* sequence, ull size) {
    ull maxLength = 0,
        subsequenceCount = 0;
    
    /*ull lengths[100000];
    ull counts[100000];
    ull* lengths = new ull[size];
    ull* counts = new ull[size];*/
    vector<ull> lengths(size, 1);
    vector<ull> counts(size, 1);
    /*// Initialize with ones;
    for(ull i = 0; i < size; i++) {
        lengths[i] = 1; 
        counts[i] = 1;
    }*/
    for(ull i = 0; i < size; i++) {
        for(ull j = 0; j < i; j++) {
            
            if(sequence[j] >= sequence[i]) {
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
        
        if (maxLength < lengths[i]) {
            maxLength = lengths[i];
            subsequenceCount = counts[i];
        }
        else if (maxLength == lengths[i]) {
            subsequenceCount += counts[i];
        } 
    }/*
    for(ull i = 0; i < size; i++)
        cout << sequence[i] << ' ';
    cout << endl;
    for(ull i = 0; i < size; i++)
        cout << lengths[i] << ' ';
    cout << endl;
    for(ull i = 0; i < size; i++)
        cout << counts[i] << ' ';
    cout << endl;*/
    return pair<ull, ull>(maxLength, subsequenceCount);
}

pair<ull, ull> findNumberAndLengthOfLIS1(int* sequence, ull size) {
    ull maxLength = 0,
        subsequenceCount = 0;
    
    vector<ull> lengths(size, 1);
    vector<ull> counts(size, 1);

    for(ull i = 0; i < size; i++) {
        for(long long j = i - 1; j >= 0; j--) {
            if(sequence[j] >= sequence[i]) {
                continue;
            }
            
            lengths[i] = lengths[j] + 1;
            counts[i] = counts[j];
            
            for(j--; j >= 0; j--) {
                if(lengths[j] == lengths[i] - 1 && sequence[j] < sequence[i]) {
                    counts[i] += counts[j];
                }
            }
            break;
        }

        if (maxLength < lengths[i]) {
            maxLength = lengths[i];
            subsequenceCount = counts[i];
        }
        else if (maxLength == lengths[i]) {
            subsequenceCount += counts[i];
        }
    }
    /*
    for(ull i = 0; i < size; i++)
        if(maxLength < lengths[i])
            maxLength = lengths[i];

    for(ull i = 0; i < size; i++)
        if(lengths[i] == maxLength)
            subsequenceCount += counts[i];
    */
    /*
    for(ull i = 0; i < size; i++)
        cout << sequence[i] << ' ';
    cout << endl;
    for(ull i = 0; i < size; i++)
        cout << lengths[i] << ' ';
    cout << endl;
    for(ull i = 0; i < size; i++)
        cout << counts[i] << ' ';
    cout << endl;
    */
    return pair<ull, ull>(maxLength, subsequenceCount);
}


pair<ull, ull> findNumberAndLengthOfLIS2(vector<int>& seq){
    vector<pair<int, int>> dp;
    int longest = 1,
        current,
        count;

    for(ull i = 0; i < seq.size(); i++)
        dp.push_back(make_pair(1, 1));

    for(ull i = 0; i < seq.size(); i++) {
        current = 1;
        count = 0;
        for(ull j = 0; j < i; j++)
            if(seq[j] < seq[i])
                current = max(current, dp[j].first + 1);
        for(ull j = 0; j < i; j++)
            if(dp[j].first == current-1 && seq[j] < seq[i])
                count += dp[j].second;
        dp[i] = {current, max(count, dp[i].second)};
        longest = max(longest, current);
    }
    count = 0;
    for(ull i = 0; i < seq.size(); i++)
        if(dp[i].first == longest)
            count += dp[i].second;

    return pair<ull, ull>(longest, count);
}


ull findLengthOfLCIS(vector<int>& seq1, vector<int>& seq2) {
    vector<ull> lengths(seq2.size(), 0);
    ull currentLength, 
        maxLength = 0;
    
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
    result = findNumberAndLengthOfLIS1(&(sequence[0]), sequence.size());
    
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
