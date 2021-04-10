def f(n, s, t):
  if n:
    f(n-1, s, s^t)
    print s, t
    f(n-1, s^t, t)
n = input()
print 2**n-1
f(n, 1, 3)
