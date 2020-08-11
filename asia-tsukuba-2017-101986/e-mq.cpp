#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

template <class T> struct min_stack : public stack<T> {
  stack<T> mins; // vals stored in stack inherited from the STL stack
  T mins_top() { return (mins.empty() ? INF : mins.top()); }
  void push(int x) { mins.push(min(x, mins_top())); stack<T>::push(x); }
  T pop() { mins.pop(); int x=stack<T>::top(); stack<T>::pop(); return x; }
  T minimum() { return mins_top(); }
};
template <class T> struct min_queue { min_stack<T> in, out;
  void refill() { if (out.empty()) while (!in.empty()) out.push(in.pop()); }
  void push(int x) { in.push(x); }
  T pop() { refill(); return out.pop(); }
  T front() { refill(); return out.top(); }
  bool empty() { return in.empty() && out.empty(); }
	int size() { return in.size() + out.size(); }
  T minimum() { return min(in.minimum(), out.minimum()); }
};

const int N = 5e5+1;
int dp[N], pre[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n,k;
	cin>>n>>k;
	string s,t;
	cin>>s>>t;

	for(int i=1;i<n;i++) {
		pre[i] = pre[i-1] + (t[i] != t[i-1]);
	}

	min_queue<int> mq;
	mq.push(0);
	for(int i=0;i<n;i++) {
		if(s[i]==t[i]) {
			dp[i+1] = dp[i];
		} else {
			int top = mq.minimum() + pre[i] + 2;
			dp[i+1] = (top+1)/2;
		}
		mq.push(2*dp[i+1] - pre[i+1]);
		if(mq.size() > k) mq.pop();
	}
	cout<<dp[n]<<nl;

	return 0;
}
