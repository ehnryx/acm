#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(chrono::high_resolution_clock::now().time_since_epoch().count()); }

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

namespace Hungarian {
  const int N = 1001;
  int w[N][N], ml[N], mr[N], lbl[N], lbr[N], s[N], slack[N], par[N];
  void init() {
    memset(w, 0, sizeof w);
    memset(ml, 0, sizeof ml);
    memset(mr, 0, sizeof mr);
    memset(lbl, 0, sizeof lbl);
    memset(lbr, 0, sizeof lbr);
    memset(s, 0, sizeof s);
    memset(slack, 0, sizeof slack);
    memset(par, 0, sizeof par);
  }
  int wmatch(int n, int m) {
    int i, j, k, done, al, nxt, out = 0;
    for (i = 0; i < n; i++) for (j = 0, lbl[i] = 0, ml[i] = -1; j < m; j++) lbl[i] = max(lbl[i], w[i][j]);
    for (i = 0; i < m; i++) lbr[i] = 0, mr[i] = -1;
    for (i = 0; i < n; i++) for (j = 0; j < m; j++) if (w[i][j] == lbl[i] && mr[j] == -1) {
      ml[i] = j, mr[j] = i; break;
    }
    for (i = 0; i < n; i++) if (ml[i] == -1) {
      for (j = 0; j < m; j++) s[j] = (j==i), slack[j] = (lbl[i] + lbr[j] - w[i][j]), par[j] = -1;
      for (done = 0; !done; ) {
        for (j = 0, al = INF; j < m; j++) if (par[j] == -1) al = min(al, slack[j]);
        for (j = 0, lbl[j] -= s[j]*al; j < m; ++j, lbl[j] -= s[j]*al)
          if (par[j] != -1) lbr[j] += al; else slack[j] -= al;
        for (j = 0; j < m; j++) if (!slack[j] && par[j] == -1) {
          for (k = 0; k < n; k++) if (s[k] && lbl[k] + lbr[j] == w[k][j]) { par[j] = k; break; }
          if (mr[j] == -1) { done = 1;
            do { nxt = ml[par[j]], mr[j] = par[j], ml[par[j]] = j, j = nxt; } while (j != -1);
          } else for (k = 0, s[mr[j]] = 1; k < m; k++)
            slack[k] = min(slack[k], lbl[mr[j]] + lbr[k] - w[mr[j]][k]); break;
        }
      }
    }
    for (i = 0; i < n; i++) out += w[i][ml[i]]; return out;
  }
}


int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  srand();
  Hungarian::init();

  int m, n, k;
  cin >> m >> n >> k;

  int a, b, p;
  for (int i = 0; i < k; i++) {
    cin >> a >> b >> p;
    Hungarian::w[a][b] = p;
  }

  cout << Hungarian::wmatch(1+n, 1+max(m,n)) << nl;
  vector<pii> ans;
  for (int i = 1; i <= n; i++) {
    if (Hungarian::w[i][Hungarian::ml[i]] != 0) {
      ans.push_back(pii(i, Hungarian::ml[i]));
    }
  }

  cout << ans.size() << nl;
  for (const pii& it : ans) {
    cout << it.first << " " << it.second << nl;
  }

  return 0;
}
