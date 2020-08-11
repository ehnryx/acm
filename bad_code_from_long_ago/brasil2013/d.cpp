#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, m;
bool fold(vector<int> in, const vector<int>& out, int bm) {
	bool toleft = false;
	int left, right, curr;
	int temp[2*n];
	memset(temp, 0, sizeof(temp));
	curr = n;
	left = n;
	right = n-1;
	for (int i = 0; i < n; i++) {
		if (bm & (1<<i)) {
			if (toleft) {
				curr++;
				toleft = false;
				left = min(left, curr);
			}
			else {
				curr--;
				toleft = true;
				right = max(right, curr);
			}
		}
		temp[curr] += in[i];
		if (toleft) curr--;
		else curr++;
	}
	if (toleft) {
		curr++;
		left = min(left, curr);
	}
	else {
		curr--;
		right = max(right, curr);
	}


	if (right-left+1 != out.size()) return false;
	for (int i = left; i <= right; i++)
		if (temp[i] != out[i-left])
			return false;
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	vector<int> in, out;
	cin >> n;
	in.resize(n);
	for (int i = 0; i < n; i++)
		cin >> in[i];
	cin >> m;
	out.resize(m);
	for (int i = 0; i < m; i++)
		cin >> out[i];
	
	for (int bm = 0; bm < (1<<n); bm++) {
		if (fold(in, out, bm)) {
			cout << "S" << endl;
			return 0;
		}
	}
	cout << "N" << endl;

	return 0;
}
