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

const int M = 1e6+1;
const int N = 1<<20;
const int L = 20;
int val[M], inv[M];

int rmq[N][L+1], lg[N];

void build() {
  for (int i=1; i<N; i++) {
    lg[i] = 31-__builtin_clz(i);
  }
  for (int j=1; j<=L; j++) {
    for (int i=0; i+(1<<j)-1<N; i++) {
      rmq[i][j] = max(rmq[i][j-1], rmq[i+(1<<(j-1))][j-1]);
    }
  }
}
int query_rmq(int l, int r) {
  int j = lg[r-l+1];
  return max(rmq[l][j], rmq[r-(1<<j)+1][j]);
}

namespace Other {
  ll segt[2*N], lazy[2*N];

  void push(int i) {
    if (lazy[i]) {
      lazy[2*i] += lazy[i]/2;
      lazy[2*i+1] += lazy[i]/2;
      segt[2*i] += lazy[i]/2;
      segt[2*i+1] += lazy[i]/2;
      lazy[i] = 0;
    }
  }

  void pull(int i) {
    segt[i] = segt[2*i] + segt[2*i+1];
  }

  void update(int l, int r, ll v=1, int i=1, int s=0, int e=N-1) {
    if (r<s || e<l) return;
    if (l<=s && e<=r) {
      lazy[i] += v*(e-s+1);
      segt[i] += v*(e-s+1);
      ////cerr << "upd put " << e-s+1 << " @ " << l << " " << r << " " << s << " " << e << " " << i << endl;
      return;
    }
    push(i);
    int m = (s+e)/2;
    update(l, r, v, 2*i, s, m);
    update(l, r, v, 2*i+1, m+1, e);
    pull(i);
  }

  ll query(int l, int r, int i=1, int s=0, int e=N-1) {
    if (r<s || e<l) return 0;
    if (l<=s && e<=r) {
      ////cerr << "que get " << segt[i] << " @ " << l << " " << r << " " << s << " " << e << " " << i << endl;
      return segt[i];
    }
    push(i);
    int m = (s+e)/2;
    return query(l,r,2*i,s,m) + query(l,r,2*i+1,m+1,e);
  }
}

namespace SegTree {
  ll segt[2*N], lazy[2*N];

  void push(int i) {
    if (lazy[i]) {
      lazy[2*i] += lazy[i]/2;
      lazy[2*i+1] += lazy[i]/2;
      segt[2*i] += lazy[i]/2;
      segt[2*i+1] += lazy[i]/2;
      lazy[i] = 0;
    }
  }

  void pull(int i) {
    segt[i] = segt[2*i] + segt[2*i+1];
  }

  void update(int l, int r, int i=1, int s=0, int e=N-1) {
    if (r<s || e<l) return;
    if (l<=s && e<=r) {
      lazy[i] += e-s+1;
      segt[i] += e-s+1;
      ////cerr << "upd put " << e-s+1 << " @ " << l << " " << r << " " << s << " " << e << " " << i << endl;
      return;
    }
    push(i);
    int m = (s+e)/2;
    update(l, r, 2*i, s, m);
    update(l, r, 2*i+1, m+1, e);
    pull(i);
  }

  ll query(int l, int r, int i=1, int s=0, int e=N-1) {
    if (r<s || e<l) return 0;
    if (l<=s && e<=r) {
      ////cerr << "que get " << segt[i] << " @ " << l << " " << r << " " << s << " " << e << " " << i << endl;
      return segt[i];
    }
    push(i);
    int m = (s+e)/2;
    return query(l,r,2*i,s,m) + query(l,r,2*i+1,m+1,e);
  }
}

struct Query {
  int i, l, r;
};

ll ans[M];

void solve(int l, int r, const vector<Query>& q) {
  if (l > r) return;
  int m = inv[query_rmq(l,r)];
  vector<Query> left, right, mid;
  for (const auto& it : q) {
    if (it.r<m) left.push_back(it);
    else if (it.l>m) right.push_back(it);
    else mid.push_back(it);
  }
  solve(l, m-1, left);
  solve(m+1, r, right);

  //cerr << "insert " << l << " " << r << " w/ max " << m << endl;
  SegTree::update(l, r);
  Other::update(l, r);
  Other::update(m, m, r-l);
  for (const auto& it : mid) {
    ans[it.i] = SegTree::query(l, r) - (Other::query(l, r) - Other::query(it.l, it.r));
    //cerr << "assign " << it.i << " <- " << ans[it.i] << " @ " << l << "," << r << endl;
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

  int n, q;
  cin >> n >> q;

  for (int i=1; i<=n; i++) {
    cin >> val[i];
    inv[val[i]] = i;
    rmq[i][0] = val[i];
  }
  build();

  vector<Query> queries;
  int l[q], r;
  for (int i=0; i<q; i++) {
    cin >> l[i];
  }
  for (int i=0; i<q; i++) {
    cin >> r;
    queries.push_back({i,l[i],r});
  }

  solve(1,n,queries);
  for (int i=0; i<q; i++) {
    cout << ans[i] << " ";
  }
  cout << nl;

  return 0;
}
