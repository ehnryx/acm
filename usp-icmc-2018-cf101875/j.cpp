#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
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

const int N = 1e5+1;
const int S = 350;
const int M = (N+S-1)/S;
int k;

vector<int> adj[N];

int cur = 0;
int depth[N];
int group[M][2*N];
int offset[M];

void update(int l, int r, int v) {
	//cerr << "UPDATE " << l << " " << r << " with " << v << nl;
	int lb = (l+S-1)/S;
	int rb = r/S;
	if (lb > rb) {
		//cerr << "  contained: " << l << " -> " << r << nl;
		for (int i=l; i<r; i++) {
			group[rb][depth[i]]--;
			if (offset[rb]+depth[i] <= k/2) cur--;
			group[rb][depth[i]+v]++;
			if (offset[rb]+depth[i]+v <= k/2) cur++;
			depth[i] += v;
		}
	} else {
		//cerr << "  left: " << l << " -> " << lb*S << nl;
		for (int i=l; i<lb*S; i++) {
			group[lb-1][depth[i]]--;
			if (offset[lb-1]+depth[i] <= k/2) cur--;
			group[lb-1][depth[i]+v]++;
			if (offset[lb-1]+depth[i]+v <= k/2) cur++;
			depth[i] += v;
		}
		//cerr << "  right: " << rb*S << " -> " << r << nl;
		for (int i=rb*S; i<r; i++) {
			group[rb][depth[i]]--;
			if (offset[rb]+depth[i] <= k/2) cur--;
			group[rb][depth[i]+v]++;
			if (offset[rb]+depth[i]+v <= k/2) cur++;
			depth[i] += v;
		}
		//cerr << "  middle: " << lb << " -> " << rb << nl;
		for (int i=lb; i<rb; i++) {
			if (v>0) {
				int d = k/2 - offset[i];
				cur -= group[i][d];
			} else {
				int d = k/2 - offset[i] - v;
				cur += group[i][d];
			}
			offset[i] += v;
		}
	}
}

int sub[N], start[N];
int sid = 0;

int tour(int u, int p) {
	start[u] = ++sid;
	depth[sid] = depth[start[p]]+1;
	group[sid/S][depth[sid]]++;
	cur += (offset[sid/S]+depth[sid] <= k/2);
	//cerr << "start " << u << " = " << start[u] << "  depth = " << depth[sid] << " -> " << offset[sid/S]+depth[sid] << nl;

	sub[u] = 1;
	for (int v : adj[u]) {
		if (v!=p) {
			sub[u] += tour(v, u);
		}
	}
	return sub[u];
}

int ans = 0;
void walk(int u, int p) {
	if (k%2 == 0) {
		ans = max(ans, cur);
		//cerr << " @ " << u << " w/ " << cur << nl;
	}

	for (int v : adj[u]) {
		if (v!=p) {
			update(start[v], start[v]+sub[v], -1);
			if (k%2 == 1) {
				ans = max(ans, cur);
				//cerr << " @ " << u << " -> " << v << " w/ " << cur << nl;
			}
			update(1, start[v], 1);
			update(start[v]+sub[v], sid+1, 1);
			walk(v, u);

			update(1, start[v], -1);
			update(start[v], start[v]+sub[v], 1);
			update(start[v]+sub[v], sid+1, -1);
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	fill(offset, offset+M, -N);

	int n;
	cin >> n >> k;
	for (int i=1; i<n; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	depth[0] = -1-offset[0];
	tour(1, 0);
	//cerr << "start with cur = " << cur << nl << nl;
	walk(1, 0);
	cout << ans << nl;

	return 0;
}
