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

const int N = 300+1;
int g[N][N];
ld p[N][N];
ld ncr[N][N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(5);

	freopen("fetiera.in", "r", stdin);

	for(int i=0;i<N;i++) {
		ncr[i][0] = ncr[i][i] = 1;
		for(int j=1;j<i;j++) {
			ncr[i][j] = ncr[i-1][j-1] + ncr[i-1][j];
		}
	}

	int T;
	cin>>T;
	while(T--) {
		int n,k;
		cin>>n>>k;
		ld D = (ld)n*(n+1)*n*(n+1)/4;
		ld ans = 0;
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				cin>>g[i][j];
				p[i][j] = (ld)(i+1)*(j+1)*(n-i)*(n-j)/D;
				ld cur = 0;
				if(g[i][j]) {
					cur += (1 + pow(1-p[i][j]-p[i][j],k)) / 2;
				} else {
					cur += (1 - pow(1-p[i][j]-p[i][j],k)) / 2;
				}
				ans += cur;
			}
		}
		cout<<ans<<nl;
	}

	return 0;
}
