#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int T = 1;
const vector<int> P = {101, 37, 97};
const vector<int> M = {(int)1e9+7, (int)1e9+9, (int)998244353};

struct Hash { string s;
  vector<ll> h[T];
  vector<ll> ps[T];
  Hash(const string& _s): s(_s) {
    for(int t=0; t<T; t++) {
      h[t].resize(s.size() + 1);
      ps[t].resize(s.size() + 1, 1);
      for(int i=0; i<s.size(); i++) {
        h[t][i+1] = (h[t][i] * P[t] + s[i]) % M[t];
        ps[t][i+1] = ps[t][i] * P[t] % M[t];
      }
    }
  }
  int size() const {
    return (int)h[0].size() - 1;
  }
  vector<ll> get(int i, int len) const {
    vector<ll> out;
    for(int t=0; t<T; t++) {
      ll val = (h[t][i+len] - h[t][i] * ps[t][len]) % M[t];
      out.push_back(val < 0 ? val + M[t] : val);
    }
    return out;
  }
};

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  vector<Hash> dict;
  for(string s; cin >> s && s != "#"; ) {
    dict.emplace_back(s);
  }

  for(string s; cin >> s && s != "#"; ) {
    for(string t; s.back() != '|'; s += t) {
      cin >> t;
    }
    Hash val(s);
    vector<int> dp(s.size()+1);
    for(int i=1; i<=s.size(); i++) {
      dp[i] = dp[i-1];
      for(const auto& h : dict) {
        int len = h.size();
        if(len <= i && h.get(0, len) == val.get(i-len, len)) {
          dp[i] = max(dp[i], dp[i-len] + 1);
        }
      }
    }
    cout << dp.back() << nl;
  }

  return 0;
}
