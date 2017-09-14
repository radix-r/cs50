import cs50
import sys

def main():
    
    #comfirm proper number of command line args
    if len(sys.argv) != 2:
        print ("Proper usage: python vigenere.py key")
        exit(1)
    
    
    # get argument from command line
    keyWord = sys.argv[1]
    
    #confirm validity of key word
    if (not keyWord.isalpha()):
        print("Invalid argument")
        exit(1)
    
    # make keyword lowercase
    keyWord = keyWord.lower()
    
    # get word to encrypt
    print("plaintext: ", end="")
    plainText = cs50.get_string()
    
    # initalize cyphertext
    cypherText = ""
    
    #convert keyword to int array
    shifts = []
    for ch in keyWord:
        shifts.append(ord(ch)-97)
    
    # index of key to use
    k=0
    keyLen = len(shifts)
    
    #iterate through string to encrypt
    for ch in plainText:
        #reset key index to 0 if it reaches the end of the key word
        if k >= keyLen:
            k = 0
        # apply encryption
        if ch.islower():
            cypherText += shiftChar(ch, shifts[k], 97, 122)
        elif ch.isupper():
            cypherText += shiftChar(ch, shifts[k], 65, 90)
        #increment key index
        k += 1
    
    
    print("cyphertext: {}".format(cypherText )) 
      
      
def shiftChar(ch, shift, lower, upper):
    charRange = upper - lower
    # convert to ascii value
    ascii = ord(ch)
    #apply shift
    ascii += shift
    
    #loop around if too large
    if ascii > upper:
        ascii = (ascii % upper) + lower-1
    # convert back to char
    shifted = chr(ascii)
    
        
    return shifted
    

main()