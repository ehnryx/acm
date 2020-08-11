#include <stdio.h>
#include <stdlib.h>

int main() {
  char s[117];

  int T;
  scanf("%d", &T);

  while (T--) {
    int n, i;
    scanf("%d", &n);
    scanf("%s", s);

    int bad = 0;
    for (i=0; i<n/2; i++) {
      int diff = abs(s[i]-s[n-1-i]);
      if (diff != 0 && diff != 2) {
        bad = 1;
      }
    }

    if (bad) {
      printf("NO\n");
    } else {
      printf("YES\n");
    }
  }

  return 0;
}
