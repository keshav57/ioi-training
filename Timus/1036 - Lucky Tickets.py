#Created By: Malvika Joshi
#Problem: Lucky Tickets
#Link: http://acm.timus.ru/problem.aspx?space=1&num=1036

num = []

for i in xrange(60):
    num.append([])
    for j in xrange(600):
        num[i].append(0)

def DP(N,S):    
    for k in range (0,10):
        num[1][k] = 1

    for i in range (2,N+1):
        for k in range (0,S+1):
            num[i][k] = 0
            for d in range (0,10):
                if d > k:
                    break
                num[i][k] = num[i][k] + num[i-1][k-d]

    return num[N][S]**2

ip = raw_input().split()
N = int(ip[0])
S = int(ip[1])

if S % 2:
    print '0'
else:
    S = S/2
    print DP(N,S)
