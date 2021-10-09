#include <bits/stdc++.h>
using namespace std;

struct Shop {
  long double p;
  int t;
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, x, p, t;
  cin >> n >> x;
  vector<Shop> shop(n);
  for (int i = 0; i < n; i++) {
    cin >> shop[i].p >> shop[i].t;
  }

  // prob[n] = probability that it is NOT there
  pair<long double, long double> prob[n], exp[n];
  prob[0].first = (1-shop[0].p/100);
  exp[0].first = shop[0].t;
  for (int i = 1; i < n; i++) {
    prob[i].first = (1-shop[i].p/100)*prob[i-1].first;
    exp[i].first = shop[i].t + (1-shop[i].p/100)*(1+exp[i-1].first);
    //assert(prob[i].first <= 100);
  }
  prob[n-1].second = (1-shop[n-1].p/100);
  exp[n-1].second = shop[n-1].t;
  for (int i = n-2; i >= 0; i--) {
    prob[i].second = (1-shop[i].p/100)*prob[i+1].second;
    exp[i].second = shop[i].t + (1-shop[i].p/100)*(1+exp[i+1].second);
    //assert(prob[i].second <= 100);
  }

  //cerr << fixed << setprecision(7);
  int counter = 1; //debugging
  int time, dir;
  long double probability, expected;
  long double leftfirst, rightfirst;
  int left, right, curr;
  curr = left = right = x-1;
  time = shop[x-1].t;
  probability = (1-shop[x-1].p/100);
  expected = (shop[x-1].p/100)*time;
  //cerr << "shop " << curr << ": \tp: " << probability << "\tt: " << time << endl;
  //cerr << "\t" << "left: " << left << "\tright: " << right << endl;
  while (right-left < n-1 && probability < 100) {
    assert(curr == right || curr == left);
    if (left == 0) {
      dir = 1;
    }
    else if (right == n-1) {
      dir = -1;
    }
    else {
      if (curr == right) {
        rightfirst = 1 + exp[right+1].second + (prob[right+1].second)*(n-1-left + 1 + exp[left-1].first);
        leftfirst = right-left + 1 + exp[left-1].first + (prob[left-1].first)*(right-0 + 1 + exp[right+1].second);
      }
      else {
        rightfirst = right-left + 1 + exp[right+1].second + (prob[right+1].second)*(n-1-left + 1 + exp[left-1].first);
        leftfirst = 1 + exp[left-1].first + (prob[left-1].first)*(right-0 + 1 + exp[right+1].second);
      }
      if (rightfirst < leftfirst)
        dir = 1;
      else 
        dir = -1;
    }
    assert(!(dir > 0 && right == n-1));
    assert(!(dir < 0 && left == 0));
    if (dir > 0) {
      right++;
      time += (right-curr) + shop[right].t;
      expected += probability*shop[right].p/100*(time + abs(right-(x-1)));
      probability *= (1-shop[right].p/100);
      curr = right;
    }
    else {
      left--;
      time += (curr-left) + shop[left].t;
      expected += probability*shop[left].p/100*(time + abs(left-(x-1)));
      probability *= (1-shop[left].p/100);
      curr = left;
    }
    //cerr << "shop " << curr << ": \tp: " << probability << "\tt: " << time << endl;
    //cerr << "\t" << "left: " << left << "\tright: " << right << endl;
  }
  expected += probability*(time + abs(curr-(x-1)));
  cout << fixed << setprecision(7) << expected << endl;
  
  return 0;
}
