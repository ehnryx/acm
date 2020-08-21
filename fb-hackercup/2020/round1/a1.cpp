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

vector<int> read(int n, int k) {
  vector<int> v(n+1);
  for(int i=1; i<=k; i++) {
    cin >> v[i];
  }
  ll a, b, c, d;
  cin >> a >> b >> c >> d;
  for(int i=k+1; i<=n; i++) {
    v[i] = (a*v[i-2] + b*v[i-1] + c) % d + 1;
  }
  return v;
}

void casesolve() {

	int n, k, w;
  cin >> n >> k >> w;
  vector<int> l = read(n, k);
  vector<int> h = read(n, k);

  ll ans = 1;
  ll perim = 0;
  ll cur = 0;
  for(int i=1, j=1; i<=n; i++) {
    while(l[i] > l[j] + w) {
      j++;
    }
    if(i == j) {
      perim += cur;
      cur = 2*(w + h[i]);
    } else {
      int maxh = 0;
      for(int t=j; t<i; t++) {
        maxh = max(maxh, h[t]);
      }
      int dh = max(0, h[i] - maxh);
      int dl = l[i] - l[i-1];
      cur += 2*(dh + dl);
    }
    ans = ans * ((perim + cur) % MOD) % MOD;
  }

  cout << ans << nl;

	return;
}

