""" lottery_ticket
    enduser clicks on boxes to reveal numbers
    Richard Burke
"""

#Initialize
import pygame
pygame.init()

#Display
screen = pygame.display.set_mode((640, 480))
pygame.display.set_caption("Lottery Ticket")

#Make a background
background = pygame.Surface(screen.get_size())
background = background.convert()
background.fill((0, 0, 100))

#Font for numbers
myFont = pygame.font.SysFont("Comic Sans MS", 30)

#Make grid
BOX_SIDE = 30
box1 = pygame.Surface((BOX_SIDE, BOX_SIDE))
box2 = pygame.Surface((BOX_SIDE, BOX_SIDE))
box3 = pygame.Surface((BOX_SIDE, BOX_SIDE))
box4 = pygame.Surface((BOX_SIDE, BOX_SIDE))
box5 = pygame.Surface((BOX_SIDE, BOX_SIDE))
box6 = pygame.Surface((BOX_SIDE, BOX_SIDE))
box7 = pygame.Surface((BOX_SIDE, BOX_SIDE))
box8 = pygame.Surface((BOX_SIDE, BOX_SIDE))
box9 = pygame.Surface((BOX_SIDE, BOX_SIDE))
box10 = pygame.Surface((BOX_SIDE, BOX_SIDE))
box11 = pygame.Surface((BOX_SIDE, BOX_SIDE))
box12 = pygame.Surface((BOX_SIDE, BOX_SIDE))
box13 = pygame.Surface((BOX_SIDE, BOX_SIDE))
box14 = pygame.Surface((BOX_SIDE, BOX_SIDE))
box15 = pygame.Surface((BOX_SIDE, BOX_SIDE))

box1_x = 100
box1_y = 100
box2_x = 150
box2_y = 100
box3_x = 200
box3_y = 100
box4_x = 250
box4_y = 100
box5_x = 300
box5_y = 100
box6_x = 100
box6_y = 150
box7_x = 150
box7_y = 150
box8_x = 200
box8_y = 150
box9_x = 250
box9_y = 150
box10_x = 300
box10_y = 150
box11_x = 100
box11_y = 200
box12_x = 150
box12_y = 200
box13_x = 200
box13_y = 200
box14_x = 250
box14_y = 200
box15_x = 300
box15_y = 200

#Set lottery numbers
your_numbers = [    [19, 11, 21, 27, 24],
                    [22, 13, 18, 4, 25],
                    [16, 8, 12, 17, 7]  ]
#Define labels which are the numbers that will apear
label_1 = pygame.Surface
label_2 = pygame.Surface
label_3 = pygame.Surface
label_4 = pygame.Surface
label_5 = pygame.Surface
label_6 = pygame.Surface
label_7 = pygame.Surface
label_8 = pygame.Surface
label_9 = pygame.Surface
label_10 = pygame.Surface
label_11 = pygame.Surface
label_12 = pygame.Surface
label_13 = pygame.Surface
label_14 = pygame.Surface
label_15 = pygame.Surface

    
    
#Set framerate
clock = pygame.time.Clock()
keepGoing = True

#main loop
while keepGoing:

    #Time
    clock.tick(30)

      
    #Events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            keepGoing = False
        #When mouse is clicked within boxes, print label, label comes from numbers in array
        elif event.type == pygame.MOUSEBUTTONDOWN:
            mousePos = pygame.mouse.get_pos()
            #row 1 boxes, each if/ elif are for a corresponding box
            if mousePos(1) > 100 and mousePos < 130:
                if mousePos(0) > 100 and mousePos < 130:
                    label_1 = myFont.render("%d", 1, (255, 255, 0)) % (your_numbers[0][0])
                elif mousePos(0) > 150 and mousePos < 180:
                    label_2 = myFont.render("%d", 1, (255, 255, 0)) % (your_numbers[0][1])
                elif mousePos(0) > 200 and mousePos < 230:
                    label_3 = myFont.render("%d", 1, (255, 255, 0)) % (your_numbers[0][2])
                elif mousePos(0) > 250 and mousePos < 280:
                    label_4 = myFont.render("%d", 1, (255, 255, 0)) % (your_numbers[0][3])
                elif mousePos(0) > 300 and mousePos < 330:
                    label_5 = myFont.render("%d", 1, (255, 255, 0)) % (your_numbers[0][4])
            #row 2 boxes
            elif mousePos(1) > 150 and mousePos < 180:
                if mousePos(0) > 100 and mousePos < 130:
                    label_6 = myFont.render("%d", 1, (255, 255, 0)) % (your_numbers[1][0])
                elif mousePos(0) > 150 and mousePos < 180:
                    label_7 = myFont.render("%d", 1, (255, 255, 0)) % (your_numbers[1][1])
                elif mousePos(0) > 200 and mousePos < 230:
                    label_8 = myFont.render("%d", 1, (255, 255, 0)) % (your_numbers[1][2])
                elif mousePos(0) > 250 and mousePos < 280:
                    label_9 = myFont.render("%d", 1, (255, 255, 0)) % (your_numbers[1][3])
                elif mousePos(0) > 300 and mousePos < 330:
                    label_10 = myFont.render("%d", 1, (255, 255, 0)) % (your_numbers[1][4])
            #row 3 boxes
            elif mousePos(1) > 200 and mousePos < 230:
                if mousePos(0) > 100 and mousePos < 130:
                    label_11 = myFont.render("%d", 1, (255, 255, 0)) % (your_numbers[2][0])
                elif mousePos(0) > 150 and mousePos < 180:
                    label_12 = myFont.render("%d", 1, (255, 255, 0)) % (your_numbers[2][1])
                elif mousePos(0) > 200 and mousePos < 230:
                    label_13 = myFont.render("%d", 1, (255, 255, 0)) % (your_numbers[2][2])
                elif mousePos(0) > 250 and mousePos < 280:
                    label_14 = myFont.render("%d", 1, (255, 255, 0)) % (your_numbers[2][3])
                elif mousePos(0) > 300 and mousePos < 330:
                    label_15 = myFont.render("%d", 1, (255, 255, 0)) % (your_numbers[2][4])

        
            
        

    
    
    
    


    #Refresh screen
    screen.blit(background, (0, 0))
    screen.blit(box1, (box1_x, box1_y))
    screen.blit(box2, (box2_x, box2_y))
    screen.blit(box3, (box3_x, box3_y))
    screen.blit(box4, (box4_x, box4_y))
    screen.blit(box5, (box5_x, box5_y))
    screen.blit(box6, (box6_x, box6_y))
    screen.blit(box7, (box7_x, box7_y))
    screen.blit(box8, (box8_x, box8_y))
    screen.blit(box9, (box9_x, box9_y))
    screen.blit(box10, (box10_x, box10_y))
    screen.blit(box11, (box11_x, box11_y))
    screen.blit(box12, (box12_x, box12_y))
    screen.blit(box13, (box13_x, box13_y))
    screen.blit(box14, (box14_x, box14_y))
    screen.blit(box15, (box15_x, box15_y))
    screen.blit(label_1, ((box1_x + 10), (box1_y + 10)))
    screen.blit(label_2, ((box2_x + 10), (box2_y + 10)))
    screen.blit(label_3, ((box3_x + 10), (box3_y + 10)))
    screen.blit(label_4, ((box4_x + 10), (box4_y + 10)))
    screen.blit(label_5, ((box5_x + 10), (box5_y + 10)))
    screen.blit(label_6, ((box6_x + 10), (box6_y + 10)))
    screen.blit(label_7, ((box7_x + 10), (box7_y + 10)))
    screen.blit(label_8, ((box8_x + 10), (box8_y + 10)))
    screen.blit(label_9, ((box9_x + 10), (box9_y + 10)))
    screen.blit(label_10, ((box10_x + 10), (box10_y + 10)))
    screen.blit(label_11, ((box11_x + 10), (box11_y + 10)))
    screen.blit(label_12, ((box12_x + 10), (box12_y + 10)))
    screen.blit(label_13, ((box13_x + 10), (box13_y + 10)))
    screen.blit(label_14, ((box14_x + 10), (box14_y + 10)))
    screen.blit(label_15, ((box15_x + 10), (box15_y + 10)))
    pygame.display.flip()

pygame.quit()
