#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

#define nl '\n'

const set<string> delim = {".", ",", ":", ";", "?", "!"};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, tt = 1;
  while (cin >> n) {
    cout << "Learning case " << tt++ << nl;
    unordered_map<string, int> id;
    set<vector<int>> learned;
    int curid = 0;
    id["joe"] = curid++;
    learned.insert({0});
    string s;
    vector<int> sentence;
    while (cin >> s) {
      if (delim.count(s) || s == "*") {
        for (int i = 1; i <= n; i++) {
          for (int j = 0; j+i <= sentence.size(); j++) {
            vector<int> cur;
            for (int k = 0; k < i; k++) {
              cur.push_back(sentence[j+k]);
            }
            learned.insert(cur);
          }
        }
        sentence = {};
        if (s == "*") break;
        continue;
      }
      for (char& c : s) {
        c = tolower(c);
      }
      if (!id.count(s)) {
        id[s] = curid++;
      }
      sentence.push_back(id[s]);
    }
    string dumb;
    while (cin >> s) {
      if (delim.count(s) || s == "#") {
        //cerr << "CHECK " << dumb << nl;
        bool shit = 0;
        for (int i = 1; i <= n; i++) {
          for (int j = 0; j+i <= sentence.size(); j++) {
            vector<int> cur;
            for (int k = 0; k < i; k++) {
              cur.push_back(sentence[j+k]);
            }
            //for (int i : cur) cerr << i << " "; cerr << nl;
            if (!learned.count(cur)) {
              shit = 1;
            }
            learned.insert(cur);
          }
        }
        if (shit && sentence.size() > 1) {
          dumb.pop_back();
          cout << "What does the sentence \"" << dumb << "\" mean?\n";
        }
        sentence = {};
        dumb = "";
        if (s == "#") break;
        continue;
      }
      string ss = s;
      for (char& c : s) {
        c = tolower(c);
      }
      if (!id.count(s)) {
        cout << "What does the word \"" << ss << "\" mean?\n";
        id[s] = curid++;
      }
      dumb += ss + ' ';
      sentence.push_back(id[s]);
    }
    cout << nl;
  }

  return 0;
}
