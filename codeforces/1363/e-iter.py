import os
### START FAST IO ###
os_input = os.read(0, int(1e7)).split()
os_input_pos = -1
answer_list = []
def read_s():
    global os_input_pos
    os_input_pos += 1
    return os_input[os_input_pos].decode()
def read_i():
    return int(read_s())
def write_s(v):
    answer_list.append(v)
def write_i(v):
    write_s(str(v))
def print_ans():
    os.write(1, "\n".join(answer_list).encode())
    os.write(1, "\n".encode())
#### END FAST IO ####


n = read_i()
cost = [0 for i in range(n)]
val = [0 for i in range(n)]
for i in range(n):
    cost[i] = read_i()
    a = read_i()
    b = read_i()
    val[i] = 0 if a == b else 1 if a else -1

adj = [[] for i in range(n)]
for i in range(1, n):
    a = read_i() - 1
    b = read_i() - 1
    adj[a].append(b)
    adj[b].append(a)

par = [None for i in range(n)]
order = [0 for i in range(n)]
f = n
b = n-1
par[0] = -1
while f > b:
  f -= 1
  u = order[f]
  for v in adj[u]:
    if par[v] is None:
      par[v] = u
      b -= 1
      order[b] = v
      cost[v] = min(cost[v], cost[u])

ans = 0
dp = [None for i in range(n)]
for u in order:
  ab = [val[u] == 1, val[u] == -1]
  for v in adj[u]:
    if dp[v] is not None:
      ab[dp[v][0]] += dp[v][1]
  rem = min(ab)
  ans += 2 * rem * cost[u]
  dp[u] = (ab[1] > ab[0], max(ab) - rem)

write_i(-1 if dp[0][1] else ans)


print_ans()

