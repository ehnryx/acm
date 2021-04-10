//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "abbreviation"

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

bool is_capital(const string& s) {
  if(s.size() == 1) return false;
  for(int i=0; i<s.size(); i++) {
    if(!isalpha(s[i])) return false;
    if(i == 0 && !isupper(s[i])) return false;
    if(i > 0 && !islower(s[i])) return false;
  }
  return true;
}

string abbreviate(const vector<string>& g) {
  string res;
  for(int i=(int)g.size()-1; i>=0; i-=2) {
    res.push_back(g[i][0]);
  }
  return res;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  for(string line; getline(cin, line); ) {
    string word;
    vector<string> tokens;
    for(char c : line) {
      if(isalpha(c)) {
        word.push_back(c);
      } else {
        if(!word.empty()) tokens.push_back(word);
        tokens.push_back(string(1, c));
        word.clear();
      }
    }
    if(!word.empty()) {
      tokens.push_back(word);
    }

    reverse(tokens.begin(), tokens.end());
    vector<string> ans, group;
    for(const string& s : tokens) {
      //cerr << "AT " << s << nl;
      if(s == " " && group.size() % 2 == 1) {
        //cerr << "push space to gruop" << nl;
        group.push_back(s);
      } else if(is_capital(s)) {
        //cerr << "push word to group" << nl;
        group.push_back(s);
      } else {
        if(group.size() >= 3) {
          string last = (group.size() % 2 ? "" : group.back());
          if(group.size() % 2 == 0) group.pop_back();
          ans.push_back(")");
          ans.insert(ans.end(), group.begin(), group.end());
          ans.push_back("(");
          ans.push_back(" ");
          ans.push_back(abbreviate(group));
          ans.push_back(last);
          //cerr << "abrer" << nl;
        } else if(!group.empty()) {
          ans.insert(ans.end(), group.begin(), group.end());
          //cerr << "dump" << nl;
        }
        ans.push_back(s);
        group.clear();
      }
    }
    if(group.size() >= 3) {
      string last = (group.size() % 2 ? "" : group.back());
      if(group.size() % 2 == 0) group.pop_back();
      ans.push_back(")");
      ans.insert(ans.end(), group.begin(), group.end());
      ans.push_back("(");
      ans.push_back(" ");
      ans.push_back(abbreviate(group));
      ans.push_back(last);
    } else if(!group.empty()) {
      ans.insert(ans.end(), group.begin(), group.end());
    }

    reverse(ans.begin(), ans.end());
    for(const string& s : ans) {
      cout << s;
    }
    cout << nl;
  }

  return 0;
}
