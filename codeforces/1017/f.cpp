#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 17400;
const int M = 132;

int modpow(int a, int p, int m) {
	ll b = a;
	ll v = 1;
	while (p > 0) {
		if (p & 1) v = v*b % m;
		b = b*b % m;
		p >>= 1;
	}
	return v;
}

vector<int> primes;

bool miller_rabin(int n) {
	for (int i = 1; i < 5; i++) {
		if (n % primes[i] == 0) return false;
	}

	int s = 0;
	int d = n-1;
	while (d % 2 == 0) {
		s++;
		d /= 2;
	}

	for (int r = 0; r < 1; r++) {
		int a = 2+rng()%(n-2);
		bool good = true;
		if (modpow(a,d,n) == 1) {
			good = false;
		}
		for (int i = 0; i < s; i++) {
			if (modpow(a,d<<i,n) == n-1) {
				good = false;
				break;
			}
		}
		if (good) {
			return true;
		}
	}
	return false;
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, a, b, c, d;
	cin >> n >> a >> b >> c >> d;

	auto f = [&] (unsigned int x) {
		return (unsigned int)((unsigned int)a * x*x*x + (unsigned int)b * x*x + (unsigned int)c * x + (unsigned int)d);
	};

	bitset<N> np;
	np[0] = np[1] = true;
	for (int i = 2; i < 132; i++) {
		if (!np[i]) {
			for (int j = i*i; j < N; j+=i) {
				np[j] = true;
			}
		}
	}

	for (int i = 2; i < N; i++) {
		if (!np[i]) {
			primes.push_back(i);
		}
	}

	unsigned int ans = 0;
	for (int p : primes) {
		unsigned int cur = n/p;
		unsigned int cnt = 0;
		while (cur > 0) {
			cnt += cur;
			cur /= p;
		}
		ans += cnt * f(p);
	}

	cerr << "miller rabin part" << endl;
	for (int i = primes.back()+2; i <= n; i+=2) {
		if (miller_rabin(i)) {
			ans += f(i);
		}
		if (i % 1000000 == 1) cerr << "done " << i << nl;
	}

	cout << ans << nl;

	return 0;
}
