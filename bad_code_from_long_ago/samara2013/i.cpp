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

// MODINT
template<int MOD> struct ModInt {
	ll x;
	ModInt(ll n=0) { n %= MOD; if (n < 0) n += MOD; x = n; }
	int get() const { return (int) x; }
	ModInt operator + (const ModInt& other) { return ModInt(x + other.x); }
	ModInt operator - (const ModInt& other) { return ModInt(x + MOD - other.x); }
	ModInt operator * (const ModInt& other) { return ModInt(x * other.x); } 
	ModInt& operator += (const ModInt& other) { x = (x + other.x) % MOD; return *this; }
	ModInt& operator -= (const ModInt& other) { x = (x + MOD - other.x) % MOD; return *this; }
	ModInt& operator *= (const ModInt& other) { x = (x * other.x) % MOD; return *this; }
};

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	int dir[2002];
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> dir[n-i];
	} 
	dir[n+1] = 1;
	// init
	ll cap = 2e9+1;
	ll arr[2001][2001];
	arr[1][1] = 1;
	int shift;
	// build
	for (int i = 2; i <= n; i++) {
		// shift
		if (dir[i] == 0) {
			shift = max(arr[i-1][1], arr[i-1][i-1]) + 1;
			for (int j = 1; j < i; j++)
				arr[i-1][j] -= shift;
		}
		// build
		if (dir[i] == 0) arr[i][1] = -1;
		else arr[i][1] = 1;
		for (int j = 2; j <= i; j++) {
			arr[i][j] = arr[i][j-1] + arr[i-1][j-1];
			if (abs(arr[i][j]) > 2e9+1)
				goto impossible;
		}
		if (dir[i] == 0) {
			shift = -arr[i][i] + 1;
			for (int j = 1; j <= i; j++) {
				arr[i][j] += shift;
			}
		}
	}
#ifdef DEBUG
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++)
			cout << arr[i][j] << " ";
		cout << nl;
	}
#endif
	// output
	for (int j = 1; j <= n; j++) {
		cout << arr[n][j] - 1 - (int)1e9 << " ";
	} cout << nl;
	return 0;

	impossible:
	cout << "IMPOSSIBLE" << endl;
	return 0;
}
