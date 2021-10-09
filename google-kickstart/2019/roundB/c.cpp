#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

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

const int N = 1<<17;
int rmq[2*N], lazy[2*N];

void push(int i) {
  if (lazy[i]) {
    rmq[2*i] += lazy[i];
    rmq[2*i+1] += lazy[i];
    lazy[2*i] += lazy[i];
    lazy[2*i+1] += lazy[i];
    lazy[i] = 0;
  }
}

void pull(int i) {
  rmq[i] = max(rmq[2*i], rmq[2*i+1]);
}

void update(int l, int r, int v, int i=1, int s=0, int e=N-1) {
  if (r<s || e<l) return;
  if (l<=s && e<=r) {
    rmq[i] += v;
    lazy[i] += v;
    return;
  }
  push(i);
  int m = (s+e)/2;
  update(l, r, v, 2*i, s, m);
  update(l, r, v, 2*i+1, m+1, e);
  pull(i);
}

int query(int l, int r, int i=1, int s=0, int e=N-1) {
  if (r<s || e<l) return 0;
  if (l<=s && e<=r) {
    return rmq[i];
  }
  push(i);
  int m = (s+e)/2;
  return max(query(l, r, 2*i, s, m), query(l, r, 2*i+1, m+1, e));
}

int arr[N];

void caseinit() {
  memset(rmq, 0, sizeof rmq);
  memset(lazy, 0, sizeof lazy);
}

void solve() {
  caseinit();

  int n, s;
  cin >> n >> s;

  unordered_map<int,vector<int>> index;
  unordered_map<int,int> pos;
  for (int i=0; i<n; i++) {
    cin >> arr[i];
    index[arr[i]].push_back(i);
    int cnt = index[arr[i]].size();
    if (cnt <= s) {
      update(i, n, 1);
    } else if (cnt == s+1) {
      update(i, n, -s);
    }
  }

  int ans = 0;
  for (int i=0; i<n; i++) {
    ans = max(ans, query(i, n));
    //cerr << i << ": " << query(i,n) << nl;
    auto& idx = index[arr[i]];
    update(i, n, -1);
    if (pos[arr[i]] + s < idx.size()) {
      update(idx[pos[arr[i]]+s], n, s+1);
    }
    if (pos[arr[i]] + s + 1 < idx.size()) {
      update(idx[pos[arr[i]]+s+1], n, -s);
    }
    pos[arr[i]]++;
  }
  cout << ans << nl;

  return;
}

