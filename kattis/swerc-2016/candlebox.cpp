#include <bits/stdc++.h>

using namespace std;

int main() {
	int D, R, T;
	scanf("%d%d%d", &D, &R, &T);
	for (int i = 4, sum = 4; sum <= R; i++, sum += i) {
		if (i < D + 3) {
			continue;
		}
		int rm = R - sum;
		int T_ = T + rm;
		int j = i - D;
		if ((3 + j) * (j - 2) / 2 == T_) {
			printf("%d\n", rm);
		}
	}
	return 0;
}
