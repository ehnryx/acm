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

  char s[1001];
  cin >> s;

  bitset<1001> fixed;
  int to = 0;
  int n = strlen(s);
  vector<pair<int,int>> ans;
  for (int c = 'a'; c <= 'z'; c++) {
    for (int i = 0; i < n; i++) {
      if (s[i] == c) {
        while (fixed[to]) {
          to++;
        }
        if (to == i) {
          fixed[to] = true;
        } else {
          ans.push_back(pair<int,int>(i+1, to+1));
          fixed[to] = true;
          swap(s[i], s[to]);
        }
      }
    }
  }

  for (int i = ans.size()-1; i >= 0; i--) {
    cout << ans[i].first << " " << ans[i].second << nl;
  }

  return 0;
}
