#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
const int INF = 0x3f3f3f3f;
const int N = 1 << 21;
const int L = 21;

int par[N>>1][L];
ll dis[N>>1][L];

pair<int, int> t[2*N];

void upd(int x, pair<int, int> p) {
  t[x+N] = max(t[x+N], p);
  for (x += N; x > 0; x /= 2) {
    t[x/2] = max(t[x], t[x^1]);
  }
}
pair<int, int> query(int l, int r) {
  pair<int, int> ans = {-INF, -INF};
  for (l += N, r += N+1; l < r; l /= 2, r /= 2) {
    if (l%2) ans = max(ans, t[l++]);
    if (r%2) ans = max(ans, t[--r]);
  }
  return ans;
}

int succ[N], d[N];
bool onstk[N];
int ans = INF;
void dfs(int x) {
  if (succ[x] == -1) return;
  onstk[x] = 1;
  if (onstk[succ[x]]) {
    ans = min(ans, d[x] - d[succ[x]] + 1);
    onstk[x] = 0;
    return;
  }
  if (d[succ[x]] == -1) {
    d[succ[x]] = d[x]+1;
    dfs(succ[x]);
  }
  onstk[x] = 0;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  memset(t, -1, sizeof t);
  int n, k; cin >> n >> k;
  vector<pair<int, int>> v(2*k);
  for (int i = 0; i < k; i++) {
    cin >> v[i].first >> v[i].second; v[i].first--; v[i].second--;
    if (v[i].second < v[i].first) {
      v[i].second += n;
    }
    if (v[i].second - v[i].first == n-1) {
      cout << 1 << nl;
      return 0;
    }
    v[k+i] = {v[i].first+n, v[i].second+n};
    upd(v[i].first, make_pair(v[i].second+1, i));
    upd(v[i].first+n, make_pair(v[i].second+n+1, i));
  }
  for (int i = 0; i < k; i++) {
    pair<int, int> p = query(v[i].first+n, v[i].second+n+1); p.first -= n;
    succ[i] = max(query(v[i].first, v[i].second+1), p).second;
    if (succ[i] == i) succ[i] = -1;
    //cerr << v[i].first << " " << v[i].second << " -> ";
    //if (succ[i] == -1) cerr << -1 << nl;
    //else cerr << v[succ[i]].first << " " << v[succ[i]].second << nl;
  }
  memset(d, -1, sizeof d);
  for (int i = 0; i < k; i++) {
    if (d[i] == -1) {
      d[i] = 0;
      dfs(i);
    }
  }
  //cerr << " dfs gets " << ans <<endl;

  memset(par, -1, sizeof par);
  for(int j=0;j<k;j++) {
    if (succ[j] == -1) continue;
    par[j][0] = succ[j];
    dis[j][0] = v[succ[j]].second+1-(v[j].second+1);
    if (dis[j][0] < 0) dis[j][0]+=n;
  }
  for(int i=1;i<L;i++) {
    for(int j=0;j<k;j++) {
      if (par[j][i-1] == -1) continue;
      par[j][i] = par[par[j][i-1]][i-1];
      dis[j][i] = dis[j][i-1]+dis[par[j][i-1]][i-1];
    }
  }
  for(int j=0;j<k;j++) {
    ll target = n - (v[j].second+1-v[j].first);
    int cur = j;
    int posans = 1;
    for(int i=L-1;i>=0;i--) {
      if (par[cur][i] == -1) continue;
      if (target > dis[cur][i]) {
        target-=dis[cur][i];
        cur = par[cur][i];
        posans+=(1<<i);
      }
    }
    //cerr << target << " " << cur << " " << dis[cur][0] <<endl;
    if (target < dis[cur][0])
      ans = min(posans+1, ans);
  }

  if (ans > k) {
    puts("impossible");
    return 0;
  }
  cout << ans << nl;

  return 0;
}
