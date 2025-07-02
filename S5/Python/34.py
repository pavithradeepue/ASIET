#Check if anagram

s1 = input("Enter 1st String: ")
s2 = input("Enter 2nd String: ")

if sorted(s1) == sorted(s2):
	print("Yes, It is an Anagram.")
else:
	print("No")
	
'''OUTPUT
student@ml-16:~/Pavithra47/Python$ python3 34.py
Enter 1st String: Stop
Enter 2nd String: Post
No
student@ml-16:~/Pavithra47/Python$ python3 34.py
Enter 1st String: post
Enter 2nd String: stop
Yes, It is an Anagram.'''
