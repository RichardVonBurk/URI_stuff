#Richard Burke
#9/11/18
#Homework 1-2 Introduction
#A Python program that will compute sales tax for purchases made in August.

TAX = 0.06  #The percent of sales tax in decimal form

#User input of company's sales for August. 
saleValue = input("Enter the value of the company's sales in dollars in August 2016: $")
saleTax = float(saleValue) * TAX  #calculate sales tax

print("The tax for the month of August is $" + str(saleTax)) #print result
