#!/usr/bin/env python2
import base64
import sys

num = int(sys.argv[2])

#used to make sure file is exactly the same
with open(sys.argv[1], 'rb') as f:
    message = f.read()
#used to make sure file is exactly the same.  cmp in console, files are the same
with open("output.txt", 'wb') as f:
    f.write(message)

def encode(text):
    return base64.encodestring(text)

def decode(text):
    return base64.decodestring(text)

def encrypt(cleartext, key):
    to_return = bytearray(len(cleartext))
    for i in xrange(len(cleartext)):
        to_return[i] = ord(cleartext[i]) ^ key
    return to_return

print("the encrypt is... ")
cipher = encode(encrypt("test", 128))
print(cipher)
print("and the decryption is...")
print(encrypt(decode(message), num))
