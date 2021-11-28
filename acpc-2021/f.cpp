#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct segment_tree {
  static constexpr int N = 1 << 17;
  vector<int> st;
  segment_tree(): st(2*N, numeric_limits<int>::max()) {}
  void insert(int i, int v) {
    i += N;
    st[i] = min(st[i], v);
    for(i/=2; i; i/=2) {
      st[i] = min(st[2*i], st[2*i+1]);
    }
  }
  int query(int l, int r) {
    int res = numeric_limits<int>::max();
    for(l+=N, r+=N+1; l<r; l/=2, r/=2) {
      if(l&1) res = min(res, st[l++]);
      if(r&1) res = min(res, st[--r]);
    }
    return res;
  }
};

// get s for mode 1
int get_mode1(int n) {
  if(n == 0) return 0;
  return 32 - __builtin_clz(n);
}

// get s for mode 2
int get_mode2(int n) {
  if(n == 0) return 0;
  if(n == -1) return 1;
  if(n > 0) return 33 - __builtin_clz(n);
  return 33 - __builtin_clz(-n - 1);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n, c;
  cin >> n >> c;
  vector<int> a(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }

  // dp[i] = min bits required to compress the first i elements
  // transition: dp[i] = min_{j<i} dp[j] + c + (i-j)*s
  //                   = c + i*s + min_{j<i} dp[j] - j*s
  // suppose we fix s, then we're done if we can query for a
  // range min on dp[j] - j*s. eg. by using a segment tree
  vector<int> dp(n+1, numeric_limits<int>::max());

  // Then we need to figure out what the range for each s is.
  // ie. the window (j, i] must be able to be encoded with s
  // Here we store the pair (s, r) to represent the rightmost
  // point so that [r, i] requires at least s bits to encode
  vector mode(2, vector<pair<int, int>>(1, pair(1789, 0)));

  // we may use 0-31 bits for encoding. ie. s \in [0,32)
  // The segment trees store a range min of dp
  static const int M = 32;
  vector<segment_tree> st(M);
  for(int s=0; s<M; s++) {
    st[s].insert(0, 0);
  }

  for(int i=1; i<=n; i++) {
    // mode 0 (0 <= x < 2^s)
    {
      int cur_s = get_mode1(a[i]);
      while(cur_s >= mode[0].back().first) {
        mode[0].pop_back();
      }
      mode[0].emplace_back(cur_s, i);
      for(int j=1; j<size(mode[0]); j++) {
        int s = mode[0][j].first;
        dp[i] = min(dp[i], c + i*s + st[s].query(mode[0][j-1].second, i-1));
      }
    }

    // mode 1 (2^{s-1} <= dx < 2^{s-1})
    {
      int da = a[i] - a[i-1];
      int cur_s = get_mode2(da);
      while(cur_s >= mode[1].back().first) {
        mode[1].pop_back();
      }
      mode[1].emplace_back(cur_s, i);
      for(int j=1; j<size(mode[1]); j++) {
        int s = mode[1][j].first;
        dp[i] = min(dp[i], c + i*s + st[s].query(mode[1][j-1].second, i-1));
      }
    }

    // update each segment tree with dp
    for(int s=0; s<M; s++) {
      st[s].insert(i, dp[i] - i*s);
    }
  }

  cout << dp[n] << nl;

  return 0;
}
