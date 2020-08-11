#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int a, b, c;
	cin >> a >> b >> c;
	if ((a^b) == 0 && (b^c) == 0) cout << "*" << endl;
	else if ((a^b) == 0) cout << "C" << endl;
	else if ((b^c) == 0) cout << "A" << endl;
	else cout << "B" << endl;

	return 0;
}
