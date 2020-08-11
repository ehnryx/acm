#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;

const string s[12] = {
	"Do",
	"Do#",
	"Re",
	"Re#",
	"Mi",
	"Fa",
	"Fa#",
	"Sol",
	"Sol#",
	"La",
	"La#",
	"Si"
};

const int N = 1e7;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cout << N << nl;
	mt19937 rng;
	for (int i = 0; i < N; i++) {
		cout << s[rng()%12] << nl;
	}

	return 0;
}
