T = int(input())
for i in range(0,T):
  s = input()
  if s == "P=NP":
    print("skipped")
  else:
    print(eval(s))
