///
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const int MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct Number {
  int index;
  int value;
  Number(int index=0, int value=0) {
    this->index = index;
    this->value = value;
  }
  int operator + (const Number& other) const {
    return this->value + other.value;
  }
  bool operator < (const Number& other) const {
    return this->value < other.value;
  }
};

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int n;
  int left, right, mid, last;
  Number arr[100000];
  int ans[100000];

  int T;
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 0; i < n; i++) {
      arr[i].index = i;
      cin >> arr[i].value;
    }
    sort(arr, arr+n);
    for (int i = 0; i < n; i++) {
      last = n-1;
      if (last == i)
        last--;
      ans[arr[i].index] = (arr[i] + arr[last]) % MOD;

      left = 0;
      right = n-1;
      while (left <= right) {
        mid = (left+right)/2;
        if (arr[i] + arr[mid] >= MOD)
          right = mid-1;
        else 
          left = mid+1;
      }
      if (arr[i] + arr[mid] >= MOD)
        mid--;
      if (mid == i)
        mid--;
      if (mid >= 0) {
        ans[arr[i].index] = max(ans[arr[i].index], (arr[i] + arr[mid]) % MOD);
      }
    }
    for (int i = 0; i < n; i++) {
      cout << ans[i] << " ";
    } cout << nl;
  }

  return 0;
}
