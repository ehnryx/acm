// 80 minutes

#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const char nl = '\n';

// MAGIC IO
inline char get(void) {
  static char buf[100000], *S = buf, *T = buf;
  if (S == T) {
    T = (S = buf) + fread(buf, 1, 100000, stdin);
    if (S == T) return EOF;
  }
  return *S++;
}
template <typename T> inline void read(T &x) {
  static char c; x = 0; int sgn = 0;
  for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
  for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
  if (sgn) x = -x;
}
void readchar(char& c) {
  while (isspace(c = get()));
}
// END MAGIC IO

const int N = 150000 + 1;
const int S = 500;

struct SegTree {
  int n; int *segt;
  SegTree(int len) {
    n = len+2;
    segt = new int[n];
    fill(segt, segt+n, 0);
  }
  void update(int x, int v) {
    for(++x; x<n; x+=x&-x) {
      segt[x] += v;
    }
  }
  int query(int x) {
    int res = 0;
    for(++x; x>0; x-=x&-x) {
      res += segt[x];
    }
    return res;
  }
  int query(int l, int r) {
    return query(r) - query(l-1);
  }
};

int rot[N];
int a[N], v[N];
vector<int> idx[N];
SegTree* st[N];
SegTree all(N);

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m, q;
  read(n); read(m); read(q);
  //cin >> n >> m >> q;
  for(int i=1; i<=n; i++) {
    read(a[i]);
    //cin >> a[i];
    idx[a[i]].push_back(i);
  }
  for(int i=1; i<=n; i++) {
    read(v[i]);
    //cin >> v[i];
  }

  vector<int> big;
  for(int i=1; i<=m; i++) {
    if(idx[i].size() < S) {
      for(int j : idx[i]) {
        all.update(j, v[j]);
      }
    } else {
      big.push_back(i);
      st[i] = new SegTree(idx[i].size());
      for(int j=0; j<idx[i].size(); j++) {
        st[i]->update(j, v[idx[i][j]]);
      }
    }
  }

  for(int i=0; i<q; i++) {
    int t;
    read(t);
    //cin >> t;
    if(t == 1) {
      int l, r;
      read(l); read(r);
      //cin >> l >> r;
      int res = all.query(l, r);
      for(int j : big) {
        auto lb = lower_bound(begin(idx[j]), end(idx[j]), l);
        auto rb = upper_bound(begin(idx[j]), end(idx[j]), r);
        if(lb < rb) {
          int sz = idx[j].size();
          int lv = (lb - begin(idx[j]) + rot[j]) % sz;
          int rv = (rb - begin(idx[j]) - 1 + rot[j]) % sz;
          if(lv <= rv) {
            res += st[j]->query(lv, rv);
          } else {
            res += st[j]->query(0, rv);
            res += st[j]->query(lv, sz-1);
          }
        }
      }
      cout << res << nl;
    } else {
      int x;
      read(x);
      //cin >> x;
      int sz = idx[x].size();
      int prerot = rot[x];
      rot[x] = (rot[x]+sz-1) % sz;
      if(sz < S) {
        for(int j=0; j<sz; j++) {
          int id = idx[x][(j+rot[x])%sz];
          int pd = idx[x][(j+prerot)%sz];
          all.update(idx[x][j], v[id]-v[pd]);
        }
      }
    }
  }

  return 0;
}
