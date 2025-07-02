#Checking whether the string is palindrome
s = input("Enter a string: ")
print("Palindrome: " if s == s[::-1] else "Not Palindrome")
