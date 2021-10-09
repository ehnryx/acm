//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int STN = 1<<17;
const int D = 4.2e7;
ll st[D];
int ls[D], rs[D];
int sid;

struct PSegTree {
  void pull(int ver) {
    st[ver] = max(st[ls[ver]], st[rs[ver]]);
  }

  int insert(int old, int x, ll v, int s=0, int e=STN-1) {
    int ver = ++sid;
    if(ver >= D) for(;;);
    ls[ver] = ls[old];
    rs[ver] = rs[old];
    st[ver] = st[old];

    if(s == e) {
      st[ver] = v;
      return ver;
    }

    int m = (s+e) / 2;
    if(x <= m) ls[ver] = insert(ls[old], x, v, s, m);
    else rs[ver] = insert(rs[old], x, v, m+1, e);
    pull(ver);
    return ver;
  }

  ll at(int ver, int x, int s=0, int e=STN-1) {
    if(s == e) return st[ver];
    int m = (s+e) / 2;
    if(x <= m) return at(ls[ver], x, s, m);
    else return at(rs[ver], x, m+1, e);
  }

  ll top(int ver) {
    return st[ver];
  }

  int drop(int old, ll v, int s=0, int e=STN-1) {
    int ver = ++sid;
    if(ver >= D) for(;;);
    ls[ver] = ls[old];
    rs[ver] = rs[old];
    st[ver] = st[old];

    if(s == e) {
      st[ver] = v;
      return ver;
    }

    int m = (s+e) / 2;
    if(st[ver] == st[ls[old]]) ls[ver] = drop(ls[old], v, s, m);
    else rs[ver] = drop(rs[old], v, m+1, e);
    pull(ver);
    return ver;
  }
};

struct State {
  int dsu, sz, ver, off;
  State() {}
  State(int d, int s, int v, int o): dsu(d), sz(s), ver(v), off(o) {}
};

const int N = 1e5 + 1;
State root[N];
PSegTree segt[N];
PSegTree sz;
PSegTree dsu;
PSegTree ver;
PSegTree off;

int find(int v, int i) {
  int par = dsu.at(v, i);
  if(par == -1) return i;
  return find(v, par);
}

State link(const State& cur, int i, int j) {
  i = find(cur.dsu, i);
  j = find(cur.dsu, j);
  if(i == j) return cur;
  int si = sz.at(cur.sz, i);
  int sj = sz.at(cur.sz, j);
  if(si > sj) {
    swap(i, j);
    swap(si, sj);
  }
  int iv = ver.at(cur.ver, i);
  int jv = ver.at(cur.ver, j);
  ll ioff = off.at(cur.off, i);
  ll joff = off.at(cur.off, j);
  for(int k=0; k<si; k++) {
    ll val = segt[i].at(iv, k);
    jv = segt[j].insert(jv, sj + k, val + ioff - joff);
  }
  int ndsu = dsu.insert(cur.dsu, i, j);
  int nsz = sz.insert(cur.sz, j, si + sj);
  int nver = ver.insert(cur.ver, j, jv);
  return State(ndsu, nsz, nver, cur.off);
}

pair<ll,State> pop(const State& cur, int a) {
  a = find(cur.dsu, a);
  int version = ver.at(cur.ver, a);
  ll offset = off.at(cur.off, a);
  ll val = segt[a].top(version);
  int nver = ver.insert(cur.ver, a, segt[a].drop(version, -offset));
  return make_pair(val + offset, State(cur.dsu, cur.sz, nver, cur.off));
}

State push(const State& cur, int a, int c) {
  a = find(cur.dsu, a);
  ll offset = off.at(cur.off, a);
  int noff = off.insert(cur.off, a, offset + c);
  return State(cur.dsu, cur.sz, cur.ver, noff);
}

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  st[0] = -INFLL;

  int n, q;
  cin >> n >> q;
  int lastdsu = 0;
  int lastsz = 0;
  int lastver = 0;
  int lastoff = 0;
  for(int i=1; i<=n; i++) {
    int v;
    cin >> v;
    int nv = segt[i].insert(0, 0, v);
    lastdsu = dsu.insert(lastdsu, i, -1);
    lastsz = sz.insert(lastsz, i, 1);
    lastver = ver.insert(lastver, i, nv);
    lastoff = off.insert(lastoff, i, 0);
  }
  root[0] = State(lastdsu, lastsz, lastver, lastoff);

  ll last = 0;
  for(int i=1; i<=q; i++) {
    int t;
    cin >> t;
    if(t == 1) {
      ll j, a, b;
      cin >> j >> a >> b;
      j ^= last; a ^= last; b ^= last;
      root[i] = link(root[j], a, b);
    } else if(t == 2) {
      ll j, a;
      cin >> j >> a;
      j ^= last; a ^= last;
      tie(last, root[i]) = pop(root[j], a);
      cout << last << nl;
    } else {
      ll j, a, c;
      cin >> j >> a >> c;
      j ^= last; a ^= last; c ^= last;
      root[i] = push(root[j], a, c);
    }
  }

  return 0;
}
