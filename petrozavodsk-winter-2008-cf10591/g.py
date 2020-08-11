cin = open("vasya.in", "r")
cout = open("vasya.out", "w")

a, b, k = map(int, cin.read().split())
cout.write(str((a+b)**k) + '\n')
