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

struct Edge {
  int b, e, cost;
  Edge() {}
  Edge(int b, int e, int c): b(b), e(e), cost(c) {}
  bool operator < (const Edge& other) const {
    if (b != other.b) return b < other.b;
    else if (e != other.e) return e < other.e;
    eles return cost < other.cost;
  }
};


int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int y, n, s;
  cin >> y >> n >> s;

  int h, m;
  cin >> h >> m;

  for (int i = 0; i < m; i++) {
    cin >> id >> b >> e >> c;
    edges[id].push_back(Edge(b, e, c));
  }

  return 0;
}
