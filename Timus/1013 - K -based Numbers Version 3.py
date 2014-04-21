# Created By: Malvika Joshi
# Problem: K-based Numbers. Version 3
# Link: http://acm.timus.ru/problem.aspx?space=1&num=1013
zero = [0]*2000
nonzero = [0]*2000

def DP(N,K):
    zero[0] = 0
    nonzero[0] = K-1

    for i in range(1,N):
        zero[i] = nonzero[i-1]
        nonzero[i] = (zero[i-1]+nonzero[i-1])*(K-1)

    return zero[N-1]+nonzero[N-1]

ip = raw_input()
N = int(ip)
ip = raw_input()
K = int(ip)

print DP(N,K)
