"""
    Richard Burke
    5/11/16
    Get Squeakers! Game, Enhanced
"""

import pygame           
import random           
pygame.init()       
pygame.mixer.init()     


def main(): 
    screen = pygame.display.set_mode((640, 480))    
    pygame.display.set_caption("Get Squeakers!")    

    background = pygame.Surface(screen.get_size())        
    background = background.convert()               
    background.fill((130, 165, 145))                
 

    #Heads Up Display classes set up labels to be used as the display of the timer and score
    class HUD_Score(pygame.sprite.Sprite):
        def __init__(self):
            pygame.sprite.Sprite.__init__(self)
            self.score = 0
            self.font = pygame.font.SysFont("None", 30)

        def update(self):
            self.text = "Score: %d" % (self.score)
            self.image = self.font.render(self.text, 1, (255, 255, 255))
            self.image.convert()
            self.rect = self.image.get_rect()
            self.rect.centery = 35

        def addPoint(self): #when mouse collides with good Squeaker
            self.score += 1

            
    class HUD_Timer(pygame.sprite.Sprite):
        def __init__(self):
            pygame.sprite.Sprite.__init__(self)
            self.internalTimer = 1800 #1min timer, based on each tick, 60secs x 30frames
            self.displayTimer = self.internalTimer / 30 #internal timer is based on ticks but endUser needs time displayed in secs
            self.font = pygame.font.SysFont("None", 30)
        
        def update(self):
            self.internalTimer -= 1 #every update from each tick subtracts 1
            self.displayTimer = self.internalTimer / 30
            self.text = "Time Left: %d" % (self.displayTimer)
            self.image = self.font.render(self.text, 1, (255, 255, 255))
            self.rect = self.image.get_rect()
            if self.displayTimer == 0:
                return False

        def addTime(self):
            self.internalTimer += 30 #add 1sec (30frames x 1sec) when good Squeaker is collided with mouse

        def loseTime(self):
            self.internalTimer -= 150 #subtract 5sec (30frames x 5sec) when Bad Squeaker is collided with mouse
            
    hud_score = HUD_Score()
    hud_timer = HUD_Timer()

         
    #Squeaker Class (endUser's objective is to hit these which gains points and gains time)
    class Squeaker(pygame.sprite.Sprite):   #aka good Squeaker        
        def __init__(self):                         
            pygame.sprite.Sprite.__init__(self)         
            self.image = pygame.image.load("Squeaker.jpg")  
            self.rect = self.image.get_rect()       
            self.rect.centerx = random.randint(0, screen.get_width())   
            self.rect.centery = random.randint(0, screen.get_height())  
            self.squeak = pygame.mixer.Sound("SqueakSound.ogg") 
            self.dx = random.randint(-10, 10)
            self.dy = random.randint(-10, 10)
            
        def play_squeak(self):
            self.squeak.play()

        def reset(self):
            self.rect.centerx = random.randint(0, screen.get_width())   
            self.rect.centery = random.randint(0, screen.get_height())
            self.dx = random.randint(-10, 10)
            self.dy = random.randint(-10, 10)

        def update(self):
            self.rect.centerx += self.dx
            self.rect.centery += self.dy
        
            if self.rect.centerx >= screen.get_width() or self.rect.centerx < 0 or self.rect.centery >= screen.get_height() or self.rect.centery < 0:
                self.reset()


    #Bad_Squeaker Class (endUser must avoid these or lose time)
    class Bad_Squeaker(pygame.sprite.Sprite):           
        def __init__(self):                         
            pygame.sprite.Sprite.__init__(self)         
            self.image = pygame.image.load("Bad_Squeaker.jpg")  
            self.rect = self.image.get_rect()       
            self.rect.centerx = random.randint(0, screen.get_width())   
            self.rect.centery = random.randint(0, screen.get_height())  
            self.squeak = pygame.mixer.Sound("Bad_SqueakSound.ogg") 
            self.dx = random.randint(-10, 10)
            self.dy = random.randint(-10, 10)
            
        def play_squeak(self):
            self.squeak.play()

        def reset(self):
            self.rect.centerx = random.randint(0, screen.get_width())   
            self.rect.centery = random.randint(0, screen.get_height())
            self.dx = random.randint(-10, 10)
            self.dy = random.randint(-10, 10)

        def update(self):
            self.rect.centerx += self.dx
            self.rect.centery += self.dy

            if self.rect.centerx >= screen.get_width() or self.rect.centerx < 0 or self.rect.centery >= screen.get_height() or self.rect.centery < 0:
                self.reset()

    
    class CursorCircle(pygame.sprite.Sprite):       
        def __init__(self):
            pygame.sprite.Sprite.__init__(self)
            self.image = pygame.Surface((20, 20))
            pygame.draw.circle(self.image, (255, 0, 0), (300, 300), 10, 0)
            self.rect = self.image.get_rect()

        def update(self):                       
            mouseXY = pygame.mouse.get_pos() 
            self.rect.center = mouseXY

    #Create variable for CursorCircle class
    cursorCir = CursorCircle()
 

    #Spawn 'X' good Squeakers                       
    squeaker1 = Squeaker()
    squeaker2 = Squeaker()
    squeaker3 = Squeaker()
    
    #Spawn 'X' Bad_Squeakers                       
    bad_squeaker1 = Bad_Squeaker()
    bad_squeaker2 = Bad_Squeaker()
    bad_squeaker3 = Bad_Squeaker()
    
    #Create Groups by sprite type
    allHUDs = pygame.sprite.Group(hud_score, hud_timer)
    allSqueakers = pygame.sprite.Group(squeaker1, squeaker2, squeaker3)
    allBad_Squeakers = pygame.sprite.Group(bad_squeaker1, bad_squeaker2, bad_squeaker3)
    allCursorCir = pygame.sprite.Group(cursorCir)

    
    #assign
    clock = pygame.time.Clock()
    keepGoing = True
    pygame.mouse.set_visible(False)
    
    #loop
    while keepGoing:
        #time
        clock.tick(30)

              
        #events
        for event in pygame.event.get():  
            if event.type == pygame.QUIT:
                keepGoing = False
                
            #collision of mouse sprite with squeaker (good)
        goodCollision = pygame.sprite.spritecollide(cursorCir, allSqueakers, False)
        for squeaker in goodCollision:
            squeaker.play_squeak()
            squeaker.reset()
            keepGoing = hud_score.addPoint()
            keepGoing = hud_timer.addTime()
            keepGoing = True
                
                
            #collision of mouse sprite with bad squeaker
        badCollision = pygame.sprite.spritecollide(cursorCir, allBad_Squeakers, False)
        for bad_squeaker in badCollision:
            bad_squeaker.play_squeak()
            bad_squeaker.reset()
            keepGoing = hud_timer.loseTime()
            keepGoing = True

        if hud_timer.displayTimer == False:   #When displayed timer hits 0 game ends, originally had internalTimer but game would end at -1 displayed time
                keepGoing = False             #I also had this within the for event loop but wouldn't work there for some reason
           
                
        
        
        #refresh
        screen.blit(background, (0,0))
        allSqueakers.clear(screen, background)
        allSqueakers.update()
        allSqueakers.draw(screen)
        allBad_Squeakers.clear(screen, background)
        allBad_Squeakers.update()
        allBad_Squeakers.draw(screen)
        allHUDs.clear(screen, background)
        allHUDs.update()
        allHUDs.draw(screen)
        allCursorCir.clear(screen, background)
        allCursorCir.update()
        allCursorCir.draw(screen)
              
        pygame.display.flip()

    pygame.quit()
    
if __name__ == "__main__":  
    main()
