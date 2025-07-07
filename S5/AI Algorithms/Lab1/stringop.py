text = input("Enter a sentence: ")
count = len(text)
print("Number of characters: ",count)
utext = text.upper()
print("Sentence in uppercase: ",utext)
ltext = text.lower()
print("Sentence in lowercase: ",ltext)
rtext = text.replace(" ","_")
print("Sentence replaced with _: ",rtext)

if "python" in text.lower():
         print("Python is there in the sentence.")
else:
         print("Python is not there in the sentence.")
