#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int N; cin >> N;
	for(int i=0;i<N;++i) {
		ll K ; cin >> K;
		cout << (1LL << K)-1 << endl;
	}
	return 0;
}
