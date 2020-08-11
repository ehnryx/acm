#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	set<int> points;
	int n, a, sum;
	sum = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a;
		sum += a;
		if (i == n-1) points.insert(0);
		else points.insert(sum);
	}
	int tri = 0;
	for (auto& p: points) {
		if (points.count((p+sum/3)%sum) && points.count((p+2*sum/3)%sum))
			tri++;
	}
	if (sum%3 != 0) {
		cout << "0" << endl;
	}
	else {
		cout << tri/3 << endl;
	}

	return 0;
}
