//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

template <class U, class V>
ostream& operator << (ostream& os, const pair<U,V>& v) {
  return os << "(" << v.first << ", " << v.second << ")";
}

const int L = 19;
const int N = 1 << L;
vector<int> adj[N];
int par[N], anc[N][L];
pair<int,int> range[N];

int jump(int u, int d) {
  for(int j=0; j<L; j++) {
    if(d & 1<<j) {
      u = anc[u][j];
    }
  }
  return u;
}

vector<int> manacher(const string& s) {
  int n = s.size();
  vector<int> len(2*n-1), last(2*n-1);

  int u = 0;
  len[0] = 1;
  range[++u] = make_pair(0, 1);
  par[u] = anc[u][0] = 0;
  for(int j=1; j<L; j++) anc[u][j] = anc[anc[u][j-1]][j-1];
  last[0] = u;

  for(int d, i=1; i+1 < 2*n; i+=d) {
    int &r = len[i], left = (i-r-1)/2, right = (i+r+1)/2;
    while(0 <= left && right < n && s[left] == s[right]) {
      range[++u] = make_pair(left, right + 1);
      par[u] = anc[u][0] = last[i];
      for(int j=1; j<L; j++) anc[u][j] = anc[anc[u][j-1]][j-1];
      last[i] = u;
      --left; ++right; r += 2;
    }

    for(d=1; len[i-d] < r-d; d++) {
      len[i+d] = len[i-d];
      last[i+d] = last[i-d];
    }
    len[i+d] = r-d;
    last[i+d] = jump(last[i-d], (len[i-d] - len[i+d]) / 2);
  }

  assert(u < N);
  for(int i=0; i<=u; i++) {
    if((range[i].second - range[i].first) % 2) continue;
    adj[i].clear();
    if(i > 0) adj[par[i]].push_back(i);
  }

  return last;
}

int dp[N], half[N];
int rmq[N][L];

void solve_case() {
  string s;
  cin >> s;
  int n = s.size();

  vector<int> last = manacher(s);
  for(int i=1; i<n; i++) {
    int j = 2*i - 1;
    int r = (range[last[j]].second - range[last[j]].first) / 2;
    rmq[i][0] = i - r;
  }
  for(int j=1; j<L; j++) {
    for(int i=1; i+(1<<j)<=n; i++) {
      rmq[i][j] = min(rmq[i][j-1], rmq[i+(1<<(j-1))][j-1]);
    }
  }

  function<int(int,int)> query = [=](int l, int r) {
    assert(l < r);
    int j = 31 - __builtin_clz(r-l);
    return min(rmq[l][j], rmq[r-(1<<j)][j]);
  };

  function<int(int,int)> solve_prefix = [&](int left, int right) {
    int len = right - left;
    int mid = left + len/2;
    int l = left + 1;
    int r = left + len/2;
    while(l < r) {
      int m = (l+r+1) / 2;
      if(query(m, mid+1) <= left) {
        l = m;
      } else {
        r = m-1;
      }
    }

    if(r > 0 && rmq[r][0] <= left) {
      int add = len - 2*(r-left);
      int j = 2*r - 1;
      int lenlast = (range[last[j]].second - range[last[j]].first) / 2;
      int lenwant = (r-left);
      int i = jump(last[j], lenlast - lenwant);
      return add + dp[i];
    } else {
      return len;
    }
  };

  vector<int> visited;
  queue<int> bfs;
  bfs.push(0);
  half[0] = dp[0] = 0;
  while(!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();
    visited.push_back(u);
    for(int v : adj[u]) {
      bfs.push(v);

      int len = range[v].second - range[v].first;
      int mid = (range[v].second + range[v].first) / 2;
      half[v] = len / 2;
      half[v] = min(half[v], half[u] + 1);
      half[v] = min(half[v], solve_prefix(range[v].first, mid));
      dp[v] = half[v] + 1;
      dp[v] = min(dp[v], dp[u] + 2);
      dp[v] = min(dp[v], solve_prefix(range[v].first, range[v].second));
    }
  }

  int ans = n;
  for(int u : visited) {
    ans = min(ans, dp[u] + n - (range[u].second - range[u].first));
  }
  cout << ans << nl;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int T;
  cin >> T;
  while(T--) {
    solve_case();
  }

  return 0;
}
