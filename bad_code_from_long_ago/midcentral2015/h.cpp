#include <cstdio>
#include <vector>

using namespace std;

const int N = 1000000 + 5;

bool exist[N];

int main() {
  vector<int> v;
  int x;
  scanf("%d", &x);
  while (x != -1) {
    v.push_back(x);
    exist[x] = true;
    scanf("%d", &x);
  }
  for (int i = 0; i < v.size(); i++) {
    int x = v[i], digit[18];
    for (int j = 0; j < 18; j++) {
      digit[j] = 0;
    }
    for (int j = x, l = 0; j; j >>= 1) {
      digit[l++] = (j & 1);
    }
    int ans = 0;
    for (int j = 0; j < 18; j++) {
      if (!digit[j] && exist[x + (1 << j)]) {
        ans++;
      }
    }
    for (int j = 0; j < 18; j++) {
      for (int k = j + 1; k < 18; k++) {
        if (!digit[j] && !digit[k]) {
          ans += exist[x + (1 << j) + (1 << k)];
        } else if (digit[j] && !digit[k]) {
          ans += exist[x - (1 << j) + (1 << k)];
        }
      }
    }
    printf("%d:%d\n", x, ans);
  }
  return 0;
}
