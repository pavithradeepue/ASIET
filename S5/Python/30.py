#average
#convert temp def
#recursive sum of nat numbers

#Program to count vowels and consonants
s = input("Enter a string: ")
vowels = "aeiouAEIOU"
v,c = 0,0
for ch in s:
	if ch.isalpha():
		if ch in vowels:
			v += 1
		else:
			c += 1
print("Vowels: ",v,"Consonants: ",c)
print("Number of letters in the string is: ",len(s))
