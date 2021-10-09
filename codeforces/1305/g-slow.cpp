//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const char nl = '\n';

const int N = 1<<18;
int cnt[N];
int dsu[N];
int find(int i) {
  if(dsu[i] == -1) return i;
  return dsu[i] = find(dsu[i]);
}
int link(int i, int j) {
  i = find(i); j = find(j);
  if(i == j) return 0;
  int edges = cnt[i] + cnt[j] - 1;
  cnt[i] = cnt[j] = 1;
  dsu[i] = j;
  return edges;
}

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  memset(dsu, -1, sizeof dsu);

  int n;
  cin >> n;
  ll sum = 0;
  for(int i=0; i<n; i++) {
    int v;
    cin >> v;
    cnt[v]++;
    sum += v;
  }
  cnt[0]++;

  ll ans = 0;
  for(int cost=N-1; cost>=0; cost--) {
    for(int u=cost; u>0; u=(u-1)&cost) {
      int v = cost ^ u;
      if(cnt[u] && cnt[v]) {
        ans += (ll)cost * link(u, v);
      }
    }
  }
  cout << ans - sum << nl;

  return 0;
}
