#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;

const int unrot[10] = {
	0b010111010,
	0b111100100,
	0b110011001,
	0b011010110,
	0b110010011,
	0b010010111,
	0b010111011,
	0b010011110,
	0b011111110,
	0b001111110
};

ll tiles[10][4];
int rot(int x) {
	int ans = 0;
	ans += (1 << 8) * ((x >> 6) & 1);
	ans += (1 << 7) * ((x >> 3) & 1);
	ans += (1 << 6) * ((x >> 0) & 1);
	ans += (1 << 5) * ((x >> 7) & 1);
	ans += (1 << 4) * ((x >> 4) & 1);
	ans += (1 << 3) * ((x >> 1) & 1);
	ans += (1 << 2) * ((x >> 8) & 1);
	ans += (1 << 1) * ((x >> 5) & 1);
	ans += (1 << 0) * ((x >> 2) & 1);
	return ans;
}

void printtile(int x) {
	for (int i = 2; i >= 0; i--) {
		for (int j = 2; j >= 0; j--) {
			cerr << ((x >> (3*i+j) & 1));
		}
		cerr << nl;
	}
}
void printgrid(int x) {
	for (int i = 9; i >= 0; i--) {
		for (int j = 2; j >= 0; j--) {
			cerr << ((x >> (3*i+j) & 1));
		}
		cerr << nl;
	}
}

void pre() {
	for (int i = 0; i < 10; i++) {
		//cerr << "TILE " << i << nl;
		tiles[i][0] = unrot[i];
		//printtile(tiles[i][0]); cerr << nl;
		for (int j = 1; j < 4; j++) {
			tiles[i][j] = rot(tiles[i][j-1]);
			//printtile(tiles[i][j]); cerr << nl;
		}
	}
}

const int N = 52;
int n;
int a[N];

inline ll h(ll bm, int pos) {
	return (bm << 9) + pos;
}

unordered_map<ll, int> dp;
unordered_set<ll> vis;
unordered_map<ll, unordered_map<int, ll>> par;

int solve(ll bm, int pos) {
	//assert(bm < (1LL << 30));
	ll ha = h(bm, pos);
	if (dp.count(ha)) return dp[ha];
	if (vis.count(ha)) {
		puts("-1");
		exit(0);
	}
	vis.insert(ha);
	ll x = tiles[a[pos]][0];
	if ((bm & (x << 27)) || (bm & (x << 24)) || (bm & (x << 21))) return dp[ha] = 0;
	x = 0b111111111 << 21;
	if (bm & x) return dp[ha] = 0;
	int ans = 0;
	for (int i = 0; i < 4; i++) {
		ll cur = tiles[a[pos]][i] << (3*9);
		/*
		if (i == 0 && (cur & bm)) {
			return dp[ha] = 0;
		}*/
		for (int j = 9; j >= 0; j--, cur >>= 3) {
			if ((cur & bm) || j == 0) {
				if (j >= 7) {
					break;
				}
				if (cur & bm) {
					cur <<= 3;
				}
				//assert(!(bm & cur));
				ll nbm = bm ^ cur;
				//cerr << "before:\n"; printgrid(nbm);
				for (int k = 9; k >= 0; k--) {
					ll mask = 7LL << (3*k);
					if ((mask & nbm) == mask) {
						ll add = (nbm & ~((1LL << (3*(k+1))) - 1)) >> 3;
						nbm &= (1LL << (3*k)) - 1;
						nbm += add;
					}
				}
				//cerr << "after:\n"; printgrid(nbm);
				if (solve(nbm, (pos+1)%n)+1 > ans) {
					par[bm][pos] = nbm;
				}
				ans = max(ans, solve(nbm, (pos+1)%n)+1);
				break;
			}
		}
	}
	//printgrid(bm); cerr << a[pos] << " -> " << ans <<nl;
	return dp[ha] = ans;
}

int recover(ll bm, int pos) {
	cerr << "pos = " << pos << nl;
	printgrid(bm);
	if (par.count(bm) && par[bm].count(pos)) {
		int k = recover(par[bm][pos], (pos+1)%n)+1;
		assert(k == solve(bm, pos));
		return k;
	} else return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	pre();
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cout << solve(0, 0) << nl;
	//recover(0, 0);

	return 0;
}
