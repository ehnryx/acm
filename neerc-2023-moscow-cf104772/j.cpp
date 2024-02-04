%:include "main.h"
SOLVE() {
  int n;
  cin >> n;
  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }

  int left = 0;
  for (int i = 0, j = 0; i < n; i++) {
    if (a[i] > b[j]) {
      left++;
      j++;
    }
  }
  int right = 0;
  for (int i = n - 1, j = n - 1; i >= 0; i--) {
    if (a[i] < b[j]) {
      right++;
      j--;
    }
  }
  right = n - right;
  assert(left >= right);

  cout << left - right + 1 << nl;
  for (int i = right; i <= left; i++) {
    cout << i << " ";
  }
  cout << nl;
}
