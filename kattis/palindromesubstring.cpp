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

	for(string s;cin>>s;) {
		set<string> ans;
		int n = s.size();
		for(int i=0;i<n;i++) {
			for(int j=1;i-j>=0&&i+j<n&&s[i-j]==s[i+j];j++) {
				ans.insert(s.substr(i-j,2*j+1));
			}
			if(i>0) {
				for(int j=1;i-j>=0&&i+j-1<n&&s[i-j]==s[i+j-1];j++) {
					ans.insert(s.substr(i-j,2*j));
				}
			}
		}
		for(const string& it:ans) {
			cout<<it<<nl;
		}
		cout<<nl;
	}

	return 0;
}
