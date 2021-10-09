//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace SuffixArray {
  const int L = 17; const int N = 1<<L; const int A = 1e9+7;
  int p[L+1][N]; pair<ll,int> m[N]; int last, n;
  /// replace pair<ll,int> ^here with pair<pair<int,int>,int> for 32-bit
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
    for (int k = last; k >= 0 && i < n && j < n; k--) {
      if (p[k][i] == p[k][j]) { i += 1<<k; j += 1<<k; len += 1<<k; }
    } return len; }
}

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  string s;
  cin >> s;
  int n = s.size();
  SuffixArray::build(s);
  vector<ll> ans(n);

  vector<int> idx(n), rev(n);
  for(int i=0; i<n; i++) {
    idx[i] = SuffixArray::idx()[i];
    rev[idx[i]] = i;
  }

  int m, k;
  cin >> m >> k;

  ll curAns = 0;
  set<int> active;
  vector<unordered_set<int>> to_remove(n);
  vector<int> start(n, -1);

  function<int(set<int>::iterator,int)> get_value = [&](set<int>::iterator it, int r) {
    if(it == active.end()) return 0;
    if(it == active.begin()) return r - rev[*it];
    int i = rev[*it];
    int j = rev[*prev(it)];
    int lcp = SuffixArray::lcp(i, j);
    assert(i + lcp <= r);
    return r - (i+lcp);
  };

  function<void(set<int>::iterator)> update_start = [&](set<int>::iterator it) {
    int i = rev[*it];
    if(start[i] != -1) {
      to_remove[start[i]].erase(i);
    }

    start[i] = i;
    if(it != active.begin()) {
      int j = rev[*prev(it)];
      start[i] = max(start[i], i + SuffixArray::lcp(i, j));
    }
    if(next(it) != active.end()) {
      int j = rev[*next(it)];
      start[i] = max(start[i], i + SuffixArray::lcp(i, j));
    }
    to_remove[start[i]].insert(i);
  };

  auto remove_suffix = [&](set<int>::iterator it, int r) {
    int i = rev[*it];
    curAns -= get_value(it, r);
    curAns -= get_value(next(it), r);
    it = active.erase(it);
    curAns += get_value(it, r);

    to_remove[start[i]].erase(i);
    if(it != active.begin()) {
      update_start(prev(it));
    }
    if(it != active.end()) {
      update_start(it);
    }
    return it;
  };

  function<void(int)> add_suffix = [&](int i) {
    int r = min(i+k, n);
    set<int>::iterator it = active.lower_bound(idx[i]);
    if(it != active.end()) {
      int j = rev[*it];
      int lcp = SuffixArray::lcp(i, j);
      if(j + lcp >= r) {
        it = remove_suffix(it, r);
      }
    }
    if(it != active.begin()) {
      int j = rev[*prev(it)];
      int lcp = SuffixArray::lcp(i, j);
      if(j + lcp >= r) {
        it = remove_suffix(prev(it), r);
      }
    }

    curAns -= get_value(it, r);
    it = active.insert(idx[i]).first;
    curAns += get_value(it, r);
    curAns += get_value(next(it), r);

    if(it != active.begin()) {
      update_start(prev(it));
    }
    if(next(it) != active.end()) {
      update_start(next(it));
    }
    update_start(it);
  };

  function<void(int)> shift_to = [&](int i) {
    if(i+k >= n) return;
    curAns -= active.size();
    while(!to_remove[i+k].empty()) {
      int j = *to_remove[i+k].begin();
      remove_suffix(active.find(idx[j]), i+k);
    }
  };

  for(int i=1; i<=n; i++) {
    shift_to(n-i);
    add_suffix(n-i);
    if(i >= k) {
      ans[n-i+1] = curAns;
    }
  }

  for(int i=0; i<m; i++) {
    int v;
    cin >> v;
    cout << ans[v] << nl;
  }

  return 0;
}
