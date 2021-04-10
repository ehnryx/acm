#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const char nl = '\n';

vector<ll> a, diff;
int n;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> n;
	a = vector<ll>(n+1);
	diff = vector<ll>(n);
	for (int i=1; i<=n; ++i) {
		cin >> a[i];
	}
	int d1 = 0;
	for (int i=1; i<n; ++i) {
		diff[i] = a[i+1]-a[i];
		if (diff[i] < 0) {
			d1 = i;
		}
	}
	if (!d1) {
		cout << "1 1\n";
		return 0;
	}

	int u1, u2;
	for (u1=d1; u1>0 && diff[u1] <= 0; --u1) {
	}
	for (u2=d1; u2<n && diff[u2] <= 0; ++u2) {
	}
	reverse(a.begin()+u1+1, a.begin()+u2+1);
	for (int i=1; i<n; ++i) {
		if (a[i+1]-a[i] < 0) {
			cout << "impossible\n";
			return 0;
		}
	}
	cout << u1+1 << " " << u2 << "\n";

	return 0;
}
