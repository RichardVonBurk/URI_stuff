alphabet=['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'] 

def affine(plaintext, a, b, m):

    ciphertext = ""
    if relprime(a, m) == False:
        return ciphertext
    
    # ofr every letter in plaintext
    for i in range(len(plaintext)):
        #find position in alphabet
        letter = plaintext[i]
        position = alphabet.index(letter)
        # add key to the number
        # shiftedPosition = ((a*position) + b) % m
        shiftedPosition = (a(position - b)) % m
        # find letter in the position
        cipherLetter = alphabet[shiftedPosition]
        # append letter to cipher text 
        ciphertext = ciphertext + cipherLetter

    return ciphertext

def invMod(a, m): 
    a = a % m
    
    for x in range(1, m): 
        if ((a * x) % m == 1): 
            return x 
    return 0

def decrypt(a, b, ciphertext, m):
    p = ""
    x = invMod(a, m)
    plainText = ""
    for i in range(len(ciphertext)):
        letter = ciphertext[i]
        c = alphabet.index(letter)
        pos = (x*(c-b)) % m

        p = alphabet[pos]
        plainText = plainText + str(p)

    return plainText
