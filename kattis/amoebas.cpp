#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_cxx;
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

vector<int> di = {0,0,1,1,1,-1,-1,-1};
vector<int> dj = {1,-1,0,1,-1,0,1,-1};

const int N = 2e4+1;
int dsu[N];
int find(int i) {
	if(dsu[i]==-1) return i;
	return dsu[i]=find(dsu[i]);
}
void link(int i, int j) {
	if(find(i)!=find(j)) dsu[find(i)]=find(j);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n,m;
	cin>>n>>m;
	memset(dsu,-1,sizeof dsu);
	char g[n+2][m+2];
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			cin>>g[i][j];
		}
	}

	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			if(g[i][j]=='#') {
				for(int d=0;d<8;d++) {
					int ni = i+di[d];
					int nj = j+dj[d];
					if(g[ni][nj]=='#') {
						link(i*(m+2)+j,ni*(m+2)+nj);
					}
				}
			}
		}
	}

	int ans = 0;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			if(g[i][j]=='#' && find(i*(m+2)+j)==i*(m+2)+j) {
				ans++;
			}
		}
	}
	cout<<ans<<nl;

	return 0;
}
