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
  os << "{ ";
  for (const T& it : v) os << it << " ";
  os << "}"; return os;
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

const int N = 1e5+4;
const int Q = 1<<20;

struct RMQ {
  ll nodes[2*Q];
  void clear() {
    memset(nodes, INF, sizeof nodes);
  }

  void insert(int x, ll v) {
    for (nodes[x += Q] = v; x > 1; x >>= 1)
      nodes[x>>1] = min(nodes[x], nodes[x^1]);
  }

  ll query(int l, int r) {
    r++;
    ll res = INFLL;
    for (l += Q, r += Q; l < r; l >>= 1, r >>= 1) {
      if (l & 1) res = min(res, nodes[l++]);
      if (r & 1) res = min(res, nodes[--r]);
    }
    return res;
  }
};

ll s[Q];
int timestamp[N];
queue<pii> history;
set<int> curline;
int interval[Q+6];
ll dp[Q];
RMQ rmq;

void init() {
  curline.clear();
  rmq.clear();
  memset(dp, INF, sizeof dp);
  memset(interval, -1, sizeof interval);
  while (!history.empty()) 
    history.pop();
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int T;
  cin >> T;
  while (T--) {
    init();

    int n, k, q;
    cin >> n >> k >> q;

    for (int i = 1; i <= q; i++) {
      cin >> s[i];
    }
    s[1] = s[q+1] = 0;
    interval[q+1] = q+1;

    int cap, temp;
    for (int i = 1; i <= q; i++) {
      cin >> cap;
      for (int j = 0; j < cap; j++) {
        cin >> temp;

        timestamp[temp] = i;
        curline.insert(temp);
        history.push(pii(temp, i));
      }

      while (curline.size() > k) {
        pii curp = history.front();
        history.pop();
        if (curp.second == timestamp[curp.first]) {
          curline.erase(curp.first);
          if (interval[curp.second] == -1)
            interval[curp.second] = i;
        }
      }
    }

    for (int i = q; i >= 1; i--) {
      if (interval[i] == -1)
        interval[i] = interval[i+1];
    }

    rmq.insert(q+1, 0);
    for (int i = q; i >= 1; i--) {
      dp[i] = rmq.query(i+1, interval[i]);
      rmq.insert(i, s[i] + dp[i]);
    }
    cout << dp[1] << nl;
  }

  return 0;
}
