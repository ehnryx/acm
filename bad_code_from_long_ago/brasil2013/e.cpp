#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	bitset<10001> alive;
	int n, r, a;
	cin >> n >> r;
	for (int i = 0; i < r; i++) {	
		cin >> a;
		alive[a] = true;
	}
	for (int i = 1; i <= n; i++) {
		if (alive[i] == false) cout << i << " ";
	}
	if (n == r) cout << "*";
	cout << endl;

	return 0;
}
