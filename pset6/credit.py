# checks validity and brand of credit card number
import cs50

def main():
    
    print("Number: ", end="")
    # input as string or int?
    number = cs50.get_int()
    copy = number
        
    sum1 = 0
    sum2 = 0
    counter = 0 
    while copy > 0:
        digit = copy % 10
        
        if counter % 2 == 0:
            sum1 += digit
        else:
            sum2 += sumDigits(digit*2)
        
        
        
        # chop off the last digit
        copy = copy//10
        counter += 1

    #get ID of credit card company
    cardID = number//(10**(counter -2))
    company =""
    #print ("cardID: {}".format(cardID))
    
    if (cardID == 34) or (cardID == 37):
        company = "AMEX"
    elif(cardID >= 51) and (cardID <=55):
        company = "MASTERCARD"
    elif(cardID >= 40) and (cardID <= 49):
        company = "VISA"
    else:
        print("INVALID")
        return
        
    final = sum1 + sum2
    if final % 10 == 0:
        print("{}".format(company))
    
    
def sumDigits(num):
    if num == 0:
        return 0
    else:
        return num % 10 + sumDigits(num//10) 
        

if __name__ == "__main__":
    main()