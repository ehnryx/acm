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

const int N = 20;
string g[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	for(int n,m,tt=1;cin>>n>>m&&n;tt++) {
		swap(n,m);
		int s,t; s=t=-1;
		for(int i=0;i<n;i++) {
			cin>>g[i];
			for(int j=0;j<m;j++) {
				if(g[i][j] == '*') {
					s = i; t = j;
				}
			}
		}
		int dx,dy;
		if(s==0) tie(dx,dy) = pii(1,0);
		else if(s==n-1) tie(dx,dy) = pii(-1,0);
		else if(t==0) tie(dx,dy) = pii(0,1);
		else tie(dx,dy) = pii(0,-1);
		while(g[s][t]!='x') {
			s+=dx; t+=dy;
			if(g[s][t]=='/') {
				swap(dx,dy); dx = -dx; dy = -dy;
			} else if(g[s][t]=='\\') {
				swap(dx,dy);
			}
		}
		g[s][t] = '&';
		cout<<"HOUSE "<<tt<<nl;
		for(int i=0;i<n;i++) {
			for(int j=0;j<m;j++) {
				cout<<g[i][j];
			}
			cout<<nl;
		}
	}

	return 0;
}
