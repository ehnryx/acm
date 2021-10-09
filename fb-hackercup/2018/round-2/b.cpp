#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef mt19937 RNG;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  return os << '(' << v.first << ',' << v.second << ')';
}
template <class T> 
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}
template <class T> 
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) os << it << " "; 
  return os << '}';
}
template <class T, class U> 
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ "; for (const pair<T,U>& it : v) os << it << " ";
  return os << '}';
}

////////////////////////////////////////////////////////////////////////

void solve();
void init() {
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
  init();

  int T;
  cin >> T;
  for (int cc = 1; cc <= T; cc++) {
    cout << "Case #" << cc << ": ";
    solve();
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////

const int N = 2e5+1;
int parent[N];
vector<int> adj[N];
set<int> active[N];
int idx[N];
int cnt[N];

void caseinit() {
  fill(adj, adj+N, vector<int>());
  fill(active, active+N, set<int>());
  memset(cnt, 0, sizeof cnt);
  for (int i = 0; i < N; i++) {
    idx[i] = i;
  }
}

ll solve(int cur) {
  ll res = 0;
  if (!adj[cur].empty()) {
    vector<int> merge;
    merge.push_back(cur);
    for (int x : adj[cur]) {
      res += solve(x);
      merge.push_back(x);
      if (active[idx[x]].size() > active[idx[cur]].size()) {
        idx[cur] = idx[x];
      }
    }

    for (int i : merge) {
      if (idx[i] != idx[cur]) {
        for (int v : active[idx[i]]) {
          active[idx[cur]].insert(v);
        }
      }
    }
  }

  active[idx[cur]].insert(cur);
  while (cnt[cur] > 0 && !active[idx[cur]].empty()) {
    res += *active[idx[cur]].rbegin();
    active[idx[cur]].erase(prev(active[idx[cur]].end()));
    cnt[cur]--;
  }

  return res;
}

void solve() {
  caseinit();

  int n, m, a, b;
  cin >> n >> m >> a >> b;

  for (int i = 1; i < n; i++) {
    cin >> parent[i];
    adj[parent[i]].push_back(i);
  }

  for (int i = 0; i < m; i++) {
    int root = (a*i + b) % n;
    cnt[root]++;
  }

  cout << solve(0) << nl;

  return;
}

