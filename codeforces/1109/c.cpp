#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1<<19;

int dcmp[N];
map<int,int> cmpr;
map<int,int> events;

ll rmq[2*N], lazy[2*N];
bool flag[2*N];

void push(int i) {
  if (flag[i]) {
    lazy[2*i] += lazy[i];
    rmq[2*i] += lazy[i];
    lazy[2*i+1] += lazy[i];
    rmq[2*i+1] += lazy[i];
    lazy[i] = 0;
    flag[2*i] = flag[2*i+1] = true;
    flag[i] = false;
  }
}

void pull(int i) {
  rmq[i] = min(rmq[2*i], rmq[2*i+1]);
}

ll query_point(int x, int i=1, int s=0, int e=N-1) {
  if (s == e) {
    return rmq[x];
  }
  push(i);
  int m = (s+e)/2;
  if (x<=m) return query_point(x, 2*i, s, m);
  else return query_point(x, 2*i+1, m+1, e);
}

void updshift(int l, int r, ll v, int i, int s, int e) {
  if (r<s || e<l) return;
  if (l<=s && e<=r) {
    flag[i] = true;
    lazy[i] = v;
    rmq[i] += v;
    return;
  }
  push(i);
  int m = (s+e)/2;
  updshift(l, r, v, 2*i, s, m);
  updshift(l, r, v, 2*i+1, m+1, e);
  pull(i);
}

void insert(int l, int r, int val, int old) {
  updshift(cmpr[r], cmpr[2*INF], (ll)(val-old)*(r-l), 1, 0, N-1);
}

void answer(int l, int r, int v) {
  if (v == 0) {
    cout << l << nl;
  } else {
    auto cur = prev(events.upper_bound(l));
    ll val = query_point(cmpr[l]) + (ll)cur->second*(l-cur->first);
    int id = query_min(l, val-v);
    int bot = query_point(id);
    ld pos = dcmp[id] - ((val-v)-bot)/prev(events.lower_bound(dcmp[id]))->second;
    if (pos < r+EPS) {
      cout << pos << nl;
    } else {
      cout << -1 << nl;
    }
  }
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n;
  cin >> n;

  vector<Query> queries;
  for (int i=0; i<n; i++) {
    int t, a, b, c;
    cin >> t;
    if (t == 1) {
      cin >> a >> b;
      queries.push_back({t,a,b});
      cmpr[a];
    } else if (t == 2) {
      cin >> a;
      queries.push_back({t,a});
      assert(cmpr.count(a));
    } else {
      cin >> a >> b >> c;
      queries.push_back({t,a,b,c});
      cmpr[a]; cmpr[b];
    }
  }
  cmpr[0]; cmpr[2*INF];

  int dnum = 0;
  for (auto& it : cmpr) {
    dcmp[dnum] = it.first;
    it.second = dnum++;
  }

  events[0] = events[2*INF] = 0;
  for (const Query& it : queries) {
    if (it.t == 1) {
      auto nxt = events.upper_bound(it.a);
      insert(it.a, nxt->first, it.b, prev(nxt)->second);
      events[it.a] = it.b;
    } else if (it.t == 2) {
      auto cur = events.find(it.a);
      insert(it.a, next(cur)->first, prev(cur)->second, cur->second);
      events.erase(it.a);
    } else {
      answer(it.a, it.b, it.c);
    }
  }

  return 0;
}
