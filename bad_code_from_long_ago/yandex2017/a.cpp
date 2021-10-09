#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  queue<int> q;
  int count, curr, toread, attime;
  int n, a, b;
  cin >> n >> a >> b;

  count = 0;
  while (n--) {
    cin >> curr;
    // if read before curr
    while (!q.empty() && curr - q.front() > b) {
      toread = (count+1)/2;
      attime = q.front() + b;
      while (toread--) {
        cout << attime << " ";
        q.pop();
        count--;
      }
    }
    q.push(curr);
    count++;
    // if read at curr
    if (curr - q.front() == b || count == a) {
      toread = (count+1)/2;
      attime = curr;
      while (toread--) {
        cout << attime << " ";
        q.pop();
        count--;
      }
    }
  }
  while (!q.empty()) {
    toread = (count+1)/2;
    attime = q.front() + b;
    while (toread--) {
      cout << attime << " ";
      q.pop();
      count--;
    }
  }
  cout << endl;

  return 0;
}
