#pragma GCC optimize("O3")

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

struct Pair {
	int i, j;
};

const int N = 1e5;
int l[N], r[N], p[N], cnt[N];
unordered_map<int,int> vis[N];

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, a, b;
	cin >> n >> a >> b;
	if (a > b) swap(a,b);

	For(i,n) {
		cin >> l[i] >> r[i] >> p[i];
	}

	if (p[a]^p[b]) {
		cout << 0 << nl;
		return 0;
	}

	int ans = -1;
	const int CAP = 17;
	queue<Pair> bfs;
	bfs.push({a,b});
	vis[a][b] = 1;
	cnt[a]++; cnt[b]++;
	int tot = 1;
	while (!bfs.empty()) {
		Pair c = bfs.front();
		bfs.pop();
		{ // left
			int ni = min(l[c.i], l[c.j]);
			int nj = max(l[c.i], l[c.j]);
			if (ni != nj && !vis[ni].count(nj) && cnt[ni]<CAP && cnt[nj]<CAP) {
				if (p[ni]^p[nj]) {
					ans = vis[c.i][c.j];
					break;
				}
				vis[ni][nj] = vis[c.i][c.j]+1;
				bfs.push({ni,nj});
				cnt[ni]++; cnt[nj]++;
				tot++;
			}
		}
		{ // right
			int ni = min(r[c.i], r[c.j]);
			int nj = max(r[c.i], r[c.j]);
			if (ni != nj && !vis[ni].count(nj) && cnt[ni]<CAP && cnt[nj]<CAP) {
				if (p[ni]^p[nj]) {
					ans = vis[c.i][c.j];
					break;
				}
				vis[ni][nj] = vis[c.i][c.j]+1;
				bfs.push({ni,nj});
				cnt[ni]++; cnt[nj]++;
				tot++;
			}
		}
	}

	while (!bfs.empty()) bfs.pop();
	For(i,n) vis[i].clear();
	bfs.push({a,b});
	vis[a][b] = 1;
	tot = 1;
	while (!bfs.empty() && tot<3e6) {
		Pair c = bfs.front();
		bfs.pop();
		{ // left
			int ni = min(l[c.i], l[c.j]);
			int nj = max(l[c.i], l[c.j]);
			if (ni != nj && !vis[ni].count(nj)) {
				if (p[ni]^p[nj]) {
					cout << vis[c.i][c.j] << nl;
					return 0;
				}
				vis[ni][nj] = vis[c.i][c.j]+1;
				bfs.push({ni,nj});
				tot++;
			}
		}
		{ // right
			int ni = min(r[c.i], r[c.j]);
			int nj = max(r[c.i], r[c.j]);
			if (ni != nj && !vis[ni].count(nj)) {
				if (p[ni]^p[nj]) {
					cout << vis[c.i][c.j] << nl;
					return 0;
				}
				vis[ni][nj] = vis[c.i][c.j]+1;
				bfs.push({ni,nj});
				tot++;
			}
		}
	}

	if (ans != -1) cout << ans << nl;
	else cout << "indistinguishable" << nl;

	return 0;
}
