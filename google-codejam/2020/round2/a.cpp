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

const ll BIG = 2e9;

ll find_sum(ll d) {
	ll l = 0;
	ll r = BIG;
	while(l < r) {
		ll m = (l+r+1) / 2;
		if(m*(m+1)/2 <= d) {
			l = m;
		} else {
			r = m-1;
		}
	}
	return r;
}

void casesolve() {
	//cerr<<nl;

	ll a, b;
	cin >> a >> b;
	ll k = find_sum(abs(a-b));
	if(a >= b) a -= k*(k+1)/2;
	else b -= k*(k+1)/2;

	ll l = 0;
	ll r = BIG;
	while(l < r) {
		ll m = (l+r+1) / 2;
		ll x = k*m + (m-1)*(m) + m;
		ll y = k*m + m*(m+1);
		if(a < b) swap(x, y);
		if(min(a-x, b-y) < 0) {
			r = m-1;
		} else {
			l = m;
		}
	}
	ll x = k*r + (r-1)*(r) + r;
	ll y = k*r + r*(r+1);
	if(a >= b) {
		a -= x;
		b -= y;
	} else {
		a -= y;
		b -= x;
	}
	k += 2*r;

	while(max(a, b) >= k+1) {
		if(a >= b && a >= k+1) {
			a -= k+1;
			k++;
		} else if(b > a && b >= k+1) {
			b -= k+1;
			k++;
		}
	}

	cout << k << " " << a << " " << b << nl;

	return;
}

