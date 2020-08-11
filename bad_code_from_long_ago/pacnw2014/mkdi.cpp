#include <bits/stdc++.h>

using namespace std;

int main() {
	srand(time(0));
	int t = 20;
	printf("%d\n", t);
	while (t--) {
		int n = 1000000;
		printf("%d\n", n);
		for (int i = 2; i <= n; i++) {
			printf("%d%c", i - 1, " \n"[i == n]);
		}
		for (int i = 1; i <= n; i++) {
			printf("%d%c", rand() % 1000 + 1, " \n"[i == n]);
		}
		int q = 10000;
		printf("%d\n", q);
		for (int i = 1; i <= q; i++) {
			if (rand() % 2) {
				printf("Q %d\n", rand() % n + 1);
			} else {
				printf("R %d %d\n", rand() % n + 1, rand() % 1000 + 1);
			}
		}
	}
	return 0;
}
