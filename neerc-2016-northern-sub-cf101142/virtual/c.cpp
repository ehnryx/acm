#include <bits/stdc++.h>
using namespace std;
#define problem_name "codecoder"

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

const int N = 1e5+10;
const int MAXN = 1e5+10;

int n;

int low[N], vis[N], scomp[N], scompNum, I;
vector<int> adj[N]; stack<int> verts;
void scc(int u) {
  low[u] = vis[u] = ++I; verts.push(u);
  for(int v: adj[u]) {
    if (!vis[v]) scc(v);
    if (scomp[v] == -1) low[u] = min(low[u], low[v]); }
  if (vis[u] <=low[u]) {
     int v;
     do { v=verts.top(); verts.pop(); scomp[v] = scompNum;} while(v!=u);
     ++scompNum;
  }
}

int par[MAXN];
set<int> sccadj[N];

void get_scc(int _n) {
  memset(vis, 0, sizeof vis); memset(scomp, -1, sizeof scomp);
  scompNum=I=0; for(int i=0;i<_n;i++) if(!vis[i]) scc(i); }

int parent(int a) {
  return (par[a] < 0 ? a:(par[a] = parent(par[a])));
}

int merge(int a, int b) {
  int x = parent(a), y = parent(b);
  if (x==y) return x;
  par[x]+=par[y];
  par[y] = x;
  return x;
}


int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen(problem_name ".in", "r", stdin);
  freopen(problem_name ".out", "w", stdout);
#endif
  memset(par,-1,sizeof par);
  cin >> n;
  vector<vector<int>> va;
  vector<vector<int>> vb;
  for(int i=0;i<n;i++) {
    int a, b;
    cin >> a >> b;
    va.push_back({a,b,i});
    vb.push_back({b,a,i});
  }
  sort(va.begin(), va.end());
  sort(vb.begin(), vb.end());
  int id1, id2;
  for(int i=0;i<n-1;i++) {
    id1 = va[i][2];
    id2 = va[i+1][2];
    adj[id2].push_back(id1);
    id1 = vb[i][2];
    id2 = vb[i+1][2];
    adj[id2].push_back(id1);
  }
  get_scc(n);
  vector<int> reps(scompNum);
  for(int i=0;i<n;i++) {
    reps[scomp[i]] = i;
  }
  for(int i=0;i<n-1;i++) {
    id1 = va[i][2];
    id2 = va[i+1][2]; // 2 connected to 1
    if (scomp[id1] == scomp[id2]) {
      merge(id1, id2);
    }
    else {
      sccadj[scomp[id2]].insert(scomp[id1]);
    }
    id1 = vb[i][2];
    id2 = vb[i+1][2];
    if (scomp[id1] == scomp[id2]) {
      merge(id1, id2);
    }
    else {
      sccadj[scomp[id2]].insert(scomp[id1]);
    }
  }

  int ans[scompNum];
  for(int i=0;i<scompNum;i++) {
    ans[i] = -par[parent(reps[i])];
    //cerr << i << " " << ans[i] <<endl;
    for(int v: sccadj[i]) {
      //cerr << "GOING TO " << v <<endl;
      ans[i]+=ans[v];
    }
  }

  for(int i=0;i<n;i++) {
    cout << ans[scomp[i]]-1 << '\n';
  }

  return 0;
}
