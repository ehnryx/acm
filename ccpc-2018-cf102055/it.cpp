#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;

const int T1 = 20, T2 = 100, C = 1e9;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	mt19937 rng;
	cout << T2 << nl;
	for (int i = 0; i < T1; i++) {
		const int N = 1e5;
		cout << N << nl;
		for (int i = 0; i < N; i++) {
			cout << rng()%C+1 << " " << rng()%C+1 << nl;
		}
	}
	for (int i = T1; i < T2; i++) {
		const int N = 5000;
		cout << N << nl;
		for (int i = 0; i < N; i++) {
			cout << rng()%C+1 << " " << rng()%C+1 << nl;
		}
	}

	return 0;
}
