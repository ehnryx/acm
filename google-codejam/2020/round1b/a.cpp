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



void casesolve() {

	int n, m;
	cin >> n >> m;

	string ans;
	while(abs(n)+abs(m) > 1) {
		if((n+m) % 2 == 0) {
			cout << "IMPOSSIBLE" << nl;
			return;
		}
		if(abs(n) % 2 == 1) {
			if(((n+1)/2 + m/2) % 2 != 0) {
				ans.push_back('W');
				n = (n+1) / 2;
				m = m / 2;
			} else {
				ans.push_back('E');
				n = (n-1) / 2;
				m = m / 2;
			}
		} else {
			if((n/2 + (m+1)/2) % 2 != 0) {
				ans.push_back('S');
				n = n / 2;
				m = (m+1) / 2;
			} else {
				ans.push_back('N');
				n = n / 2;
				m = (m-1) / 2;
			}
		}
	}

	if(n) {
		ans.push_back(n > 0 ? 'E' : 'W');
	} else {
		ans.push_back(m > 0 ? 'N' : 'S');
	}

	cout << ans << nl;

	return;
}

