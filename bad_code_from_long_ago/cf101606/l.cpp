#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const int INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;

#define USE_MAGIC_IO
#ifdef USE_MAGIC_IO
inline char get(void) {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
inline void read(int &x) {
	static char c; x = 0; int sgn = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
	if (sgn) x = -x;
}
#else
#define get() getchar()
#define read(x) scanf("%d",&x)
#endif

struct Double {
	ld argument;
	Double(ld k = INF): argument(k) {}
	bool operator < (const Double& other) {
		return argument < other.argument - EPS;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	ll x, y;
	int xx, yy;
	int a, b;
	int h;
	int n;

	//cin >> x >> y;
	//cin >> n;
	read(xx); read(yy); x = xx; y = yy;
	read(n);

	vector<vector<pair<ll, int>>> lines;
	map<ld, int> idx;
	for (int i = 0; i < n; i++) {
		//cin >> a >> b >> h;
		read(a); read(b); read(h);

		ld angle = arg(pt(a-x, b-y));
		ll dist = (b-y)*(b-y) + (a-x)*(a-x);

		ld key = angle;
		if (!idx.count(key)) {
			idx[key] = lines.size();
			lines.push_back({});
		}
		lines[idx[key]].push_back(pair<ll, int>(dist, h));
	}

	int ans = 0;
	int lis[n];
	for (int j = 0; j < lines.size(); j++) {
		int m = lines[j].size();
		memset(lis, INF, m*sizeof(lis[0]));
		sort(lines[j].begin(), lines[j].end());
		for (int i = 0; i < m; i++) {
			int* it = lower_bound(lis, lis+m, lines[j][i].second);
			*it = lines[j][i].second;
		}
		ans += lower_bound(lis, lis+m, INF) - lis;
	}
	cout << ans << nl;

	return 0;
}
