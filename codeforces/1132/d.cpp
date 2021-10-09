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
const ll INFLL = 1e12 + 7;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

// MAGIC IO
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
inline void readll(ll &x) {
  static char c; x = 0; int sgn = 0;
  for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
  for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
  if (sgn) x = -x;
}
void readchar(char& c) {
  while (isspace(c = get()));
}
// END MAGIC IO

struct Node {
  int id; ll val, dist, time;
  bool operator < (const Node& o) const {
    return dist > o.dist;
  }
};

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, k;
  //cin >> n >> k;
  read(n); read(k);

  ll a[n], b[n];
  for (int i=0; i<n; i++) {
    //cin >> a[i];
    readll(a[i]);
  }
  for (int i=0; i<n; i++) {
    //cin >> b[i];
    readll(b[i]);
  }

  auto valid = [&] (ll x) {
    priority_queue<Node> nxt;
    for (int i=0; i<n; i++) {
      nxt.push({ i, a[i], a[i]/b[i], 0 });
    }
    for (int t=0; t<k; t++) {
      Node cur = nxt.top(); nxt.pop();
      if (cur.dist < t) {
        return false;
      }
      ll curval = cur.val - (t-cur.time)*b[cur.id];
      if (curval > INFLL) {
        break;
      }
      if (curval < 0) {
        return false;
      }
      ll nxtval = curval - b[cur.id] + x;
      if (nxtval < 0) {
        nxt.push({ cur.id, nxtval, t, t+1 });
      } else {
        nxt.push({ cur.id, nxtval, t+1 + nxtval/b[cur.id], t+1 });
      }
    }
    return true;
  };

  ll left = 0;
  ll right = INFLL;
  while (left < right) {
    ll mid = (left+right)/2;
    if (valid(mid)) {
      right = mid;
    } else {
      left = mid+1;
    }
  }
  if (left == INFLL) left = -1;
  cout << left << nl;

  return 0;
}
