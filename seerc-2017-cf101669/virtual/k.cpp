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

	int n;
	cin >> n;

	vector<pii> p;
	for (int i=0; i<n; i++) {
		int a;
		cin >> a;
		p.push_back(pii(a,i));
	}
	sort(p.begin(), p.end());

	int ans[n];
	for (int i=0; i<n; i++) {
		ans[p[i].second] = n-i;
	}
	for (int i=0; i<n; i++) {
		cout << ans[i] << " ";
	}
	cout << nl;

	return 0;
}
