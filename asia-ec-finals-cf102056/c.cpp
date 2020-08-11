#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int MAXP = 4e4;
const int MAXN = 1e9+1;
const char nl = '\n';
const int INF = 0x3f3f3f3f;
const int N = 200;

vector<int> off[11];
vector<int> primes;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	bitset<MAXN> square;
	bitset<MAXP> np;
	np[0] = np[1] = 1;
	for (int i=2; i*i<MAXP; i++) {
		if (!np[i]) {
			for (int j=i*i; j<MAXP; j += i) {
				np[j] = 1;
			}
		}
	}
	for (int i=10; i < MAXP; i++) {
		if (!np[i]) primes.push_back(i);
	}

	for (int p : primes) {
		int add = p*p;
		for (int j=add; j<MAXN; j+=add) {
			square[j] = true;
		}
	}
	//cerr << square.count() << " squares " << nl;

	string s;
	for (int i = 0; i < 10; i++) {
		string t; cin >> t; s += t;
	}
	for (int i : {2, 3, 5, 7}) {
		for (int j = 0; j < i*i; j++) {
			bool good = 1;
			for (int k = j; k < N; k += i*i) {
				if (s[k] == '1') {
					good = 0;
					break;
				}
			}
			if (good) {
				off[i].push_back((i*i-j)%(i*i));
			}
		}
	}

	if (off[2].size() != 1 || off[3].size() != 1 || off[5].size() != 1 || off[7].empty()) {
		puts("-1");
		return 0;
	}

	/*
	for (int i : {2, 3, 5, 7}) {
		cerr << i << ": ";
		for (int j : off[i]) cerr << j << " ";
		cerr << nl;
	}
	*/

	const int mod = 2*3*5*7*2*3*5*7;
	int ans = INF;
	for (int k : off[7]) {
		int rem = -1;
		for (int i=0; i<mod; i++) {
			if (i%4 == off[2][0] && i%9 == off[3][0] && i%25 == off[5][0] && i%49 == k) {
				rem = i;
				break;
			}
		}
		assert(rem != -1);
		if (rem == 0) rem = mod;

		//cerr << rem << " mod " << mod << nl;

		for (int i=rem; i+N<=MAXN; i+=mod) {
			bool ok = true;
			for (int j=0; j<N; j++) {
				int ij = i+j;
				if (ij%4==0 || ij%9==0 || ij%25==0 || ij%49==0) continue;
				if ((s[j] == '0' && !square[ij]) || (s[j] == '1' && square[ij])) {
					ok = false;
					break;
				}
			}
			if (ok) {
				ans = min(ans, i);
				break;
			}
		}
	}

	if (ans == INF) {
		cout << -1 << nl;
	} else {
		cout << ans << nl;
	}

	return 0;
}
