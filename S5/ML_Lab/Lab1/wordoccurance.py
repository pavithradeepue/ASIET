s = input("Enter the sentence: ")
words = s.split()
occurance={}
for word in words:
	if word in occurance:
		occurance[word]+=1
	else:
		occurance[word]=1
print("Word Occurance\n")
for word,count in occurance.items():
	print(word,":",count)
