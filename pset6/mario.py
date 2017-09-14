import cs50

def main():
    print("Height: ", end="")
    height = cs50.get_int()
    
    while height < 0 or height >= 23:
        #print("Please enter a positive int that is less than 23")
        print("retry: ", end ="")
        height = cs50.get_int()
        
    sharps = 1
    spaces = height-1
    
    
    for i in range(height):
        while spaces >= 0:
            for s in range(spaces):
                print(" ", end="")
            for sh in range(sharps):
                print("#",end="")
            
            print(" ", end ="")
            
            for sh in range(sharps):
                print("#",end="")
            for s in range(spaces):
                print(" ", end="")
                
            #newline    
            print("")
            
            #decrement and increment values
            sharps +=1
            spaces -=1

main()
            
            