#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct Int {
	ll x;
	Int(ll n=0) {
		x = n%MOD;
	}
	Int operator * (const Int& other) {
		return Int(x*other.x);
	}
	Int operator + (const Int& other) {
		return Int(x+other.x);
	}
	int get() {
		return x;
	}
};

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	int n;
	int arr[100001];
	Int ans[100001];

	int T;
	cin >> T;
	while (T--) {
		cin >> n;
		arr[0] = 0;
		for (int i = 1; i <= n; i++)	{
			cin >> arr[i];
		}
		ans[0] = Int(0);
		for (int i = 1; i <= n; i++) {
			ans[i] = ans[i-1] * Int(arr[i]+1) + Int(arr[i]);
		}
		cout << ans[n].get() << nl;
	}

	return 0;
}
