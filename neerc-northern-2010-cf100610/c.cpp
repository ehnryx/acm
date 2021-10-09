#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
typedef long long ll;
typedef long double ld;
const int INF = 0x3f3f3f3f;
const char nl = '\n';

#define FILE "commuting"

const int N = 2e5+1;

int dsu[N], sz[N];
int find(int i) {
  if(dsu[i] == -1) return i;
  return dsu[i] = find(dsu[i]);
}
void link(int i, int j) {
  i = find(i); j = find(j);
  if(i == j) return;
  dsu[i] = j;
  sz[j] += sz[i];
}

vector<int> vals[N];
int seen[N];
int a[N], ans[N];

int main() {
  if (fopen(FILE ".in", "r")) {
    freopen(FILE ".in", "r", stdin);
    freopen(FILE ".out", "w", stdout);
  }

  int n;
  cin >> n;

  memset(dsu, -1, sizeof dsu);
  fill(sz, sz+N, 1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
    link(i, a[i]);
  }

  for(int i=1; i<=n; i++) {
    int s = sz[find(i)];
    int minv = INF;
    for(int d=1; d*d<=s; d++) {
      if(s%d) continue;
      if(seen[d]) minv = min(minv, seen[d]);
      if(seen[s/d]) minv = min(minv, seen[s/d]);
    }
    if(minv < INF) {
      if(seen[s]) assert(minv >= seen[s]);
      seen[s] = minv;
      continue;
    }
    seen[s] = i;
    vals[i].push_back(i);
    for(int u=a[i]; u!=i; u=a[u]) {
      vals[i].push_back(u);
    }
  }

  for(int i=1; i<=n; i++) {
    if(ans[i]) continue;
    int ref = seen[sz[find(i)]];
    int s = vals[ref].size();
    assert(sz[find(i)] % s == 0);
    ans[i] = vals[ref][0];
    for(int u=a[i], j=1; u!=i; u=a[u], j++) {
      ans[u] = vals[ref][j%s];
    }
  }

  for(int i=1; i<=n; i++) {
    cout << ans[i] << " ";
  }
  cout << nl;

  return 0;
}
