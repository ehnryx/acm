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

const int N = 100 + 1;
int x[N], y[N];

int solve(int n, int dx, int dy) {
  map<ll,int> cnt; // c -> cnt, c = y*dx - x*dy
  for(int i=0; i<n; i++) {
    ll c = (ll)y[i]*dx - (ll)x[i]*dy;
    cnt[c]++;
  }

  int ones = 0;
  int odd = 0;
  int even = 0;
  int ans = 0;
  for(const auto& it : cnt) {
    if(it.second == 1) {
      ones++;
    } else if(it.second % 2 == 0) {
      even++;
      ans += it.second;
    } else {
      odd++;
      ans += it.second;
    }
  }

  if(odd % 2 == 1) {
    ans += min(ones, 1);
  } else {
    ans += min(ones, 2);
  }
  return ans;
}

void casesolve() {

  int n;
  cin >> n;
  for(int i=0; i<n; i++) {
    cin >> x[i] >> y[i];
  }

  int ans = 1;
  set<pair<int,int>> seen;
  for(int i=0; i<n; i++) {
    for(int j=0; j<i; j++) {
      ll dx = x[i] - x[j];
      ll dy = y[i] - y[j];
      ll g = __gcd(dx, dy);
      dx = dx / g;
      dy = dy / g;
      pair<int,int> s(dx, dy);
      if(seen.insert(s).second) {
        ans = max(ans, solve(n, dx, dy));
      }
    }
  }
  cout << ans << nl;

  return;
}

