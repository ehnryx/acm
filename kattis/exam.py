print[t[1]-abs(t[2]-t[0])for t in[[t[0],len(t[1]),sum([1 if t[1][i]==t[2][i]else 0 for i in range(len(t[1]))])]for t in[[int(raw_input()),raw_input(),raw_input()]]]][0]
