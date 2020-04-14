#Python solution that passes all the test cases


def sumsub(ls,k):

if k==0:

return(sum(ls))
else:

ls.sort()

if len(ls)>=k:

    for j in range(0,k):

        if(ls[0]<0):

             ls.remove(ls[0])

    return(sum(ls))
else:

      for i in range(len(ls)):
          if ls[0]<0:
              ls.remove(ls[0])
      return(sum(ls))
n,k= map(int,input().split(" "))

l=[]

smax=0

for i in range(n):

m=input()

l.append(int(m))

for i in range(n):

for j in range(n,0,-1):

s=sumsub(l[i:j],k)

if s>smax :

    smax=s
print(smax)
