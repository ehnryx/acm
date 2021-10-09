#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, circ, one, two;
vector<pair<int,int> > pprev;
vector<int> holes;

int search(int i, int v) {
  for (int s = 1; s < n; s++)
    if ((holes[i] - holes[(i-s+n)%n] + circ) % circ > v)
      return (i-(s-1)+n)%n;
  return (i+1)%n;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n >> circ >> one >> two;
  pprev.resize(n);
  holes.resize(n);
  if (one > two) {
    int temp = one;
    one = two;
    two = temp;
  }

  for (int i = 0; i < n; i++) {
    cin >> holes[i];
  }
  for (int i = 0; i < n; i++) {
    pprev[i].first = search(i, one);
    pprev[i].second = search(i, two);
  }
  
  //#define debug

  #ifdef debug
  for (int i = 0; i < n; i++) {
    cerr << i << ": " << pprev[i].first << " " << pprev[i].second << endl;
  }
  #endif

  int cmax;
  int cmin = 2e9+7;
  int dp[n];
  for (int start = 0; start < n; start++) {
    memset(dp, 0, sizeof(dp));
    cmax = one;
    dp[start] = one;
    for (int i = pprev[start].first; i%n != start; i++)
      dp[i%n] = one;
    for (int i = 1; dp[(start+i)%n] == 0; i++) {
      if (dp[(pprev[(start+i)%n].first+n-1)%n] == 0) dp[(start+i)%n] = one;
      else {
        dp[(start+i)%n] = dp[(pprev[(start+i)%n].first+n-1)%n] + one;
        if (dp[(pprev[(start+i)%n].second+n-1)%n] != 0) 
          dp[(start+i)%n] = min(dp[(start+i)%n], dp[(pprev[(start+i)%n].second+n-1)%n] + two);
      }
      cmax = max(cmax, dp[(start+i)%n]);
    }
    cmin = min(cmin, cmax);
    #ifdef debug
    cerr << "start at " << start << endl;
    for (int i = 0; i < n; i++) cerr << dp[i] << " "; cerr << endl;
    #endif
    memset(dp, 0, sizeof(dp));
    cmax = two;
    dp[start] = two;
    for (int i = pprev[start].second; i%n != start; i++)
      dp[i%n] = two;
    for (int i = 1; dp[(start+i)%n] == 0; i++) {
      if (dp[(pprev[(start+i)%n].second+n-1)%n] == 0) dp[(start+i)%n] = two;
      else {
        dp[(start+i)%n] = min(dp[(pprev[(start+i)%n].first+n-1)%n] + one, dp[(pprev[(start+i)%n].second+n-1)%n] + two);
      }
      cmax = max(cmax, dp[(start+i)%n]);
    }
    cmin = min(cmin, cmax);
    #ifdef debug
    for (int i = 0; i < n; i++) cerr << dp[i] << " "; cerr << endl;
    #endif
  }
  cout << cmin << endl;

  return 0;
}
