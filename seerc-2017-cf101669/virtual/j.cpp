#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;

const int N = 1e5+10;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n; cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	if (n == 1) {
		puts("Win");
		return 0;
	}
	sort(a.rbegin(), a.rend());
	if (n == 2) {
		puts(a[1] == 1 ? "Win" : "Lose");
		return 0;
	}
	if (a[2] > 1) {
		puts("Lose");
		return 0;
	}
	if (a[0] == 1) {
		puts(n % 3 ? "Win" : "Lose");
		return 0;
	}
	if (a[1] == 2) {
		puts(n % 3 == 2 ? "Lose" : "Win");
		return 0;
	}
	if (a[1] == 1) {
		puts("Win");
		return 0;
	}
	puts("Lose");

	return 0;
}
