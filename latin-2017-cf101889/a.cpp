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

const int N = 14+1;
vector<pt> p[N];
int maxv[N], minv[N];
ld adj[N][N];

ld distance(int a, int b, ld d) {
	int pa = 1;
	int pb = p[b].size()-1;

	ld res = d - p[a][pa].real();
	while (p[a][pa].imag() != p[a][pa+1].imag() && p[b][pb].imag() != p[b][pb-1].imag()) {
		if (p[a][pa+1].imag() < p[b][pb-1].imag()) {
			ld top = p[b][pb-1].imag() - p[a][pa+1].imag();
			ld bot = p[a][pa+1].imag() - p[b][pb].imag();
			ld x = (top*p[b][pb].real() + bot*p[b][pb-1].real()) / (top+bot);
			res = min(res, x+d - p[a][pa+1].real());
			pa++;
		}
		else {
			ld top = p[a][pa+1].imag() - p[b][pb-1].imag();
			ld bot = p[b][pb-1].imag() - p[a][pa].imag();
			ld x = (top*p[a][pa].real() + bot*p[a][pa+1].real()) / (top+bot);
			res = min(res, p[b][pb-1].real()+d - x);
			pb--;
		}
	}
	return res;
}

ld dp[1<<N][N];
ld tsp(int bm, int last) {
	assert(bm);
	if (dp[bm][last] < 1) return dp[bm][last];

	int nxt = bm ^ 1<<last;
	ld res = 0;
	for (int i=0; i<N; i++) {
		if (nxt & 1<<i) {
			res = min(res, tsp(nxt, i) + adj[i][last]);
		}
	}
	return dp[bm][last] = res;
}

void init() {
	for (int i=0; i<1<<N; i++)
		for (int j=0; j<N; j++)
			dp[i][j] = 2;
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(3);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	init();

	int n, k, x, y;
	cin >> n;

	ld sum = 0;
	for (int i=0; i<n; i++) {
		minv[i] = INF;
		maxv[i] = -INF;

		cin >> k;
		for (int j=0; j<k; j++) {
			cin >> x >> y;
			minv[i] = min(minv[i], x);
			maxv[i] = max(maxv[i], x);
			p[i].push_back(pt(x,y));
		}
		p[i].push_back(p[i][0]);
		sum += maxv[i] - minv[i];
	}

	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			if (i != j) {
				adj[i][j] = -distance(i, j, maxv[i] - minv[j]);
			}
		}
	}

	ld ans = 1e22;
	for (int i=0; i<n; i++) {
		ans = min(ans, tsp((1<<n)-1, i));
	}
	cout << sum + ans << nl;

	return 0;
}
