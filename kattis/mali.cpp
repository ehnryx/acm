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

int solve(vector<int> a, vector<int> b) {
	int ans = 0;
	for(int j=1,k=100;j<=100;j++) {
		while(k>0 && a[k]<=b[j]) {
			if(a[k]>0) ans = max(ans, j+k);
			b[j] -= a[k--];
		}
		if(b[j]>0) {
			ans = max(ans, j+k);
			a[k] -= b[j];
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin>>n;
	vector<int> ca(101), cb(101);
	for(int i=0;i<n;i++) {
		int a,b;
		cin>>a>>b;
		ca[a]++;
		cb[b]++;
		cout<<solve(ca,cb)<<nl;
	}

	return 0;
}
