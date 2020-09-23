""" move_box.py
    illustrates basic motion
    in the IDEA/ALTER framework
    moves a rect across the screen
"""

# Initialize
import pygame
import random
pygame.init()

# Display
screen = pygame.display.set_mode((640, 480))
pygame.display.set_caption("move a box")

#Entities
#Make a green-gray background.
background = pygame.Surface(screen.get_size())
background = background.convert()
background.fill((130, 165, 145))

#Make a red box.
BOX_SIDE = 25
box = pygame.Surface((BOX_SIDE, BOX_SIDE))
box = pygame.image.load("katze.png")
box = box.convert()


#Set variables so box will bounce diagonally downwards
box_x = 100
box_y = 100
dx = 1
dy = 1

#Setup Counters for timed events based on clock.tick(30) = 1 sec
GrowthAndColor = 0
SizeAndColor = 0
TeleportCounter = 0
ReverseCounter = 0

    #Assign
clock = pygame.time.Clock()
keepGoing = True

#pygame.time.set_timer(counter, 5000)
    #Loop
while keepGoing:

    

    #Time
    clock.tick(30)



 
        
    #modify box value
    box_x += dx
    box_y += dy
    
    #Events
    for eventQuit in pygame.event.get():
        if eventQuit.type == pygame.QUIT:
            keepGoing = False
    def checkKeys(myData):

        (event, keepGoing, box_x, box_y, dx, dy, box) = myData
        
        if event.key == pygame.K_ESCAPE:
            keepGoing = False
        elif event.key == pygame.K_UP:
            box_y += 1
        
        myData = (event, background, keepgoing)
        return myData
        #elif event.key == pygame.K_DOWN:
        #elif event.key == pygame.K_LEFT:
        #elif event.key == pygame.K_RIGHT:
        #elif event.key == pygame.K_w:
        #elif event.key == pygame.K_s:
        #elif event.key == pygame.K_SPACE:
            
        

    
    
    
    
    
    

    #Teleports Square
    if TeleportCounter == 200:
        box_x = random.randint(0, screen.get_width())
        box_y = random.randint(0, screen.get_height())
        TeleportCounter = 0
    else:
        TeleportCounter += 1

    
    #check boundaries
    if box_x + BOX_SIDE > screen.get_width():
        dx *= -1
    elif box_x < 0:
        dx *= -1
    if box_y + BOX_SIDE > screen.get_height():
        dy *= -1
    elif box_y < 0:
        dy *= -1

    #Refresh screen
    screen.blit(background, (0, 0))
    screen.blit(box, (box_x, box_y))
    pygame.display.flip()

pygame.quit()
