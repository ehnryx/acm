#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e6+100;
vector<int> primes;

void init() {
	const int lim = sqrt(N);
	bitset<N> notp;
	notp[0] = notp[1] = true;
	for (int i = 2; i < lim; i++) {
		if (notp[i]) {
			for (int j = i*i; j < N; j++) {
				notp[j] = true;
			}
		}
	}
	for (int i = 2; i < N; i++) {
		if (!notp[i]) {
			primes.push_back(i);
		}
	}
}

int phi(int n) {
	int res = 1;
	int lim = sqrt(n);

	for (int p : primes) {
		if (p > lim) break;
		if (n % p == 0) {
			int cnt = 0;
			while (n % p == 0) {
				n /= p;
				cnt++;
			}
			res *= p-1;
			for (int i = 1; i < cnt; i++) {
				res *= p;
			}
			lim = sqrt(n);
		}
	}
	if (n > 1) {
		res *= n-1;
	}
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
	init();

	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		//cerr << "phi: " << phi(n) << endl;
		cout << (ll) phi(n) * (n-1) << nl;
	}

	return 0;
}
