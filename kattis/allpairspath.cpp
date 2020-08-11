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
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 150;
int dist[N][N], odist[N][N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	for(int n,m,q;cin>>n>>m>>q&&n;) {
		memset(dist,INF,sizeof dist);
		for(int i=0;i<n;i++) dist[i][i] = 0;
		for(int i=0;i<m;i++) {
			int a,b,c;
			cin>>a>>b>>c;
			dist[a][b] = min(dist[a][b], c);
		}
		for(int k=0;k<n;k++) {
			for(int i=0;i<n;i++) {
				for(int j=0;j<n;j++) {
					if(dist[i][k]==INF || dist[k][j]==INF) continue;
					dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
				}
			}
		}
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				odist[i][j] = dist[i][j];
			}
		}
		for(int k=0;k<n;k++) {
			for(int i=0;i<n;i++) {
				for(int j=0;j<n;j++) {
					if(dist[i][k]==INF || dist[k][j]==INF) continue;
					dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
				}
			}
		}
		for(int i=0;i<q;i++) {
			int a,b;
			cin>>a>>b;
			if(dist[a][b]==INF) cout<<"Impossible"<<nl;
			else if(dist[a][b]==odist[a][b]) cout<<dist[a][b]<<nl;
			else cout<<"-Infinity"<<nl;
		}
		cout<<nl;
	}

	return 0;
}
