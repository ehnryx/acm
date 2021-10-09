#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long long ll;
typedef long double ld;

const int N = 1<<16;
const int D = 2e7;
int ls[D], rs[D], st[D];
int sid = 0;

int insert(int old, int x, int v, int s=0, int e=N-1) {
  int ver = ++sid;
  ls[ver] = ls[old];
  rs[ver] = rs[old];
  if(s == e) {
    st[ver] = v;
  } else {
    int m = (s+e) / 2;
    if(x <= m) ls[ver] = insert(ls[old], x, v, s, m);
    else rs[ver] = insert(rs[old], x, v, m+1, e);
  }
  return ver;
}

int at(int ver, int x, int s=0, int e=N-1) {
  if(s == e) return st[ver];
  int m = (s+e) / 2;
  if(x <= m) return at(ls[ver], x, s, m);
  else return at(rs[ver], x, m+1, e);
}

pair<int,int> ans[N];
bool down[2*N];
vector<pair<int,int>> add[2*N];

void add_flag(int x, int i=1, int s=0, int e=N-1) {
  down[i] = true;
  if(s == e) return;
  int m = (s+e) / 2;
  if(x<=m) add_flag(x, 2*i, s, m);
  else add_flag(x, 2*i+1, m+1, e);
}

void add_range(int l, int r, pair<int,int> v, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l) return;
  if(l<=s && e<=r) {
    add[i].push_back(v);
    return;
  }
  int m = (s+e) / 2;
  add_range(l, r, v, 2*i, s, m);
  add_range(l, r, v, 2*i+1, m+1, e);
}

const int M = 1500 + 2;
const vector<int> dx = {0, 0, 1, -1};
const vector<int> dy = {1, -1, 0, 0};
map<pair<int,int>,int> remap;
pair<int,int> pos[N];
bool g[M][M];

int squares(int a, int b) {
  int res = 0;
  res += (g[a-1][b-1] && g[a-1][b] && g[a][b-1]);
  res += (g[a-1][b+1] && g[a-1][b] && g[a][b+1]);
  res += (g[a+1][b-1] && g[a+1][b] && g[a][b-1]);
  res += (g[a+1][b+1] && g[a+1][b] && g[a][b+1]);
  return res;
}

struct State {
  int dsu, face;
  State(int d, int f): dsu(d), face(f) {}
};

pair<int,int> find(int ver, int i) {
  int par = at(ver, i);
  if(par == 0) return make_pair(ver, i);
  auto [dsu, ref] = find(ver, par);
  if(ref != par) dsu = insert(dsu, i, ref);
  return make_pair(dsu, ref);
}

pair<State,pair<int,int>> link(State ver, int i, int j) {
  tie(ver.dsu, i) = find(ver.dsu, i);
  tie(ver.dsu, j) = find(ver.dsu, j);
  if(i == j) {
    int f = at(ver.face, i);
    int nf = f + 1;
    ver.face = insert(ver.face, j, nf);
    return make_pair(ver, make_pair(0, (int)!!nf - !!f));
  } else {
    int fi = at(ver.face, i);
    int fj = at(ver.face, j);
    ver.dsu = insert(ver.dsu, i, j);
    ver.face = insert(ver.face, j, fi + fj);
    return make_pair(ver, make_pair(-1, (int)!!(fi+fj) - !!fi - !!fj));
  }
}

void solve(int l, int r, State ver, pair<int,int> cur, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l || !down[i]) return;

  for(auto [a, b] : add[i]) {
    if(g[a][b]) for(;;);
    g[a][b] = true;
    cur.first++;
    int u = remap[make_pair(a, b)];
    for(int d=0; d<4; d++) {
      int na = a + dx[d];
      int nb = b + dy[d];
      if(!g[na][nb]) continue;
      int v = remap[make_pair(na, nb)];
      pair<int,int> dcur;
      tie(ver, dcur) = link(ver, u, v);
      cur.first += dcur.first;
      cur.second += dcur.second;
    }
    tie(ver.dsu, u) = find(ver.dsu, u);
    int faces = at(ver.face, u);
    int sqr = squares(a, b);
    ver.face = insert(ver.face, u, faces - sqr);
    cur.second += (int)!!(faces-sqr) - !!faces;
  }

  if(s == e) {
    ans[s] = cur;
  } else {
    int m = (s+e) / 2;
    solve(l, r, ver, cur, 2*i, s, m);
    solve(l, r, ver, cur, 2*i+1, m+1, e);
  }

  for(auto [a, b] : add[i]) {
    g[a][b] = false;
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  memset(ans, -1, sizeof ans);

  int n, m;
  cin >> n >> m;

  vector<char> t(m);
  map<pair<int,int>,vector<int>> ev;
  for(int i=0; i<m; i++) {
    cin >> t[i];
    if(t[i] == '?') {
      add_flag(i);
    } else {
      int a, b;
      cin >> a >> b;
      ev[make_pair(a, b)].push_back(i);
      remap[make_pair(a, b)];
    }
  }

  int rid = 0;
  for(auto& it : remap) {
    it.second = ++rid;
    pos[rid] = it.first;
  }

  for(const auto& [v, times] : ev) {
    bool in = false;
    int pre = -1;
    for(int i : times) {
      if(in) {
        add_range(pre, i, v);
      }
      in ^= 1;
      pre = i;
    }
    if(in) {
      add_range(pre, m-1, v);
    }
  }

  solve(0, m-1, State(0, 0), make_pair(0, 0));
  for(int i=0; i<m; i++) {
    if(t[i] == '?') {
      assert(ans[i].first != -1);
      cout << ans[i].first << " " << ans[i].first - ans[i].second << nl;
    }
  }

  return 0;
}
