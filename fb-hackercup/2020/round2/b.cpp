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

ld nc2(int n) {
  return n*(n-1)/2;
}

void casesolve() {

	int n;
  cin >> n;
  ld p;
  cin >> p;

  vector<vector<ld>> dp(n+1, vector<ld>(n+1));
  for(int i=2; i<=n; i++) {
    for(int k=1; k<=i; k++) {
      dp[i][k] = 1
        + (k-1)/nc2(i) * p * dp[i-1][k-1]
        + (i-k)/nc2(i) * (1-p) * dp[i-1][k]
        + nc2(k-1)/nc2(i) * dp[i-1][k-1]
        + nc2(i-k)/nc2(i) * dp[i-1][k]
        + (k-1)*(i-k)/nc2(i) * (p * dp[i-1][k-1] + (1-p) * dp[i-1][k]);
    }
  }

  cout << nl;
  for(int k=1; k<=n; k++) {
    cout << dp[n][k] << nl;
  }

	return;
}

