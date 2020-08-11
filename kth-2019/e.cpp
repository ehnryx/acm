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

	string line;

	getline(cin,line);
	int n = stoi(line);
	for(int i=0;i<n;i++) {
		getline(cin,line);
		int k = stoi(line);
		string name;
		getline(cin,name);
		bool pea = false;
		bool pan = false;
		for(int j=0;j<k;j++) {
			getline(cin,line);
			if(line == "pea soup") {
				pea = true;
			}
			if(line == "pancakes") {
				pan = true;
			}
		}
		if(pea && pan) {
			cout<<name<<nl;
			return 0;
		}
	}

	cout<<"Anywhere is fine I guess"<<nl;

	return 0;
}
