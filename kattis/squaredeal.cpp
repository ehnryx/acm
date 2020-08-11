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

bool solve(int a[], int b[]) {
	if(a[0]==a[1] && a[1]==a[2] && b[0]+b[1]+b[2]==a[0]) return true;
	if(a[0]==a[1] && b[0]+b[1]==a[2] && a[0]+b[2]==a[2]) return true;
	if(a[1]==a[2] && b[1]+b[2]==a[0] && a[1]+b[0]==a[0]) return true;
	if(a[2]==a[0] && b[2]+b[0]==a[1] && a[2]+b[1]==a[1]) return true;
	return false;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int a[3],b[3];
	for(int i=0;i<3;i++) {
		cin>>a[i]>>b[i];
	}
	if(solve(a,b)) { cout<<"YES"<<nl; return 0; }
	swap(a[0],b[0]);
	if(solve(a,b)) { cout<<"YES"<<nl; return 0; }
	swap(a[1],b[1]);
	if(solve(a,b)) { cout<<"YES"<<nl; return 0; }
	swap(a[0],b[0]);
	if(solve(a,b)) { cout<<"YES"<<nl; return 0; }
	swap(a[2],b[2]);
	if(solve(a,b)) { cout<<"YES"<<nl; return 0; }
	swap(a[0],b[0]);
	if(solve(a,b)) { cout<<"YES"<<nl; return 0; }
	swap(a[1],b[1]);
	if(solve(a,b)) { cout<<"YES"<<nl; return 0; }
	swap(a[0],b[0]);
	if(solve(a,b)) { cout<<"YES"<<nl; return 0; }

	cout<<"NO"<<nl;

	return 0;
}
