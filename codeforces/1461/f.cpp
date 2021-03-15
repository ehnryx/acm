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
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }
  string allowed;
  cin >> allowed;

  if(allowed.size() == 1) {
    for(int i=0; i<n; i++) {
      if(i > 0) cout << allowed[0];
      cout << a[i];
    }
    cout << nl;
    return 0;
  }

  if(allowed.size() == 2 && allowed.find('-') != -1) {
    if(allowed.find('+') != -1) {
      for(int i=0; i<n; i++) {
        if(i > 0) cout << '+';
        cout << a[i];
      }
      cout << nl;
    } else {
      for(int i=0; i<n; i++) {
        if(i > 0) {
          if(a[i] == 0) cout << '-';
          else cout << '*';
        }
        cout << a[i];
      }
      cout << nl;
    }
    return 0;
  }

  assert(allowed.find('+') != -1 && allowed.find('*') != -1);

  vector<char> out(n);
  function<void(int,int)> solve = [&](int l, int r) {
    if(l == r) return;
    vector<tuple<int,int,ll>> blocks;
    for(int i=l,s=l; i<=r; i++) {
      if(a[i] == 1) {
        if(a[s] != 1) {
        } else {
        }
      } else {
      }
    }
  };

  for(int i=0,s=0; i<n; i++) {
    if(a[i] == 0) {
      if(i > 0) out[i] = '+';
      if(i+1 < n) out[i+1] = '+';
      if(i > s) {
        solve(s, i-1);
      }
      s = i+1;
    }
  }

  for(int i=0; i<n; i++) {
    if(i > 0) cout << out[i];
    cout << a[i];
  }
  cout << nl;

  return 0;
}
