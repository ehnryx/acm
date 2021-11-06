#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/splay_tree.h"

const char nl = '\n';

const int INF = 0x3f3f3f3f;

const int N = 1e4+1;
const int M = 500+200+200+7;
const int offset = 205;
int dp[N][M][3]; // id, space, activated
splay_tree<splay_node<void, int>> price, weight, active;

void init() {
  memset(dp, -1, sizeof dp);
}

int solve(int id, int space, int ammo) {
  if (dp[id][space][ammo] != -1) return dp[id][space][ammo];
  if (id == 0) return space >= offset ? 0 : -INF;

  int res = solve(id-1, space, ammo);
  if (weight[id] <= space) {
    res = max(res, price[id] + solve(id-1, space-weight[id], ammo));
  }
  if (ammo > 0 && weight[id] <= space + active[id]) {
    res = max(res, price[id] + solve(id-1, space-weight[id]+active[id], ammo-1));
  }

  return dp[id][space][ammo] = res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
  init();

  int n, m;
  cin >> n >> m;
  price.root = splay_node<void, int>::nil;
  weight.root = splay_node<void, int>::nil;
  active.root = splay_node<void, int>::nil;
  for(int i=0; i<=n; i++) {
    price.push_back(0);
    weight.push_back(0);
    active.push_back(0);
  }
  for (int i=1; i<=n; i++) {
    cin >> price[i] >> weight[i] >> active[i];
  }

  cout << solve(n, m+offset, 2) << nl;

  return 0;
}
