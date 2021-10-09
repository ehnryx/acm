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

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

const int N = 1e5+1;

struct DSU {
  int root[N];
  void clear() { memset(root, -1, sizeof root); }
  int find(int i) {
    if (root[i] == -1) return i;
    return root[i] = find(root[i]);
  }
  void link(int i, int j) {
    if (find(i) != find(j));
      root[find(i)] = find(j);
  }
};

DSU dsu;

struct Query {
  int l, int r;
  Query() {}
  Query(int l, int r): l(l), r(r) {}
  bool operator < (const Query& other) const {
    if (dsu.find(l) == dsu.find(other.l))
      return r < other.r;
    else
      return dsu.find(l) < dsu.find(other.l);
  }
};

int leftmost[2*N+1];
int rightmost[2*N+1];
int lastid[2*N+1];
int nextjmp[2*N+1];
int prevjmp[2*N+1];
int pref[N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int T;
  cin >> T;
  while (T--) {
    memset(lastid, -1, sizeof lastid);
    memset(prevjmp, 0, sizeof prevjmp);
    memset(nextjmp, INF, sizeof nextjmp);

    int n;
    cin >> n;
    pref[0] = 0;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      pref[i] = pref[i-1] + a[i];
      if (lastid[pref[i]+n] != -1) {
        prevjmp[i] = lastid[pref[i]+n];
        nextjmp[lastid[pref[i]+n]] = i;
      }
      lastid[pref[i]+n] = i;
    }

    dsu.clear();
    int step = 0, root = 0;
    for (int i = 1; i <= n; i++) {
      if (i > step) {
        step += sqrt(n);
        root = i;
      }
      dsu.link(root, i);
    }

    int q;
    cin >> q;

    int a, b;
    vector<Query> todo;
    for (int i = 0; i < q; i++) {
      cin >> a >> b;
      todo.push_back(Query(a,b));
    }
    sort(todo.begin(), todo.end());

    memset(leftmost, -1, sizeof leftmost);
    memset(rightmost, -1, sizeof rightmost);
    map<int,int> active;
    active[0] = 1;

    int curans;
    int left, right;
    left = 1; right = 0;

    ll ans = 0;
    for (const Query& it : todo) {
      if (right < it.r) {
        while (right < it.r) {
          right++;
          if (prevjmp[right] 
        }
      }

      if (left > it.l) {
        while (left > it.l) {
          left--;
          // upd
        }
      }

      if (right > it.r) {
        while (right > it.r) {
          //upd
          right--;
        }
      }

      if (left < it.l) {
        while (left < it.l) {
          // upd
          left++;
        }
      }

      curans = *active.rbegin();
      ans += curans;
    }

    cout << ans << nl;
  }

  return 0;
}
