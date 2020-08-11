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

struct Line {
	ll a, b, c;
	Line(const pii& p, const pii& q) {
		a = p.second-q.second;
		b = q.first-p.first;
		c = (ll)p.second*(p.first-q.first)-(ll)p.first*(p.second-q.second);
		ll g = __gcd(a, __gcd(b,c));
		a /= g; b /= g; c /= g;
	}
	bool operator < (const Line& o) const {
		if (a!=o.a) return a<o.a;
		if (b!=o.b) return b<o.b;
		else return c<o.c;
	}
};

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n;
	for (cin>>n; n; cin>>n) {
		int a, b;
		vector<pii> p;
		map<Line,int> cnt;
		for (int i=0; i<n; i++) {
			cin >> a >> b;
			p.push_back(pii(a,b));
			for (int j=0; j<i; j++) {
				cnt[Line(p[i],p[j])]++;
			}
		}
		int ans = 1;
		for (const pair<Line,int>& it : cnt) {
			//cerr << it.first.a << " " << it.first.b << " " << it.first.c << " -> " << it.second << nl;
			ans = max(ans, (int)floor(sqrt(2*it.second))+1);
		}
		cout << ans << nl;
	}

	return 0;
}
