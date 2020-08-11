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

	cout << "50\n";
	mt19937 rng;
	for (int i = 0; i < 50; i++) {
		cout << rng()%10 << " ";
	}
	cout << nl;

	return 0;
}
