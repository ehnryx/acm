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

//#define DEBUG
#ifdef DEBUG
const int N = 400;
ll ncr[N][N];
#endif

int main(int argc, char** argv) {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

#ifdef DEBUG
	for(int i=0; i<N; i++) {
		ncr[i][i] = ncr[i][0] = 1;
		for(int j=1; j<i; j++) {
			ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
		}
	}
#endif

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
	cout << nl;

	int n;
	cin >> n;

	if(n <= 30) {
		for(int i=1; i<=n; i++) {
			cout << i << " " << 1 << nl;
		}
		return;
	}

#ifdef DEBUG
	ll res = 0;
	int cnt = 0;
#endif

	n -= 30;
	int taken = 0;
	bool left = true;
	for(int i=1; i<=30; i++) {
		if(1<<(i-1) & n) {
			taken++;
			if(left) {
				for(int j=1; j<=i; j++) {
					cout << i << " " << j << nl;
				}
			} else {
				for(int j=i; j>=1; j--) {
					cout << i << " " << j << nl;
				}
			}
			left ^= 1;
#ifdef DEBUG
			for(int j=1; j<=i; j++) {
				res += ncr[i-1][j-1];
				cnt++;
			}
#endif
		} else {
			if(left) {
				cout << i << " " << 1 << nl;
			} else {
				cout << i << " " << i << nl;
			}
#ifdef DEBUG
			res += 1;
			cnt++;
#endif
		}
	}

	// have n - 30 + (30 - taken) = n-taken
#ifdef DEBUG
	cerr<<"taken: "<<taken<<nl;
	cerr<<"HAVE: "<<res<<" WANT: "<<n+(30-taken)<<endl;
	cerr<<"TOOK "<<cnt<<" steps"<<endl;
	assert(res == n+30-taken);
	assert(cnt <= 500);
#endif
	for(int i=1; i<=taken; i++) {
		if(left) {
			cout << 30 + i << " " << 1 << nl;
		} else {
			cout << 30 + i << " " << 30 + i << nl;
		}
	}

	return;
}

