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
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 100+1;
int ally[N];
int dist[N][N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n,m,B,A;
	cin >> n >> m >> B >> A;
	if(n<1 || n>100) for(;;);

	for (int i=0;i<A;i++) {
		int a;
		cin >> a;
		if(a<0 || a>=n) for(;;);
		ally[a] = true;
	}

	memset(dist,INF,sizeof dist);
	for (int i=0;i<n;i++) {
		dist[i][i] = 0;
	}

	for (int i=0;i<m;i++) {
		int a,b;
		cin >> a >> b;
		if(a<0 || a>=n || b<0 || b>=n) for(;;);
		dist[a][b] = 1 - ally[b];
		dist[b][a] = 1 - ally[a];
	}

	for (int k=0;k<n;k++) {
		for (int i=0;i<n;i++) {
			for (int j=0;j<n;j++) {
				dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
			}
		}
	}

	if(dist[0][n-1] <= 2+B) {
		cout << dist[0][n-1] << nl;
	} else {
		cout << -1 << nl;
	}

	return 0;
}
