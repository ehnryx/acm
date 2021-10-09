#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;
const int MOD = 1e9+7;

ll inv(ll n) {
  ll res = 1;
  for (int e=MOD-2; e>0; e/=2) {
    if (e&1) res = res*n%MOD;
    n = n*n%MOD;
  }
  return res;
}

struct F {
  ll n, d;
  F() { n=d=INF; }
  F(ll a, ll b) { n = a%MOD; d = b%MOD; if (d==0) { n=0; d=1; } }
  bool done() const { return n!=INF; }
  F operator + (const F& f) const { return F(n*f.d + d*f.n, d*f.d); }
  F operator - (const F& f) const { return F(n*f.d - d*f.n, d*f.d); }
  F operator * (const F& f) const { return F(n*f.n, d*f.d); }
  ll get() const { return (n*inv(d)%MOD + MOD) % MOD; }
};

F one(1,1);
F zero(0,1);

F probe(int,int,int);
F prob(int,int,int);
F solve(int,int,int,int);

const int N = 1e5+1;
vector<int> adj[N];
int val[N], deg[N];

F pb[N][2], p1[N][2], dp[N][2][2];

F probe(int u, int b, int p) {
  if (p1[u][b].done()) return p1[u][b];
  F res = zero;
  F take = F(1,deg[u]-b);
  for (int x : adj[u]) {
    if (x!=p) {
      res = res + take * F(1,deg[x]);
    }
  }
  return p1[u][b] = res;
}

F prob(int u, int b, int p) {
  if (pb[u][b].done()) return pb[u][b];
  F res = zero;
  F take = F(1,deg[u]-b);
  for (int x : adj[u]) {
    if (x!=p) {
      // down and up
      res = res + take*F(1,deg[x]);
      // one less choice at child
      res = res + take*(prob(x,0,u)-probe(x,0,u))*F(1,deg[x]-1);
      // extra choice at child
      res = res + take*probe(x,0,u)*F(1,deg[x]);
    }
  }
  return pb[u][b] = res;
}

F solve(int u, int b, int vis, int p) {
  if (dp[u][b][vis].done()) return dp[u][b][vis];

  // leaf case
  if (deg[u] == 1) {
    if (b) return dp[u][b][vis] = F(val[u],1);
    else return dp[u][b][vis] = zero;
  }

  // initialize values
  F res = zero;
  F take = F(1,deg[u]-b);
  F other = F(1,deg[u]-b-1);

  // transitions
  if (vis) {
    for (int x : adj[u]) {
      if (x!=p) {
        res = res + take * solve(x,1,0,u);
      }
    }
  }

  else {
    for (int x : adj[u]) {
      if (x!=p) {
        // just go down
        res = res + take * solve(x,0,0,u);
        // down up down on the same
        res = res + take * F(1,deg[x]) * take * solve(x,1,1,u);
        // down up down on different
        res = res + (probe(u,b,p)-take*F(1,deg[x])) * take * solve(x,1,0,u);
        // down path up path down different
        res = res + (prob(u,b,p)-probe(u,b,p)) * other * solve(x,1,0,u);
        // remove down same length = 2
        res = res - take * probe(x,0,p) * F(1,deg[x]) * other * solve(x,1,0,u);
        // remove down same length > 2
        res = res - take * (prob(x,0,p)-probe(x,0,p)) * F(1,deg[x]-1) * other * solve(x,1,0,u);
      }
    }
  }

  // deg2 case, if we get stuck at u
  if (b && deg[u] == 2 && !vis) {
    res = res + (prob(u,b,p)-probe(u,b,p)) * F(val[u],1);
  }
  return dp[u][b][vis] = res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int T; cin >> T;
  for (int tt = 1; tt <= T; tt++) {
    cout << "Case " << tt << ": ";

    int n;
    cin >> n;

    for (int i=1; i<=n; i++) {
      cin >> val[i];
      adj[i].clear();
      deg[i] = 0;
      for (int j=0; j<2; j++) {
        pb[i][j] = F();
        p1[i][j] = F();
        for (int k=0; k<2; k++) {
          dp[i][j][k] = F();
        }
      }
    }

    for (int i=1; i<n; i++) {
      int a, b;
      cin >> a >> b;
      adj[a].push_back(b);
      adj[b].push_back(a);
      deg[a]++;
      deg[b]++;
    }

    int s;
    cin >> s;
    deg[s]++;
    cout << solve(s,1,0,0).get() << nl;
  }

  return 0;
}
