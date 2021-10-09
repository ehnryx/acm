#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int a;

  vector<int> b;
  while (cin >> a) {
    b.pb(a);
  }
  int preans = -1;
  int ans = 0;
  set<vector<int>> s;
  s.insert(b);
  for (;;) {
    int j = -1;
    int m = -1;
    int n = b.size();
    for (int i = 0; i < b.size(); i++) {
      if (b[i] > m) {
        j = i;
        m = b[i];
      }
    }
    int id = j+1;
    int cc = b[j];
    for (int c = b[j]; c > 0; c--) {
      b[id%n]++;
      id++;
    }
    b[j] -= cc;
    ans++;
    if (s.count(b)) {
      bool quit = false;
      if (preans != -1) quit = true;
      cout << ans - preans << endl;
      preans = ans;
      cout << preans << endl << endl;
      s.clear();
      if (quit) break;
    }
    s.insert(b);
  }

  return 0;
}
