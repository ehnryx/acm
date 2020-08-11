#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
#define nl '\n'

void solve() {
	int amt = 0;
	int a[110];
	int n, m;
	cin >> n >> m;
	//cerr << " N = " << n << endl;
	for (int i=0; i<n; ++i) {
		cin >> a[i];
	}
	int k = 9;
	int pgoal = a[m];
	int i;
	for (i=0; i<n; ++i) {
		amt += (a[i] > pgoal && a[i] <= 9);
	}
	int lastseen = n*100;
	i = n*100;
	for (; k>pgoal; --i) {
		if (a[i%n] == k || i == lastseen-n) {
			--k;
			lastseen = i;
			++i;
		}
	}
	//cerr << " i = " << i << " i e " << i%n << endl;
	for (; i%n != m; ++i) {
		if (a[i%n] == pgoal) ++ amt;
	}
	++ amt;
	cout << amt << "\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int TT;
	cin >> TT;
	while (TT--) {
		solve();
	}

	return 0;
}
