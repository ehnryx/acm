#include <cstdio>
#include <set>
#include <utility>

using namespace std;

const int N = 100000 + 5;

int r[N], g[N], b[N], id[N], u[N];
set<pair<int, int> > rs, gs, bs;

struct cmp_us {
  bool operator() (const pair<int, int>& a, const pair<int, int>& b) const {
    return a.first < b.first || (a.first == b.first && a.second > b.second);
  }
};

set<pair<int, int>, cmp_us> us;

pair<pair<int, int>, pair<int, int> > get_geq_leq(int v, int i, set<pair<int, int> >& s, bool readd = true) {
  s.erase(make_pair(v, i));
  pair<int, int> geq, leq;
  set<pair<int, int> >::iterator it = s.lower_bound(make_pair(v, i));
  if (it == s.end()) {
    geq = *s.begin();
  } else {
    geq = *it;
  }
  it = s.upper_bound(make_pair(v, i));
  if (it == s.begin()) {
    leq = *s.rbegin();
  } else {
    leq = *(--it);
  }
  if (readd) {
    s.insert(make_pair(v, i));
  }
  return make_pair(geq, leq);
}

int get_u_c(int v, int i, set<pair<int, int> >& s) {
  pair<pair<int, int>, pair<int, int> > geq_leq = get_geq_leq(v, i, s);
  pair<int, int> geq = geq_leq.first, leq = geq_leq.second;
  return (geq.first - v + 360) % 360 + (v - leq.first + 360) % 360;
}

int get_u(int i) {
  return get_u_c(r[i], i, rs) + get_u_c(g[i], i, gs) + get_u_c(b[i], i, bs);
}

void rm_c(int v, int i, set<pair<int, int> >& s) {
  pair<pair<int, int>, pair<int, int> > geq_leq = get_geq_leq(v, i, s, false);
  pair<int, int> geq = geq_leq.first, leq = geq_leq.second;
  us.erase(make_pair(u[geq.second], geq.second));
  us.erase(make_pair(u[leq.second], leq.second));
  u[geq.second] = get_u(geq.second);
  u[leq.second] = get_u(leq.second);
  us.insert(make_pair(u[geq.second], geq.second));
  us.insert(make_pair(u[leq.second], leq.second));
}

void rm(int i) {
  us.erase(make_pair(u[i], i));
  rm_c(r[i], i, rs);
  rm_c(g[i], i, gs);
  rm_c(b[i], i, bs);
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d%d%d", &r[i], &g[i], &b[i], &id[i]);
    rs.insert(make_pair(r[i], i));
    gs.insert(make_pair(g[i], i));
    bs.insert(make_pair(b[i], i));
  }
  for (int i = 1; i <= n; i++) {
    u[i] = get_u(i);
    us.insert(make_pair(u[i], i));
  }
  for (int i = 1; i < n; i++) {
    int t = us.begin()->second;
    printf("%d\n", id[t]);
    if (i + 1 < n) {
      rm(t);
    } else {
      us.erase(make_pair(u[t], t));
    }
  }
  printf("%d\n", id[us.begin()->second]);
  return 0;
}
