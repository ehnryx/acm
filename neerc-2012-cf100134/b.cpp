#include <bits/stdc++.h>

using namespace std;

#define FILENAME sad

#define nl '\n'
typedef long long ll;
typedef long double ld;


int main() {
  ios::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
  //freopen(FILENAME ".in", "r", stdin);
  //freopen(FILENAME ".out", "w", stdout);
#endif

  int T = 300;

  int n, c, cur;
  cin >> n >> c >> cur;

  cout << "accept" << endl;
  for(int i=0; i<T; i++) {
    int nxt;
    cin >> nxt;
    if(nxt > cur) {
      cout << "accept" << endl;
      cur = nxt;
    } else {
      cout << "decline" << endl;
    }
  }

  vector<int> w;
  while(w.size() < n) {
    int nxt;
    cin >> nxt;
    if(nxt < cur) {
      cout << "accept" << endl;
      w.push_back(cur - nxt);
      cur = nxt;
    } else {
      cout << "decline" << endl;
    }
  }
  sort(w.begin(), w.end());

  pair<int,int> best(-1, -1);
  for(int bm=0; bm<1<<n; bm++) {
    int sum = 0;
    for(int i=0; i<n; i++) {
      if(bm & 1<<i) {
        sum += w[i];
      }
    }
    if(sum <= c) {
      best = max(best, make_pair(sum, bm));
    }
  }
  int want = best.second;

  int have = 0;
  for(;;) {
    int nxt;
    cin >> nxt;
    int val = abs(nxt - cur);
    int id = -1;
    if(nxt > cur) {
      for(int i=0; i<n; i++) {
        if(w[i] == val && !(have & 1<<i)) {
          id = i;
        }
      }
    } else {
      for(int i=n-1; i>=0; i--) {
        if(w[i] == val && (have & 1<<i)) {
          id = i;
        }
      }
    }

    if(((have >> id & 1) ^ 1) == (want >> id & 1) || have == want) {
      have ^= 1 << id;
      if(have == want) {
        cout << "stop" << endl;
        return 0;
      } else {
        cout << "accept" << endl;
        cur = nxt;
      }
    } else {
      cout << "decline" << endl;
    }
  }

  return 0;
}
