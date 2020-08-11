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



void init() {
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	init();

	int T;
	cin >> T;
	for (int cc = 1; cc <= T; cc++) {
		cout << "Case #" << cc << ": ";
		casesolve();
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////



void caseinit() {
}

void casesolve() {
	caseinit();

	int n;
	cin >> n;
	string s[n];
	for(int i=0; i<n; i++) {
		cin >> s[i];
		while(s[i].size() < 500) {
			s[i] += s[i];
		}
	}

	string ans;
	vector<bool> done(n);
	for(int j=0; j<500; j++) {
		bool R, P, S;
		R = P = S = false;
		for(int i=0; i<n; i++) {
			if(done[i]) continue;
			R |= (s[i][j] == 'R');
			P |= (s[i][j] == 'P');
			S |= (s[i][j] == 'S');
		}

		if(!R && !P && !S) {
			cout << ans << nl;
			return;
		}
		if(R && P && S) {
			cout << "IMPOSSIBLE" << nl;
			return;
		}

		if(R && P) {
			ans.push_back('P');
		} else if(P && S) {
			ans.push_back('S');
		} else if(S && R) {
			ans.push_back('R');
		} else if(R) {
			ans.push_back('P');
		} else if(P) {
			ans.push_back('S');
		} else if(S) {
			ans.push_back('R');
		}

		for(int i=0; i<n; i++) {
			if(done[i]) continue;
			if(ans.back() == 'R' && s[i][j] == 'S') done[i] = true;
			if(ans.back() == 'P' && s[i][j] == 'R') done[i] = true;
			if(ans.back() == 'S' && s[i][j] == 'P') done[i] = true;
		}
	}

	assert(false);

	return;
}

