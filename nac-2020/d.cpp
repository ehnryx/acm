/* Solution idea:
 * 0. consider each problem as a block of size xi that we need to place on a
 *    strip of t slots. Let tot = sum_i xi.
 * 1. we add an extra time slot and consider the problem on a circle, after we
 *    place all the blocks, we can choose an empty slot to split the circle.
 *    There are t-tot+1 ways to choose this empty slot.
 * 2. consider the blocks as dividers instead, we have t-tot+1 empty slots on
 *    the circle. Since the blocks can be adjacent, add n empty slots and
 *    enforce that the dividers are not adjacent (a la stars and bars). This
 *    gives a total of t-tot+1+n "stars" to divide.
 * 3. the first divider can be placed arbitrarily because circular symmetry.
 * 4. starting from the second divider, we can either [case 1] obtain the idea
 *    during an existing block (whence we must put this divider immediately
 *    after the other exiting one), or [case 2] choose any empty space to put
 *    the divider.
 * 5. [case 1]: there are sum_{j<i} xj ways to obtain the idea this way.
 * 6. [case 2]: there are t-tot+1+n positions, of which i-1 are already taken.
 * 7. These two cases are independent, so the answer is
 *          (t-tot+1) * prod_{i=1}^n (t-tot+1+n - (i-1) + sum_{j<i} xj)
 */

#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long long ll;
const ll MOD = 998244353;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n, t;
  cin >> n >> t;
  vector<int> x(n+1);
  int tot = 0;
  for(int i=1; i<=n; i++) {
    cin >> x[i];
    tot += x[i];
  }

  ll sum = x[1];
  ll ans = t-tot+1;
  for(int i=2; i<=n; i++) {
    ans = ans * (t-tot+1+n - (i-1) + sum) % MOD;
    sum += x[i];
  }
  cout << ans << nl;

  return 0;
}
