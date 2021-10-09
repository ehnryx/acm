#include <bits/stdc++.h>
using namespace std;

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
const int N = 1 << 19;

ll segt[2*N];
void put(int x, ll v) {
  segt[x+N] = max(segt[x+N], v);
  for (x += N; x > 1; x /= 2) {
    segt[x/2] = max(segt[x], segt[x^1]);
  }
}
ll query(int l, int r) {
  ll ans = 0;
  for (l += N, r += N+1; l < r; l /= 2, r /= 2) {
    if (l%2) ans = max(ans, segt[l++]);
    if (r%2) ans = max(ans, segt[--r]);
  }
  return ans;
}

int c[N], d[N];
vector<pair<int, int>> rght[N], down[N];

ll ans[N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  int n; cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> c[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> d[i];
  }
  auto in = [&](int x) {
    return x >= 1 && x <= n;
  };
  for (int i = 1; i <= n; i++) {
    if (in(c[i] + i - 1) && in(i+1)) rght[i+1].emplace_back(c[i] + i - 1, d[i]);
    //down[c[i] + i - 1].emplace_back(i, d[i]);
    if (in(i - c[i] + 1)) down[i - c[i] + 1].emplace_back(i, d[i]);
    //rght[i].emplace_back(c[i] + i - 1, d[i]);
  }
  for (int i = 1; i <= n; i++) {
    sort(down[i].rbegin(), down[i].rend());
    sort(rght[i].begin(), rght[i].end());
  }
  for (int i = 1; i <= n; i++) {
    cerr << "x = " << i << nl;
    for (const auto& p : rght[i]) {
      cerr << "right " << p.first << " " << p.second << nl;
      ll x = query(p.first, n);
      put(p.first, x + p.second);
    }
    for (const auto& p : down[i]) {
      cerr << "down " << p.first << " " << p.second << nl;
      ll x = query(p.first+1, n);
      put(p.first, x + p.second);
    }
    cout << query(i, n) << " ";
  }
  cout << nl;
  return 0;
}
