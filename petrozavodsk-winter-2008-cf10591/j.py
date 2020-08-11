cin = open("lesson.in", "r")
cout = open("lesson.out", "w")

n, m = map(int, cin.read().split())
cout.write(str(2**n + 2**m - 2) + '\n')
