#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Node {
  ll sold, left, todo;
  Node(ll s=0, ll l=0, ll t=0): sold(s), left(l), todo(t) {}
  Node operator + (const Node& o) const {
    ll cancel = min(left, o.todo);
    return Node(
      sold + o.sold + cancel,
      left + o.left - cancel,
      todo + o.todo - cancel
    );
  }
  void update(int v) {
    todo += v;
    int cancel = min(left, todo);
    left -= cancel;
    todo -= cancel;
    sold += cancel;
  }
};

struct SegTree {
  static const int N = 1<<17;
  Node t[2*N];
  void init(int v) {
    For(i,N) {
      if (i>0) t[i+N] = Node(0,v,0);
      else t[i+N] = Node(0,0,0);
    }
    for (int i=N-1; i>0; i--) {
      t[i] = t[2*i] + t[2*i+1];
    }
  }

  void update(int x, int v, int i=1, int s=0, int e=N-1) {
    if (s == e) {
      t[i].update(v);
      return;
    }
    int m = (s+e)/2;
    if (x<=m) update(x,v,2*i,s,m);
    else update(x,v,2*i+1,m+1,e);
    t[i] = t[2*i] + t[2*i+1];
  }

  Node query(int l, int r, int i=1, int s=0, int e=N-1) {
    assert(i < 2*N);
    if (r<s || e<l) return Node();
    if (l<=s && e<=r) {
      return t[i];
    }
    int m = (s+e)/2;
    return query(l,r,2*i,s,m) + query(l,r,2*i+1,m+1,e);
  }

  void print() {
    For(i,N) {
      cout << t[i].sold << ',' << t[i].left << ',' << t[i].todo << "  ";
    }
    cout << nl;
    For(i,N) {
      cout << t[N+i].sold << ',' << t[N+i].left << ',' << t[N+i].todo << "  ";
    }
    cout << nl;
  }
};

SegTree sa, sb;

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, k, a, b, m;
  cin >> n >> k >> a >> b >> m;

  sa.init(a);
  sb.init(b);

  while (m--) {
    int t;
    cin >> t;

    if (t == 1) {
      int x, v;
      cin >> x >> v;
      sa.update(x,v);
      sb.update(x,v);
    } else {
      int x;
      cin >> x;
      Node left, right;
      if (x>1) left = sb.query(1,x-1);
      if (x+k<=n) right = sa.query(x+k,n);
      //cerr << "left: " << left.sold << ',' << left.left << ',' << left.todo << nl;
      //cerr << "right: " << right.sold << ',' << right.left << ',' << right.todo << nl;
      cout << (left+right).sold << nl;
    }

#ifdef DEBUG
    cerr << "SA: " << nl;
    sa.print();
    cerr << "SB: " << nl;
    sb.print();
    cerr << nl;
#endif
  }

  return 0;
}
