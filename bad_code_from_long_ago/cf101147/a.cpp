#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

int parity(int b, int n) {
	if (b == 1) {
		return n % 2;
	}
	vector<int> a;
	while (n > 0) {
		a.push_back(n % b);
		n /= b;
	}
	int m = a.size();
	int sum = 0;
	for (int i = 0; i < m; i++) {
		int j = i;
		while (a[j] == 0) 
			j++;
		if (i == j)
			sum ^= a[i] % 2;
		else {
			if (b % 2 == 0)
				sum ^= 2;
			else if ((j-i) % 2 == 0)
				sum ^= a[i] % 2;
			else
				sum ^= 2;
		}
		i = j;
	}
	return sum;
}

int main() {
	freopen("powers.in", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int T;
	cin >> T;
	while (T--) {
		int G, b, n;
		cin >> G;
		int ans = 0;
		for (int i = 0; i < G; i++) {
			cin >> b >> n;
			ans ^= parity(b, n);
		}
		if (ans) cout << 1 << nl;
		else cout << 2 << nl;
	}

	return 0;
}
