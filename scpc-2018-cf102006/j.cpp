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
  int i, d;
  bool operator < (const Node& o) const {
    return d > o.d;
  }
};

const int N = 1e5+1;
vector<int> idx[N];
vector<int> clar[2*N];
bool seen[N];

void solve() {
  int m, n, k;
  cin >> m >> n >> k;

  for (int i=1; i<=k; i++) {
    idx[i].clear();
    seen[i] = false;
  }
  for (int i=1; i<=m+n; i++) {
    clar[i].clear();
  }

  for (int i=0; i<n; i++) {
    int t, p;
    cin >> t >> p;
    idx[p].push_back(t);
    clar[t].push_back(p);
  }

  for (int i=1; i<=k; i++) {
    idx[i].push_back(INF);
    sort(idx[i].begin(), idx[i].end());
  }

  int done = 0;
  int active = 0;
  unordered_map<int,int> wait;
  priority_queue<Node> nxt;
  for (int i=1; i<=m+n; i++) {
    for (int it : clar[i]) {
      if (seen[it]) {
        active++;
      } else {
        if (!wait.count(it)) {
          nxt.push({it, *next(lower_bound(idx[it].begin(), idx[it].end(), i))});
        }
        wait[it]++;
      }
    }

    // hasan
    if (active > 0) {
      active--;
      done++;
    }

    // kan
    if (!nxt.empty()) {
      int cur = nxt.top().i;
      nxt.pop();
      seen[cur] = true;
      active += wait[cur];
    }
    if (active > 0) {
      active--;
      done++;
    }

    if (done == n) {
      cout << i << nl;
      return;
    }
  }

  assert(false);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#define FILENAME "clar"
  cerr << "File IO: " << FILENAME << nl;
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
#endif

  int T;
  cin >> T;
  while (T--) {
    solve();
  }

  return 0;
}
