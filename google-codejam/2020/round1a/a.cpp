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

	int n;
	cin >> n;

	bool ok = true;
	string pref, suff, middle;
	for(int i=0; i<n; i++) {
		string s;
		cin >> s;
		int m = s.size();
		vector<int> ast;
		for(int j=0; j<m; j++) {
			if(s[j] == '*') {
				ast.push_back(j);
			}
		}

		int plen = min((int)pref.size(), ast.front());
		ok &= (pref.substr(0, plen) == s.substr(0, plen));
		if(ast.front() > pref.size()) pref = s.substr(0, ast.front());

		int slen = min((int)suff.size(), m-1 - ast.back());
		ok &= (suff.substr(suff.size()-slen) == s.substr(s.size()-slen));
		if(m-1 - ast.back() > suff.size()) suff = s.substr(ast.back()+1);

		for(int j=1; j<ast.size(); j++) {
			int l = ast[j-1] + 1;
			int r = ast[j] - 1;
			middle += s.substr(l, r-l+1);
		}
	}

	if(ok) {
		cout << pref + middle + suff << nl;
	} else {
		cout << "*" << nl;
	}

	return;
}

