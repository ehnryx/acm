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

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace SuffixArray {
  const int L = 18; const int N = 1<<L; const int A = 1e9+7;
  int p[L+1][N]; pair<ll,int> m[N]; int last, n;
  void build(const string& s) { n = s.size();
    if(n <= 1) { p[0][0] = last = 0; return; }
    for(int i=0; i<n; i++) p[0][i] = s[i];
    for(int j=1, v=1; j<n; j*=2, v++) {
      for(int i=0; i<n; i++) {
        m[i] = {(ll)p[v-1][i] * A + (i+j<n ? p[v-1][i+j] : -1), i};
      } sort(m, m+n);
      for(int i=0; i<n; i++) {
        p[v][m[i].second] = (i > 0 && m[i].first == m[i-1].first) ?
            p[v][m[i-1].second] : i; } last = v; } }
  int* idx() { return p[last]; }
  int lcp(int i, int j) {
    int len = 0; if(i==j) return n-i;
    for(int k=last; k>=0 && i<n && j<n; k--) {
      if(p[k][i] == p[k][j]) { i+=1<<k; j+=1<<k; len+=1<<k; }
    } return len;
  }
}

const int N = SuffixArray::N;
int rev[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while(T--) {
    string s, t;
    cin >> s >> t;
    int n = s.size();
    int m = t.size();
    SuffixArray::build(s+t);
    int* idx = SuffixArray::idx();
    for(int i=0; i<n+m; i++) {
      rev[idx[i]] = i;
    }

    ll ans = 0;
    set<int> seen;
    for(int i=n-1; i>=0; i--) {
      int lb = n-i;
      auto it = seen.lower_bound(idx[i]);
      if(it != seen.end()) {
        lb = max(lb, SuffixArray::lcp(i, rev[*it]));
      }
      if(it != seen.begin()) {
        lb = max(lb, SuffixArray::lcp(i, rev[*prev(it)]));
      }
      seen.insert(idx[i]);
      ans += n+m-i - lb;
    }
    cout << ans << nl;
  }

  return 0;
}
