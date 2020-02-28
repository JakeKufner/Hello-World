#!/usr/bin/env python2
#CODE IS FROM: https://www.geeksforgeeks.org/python-frequency-of-each-character-in-string/
# Python3 code to demonstrate  
# each occurrence frequency using  
# naive method  

import sys 

message = open(sys.argv[1], 'rb')

# change from string to input of file

test_str = message


# using naive method to get count  
# of each element in string  
all_freq = {} 
  
for i in test_str: 
    if i in all_freq: 
        all_freq[i] += 1
    else: 
        all_freq[i] = 1
  
# printing result  
#print ("Count of all characters in GeeksforGeeks is :\n "
#                                       +  str(all_freq)) 

for entry in all_freq.items():
    print(entry)
