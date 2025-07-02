# second largest number in list
l = input().split()
#l = [int(d) for d in l]
l = map(int,l)
l = l.sort()
print("Second largest element is:",l[2])
#l.sort(reverse=True)
