#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct Edge {
  int u, v;
  ll c, rv;
};

const int N = 2e5+1;
vector<Edge> adj[N], tree[N];
vector<int> cyc[N];
unordered_set<int> skip[N];
vector<Edge> cycle[N]; // stored in reverse
vector<Edge> par[N]; // stored in reverse
ll vval[N];
bool vis[N];

void find_cycle(int u, int p, int cid) {
  cycle[cid].push_back(par[u].back());
  par[u].pop_back();
  for(int v=p; v!=u; v=par[v].back().u) {
    cycle[cid].push_back(par[v].back());
  }
  cyc[u].push_back(cid);
}

int decompose(int u, int p, int& cid) {
  if(vis[u]) {
    find_cycle(u, p, ++cid);
    skip[u].insert(p);
    return u;
  }

  vis[u] = true;
  int wait = 0;
  for(const Edge& e:adj[u]) {
    if(e.v == p || skip[u].count(e.v)) continue;
    par[e.v].push_back(e);
    int to = decompose(e.v, u, cid);
    if(!to) {
      tree[u].push_back(e);
    } else if(to != u) {
      assert(!wait);
      wait = to;
    }
  }
  return wait;
}


struct Max2 {
  ll a, b;
  Max2(): a(0), b(0) {}
  void update(ll v) {
    if(v > a) {
      b = a;
      a = v;
    } else if(v > b) {
      b = v;
    }
  }
  ll best() const {
    return a;
  }
  ll sum() const {
    return a + b;
  }
};

Max2 dist[N];
ll diam[N];

void init() {
  fill(dist, dist+N, Max2());
  fill(diam, diam+N, 0);
}

bool solve(int, ll);
bool solve_cyc(int, ll);

bool solve(int u, ll ub) {
  for(const Edge& e:tree[u]) {
    if(!solve(e.v, ub)) {
      return false;
    }
    diam[u] = max(diam[u], diam[e.v]);
    dist[u].update(dist[e.v].best() + e.c);
  }
  for(int v:cyc[u]) {
    if(!solve_cyc(v, ub)) {
      return false;
    }
    diam[u] = max(diam[u], diam[v]);
    dist[u].update(dist[v].best());
  }
  diam[u] = max(diam[u], dist[u].sum());
  return diam[u] <= ub;
}

ll ldist[N], rdist[N], llen[N], rlen[N];
ll ldiam[N], rdiam[N], ldmax[N], rdmax[N];
ll lval[N], rval[N], ldiff[N], rdiff[N];

bool solve_cyc(int u, ll ub) {
  //cerr<<"@ cycle "<<u<<nl;
  const auto& cur = cycle[u];
  int sz = cur.size();
  for(int i=1; i<sz; i++) {
    if(!solve(cur[i].v, ub)) {
      return false;
    }
    diam[u] = max(diam[u], diam[cur[i].v]);
  }

  lval[0] = cur.front().rv + vval[cur[0].v];
  rval[0] = cur.back().rv + vval[cur[0].v];
  for(int i=1; i<sz; i++) {
    llen[i] = llen[i-1] + cur[i-1].c;
    rlen[i] = rlen[i-1] + cur[sz-i].c;
    ldist[i] = dist[cur[i].v].best();
    rdist[i] = dist[cur[sz-i].v].best();
    lval[i] = cur[i].rv + vval[cur[i].v];
    rval[i] = cur[sz-1-i].rv + vval[cur[sz-i].v];
  }

  for(int i=1; i<sz; i++) {
    ldmax[i] = max(ldmax[i-1], llen[i] + ldist[i]);
    rdmax[i] = max(rdmax[i-1], rlen[i] + rdist[i]);
    ldiam[i] = max(ldiam[i-1], ldiff[i-1] + llen[i] + ldist[i]);
    rdiam[i] = max(rdiam[i-1], rdiff[i-1] + rlen[i] + rdist[i]);
    ldiff[i] = max(ldiff[i-1], ldist[i] - llen[i]);
    rdiff[i] = max(rdiff[i-1], rdist[i] - rlen[i]);
  }

  ll best = INFLL;
  ll ndiam = INFLL;
  for(int i=0; i<sz; i++) {
    //cerr<<"try cutting @ "<<i<<nl;
    int j = sz-1-i;
    ll combine = max(ldmax[i], llen[i]+lval[i]) + max(rdmax[j], rlen[j]+rval[j]);
    ll cdiam = max(combine, max(ldiam[i], rdiam[j]));
    cdiam = max(cdiam, ldiff[i] + llen[i] + lval[i]);
    cdiam = max(cdiam, rdiff[j] + rlen[j] + rval[j]);
    //cerr<<"got diam max of "<<combine<<" "<<ldiam[i]<<" "<<rdiam[j]<<" = "<<cdiam<<nl;
    if(cdiam <= ub) {
      ll maxdist = max(max(ldmax[i], llen[i]+lval[i]), max(rdmax[j], rlen[j]+rval[j]));
      //cerr<<" -> got maxdist "<<maxdist<<nl;
      if(maxdist < best) {
        best = maxdist;
        ndiam = cdiam;
      }
    }
  }
  //cerr<<"best dist = "<<best<<nl;

  diam[u] = max(diam[u], ndiam);
  dist[u].update(best);
  return diam[u] <= ub;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  for(int i=1; i<=n; i++) {
    cin >> vval[i];
  }
  for(int i=0; i<m; i++) {
    int a, b, c, rv;
    cin >> a >> b >> c >> rv;
    adj[a].push_back({a,b,c,rv});
    adj[b].push_back({b,a,c,rv});
  }

  int cid = n;
  decompose(1, 0, cid);

  //cerr<<"Tree edges: "<<nl; for(int i=1; i<=n; i++) {
  //cerr<<i<<" -> "<<nl; for(const Edge& e:tree[i]) {
  //cerr<<"  "<<e.u<<" "<<e.v<<" "<<e.c<<" "<<e.rv<<nl; } }
  //cerr<<nl;

  //cerr<<"Cycle edges: "<<nl; for(int i=1; i<=n; i++) {
  //cerr<<i<<" -> "<<nl; for(int v:cyc[i]) {
  //cerr<<"  "<<v<<nl; } }
  //cerr<<nl;

  //cerr<<"Cycles: "<<nl; for(int i=n+1; i<=cid; i++) {
  //cerr<<i<<" -> "<<nl; for(const Edge& e:cycle[i]) {
  //cerr<<"  "<<e.u<<" "<<e.v<<" "<<e.c<<" "<<e.rv<<nl; } }
  //cerr<<nl;

  //cerr<<"--------------"<<nl<<endl;

  ll left = 0;
  ll right = (ll)(n+7)*INF;
  while(left<right) {
    ll mid = (left+right)/2;
    //cerr<<"solving ub = "<<mid<<endl;
    init();
    if(solve(1, mid)) {
      right = mid;
    } else {
      left = mid+1;
    }
    //cerr<<"-----------"<<nl<<endl;
  }
  cout << left << nl;

  return 0;
}
