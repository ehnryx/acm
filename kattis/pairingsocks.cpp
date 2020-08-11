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



int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin>>n;
	stack<int> left,right;
	for(int i=0;i<2*n;i++) {
		int a;
		cin>>a;
		left.push(a);
	}

	int ans = 0;
	while(!left.empty()) {
		ans++;
		if(!right.empty() && left.top()==right.top()) {
			left.pop();
			right.pop();
		} else {
			right.push(left.top());
			left.pop();
		}
	}

	if(right.empty()) {
		cout<<ans<<nl;
	} else {
		cout<<"impossible"<<nl;
	}

	return 0;
}
