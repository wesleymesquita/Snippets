#include <bits/stdc++.h>

using namespace std;
class trie;

class trie{
    int n_leaf; // how many leaf there is from this node
    map<char, trie> pref;
public:
    trie(): n_leaf{0}{}

    void add(const string& s, int i){
        
        if(i == s.size()) return;

        if(pref.find(s[i]) == pref.end())
            pref[s[i]] = trie{};
        
        pref[s[i]].add(s, i+1);       
        pref[s[i]].n_leaf++;
    }
    void find(const string& p, int i, int& count){
        if(i < p.size()) {
            if(pref.find(p[i]) == pref.end()) return;
            pref[p[i]].find(p, i+1, count);
        }else{
            count += n_leaf;
        }
    }
};
/*
 * Complete the contacts function below.
 */
vector<int> contacts(vector<vector<string>> queries) {

    trie t{};
    vector<int> r;
    for(auto& q : queries) {
        if (q[0] == "add") {
            // add
            t.add(q[1], 0);
        }else {
            int count=0;
            t.find(q[1], 0, count);
            r.push_back(count);
        }
    }
    return r;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int queries_rows;
    cin >> queries_rows;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<string>> queries(queries_rows);
    for (int queries_row_itr = 0; queries_row_itr < queries_rows; queries_row_itr++) {
        queries[queries_row_itr].resize(2);

        for (int queries_column_itr = 0; queries_column_itr < 2; queries_column_itr++) {
            cin >> queries[queries_row_itr][queries_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<int> result = contacts(queries);

    for (int result_itr = 0; result_itr < result.size(); result_itr++) {
        fout << result[result_itr];

        if (result_itr != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

