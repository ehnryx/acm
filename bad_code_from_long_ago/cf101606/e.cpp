#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
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

  int n, m;
  cin >> n >> m;

  set<pii> s;
  int c[m];
  pii r[m];

  for (int i = 0; i < n; i++) {
    int temp;
    cin >> temp;
    s.insert(pii(temp, i));
  }
  for (int i = 0; i < m; i++) {
    cin >> c[i];
  }
  for (int i = 0; i < m; i++) {
    cin >> r[i].first;
    r[i].second = i;
  }
  sort(r, r+m);

  int cnt = 0;
  int ans[n];
  for (int i = 0; i < m; i++) {
    auto it = s.upper_bound(pii(c[r[i].second], INF));
    if (it == s.begin()) {
      continue;
    }
    it = prev(it);
    ans[it->second] = r[i].second+1;
    s.erase(it);
    cnt++;
    if (cnt == n) {
      break;
    }
  }

  if (cnt < n) {
    cout << "impossible" << nl;
  }
  else {
    for (int i = 0; i < n; i++) {
      cout << ans[i] << " ";
    }
    cout << nl;
  }

  return 0;
}
