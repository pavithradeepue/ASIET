#index func - member fuction of class list
#index cannot be used in string, parameter should be passed
#if - keyword, in - operation

lst = eval(input("Enter the list elements: "))
n = int(input("Enter the index element: "))
if n in lst:
	print("INDEX: ",lst.index(n))
else:
	print("Not Found")

#sort() - membership fn of list

#sorted() - wont act on the og string
print(sorted(lst))
print(lst)
