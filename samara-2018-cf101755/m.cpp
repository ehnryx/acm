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

  string s[3];
  for (int x = 0; x < 3; x++) cin >> s[x];
  int n = s[0].size();

  unordered_set<int> bad;
  for (int x = 0; x < 3; x++) {
    for (int i = 0; i < n; i++) {
      if (s[x][i] != s[(x+1)%3][i]) {
        bad.insert(i);
      }
    }
  }

  if (bad.size() > 3) {
    cout << "Impossible" << nl;
  }
  else if (bad.size() <= 1) {
    cout << "Ambiguous" << nl;
  }
  else {
    vector<int> id;
    for (int i : bad) id.push_back(i);
    unordered_set<string> good;
    string t;
    int j[3], res[3];
    for (j[0] = 0; j[0] < 3; j[0]++) {
      for (j[1] = 0; j[1] < 3; j[1]++) {
        for (j[2] = 0; j[2] < 3; j[2]++) {
          t = s[0];
          for (int i = 0; i < id.size(); i++) {
            t[id[i]] = s[j[i]][id[i]];
          }
          memset(res, 0, sizeof res);
          for (int x = 0; x < 3; x++) {
            for (int i = 0; i < n; i++) {
              if (s[x][i] != t[i]) res[x]++;
            }
          }
          if (res[0] <= 1 && res[1] <= 1 && res[2] <= 1) {
            good.insert(t);
          }
        }
      }
    }

    if (good.empty()) cout << "Impossible" << nl;
    else if (good.size() == 1) cout << *good.begin() << nl;
    else cout << "Ambiguous" << nl;
  }

  return 0;
}
