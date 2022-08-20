#include <bits/stdc++.h>
using namespace std;

%:include "utility/defines.h"
%:include "utility/fast_input.h"
%:include "utility/output.h"
//%:include "ds/segment_tree.h"
//%:include "ds/segment_tree_nodes_bitwise.h"
%:include "ds/rmq.h"

using ll = unsigned long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

//struct node : segment_node::custom_update_range_and<ll> {
//  using base = segment_node::custom_update_range_and<ll>;
//  using base::base;
//  bool contains(ll x, ll& have) {
//    if((have & value) < x) return true;
//    have &= value;
//    return false;
//  }
//};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n;
  ll x;
  cin >> n >> x;
  auto a = cin.read<ll>(n);
  if(*min_element(begin(a), end(a)) < x) {
    cout << -1 << nl;
    return 0;
  }

  rmq_functional<ll, std::bit_and<ll>> rmq(a);
  //segment_tree<node> st(a);
  vector<int> len(n);
  for(int i=0; i<n; i++) {
    //int r = st.search_left(i, n-1, x, ~0ull);
    //len[i] = (r == n ? n : r - i);
    int l = i + 1;
    int r = n;
    while(l < r) {
      int m = (l+r + 1) / 2;
      if(rmq.query(i, m) < x) {
        r = m - 1;
      } else {
        l = m;
      }
    }
    len[i] = (r == n ? n : r - i);
  }

  for(int k=n; k>0; k--) {
    int at = 0;
    while(at < n) {
      if(len[at] < k) break;
      at += k;
    }
    if(at >= n) {
      cout << k << nl;
      return 0;
    }
  }

  assert(false);

  return 0;
}
