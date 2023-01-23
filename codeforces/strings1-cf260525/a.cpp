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

struct node {
  int cnt = 0;
  node* child[2] = {};
  node* add(int bit) {
    if(not child[bit]) child[bit] = new node;
    child[bit]->cnt++;
    return child[bit];
  }
  node* sub(int bit) {
    assert(child[bit]);
    node* to = child[bit];
    if(--to->cnt == 0) {
      child[bit] = nullptr;
    }
    return to;
  }
  pair<node*, int> query(int bit) {
    if(child[bit^1]) {
      return pair(child[bit^1], 1);
    } else {
      assert(child[bit]);
      return pair(child[bit], 0);
    }
  }
};

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int q;
  cin >> q;
  node* root = [] {
    node* r = new node;
    node* u = r;
    for(int i=30; i>=0; i--) {
      u = u->add(0);
    }
    return r;
  }();

  static constexpr int L = 30;
  while(q--) {
    char query; int v;
    cin >> query >> v;
    node* at = root;
    if(query == '+') {
      for(int i=L-1; i>=0; i--) {
        at = at->add(v>>i & 1);
      }
    } else if(query == '-') {
      for(int i=L-1; i>=0; i--) {
        at = at->sub(v>>i & 1);
      }
    } else {
      int ans = 0;
      for(int i=L-1; i>=0; i--) {
        auto [nxt, bit] = at->query(v>>i & 1);
        ans |= bit<<i;
        at = nxt;
      }
      cout << ans << nl;
    }
  }
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
