#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, k;
  cin >> n >> k;
  vector<int> cnt(k);
  int base = 0;
  for(int i=0; i<n; i++) {
    int v;
    cin >> v;
    if(v % k == 0) {
      base += v / k - 1;
    } else {
      base += v / k;
      cnt[v % k]++;
    }
  }

  for(int i=1; i<k; i++) {
    int sub = min(cnt[i], cnt[k-i]);
    if(i == k-i) {
      cnt[i] -= (sub/2) * 2;
    } else {
      cnt[i] -= sub;
      cnt[k-i] -= sub;
    }
  }

  auto match = [&](auto&& self, int v, int i) -> bool {
    if(i == 0) return v == 0;
    if(cnt[i] and i <= v) {
      cnt[i]--;
      if(self(self, v - i, i)) {
        return true;
      }
      cnt[i]++;
    }
    return self(self, v, i-1);
  };

  map<vector<int>, int> have;
  have[vector(k, 0)] = 0;
  for(int i=1; i<k; i++) {
    while(cnt[i]--) {
      map<vector<int>, int> nxt;
      for(const auto& [vec, c] : have) {
        vector<int> v = vec;
        for(int j=1; i+j<k; j++) {
          if(v[j]) {
            v[j]--;
            v[i+j]++;
            nxt[v] = min(nxt[v], c);
            v[i+j]--;
            v[j]++;
          }
        }
        for(int j=k-i+1; j<k; j++) {
          if(v[j]) {
            v[j]--;
            v[i+j-k]++;
            nxt[v] = min(nxt[v], c - 1);
            v[i+j-k]--;
            v[j]++;
          }
        }
        if(v[k-i]) {
          v[k-i]--;
          nxt[v] = min(nxt[v], c);
          v[k-i]++;
        }
        v[i]++;
        nxt[v] = min(nxt[v], c);
      }
      swap(have, nxt);
    }
  }

  int ans = 0;
  for(const auto& [v, c] : have) {
    ans = max(ans, -c);
  }
  cout << base + ans << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
