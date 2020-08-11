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



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	string cur;
	cin>>cur;
	int n;
	cin>>n;
	string s[n];
	map<char,int> cnt;
	for(int i=0;i<n;i++) {
		cin>>s[i];
		cnt[s[i].front()]++;
	}
	for(int i=0;i<n;i++) {
		if(s[i].front() == cur.back()) {
			if(cnt[s[i].back()] - (s[i].back()==s[i].front()) == 0) {
				cout<<s[i]<<"!"<<nl;
				return 0;
			}
		}
	}
	for(int i=0;i<n;i++) {
		if(s[i].front() == cur.back()) {
			cout<<s[i]<<nl;
			return 0;
		}
	}
	cout<<"?"<<nl;

	return 0;
}
