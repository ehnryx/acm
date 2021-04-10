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

vector<int> dx = { 1, 1, -1, -1, 2, 2, -2, -2 };
vector<int> dy = { 2, -2, 2, -2, 1, -1, 1, -1 };

const int N = 100+4;
char g[N][N];
int dist[N][N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin>>n;
	fill(&g[0][0],&g[0][0]+N*N,'#');
	int s,t;
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cin>>g[2+i][2+j];
			if(g[2+i][2+j] == 'K') {
				s=2+i; t=2+j;
			}
		}
	}

	queue<pii> bfs;
	bfs.push(pii(s,t));
	memset(dist,-1,sizeof dist);
	dist[s][t] = 0;
	while(!bfs.empty()) {
		int i,j;
		tie(i,j) = bfs.front();
		bfs.pop();
		for(int d=0;d<8;d++) {
			int ni = i+dx[d];
			int nj = j+dy[d];
			if(dist[ni][nj]==-1 && g[ni][nj]!='#') {
				dist[ni][nj] = dist[i][j]+1;
				bfs.push(pii(ni,nj));
			}
		}
	}
	cout<<dist[2][2]<<nl;

	return 0;
}
