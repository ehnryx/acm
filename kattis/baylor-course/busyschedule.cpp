#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Time {
	int h, m, pm;
	int v;
	Time(int _h, int _m, char _t) {
		h = (_h==12 ? 0 : _h);
		m = _m;
		pm = (_t == 'p');
		v = pm*12*60 + h*60 + m;
	}
	bool operator < (const Time& o) const {
		return v < o.v;
	}
	void print() const {
		cout << (h ? h : 12) << ':';
		cout << setw(2) << setfill('0') << m;
		cout << (pm ? " p.m." : " a.m.") << nl;
	}
};

//#define FILEIO
int main() {
	//ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n;
	bool linebreak = false;;
	for (cin>>n; n; cin>>n) {
		if (linebreak) cout << nl;
		linebreak = true;

		int h, m; char t;
		vector<Time> res;
		for (int i=0; i<n; i++) {
			scanf("%d:%d %c.m.", &h, &m, &t);
			res.push_back(Time(h,m,t));
		}
		sort(res.begin(), res.end());

		for (const Time& it : res) {
			it.print();
		}
	}

	return 0;
}
