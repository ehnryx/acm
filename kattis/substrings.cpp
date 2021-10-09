//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<int> vi;
typedef pair<int,int> pii;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace SuffixArray {
  const int L = 17; const int N = 1<<L; const int A = 1e9+7;
  int p[L+1][N]; pair<ll,int> m[N]; int last, n;
  void build(const string& s) { n = s.size();
    if(n <= 1) { p[0][0] = last = 0; return; }
    for (int i = 0; i < n; i++) p[0][i] = s[i];
    for (int j = 1, v = 1; j < n; j *= 2, v++) {
      for (int i = 0; i < n; i++) {
        m[i] = { (ll)p[v-1][i] * A + (i+j<n ? p[v-1][i+j] : -1), i };
      } sort(m, m+n);
      for (int i = 0; i < n; i++) {
        p[v][m[i].second] = (i > 0 && m[i].first == m[i-1].first) ?
          p[v][m[i-1].second] : i; } last = v; } }
  int* idx() { return p[last]; }
  int lcp(int i, int j) {
    int len = 0; if (i == j) return n - i;
    for (int k = last; k >= 0 && i < n && j < n; k--)
      if (p[k][i] == p[k][j]) { i += 1<<k; j += 1<<k; len += 1<<k; }
    return len; }
}

const int N = 1e5 + 1;
int rev[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while(T--) {
    string s;
    cin >> s;
    int n = s.size();
    SuffixArray::build(s);
    int* idx = SuffixArray::idx();
    for(int i=0; i<n; i++) {
      rev[idx[i]] = i;
    }
    ll ans = 0;
    int cur = 0;
    for(int i=1; i<n; i++) {
      int nxt = SuffixArray::lcp(rev[i], rev[i-1]);
      if(nxt > cur) ans += nxt - cur;
      cur = nxt;
    }
    cout << ans << nl;
  }

  return 0;
}
