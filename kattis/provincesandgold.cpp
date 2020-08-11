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

	int g,s,c;
	cin>>g>>s>>c;
	int n = g*3+s*2+c;
	if(n<2) cout<<"Copper"<<nl;
	else if(n<3) cout<<"Estate or Copper"<<nl;
	else if(n<5) cout<<"Estate or Silver"<<nl;
	else if(n<6) cout<<"Duchy or Silver"<<nl;
	else if(n<8) cout<<"Duchy or Gold"<<nl;
	else cout<<"Province or Gold"<<nl;

	return 0;
}
