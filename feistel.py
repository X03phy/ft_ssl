import random

# Function to generate a random binary key of given length
def rand_key(length):
    return "".join(str(random.randint(0, 1)) for _ in range(length))

# Function to perform XOR between two binary strings
def xor(a, b):
    return "".join("0" if a[i] == b[i] else "1" for i in range(len(a)))

# Feistel round function
def feistel_round(left, right, key):
    # Round function: f = XOR(right, key)
    f = xor(right, key)
    new_left = right
    new_right = xor(left, f)
    print(new_right)
   #  print(left ^ f)
    return new_left, new_right

# Encryption function
def feistel_encrypt(plain_text, rounds=2):
    # Convert plaintext to binary (8 bits for each character)
    pt_bin = "".join(format(ord(c), "08b") for c in plain_text)

    # Split into two halves
    n = len(pt_bin) // 2
    left, right = pt_bin[:n], pt_bin[n:]

    # Generate random round keys
    keys = [rand_key(len(right)) for _ in range(rounds)]

    # Apply Feistel rounds
    for i in range(rounds):
        left, right = feistel_round(left, right, keys[i])

    # Final ciphertext in binary
    cipher_bin = left + right

    # Convert binary to string
    cipher_text = ""
    for i in range(0, len(cipher_bin), 8):
        byte = cipher_bin[i:i+8]
        cipher_text += chr(int(byte, 2))

    return cipher_text, keys

# Decryption function
def feistel_decrypt(cipher_text, keys):
    # Convert ciphertext to binary
    ct_bin = "".join(format(ord(c), "08b") for c in cipher_text)

    # Split into two halves
    n = len(ct_bin) // 2
    left, right = ct_bin[:n], ct_bin[n:]

    # Apply Feistel rounds in reverse
    for i in reversed(range(len(keys))):
        right, left = feistel_round(right, left, keys[i])

    # Final plaintext in binary
    plain_bin = left + right

    # Convert binary back to string
    plain_text = ""
    for i in range(0, len(plain_bin), 8):
        byte = plain_bin[i:i+8]
        plain_text += chr(int(byte, 2))

    return plain_text

# Driver Code
if __name__ == "__main__":
    plaintext = "Hellooadiazhdaehzeoufcçreuiuerufherufhuerfjerfierjijduzehudhze"
    print("Plain Text:", plaintext)

    # Encryption
    cipher, round_keys = feistel_encrypt(plaintext)
    print("Cipher Text:", cipher)

    # Decryption
    recovered = feistel_decrypt(cipher, round_keys)
    print("Decrypted Text:", recovered)