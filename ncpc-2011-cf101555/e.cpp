#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  string s;
  cin >> s;
  s.insert(0,"?");
  s.push_back('?');

  vector<string> p;
  string cur;
  int cnt = 0;
  for (char c : s) {
    if (c == '*') {
      cnt++;
      if (!cur.empty()) {
        p.push_back(cur);
        cur.clear();
      }
    }
    else {
      cur.push_back(c);
    }
  }

  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    string t, r;
    cin >> t;
    r = t;
    t.insert(0,"?");
    t.push_back('?');

    int j = 0;
    bool good = true;
    for (const string& m : p) {
      int len = m.size();
      bool bad = true;
      while (j+len < t.size()) {
        if (t.substr(j, len) != m) j++;
        else {
          cerr << "match @ " << j << nl;
          j += len;
          bad = false;
          break;
        }
      }
      if (bad) {
        good = false;
        break;
      }
    }

    if (good) {
      if (cnt == 0 && s != t) continue;
    }
  }

  return 0;
}
