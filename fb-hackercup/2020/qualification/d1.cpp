//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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
const ld EPS = 1e-9;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  return os << '(' << v.first << ',' << v.second << ')';
}
template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) { os << it << " "; } return os;
}
template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) { os << it << " "; }
  return os << '}';
}
template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ "; for (const pair<T,U>& it : v) { os << it << " "; }
  return os << '}';
}

void casesolve();

////////////////////////////////////////////////////////////////////////



int main(int argc, char** argv) {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  for (int cc = 1; cc <= T; cc++) {
    cout << "Case #" << cc << ": ";
    casesolve();
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////

const int N = 1 << 20;
int c[N];
ll dp[N];
ll st[2*N];

void insert(int x, ll v) {
  st[x+=N] = v;
  for(x/=2; x; x/=2) {
    st[x] = min(st[2*x], st[2*x+1]);
  }
}

ll query(int l, int r) {
  ll res = INFLL;
  for(l+=N, r+=N; l<r; l/=2, r/=2) {
    if(l&1) res = min(res, st[l++]);
    if(r&1) res = min(res, st[--r]);
  }
  return res;
}

void casesolve() {

  int n, m;
  cin >> n >> m;
  for(int i=1; i<=n; i++) {
    cin >> c[i];
    if(i > 1) {
      insert(i, INFLL);
    }
  }

  for(int i=2; i<=n; i++) {
    dp[i] = query(max(1, i-m), i);
    if(c[i]) {
      insert(i, dp[i] + c[i]);
    }
  }

  if(dp[n] == INFLL) {
    cout << -1 << nl;
  } else {
    cout << dp[n] << nl;
  }

  return;
}

