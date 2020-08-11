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
struct Int {
	ll x;
	Int(ll n=0) { n %= MOD; if (n < 0) n += MOD; x = n; }
	int get() const { return (int) x; }
	Int operator + (const Int& other) { return Int(x + other.x); }
	Int operator - (const Int& other) { return Int(x + MOD - other.x); }
	Int operator * (const Int& other) { return Int(x * other.x); } 
	Int& operator += (const Int& other) { x = (x + other.x) % MOD; return *this; }
	Int& operator -= (const Int& other) { x = (x + MOD - other.x) % MOD; return *this; }
	Int& operator *= (const Int& other) { x = (x * other.x) % MOD; return *this; }
};

Int getburn(int n, ll pillar[], int start) {
	Int res;
	int next;
	if (start == 0) {
		next = n-1;
	} else {
		next = 0;
	}
	while (start != next) {
		res += Int(abs(pillar[start] - pillar[next]));
		if (start > next) {
			next = start-1;
			start = next;
		} else {
			next = start+1;
			start = next;
		}
	}
	return res;
}

void init(int n, Int fact[]) {
	int x, y;
	fact[0] = Int(1);
	for (int i = 1; i <= n; i++) {
		fact[i] = fact[i-1] * Int(i);
	}
}

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	int n;
	cin >> n;
	ll pillar[n];
	ll home; cin >> home;
	bool allsame = true;
	for (int i = 0; i < n; i++) {
		cin >> pillar[i];
		if (i > 0 && pillar[i] != pillar[i-1])
			allsame = false;
	}
	sort(pillar, pillar+n);

	// - = left, + = right
	ll burndiff = 0;
	for (int i = 0; i < n/2; i++) {
		burndiff += pillar[i+1]-pillar[i];
		burndiff -= pillar[n-i-1] - pillar[n-i-2];
	}
	if (n % 2 == 1) {
		burndiff -= abs(home - pillar[n/2]) + abs(home - pillar[0]);
		burndiff += abs(home - pillar[n/2]) + abs(home - pillar[n-1]);
	} else {
		burndiff -= abs(home - pillar[n/2]) + abs(home - pillar[0]);
		burndiff += abs(home - pillar[n/2-1]) + abs(home - pillar[n-1]);
	}
	
	Int burn;
	if (burndiff > 0) {
		burn = getburn(n, pillar, n-1);
		if (n % 2 == 1) {
			burn += Int(abs(home - pillar[n/2]) + abs(home - pillar[n-1]));
		} else {
			burn += Int(abs(home - pillar[n/2-1]) + abs(home - pillar[n-1]));
		}
	} else {
		burn = getburn(n, pillar, 0);
		burn += Int(abs(home - pillar[n/2]) + abs(home - pillar[0]));
	}

	Int fact[n+1];
	init(n, fact);
	Int ans = Int(1);
	int cnt = 1;
	for (int i = 1; i < n; i++) {
		if (pillar[i] == pillar[i-1]) {
			cnt++;
		} else {
			ans *= fact[cnt];
			cnt = 1;
		}
	}
	ans *= fact[cnt];
	if (burndiff == 0 && !allsame) {
		ans *= Int(2);
	}
	
	cout << burn.get() << " " << ans.get() << endl;

	return 0;
}
