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

const int N = 1e6+1;
vector<int> v[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin>>n;
	map<int,int> rmp;
	int a[n],b[n],c[n];
	for(int i=0;i<n;i++) {
		cin>>a[i]>>b[i];
		rmp[a[i]];
	}

	int id=0;
	for(auto& it:rmp) {
		it.second=id++;
	}
	memset(c,0,sizeof c);
	for(int i=0;i<n;i++) {
		a[i]=rmp[a[i]];
		v[a[i]].push_back(b[i]);
		c[a[i]]++;
	}

	n = id;
	for(int i=0;i<id;i++) {
		sort(v[i].begin(),v[i].end());
	}

	auto get = [&](int i, int j) {
		if(c[i]<4) {
			return v[i][j];
		} else {
			if(j<2) return v[i][j];
			else return v[i][c[i]-j+1];
		}
	};

	ll dp[n][4];
	fill(&dp[0][0],&dp[0][0]+n*4,-INFLL);
	for(int j=0;j<min(4,c[0]);j++) {
		dp[0][j] = 0;
	}
	for(int i=1;i<n;i++) {
		if(c[i] == 1) {
			for(int k=0;k<min(4,c[i-1]);k++) {
				dp[i][0] = max(dp[i][0], dp[i-1][k]+abs(get(i-1,k)-get(i,0)));
			}
		} else {
			for(int j=0;j<min(4,c[i]);j++) {
				for(int k=0;k<min(4,c[i-1]);k++) {
					for(int J=0;J<min(4,c[i]);J++) {
						if(j==J) continue;
						dp[i][J] = max(dp[i][J], dp[i-1][k]+abs(get(i-1,k)-get(i,j)));
					}
				}
			}
		}
	}
	cout<<max(max(dp[n-1][0],dp[n-1][1]),max(dp[n-1][2],dp[n-1][3]))<<nl;

	return 0;
}
