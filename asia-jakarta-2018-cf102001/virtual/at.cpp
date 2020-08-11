#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	const int N = 2000;
	mt19937 rng;
	for (int i = 0; i < N; i++) {
		cout << char(rng()%2+'0');
	}
	cout << nl;

	return 0;
}
