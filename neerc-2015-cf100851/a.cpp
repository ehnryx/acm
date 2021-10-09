#include <bits/stdc++.h>
using namespace std;
#define FILENAME "adjustment"

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, q;
  cin >> n >> q;

  ll rowsum, colsum;
  rowsum = colsum = (ll)n*(n+1)/2;

  set<int> deadrow, deadcol;

  for (int i=0; i<q; i++) {
    char c; int v;
    cin >> c >> v;

    if (c == 'R') {
      if (deadrow.count(v)) {
        cout << 0 << nl;
      } else {
        cout << colsum + (ll)v*(n-deadcol.size()) << nl;
        deadrow.insert(v);
        rowsum -= v;
      }
    } else {
      if (deadcol.count(v)) {
        cout << 0 << nl;
      } else {
        cout << rowsum + (ll)v*(n-deadrow.size()) << nl;
        deadcol.insert(v);
        colsum -= v;
      }
    }
  }

  return 0;
}
