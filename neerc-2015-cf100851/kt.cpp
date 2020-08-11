#include <bits/stdc++.h>
using namespace std;
#define FILENAME FIGHSILDEHFJiADSFSDFGJLSDGJDGHS

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif

	const int N = 1e5, M = 1e5;
	int lab[N]; iota(lab, lab + N, 0);
	shuffle(lab, lab + N, mt19937(time(0)));
	cout << N << " " << M << nl;
	for (int i = 0; i < N; i++) {
		cout << lab[i]+1 << " " << lab[(i+1)%N]+1 << nl;
	}
	/*
	for (int i = N; i < M; i++) {
		cout << (i-N)*20+1 << " " << (i-N)*20+10 << nl;
	}*/


	return 0;
}
