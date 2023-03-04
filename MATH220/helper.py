import numpy as np

# Hill Cipher

# Key
C = np.array([[5, 3], [3, 0]])
D = np.array([[14], [0]])

# Plaintext
text = "banana"

print("Plaintext: ", text)
print("C: ", C)
print("D: ", D)

# Encryption

l = len(C)
e = []

for i in range(0, len(text), l):
    x = np.array([[ord(text[i]) - ord('a')], [ord(text[i+1]) - ord('a')]])
    e.append(np.dot(C, x) + D)
    # e.append(C*x + D)

print(e)
e = [i % 26 for sub in e for i in sub]
print(e)
e = [chr(int(i) + ord('a')) for i in e]
print("Encrypted: ", e)


# Decryption

C_inverse = np.linalg.inv(C)
print("C_inverse: ", C_inverse)
print("D: ", C_inverse.dot(D))

d = []

text = "ygyi"

for i in range(0, len(text), l):
    x = np.array([[ord(text[i]) - ord('a')], [ord(text[i+1]) - ord('a')]])
    d.append(C_inverse.dot(x - D))
    # d.append(C_inverse*(x - D))

print(d)
d = [i % 26 for sub in d for i in sub]
print(d)
d = [chr(int(i) + ord('a')) for i in d]
print("Decrypted: ", d)