#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const char nl = '\n';

const int N = 505;
ld fac[N];

void setup() {
	fac[0] = 0;
	for (int i=1; i<N; ++i) {
		fac[i] = fac[i-1]+log(i);
	}
}

ld chooseOver(int n, int k, int m, int q) {
	// n choose k over m choose q
	assert(k <= n);
	assert(k >= 0);
	ld nckl = fac[n]-fac[k]-fac[n-k];
	ld mcql = fac[m]-fac[q]-fac[m-q];
	ld ansl = nckl-mcql;
	if (ansl < -40) {
		return 0;
	}
	return exp(ansl);
}

ld p[N];
int n, k;
ld ans[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	setup();
	cin >> n >> k;
	for (int i=0; i<n; ++i) {
		cin >> p[i];
	}

	for (int i=0; i<n; ++i) {
		for (int j=0; j<=n-k; ++j) {
			int z = (i+n-j)%n;
			ans[i] += chooseOver(n-1-j, k-1, n, k)*p[z];
		}
	}

	cout << fixed <<setprecision(10);
	for (int i=0; i<n; ++i) {
		cout << ans[i] << " ";
	}
	cout << "\n";

	return 0;
}
