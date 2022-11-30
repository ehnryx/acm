#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "string/suffix_array_lcp.h"
%:include "ds/segment_tree.h"
%:include "ds/segment_tree_nodes_min.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


using segtree = segment_tree<segment_node::custom_update_range_min<int>>;

#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  string s;
  cin >> s;

  // for correct brackets
  vector<int> heights(n + 1);
  for(int i=0; i<n; i++) {
    heights[i+1] = heights[i] + (s[i] == '(' ? 1 : -1);
  }
  segtree st(heights);

  auto correct = [&](int i, int len) -> bool {
    return heights[i] == heights[i+len] && st.query(i, i+len) == heights[i];
  };

  // for palindromes
  string rev_s(rbegin(s), rend(s));
  suffix_array_lcp sa(s + rev_s);

  auto palindrome = [&](int i, int len) -> bool {
    int lmid = i + len / 2 - 1;
    int rmid = i + (len+1) / 2;
    return sa.lcp(rmid, 2*n - 1 - lmid) >= len/2;
  };


  int cnt = 0;
  int at = 0;
  while(true) {
    bool found = false;
    for(int len=2; len<=n-at; len++) {
      if(palindrome(at, len) || correct(at, len)) {
        at += len;
        found = true;
        break;
      }
    }
    if(!found) {
      break;
    }
    cnt++;
  }

  cout << cnt << " " << n - at << nl;
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
