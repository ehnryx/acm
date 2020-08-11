#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e4;
int p[N], s[N];
ll c;

struct Int {
	int i;
	operator int() const { return i; }
	bool operator < (const Int& o) const {
		return value() < o.value();
	}
	ll value() const {
		return p[i] - s[i] + i*c;
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
	cin >> n >> c;

	vector<Int> nxt;
	For(i,n) {
		cin >> p[i];
	}
	For(i,n) {
		cin >> s[i];
		nxt.push_back({i});
	}
	sort(nxt.begin(), nxt.end());

	ll ans = 0;
	int pos = 0;
	for (int i=n-1; i>=0; i--) {
		int need = s[i] - min(s[i],p[i]);
		for (int k=0; k<n && need; k++, pos=(pos+1==n?0:pos+1)) {
			int j = nxt[pos];
			if (j >= i) continue;
			if (s[j]-p[j] < j*c) {
				int take = min((ll)need, min(c, p[j]-s[j]+j*c));
				p[j] -= take;
				need -= take;
			}
		}
		ans += s[i]-need;
	}
	cout << ans << nl;

	return 0;
}
