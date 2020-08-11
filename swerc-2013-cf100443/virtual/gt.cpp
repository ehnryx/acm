#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

#define nl '\n'

int col[101];
const int N = 80;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cout << N << nl;
	mt19937 rng;
	for (int i = 0; i < N; i++) {
		col[i] = rng()%4;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (col[i] != col[j] && rng()%50 < 3) cout << i+1 << "-" << j+1 << nl;
		}
	}

	return 0;
}
