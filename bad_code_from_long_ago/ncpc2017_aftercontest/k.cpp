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
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

int k;
int sb, sn, se;
bool check1(int kayak[], int spd, int b, int n, int e) {
  for (int i = 0; i < k; i++) {
    if (b >= 2 && 2*sb*kayak[i] >= spd)
      b -= 2;
    else if (b >= 1 && n >= 1 && (sb+sn)*kayak[i] >= spd)
      b--, n--;
    else if (b >= 1 && e >= 1 && b+e < n+n && (sb+se)*kayak[i] >= spd)
      b--, e--;
    else if (n >= 2 && n+n < b+e && 2*sn*kayak[i] >= spd)
      n -= 2;
    else if (b >= 1 && e >= 1 && b+e > n+n && (sb+se)*kayak[i] >= spd)
      b--, e--;
    else if (n >= 1 && e >= 1 && (sn+se)*kayak[i] >= spd)
      n--, e--;
    else if (e >= 2 && 2*se*kayak[i] >= spd)
      e -= 2;
    else 
      return false;
  }
  return true;
}
bool check2(int kayak[], int spd, int b, int n, int e) {
  for (int i = 0; i < k; i++) {
    if (b >= 2 && 2*sb*kayak[i] >= spd)
      b -= 2;
    else if (b >= 1 && n >= 1 && (sb+sn)*kayak[i] >= spd)
      b--, n--;
    else if (n >= 2 && 2*sn*kayak[i] >= spd)
      n -= 2;
    else if (b >= 1 && e >= 1 && (sb+se)*kayak[i] >= spd)
      b--, e--;
    else if (n >= 1 && e >= 1 && (sn+se)*kayak[i] >= spd)
      n--, e--;
    else if (e >= 2 && 2*se*kayak[i] >= spd)
      e -= 2;
    else 
      return false;
  }
  return true;
}
bool check3(int kayak[], int spd, int b, int n, int e) {
  for (int i = 0; i < k; i++) {
    if (b >= 2 && 2*sb*kayak[i] >= spd)
      b -= 2;
    else if (b >= 1 && n >= 1 && (sb+sn)*kayak[i] >= spd)
      b--, n--;
    else if (b >= 1 && e >= 1 && (sb+se)*kayak[i] >= spd)
      b--, e--;
    else if (n >= 2 && 2*sn*kayak[i] >= spd)
      n -= 2;
    else if (n >= 1 && e >= 1 && (sn+se)*kayak[i] >= spd)
      n--, e--;
    else if (e >= 2 && 2*se*kayak[i] >= spd)
      e -= 2;
    else 
      return false;
  }
  return true;
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int b, n, e;
  cin >> b >> n >> e;
  k = (b+n+e)/2;
  int kayak[k];
  cin >> sb >> sn >> se;
  for (int i = 0; i < k; i++) 
    cin >> kayak[i];
  sort(kayak, kayak+k);

  int left, right, mid;
  left = 1; 
  right = 2e8;
  while (left <= right) {
    mid = (left + right) / 2;
    if (check1(kayak, mid, b, n, e) || check2(kayak, mid, b, n, e) || check3(kayak, mid, b, n, e))
      left = mid+1;
    else 
      right = mid-1;
  }
  if ((check1(kayak, mid, b, n, e) || check2(kayak, mid, b, n, e) || check3(kayak, mid, b, n, e)) == false)
    mid--;
  cout << mid << nl;

  return 0;
}
