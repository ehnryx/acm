#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void findchange(ll ch[]) {
	pair<int,int> mincoins;
	int coinnum[5000];
	coinnum[0] = 0;
	ch[0] = 0;
	for (int i = 1; i < 5000; i++) {
		mincoins = pair<int,int>(6000, 6000);
		if (i >= 1 && 1 + coinnum[i-1] < mincoins.first)
			mincoins = pair<int,int>(1 + coinnum[i-1], 1 + ch[i-1]);
		if (i >= 5 && 1 + coinnum[i-5] < mincoins.first)
			mincoins = pair<int,int>(1 + coinnum[i-5], 5 + ch[i-5]);
		if (i >= 10 && 1 + coinnum[i-10] < mincoins.first)
			mincoins = pair<int,int>(1 + coinnum[i-10], 10 + ch[i-10]);
		if (i >= 50 && 1 + coinnum[i-50] < mincoins.first)
			mincoins = pair<int,int>(1 + coinnum[i-50], 50 + ch[i-50]);
		if (i >= 100 && 1 + coinnum[i-100] < mincoins.first)
			mincoins = pair<int,int>(1 + coinnum[i-100], 100 + ch[i-100]);
		if (i >= 500 && 1 + coinnum[i-500] < mincoins.first)
			mincoins = pair<int,int>(1 + coinnum[i-500], ch[i-500]);
		if (i >= 1000 && 1 + coinnum[i-1000] < mincoins.first)
			mincoins = pair<int,int>(1 + coinnum[i-1000], ch[i-1000]);
		coinnum[i] = mincoins.first;
		ch[i] = mincoins.second;
	}
}

int main() {
	ll useful[5001];
	findchange(useful);
	useful[5000] = 0;

	ll maxchange, curr;
	ll change[5000];
	memset(change, -1, sizeof(change));

	ll n, a;
	cin >> n >> a;
	maxchange = 0;
	curr = a;
	while (change[curr % 5000] == -1 && curr + a <= n) {
		change[curr % 5000] = useful[(-curr) % 5000 + 5000] + useful[(-n+curr) % 5000 + 5000];
		maxchange = max(maxchange, change[curr % 5000]);
		curr++;
	}

	cout << maxchange << endl;

	return 0;
}
