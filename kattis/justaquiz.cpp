#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"

using ll = long long;
using ld = double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct node {
  unordered_map<string, node*> to;
  unordered_map<string, int> leaf;
  int total = 0;
  int big = 0;
};

node* add(node* u, const vector<string>& s, int i) {
  if(i+1 < s.size()) {
    if(auto v = u->to.find(s[i]); v != u->to.end()) {
      add(v->second, s, i+1);
    } else {
      u->to[s[i]] = add(new node(), s, i+1);
    }
  }
  u->leaf[s.back()]++;
  return u;
}

void build(node* u) {
  for(const auto& [_, c] : u->leaf) {
    u->big = max(u->big, c);
    u->total += c;
  }
  for(const auto& [_, v] : u->to) {
    build(v);
  }
}

ld solve(node* u, int t, auto& dp, node* root) {
  if(t == 0) return 0;
  if(dp[t].count(u)) return dp[t][u];

  ld guess = (ld)u->big / u->total + solve(root, t - 1, dp, root);
  ld listen = 0;
  for(const auto& [_, v] : u->to) {
    listen += solve(v, t - 1, dp, root) * v->total;
  }
  listen /= u->total;

  return dp[t][u] = max(guess, listen);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int t, n;
  cin >> t >> n;
  node* root = new node();
  for(int i=0; i<n; i++) {
    istringstream in(cin.getline());
    vector<string> all;
    for(string s; in >> s; ) {
      all.push_back(s);
    }
    add(root, all, 0);
  }
  build(root);

  vector<unordered_map<node*, ld>> dp(t+1);
  cout << solve(root, t, dp, root) << nl;

  return 0;
}
