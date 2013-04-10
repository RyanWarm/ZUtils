#Python
"""
Find the longest word in a dictionary, such that the word can be built one character at a time, and all substrings are words in the dictionary. A new character can be added anywhere.
"""

words = [x.strip().lower() for x in open('/usr/share/dict/words')]
words.sort(key=lambda x:len(x), reverse=True)
word_map = {}  # Maps words to (extension, max_len) tuples

for word in words:
  if word in word_map:
    max_len = word_map[word][0]
  else:
    max_len = len(word)
  for i in range(len(word)):
    new_word = word[:i] + word[i+1:]
    if new_word not in word_map or word_map[new_word][1] < max_len:
      word_map[new_word] = (word, max_len)

# Get a chain for each letter
for term in "abcdefghijklmnopqrstuvwxyz":
  chain = [term]
  while term in word_map:
    term = word_map[term][0]
    chain.append(term)
  print chain
