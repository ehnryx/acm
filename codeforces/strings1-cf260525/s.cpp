//#pragma GCC optimize("O3")
//#pragma GCC target("tune=native")

#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "utility/output.h"

%:include "string/suffix_array_lcp_linear.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  string s;
  cin >> s;
  //cerr << clock() << " INPUT" << endl;
  int n = size(s);
  string all = s;
  all.push_back(' ');
  all.insert(end(all), rbegin(s), rend(s));
  all.push_back(' ');
  //cerr << clock() << " build all" << endl;
  suffix_array_lcp_linear sa(all);
  //cerr << clock() << " build sa" << endl;
  rmq_linear rank(sa.rank);
  //cerr << clock() << " build rank" << endl;

  int k;
  cin >> k;
  if(k == 1) {
    if(sa.rank[n+1] < sa.rank[0]) {
      reverse(begin(s), end(s));
    }
    return void(cout << s << nl);
  }

  //cerr << clock() << " start loop" << endl;
  int at = 0;
  bool last_inc = false;
  while(at < n) {
    int best_rank = rank.query(n+1, n+n - at);
    int idx = 2*n - sa[best_rank];
    int len = idx - at + 1;
    if(best_rank < sa.rank[at] and sa.lcp(at, sa[best_rank]) < len) {
      if(k == 2) break;
      while(idx + len < n and sa.lcp(at, idx + 1) >= len) {
        idx += len;
      }
      last_inc = false;
      k--;
      cout << all.substr(2*n - idx, idx - at + 1);
      at = idx + 1;
    } else {
      if(not last_inc) {
        if(k == 2) break;
        last_inc = true;
        k--;
      }
      cout << s[at];
      at++;
    }
  }
  //cerr << clock() << " done loop" << endl;
  if(at == n) {
    return void(cout << nl);
  }

  auto left = pair(0, 0);
  auto right = pair(min(sa.rank[at], sa.rank[n+1]), n - at);
  for(int i=at+1; i<n; i++) {
    auto cl = pair(min(sa.rank[at], sa.rank[2*n-i+1]), i - at);
    auto cr = pair(min(sa.rank[i], sa.rank[n+1]), n - i);
    if(sa.lcp(sa[left.first], sa[cl.first]) < left.second) {
      if(cl.first < left.first) {
        left = cl;
        right = cr;
      }
    } else if(sa.lcp(sa[right.first], sa[cl.first] + left.second) < cl.second - left.second) {
      if(sa.rank[sa[cl.first] + left.second] < right.first) {
        left = cl;
        right = cr;
      }
    } else {
      if(cr.first < sa.rank[sa[right.first] + cl.second - left.second]) {
        left = cl;
        right = cr;
      }
    }
  }
  //cerr << clock() << " done two" << endl;

  if(left.second) {
    cout << all.substr(sa[left.first], left.second);
  }
  cout << all.substr(sa[right.first], right.second);
  cout << nl;
  //cerr << clock() << " done output" << endl;
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
