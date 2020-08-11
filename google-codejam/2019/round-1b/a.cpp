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

struct BIT {
	int N;
	vector<int> bit;
	BIT(int n): N(n+1) {
		bit.resize(n+1);
	}
	void insert(int l, int r) {
		update(l, 1);
		update(r+1, -1);
	}
	void update(int x, int v) {
		for(x++; x<N; x+=x&-x) {
			bit[x] += v;
		}
	}
	int query(int x) {
		int res = 0;
		for(x++; x>0; x-=x&-x) {
			res += bit[x];
		}
		return res;
	}
};

void caseinit() {
}

void casesolve() {
	caseinit();

	int n, m;
	cin >> n >> m;

	BIT x(m+1), y(m+1);

	for(int i=0; i<n; i++) {
		int a, b; char d;
		cin >> a >> b >> d;
		if(d == 'S') {
			y.insert(0, b-1);
		} else if(d == 'N') {
			y.insert(b+1, m);
		} else if(d == 'W') {
			x.insert(0, a-1);
		} else if(d == 'E') {
			x.insert(a+1, m);
		}
	}

	int ansx = -1;
	int ansy = -1;
	int bestx = -1;
	int besty = -1;
	for(int i=0; i<=m; i++) {
		int curx = x.query(i);
		int cury = y.query(i);
		if(curx > bestx) {
			bestx = curx;
			ansx = i;
		}
		if(cury > besty) {
			besty = cury;
			ansy = i;
		}
	}
	assert(ansx != -1 && ansy != -1);
	cout << ansx << " " << ansy << nl;

	return;
}

