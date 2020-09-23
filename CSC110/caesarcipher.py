alphabet=['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'] 
#richard_burke7@my.uri.edu
def caesar(plaintext):
    x=1
    while(x <= 26):
        ciphertext = ''
        # ofr every letter in plaintext
        for i in range(len(plaintext)):
            #find position in alphabet
            letter = plaintext[i]
            position = alphabet.index(letter)
            # add key to the number
            shiftedPosition = (position + x) % 26
            # find letter in the position
            cipherLetter = alphabet[shiftedPosition]
            # append letter to cipher text 
            ciphertext = ciphertext + cipherLetter
        x+=1
        print(ciphertext)


def poly(plaintext, keyword):
    ciphertext = ""
    for i in range(len(plaintext)):
        letter = plaintext[i]
        position = alphabet.index(letter)

        #get the keyword
        j = i % len(keyword)
        keyLetter = keyword[j]
        
        # get numeric value of keyletter
        keyNum = alphabet.index(keyLetter)

        # compute shifted position
        shiftedPosition = ((position * keyNum) + 4) % 26
        
        # find letter in the position
        cipherLetter = alphabet[shiftedPosition]
        # append letter to cipher text 
        ciphertext = ciphertext + cipherLetter

    return ciphertext




def relprime(a,b):
    low = 0
    high = 0
    if (a > b):
        low = b
        high = a
    else:
        low = a
        high = b

    i = 2
    factors = []
    while (i <= low):
        if ((low % i) == 0):
            factors.append(i)
        i+=1

    isRelPrime = True

    i = 0
    while (i < len(factors)):
        if ((high % factors[i]) == 0):
            isRelPrime = False
        i+=1
    return isRelPrime
