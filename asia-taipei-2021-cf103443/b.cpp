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

struct Result {
  int res, l, r;
  bool operator < (const Result& o) const {
    if(res != o.res) return res < o.res;
    if(size() != o.size()) return size() > o.size();
    return l > o.l;
  }
  int size() const { return r - l; }
  friend ostream& operator << (ostream& os, const Result& v) {
    return os << v.res << " " << v.l << " " << v.r;
  }
};

#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  string s, t;
  cin >> s >> t;
  vector<int> same(n);
  for(int i=0; i<n; i++) {
    same[i] = (s[i] == t[i]);
  }
  partial_sum(begin(same), end(same), begin(same));

  auto ans = Result(same.back(), 1, 1);
  for(int mid=0; mid<n; mid++) {
    // odd center
    {
      int cur = same.back();
      for(int r=1; 0 <= mid-r && mid+r < n; r++) {
        cur -= (s[mid-r] == t[mid-r]) + (s[mid+r] == t[mid+r]);
        cur += (s[mid-r] == t[mid+r]) + (s[mid+r] == t[mid-r]);
        ans = max(ans, Result(cur, mid-r + 1, mid+r + 1));
      }
    }
    // even center
    {
      int cur = same.back();
      for(int r=0; 0<=mid-r && mid+1+r < n; r++) {
        cur -= (s[mid-r] == t[mid-r]) + (s[mid+1+r] == t[mid+1+r]);
        cur += (s[mid-r] == t[mid+1+r]) + (s[mid+1+r] == t[mid-r]);
        ans = max(ans, Result(cur, mid-r + 1, mid+1+r + 1));
      }
    }
  }

  cout << same.back() << " " << ans << nl;
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
