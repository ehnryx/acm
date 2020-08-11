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

struct Gridcmp {
	int count;
	int index;
	Gridcmp(int i, int c) {
		index = i;
		count = c;
	}
	bool operator < (const Gridcmp& other) const {
		return this->count < other.count;
	}
};

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	int kkk, n, m, count;
	vector<Gridcmp> order;
	vector<vector<string>> grids;
	string line;
	cin >> kkk >> n >> m;
	grids.resize(kkk);
	for (int i = 0; i < kkk; i++) {
		count = 0;
		for (int j = 0; j < n; j++) {
			cin >> line;
			grids[i].push_back(line);
			for (int k = 0; k < m; k++) {
				if (grids[i][j][k] == '0')
					count++;
			}
		}
		order.push_back(Gridcmp(i, count));
	} sort(order.begin(), order.end());
	int pic[n][m];
	memset(pic, INF, sizeof(pic));
	int prev = -1;
	int cnt = 0;
	int ans[kkk];
	for (Gridcmp curr: order) {
		if (prev == -1) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < m; k++) {
					if (grids[curr.index][j][k] == '0')
						pic[j][k] = 0;
				}
			}
		}
		else {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < m; k++) {
					if (grids[curr.index][j][k] == '1' && grids[prev][j][k] == '0') {
						cout << "IMPOSSIBLE" << endl;
						return 0;
					}
					if (grids[curr.index][j][k] == '0' && grids[prev][j][k] == '1')
						pic[j][k] = cnt;
				}
			}
		}
		ans[curr.index] = ++cnt;
		prev = curr.index;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cout << min((int)1e9, pic[i][j]) << " ";
		cout << nl;
	}
	for (int i = 0; i < kkk; i++) {
		cout << ans[i] << " ";
	} cout << nl;
	return 0;
}
