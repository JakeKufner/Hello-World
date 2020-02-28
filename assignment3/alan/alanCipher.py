#!/usr/bin/env python2
import base64
import sys

InputKey = sys.argv[2]

with open(sys.argv[1], 'rb') as f:
    message = f.read()

def encode(text):
    return base64.encodestring(text)

def decode(text):
    return base64.decodestring(text)

def encrypt(cleartext, key):
    to_return = bytearray(len(cleartext))
    for i in xrange(len(cleartext)):
        to_return[i] = ord(cleartext[i]) ^ ord(key[i % len(key)])
    return str(to_return)

#print("Message encrypted is:")
#cipher = (encode(encrypt(message, InputKey)))
#print(cipher)
print("Decrypted message is:")
print(encrypt(decode(message), InputKey))
