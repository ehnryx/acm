#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const char nl = '\n';

const int N = 1<<20;
const int M = 1e5+1;
const int D = 8e6;

ll arith(int a, int b) {
  int d = b-a;
  return (ll)a*(d+1) + (ll)d*(d+1)/2;
}

struct Node {
  ll sum, z, za;
  Node(ll s=0, ll _z=0, ll a=0): sum(s), z(_z), za(a) {}
  void update(ll a, ll v, int s, int e) {
    za += a;
    sum += a * arith(s, e);
    z += v * (e-s+1);
    sum += v * (e-s+1);
  }
};

int root[M];
Node st[D];
int ls[D], rs[D];
int sid;

void push(int ver, int s, int m, int e) {
  if(ls[ver] == 0) ls[ver] = ++sid;
  if(rs[ver] == 0) rs[ver] = ++sid;
  if(st[ver].z) {
    st[ls[ver]].sum += st[ver].z/2;
    st[rs[ver]].sum += st[ver].z/2;
    st[ls[ver]].z += st[ver].z/2;
    st[rs[ver]].z += st[ver].z/2;
    st[ver].z = 0;
  }
  if(st[ver].za) {
    st[ls[ver]].sum += st[ver].za * arith(s, m);
    st[rs[ver]].sum += st[ver].za * arith(m+1, e);
    st[ls[ver]].za += st[ver].za;
    st[rs[ver]].za += st[ver].za;
    st[ver].za = 0;
  }
}

void pull(int ver) {
  st[ver].sum = st[ls[ver]].sum + st[rs[ver]].sum;
}

void insert(int& ver, int old, ll a, ll v, int l, int r, int s, int e) {
  if(r<s || e<l) return;
  ver = ++sid;
  ls[ver] = ls[old];
  rs[ver] = rs[old];
  st[ver] = st[old];

  if(l<=s && e<=r) {
    st[ver].update(a, v, s, e);
    return;
  }

  int m = (s+e)/2;
  push(ver, s, m, e);
  insert(ls[ver], ls[old], a, v, l, r, s, m);
  insert(rs[ver], rs[old], a, v, l, r, m+1, e);
  pull(ver);
}

ll query(int ver, int l, int r, int s, int e) {
  if(r<s || e<l) return 0;
  if(l<=s && e<=r) {
    return st[ver].sum;
  }
  int m = (s+e)/2;
  push(ver, s, m, e);
  return query(ls[ver], l, r, s, m)
    + query(rs[ver], l, r, m+1, e);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  int id = 0;
  for(int i=0; i<m; i++) {
    int t;
    cin >> t;
    if(t == 1) {
      int l, r, v;
      cin >> l >> r >> v;
      insert(root[id+1], root[id], v, v*(-l+1), l, r, 0, N-1);
      id++;
    } else {
      int l, r;
      cin >> l >> r;
      cout << query(root[id], l, r, 0, N-1) << nl;
    }
  }

  return 0;
}
