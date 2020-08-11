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

const int N = 60 + 1;
int dp[N][N];

void casesolve() {

	string s, t;
	cin >> s >> t;

	int n = s.size();
	int m = t.size();
	s = "0" + s;
	t = "0" + t;

	for(int i=1; i<=n; i++) {
		dp[i][0] = i;
	}
	for(int j=1; j<=m; j++) {
		dp[0][j] = j;
	}

	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + 1;
			dp[i][j] = min(dp[i][j], dp[i-1][j-1] + (s[i] != t[j]));
		}
	}

	int want = dp[n][m]/2;
	string ans;
	for(int have=0; have<want; ) {
		if(n && m && dp[n][m] == dp[n-1][m-1] && s[n] == t[m]) {
			ans.push_back(t[m]);
			n--;
			m--;
		} else {
			have++;
			if(n && dp[n][m] == dp[n-1][m] + 1) {
				n--;
			} else if(m && dp[n][m] == dp[n][m-1] + 1) {
				ans.push_back(t[m]);
				m--;
			} else {
				ans.push_back(t[m]);
				n--;
				m--;
			}
		}
	}
	while(n > 0) {
		ans.push_back(s[n]);
		n--;
	}

	reverse(ans.begin(), ans.end());
	cout << ans << nl;

	return;
}

