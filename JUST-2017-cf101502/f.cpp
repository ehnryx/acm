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

const int N = 1e5+1;
int freq[N];
void insert(int x, int cnt) {
  for ( ; x<N; x+=x&-x)
    freq[x] += cnt;
}
int query(int x) {
  int res = 0;
  for ( ; x>0; x-=x&-x)
    res += freq[x];
  return res;
}
int query(int xl, int xr) {
  return query(xr) - query(xl-1);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while (T--) {
    memset(freq, 0, sizeof freq);

    int n, q;
    cin >> n >> q;

    ll a;
    for (int i=1; i<=n; i++) {
      cin >> a;
      insert(i, __builtin_popcountll(a)-1 + 63-__builtin_clzll(a));
    }

    int l, r;
    while (q--) {
      cin >> l >> r;
      cout << query(l, r) << nl;
    }
  }

  return 0;
}
