//
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

struct BIT {
  static const int size = 10000;
  int freq[size+1];
  BIT() {
    clear();
  }
  void clear() {
    memset(freq, 0, sizeof(freq));
  }
  void insert(int x) {
    for ( ; x <= size; x += x & -x)
      freq[x]++;
  }
  int query(int x) {
    int sum = 0;
    for ( ; x > 0; x -= x & -x)
      sum += freq[x];
    return sum;
  }
  int query(int lx, int rx) {
    return query(rx) - query(lx-1);
  }
};

struct Index {
  int interval;
  int place;
  Index(int id, int size) {
    place = (id-1) % size + 1;
    interval = (id-1) / size;
  }
};

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int n, q, left, right;
  int ans;
  string s;
  char c;
  BIT letter_cnt[26];

  int T;
  cin >> T;
  while (T--) {
    for (int i = 0; i < 26; i++)
      letter_cnt[i].clear();

    cin >> n >> q;
    cin >> s;
    for (int i = 0; i < n; i++)
      letter_cnt[s[i]-'a'].insert(i+1);

    for (int i = 0; i < q; i++) {
      cin >> left >> right >> c;

      Index first(left, n);
      Index second(right, n);
      if (first.interval == second.interval) {
        ans = letter_cnt[c-'a'].query(first.place, second.place);
      } else {
        ans = (second.interval - first.interval - 1) * letter_cnt[c-'a'].query(1, n);
        ans += letter_cnt[c-'a'].query(first.place, n);
        ans += letter_cnt[c-'a'].query(1, second.place);
      }
      cout << ans << nl;
    }
  }

  return 0;
}
