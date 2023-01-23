#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "string/suffix_array_lcp.h"

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
  string s;
  cin >> s;
  string all = s + s.substr(0, k);
  int m;
  cin >> m;
  for(int i=0; i<m; i++) {
    cin >> s;
    all += s;
    // start at (n+i)*k
  }
  suffix_array_lcp sa(all);

  set<int> have;
  for(int i=1; i<=m; i++) {
    have.insert(sa.rank[(n+i)*k]);
  }

  for(int o=0; o<k; o++) {
    vector<int> removed;
    for(int i=0; i<n; i++) {
      int at = o + i*k;
      int rat = sa.rank[at];
      auto it = have.lower_bound(rat);
      int len = sa.lcp(at, sa[*it]);
      if(len >= k) {
        removed.push_back(*it);
        have.erase(it);
      } else if(it != begin(have) && (len = sa.lcp(at, sa[*--it])) >= k) {
        removed.push_back(*it);
        have.erase(it);
      } else {
        break;
      }
    }
    if(size(removed) == n) {
      cout << "YES" << nl;
      for(int it : removed) {
        cout << sa[it] / k - n << " ";
      }
      return void(cout << nl);
    } else {
      have.insert(begin(removed), end(removed));
    }
  }

  cout << "NO" << nl;
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
