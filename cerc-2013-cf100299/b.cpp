#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while (T--) {
    string s, t;
    vector<string> query, line;
    unordered_set<string> taken;
    do {
      getline(cin, s);
    } while (s.size() == 0); 
    {
      istringstream in(s);
      while (in >> t) {
        query.push_back(t);
      }
    }

    while (true) {
      getline(cin, s);
      if (s.back() == '?') break;
      istringstream in(s);
      line.clear();
      while (in >> t) {
        line.push_back(t);
      }
      taken.insert(line[2]);
    }

    for (const string& it : query) {
      if (!taken.count(it)) cout << it << " ";
    }
    cout << nl;
  }

  return 0;
}
