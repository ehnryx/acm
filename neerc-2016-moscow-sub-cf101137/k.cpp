#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

ll ans = 0;
ll best = INFLL;

const int N = 3e5+1;
int root[N];
ll ppl[N], cost[N];

int find(int i) {
  if (root[i] == -1) return i;
  return root[i] = find(root[i]);
}

void link(int i, int j, ll c) {
  i = find(i); j = find(j);
  if (i == j) return;
  root[i] = j;
  ans -= ppl[j] * cost[j] + ppl[i] * cost[i];
  ppl[j] = max(c, max(ppl[j], ppl[i]));
  cost[j] = min(cost[j], cost[i]);
  ans += ppl[j] * cost[j];
  best = min(best, ans);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  memset(root, -1, sizeof root);

  int n, m;
  cin >> n >> m;

  for (int i=1; i<=n; i++) {
    cin >> ppl[i] >> cost[i];
    ans += cost[i] * ppl[i];
  }
  best = ans;

  for (int i=0; i<m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    link(a,b,c);
  }

  cout << best << nl;

  return 0;
}
