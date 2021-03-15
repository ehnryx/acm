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

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 3e5 + 7;
int bit[N];
void insert(int x) {
  for( ; x<N; x+=x&-x) {
    bit[x] += 1;
  }
}
int query(int x) {
  int res = 0;
  for( ; x>0; x-=x&-x) {
    res += bit[x];
  }
  return res;
}
int query(int l, int r) {
  return query(r) - query(l-1);
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;
  vector<int> a(n);
  map<int,int> remap;
  for(int i=0; i<n; i++) {
    cin >> a[i];
    remap[a[i]];
  }

  int rid = 0;
  for(auto& it : remap) {
    it.second = ++rid;
  }
  for(int i=0; i<n; i++) {
    a[i] = remap[a[i]];
  }

  vector<ll> pref(n+2), suff(n+2);
  for(int i=0; i<n; i++) {
    if(a[i] == rid) {
      pref[i+1] = pref[i];
    } else {
      pref[i+1] = pref[i] + query(a[i], N-1);
      insert(a[i]);
    }
  }
  memset(bit, 0, sizeof bit);
  for(int i=n-1; i>=0; i--) {
    if(a[i] == rid) {
      suff[i] = suff[i+1];
    } else {
      suff[i] = suff[i+1] + query(a[i], N-1);
      insert(a[i]);
    }
  }

  int pos = max_element(a.begin(), a.end()) - a.begin();
  ll ans = INFLL;
  for(int i=0; i<=n; i++) {
    ans = min(ans, abs(i - pos) + pref[i] + suff[i]);
  }
  cout << ans << nl;

  return 0;
}
