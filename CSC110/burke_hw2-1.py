#Richard Burke
#9/17/18
#Programming in Python
#HW 2-1

#Get user input
sale = float(input("Enter amount of sale: $"))
#if sale is greater than $8000, apply 50% discount
if (sale > 8000):
             sale *= 0.50
#else if sale is ($4000 - $8000], apply 35% discount
elif (sale > 4000) and (sale <= 8000):
           sale *= 0.65
#else if sale is ($2000 - $4000], apply 20% discount
elif (sale > 2000) and (sale <= 4000):
           sale *= 0.80
#else if sale is [$0 - $2000], apply no discount
else:
            sale *= 1
            
print("Your discounted sale amount is $", sale)
