#Richard Burke
#10/29/18
#Homework 7 - Cryptography

#takes char and outputs ordered position of ASCII char
def ord0(char):
    #if char is '\'
    if char == "'\'":
        char = '\\'
    #expected input is 0-95 so adjust for ASCII values
    ordNum = ord(char)
    ordNum -= 32
    return ordNum

#takes chrNum and outputs char associated with the ordered position in ASCII
def chr0(chrNum):
    #expected input is 0-95 so adjust for ASCII values
    chrNum += 32
    char = chr(chrNum)
    return char

#Caesar encryption used for 95 char of ASCII
def caesar95(plaintext, shift):  
    # initialize ciphertext as blank string
    ciphertext = ""
    # loop through the length of the plaintext
    for i in range(len(plaintext)):         
        # get the ith letter from the plaintext
        letter = plaintext[i] 
        # find the number related to 95 char of the ith letter
        ordNum = ord0(letter)
        # find the number of the 95 char the cipher by adding the shift and mod 95 
        cipher_num = (ordNum + shift) % 95 
        # find the cipher letter for the cipher number
        cipher_letter = chr0(cipher_num) 
        # add the cipher letter to the ciphertext
        ciphertext = ciphertext + cipher_letter 
 
    # return the ciphertext
    return ciphertext

def main():
    #Boolean used in while loop to quit main()
    dontQuit = True
    while(dontQuit):
        string = input("Enter a string to be encrypted: ")
        shift = int(input("Enter a shift value: "))
        #if Done and 0 then quit
        if (string == "Done") and (shift == 0):            
            dontQuit = False
        else:
            encryption = caesar95(string, shift)
            #use print and not return, return will break out of main
            print(encryption)
    #Print these once out of loop
    print("Done")
    print("Thank you.")











