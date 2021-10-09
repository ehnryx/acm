#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) os << it << " "; os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ ";
  for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
  os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

#ifdef USE_MAGIC_IO
inline char get(void) {
  static char buf[100000], *S = buf, *T = buf;
  if (S == T) {
    T = (S = buf) + fread(buf, 1, 100000, stdin);
    if (S == T) return EOF;
  }
  return *S++;
}
inline void read(int &x) {
  static char c; x = 0; int sgn = 0;
  for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
  for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
  if (sgn) x = -x;
}
#else
#define get() getchar()
#define read(x) scanf("%d",&x)
#endif
////////////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

const int N = 1<<23;

vector<bool> done(N);

struct SegTree {
  int t[2*N];
  SegTree() {
    memset(t, 0, sizeof t);
  }

  void insert(int x) {
    done[x] = true;
    for (t[x += N] += 1; x > 1; x >>= 1)
      t[x>>1] = t[x] + t[x^1];
  }

  int query(int v) {
    int res = query(v, 1, 0, N-1, 0);
    insert(res);
    return res+1;
  }

  int query(int v, int i, int s, int e, int pre) {
    if (s == e) {
      return i-N;
    }
    int len = (e-s+1)/2;
    int left = pre + len - t[i<<1];
    int mid = (s+e)/2;
    if (left > v)
      return query(v, i<<1, s, mid, pre);
    else
      return query(v, i<<1|1, mid+1, e, left);
  }
};

SegTree segtree;
int ans[N], a[N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int n;
  read(n);

  for (int i = 1; i <= n; i++) {
    read(a[i]);
    a[i] = i - a[i] - 1;
  }

  for (int i = n; i > 0; i--) {
    ans[i] = segtree.query(a[i]);
  }

  for (int i = 1; i <= n; i++) {
    printf("%d ", ans[i]);
  }
  putchar(nl);

  return 0;
}
