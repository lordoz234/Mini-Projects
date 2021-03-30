import pygame

pygame.init()

display_width = 800
display_height = 600

gameDisplay = pygame.display.set_mode((display_width,display_height))
pygame.display.set_caption('A bit Racey')

black = (0,0,0)
white = (255,255,255)

clock = pygame.time.Clock()
crashed = False
carImg_right = pygame.image.load('/Users/vladislavdevlikamov/Desktop/game/game/hh1.png')
carImg_left = pygame.image.load('/Users/vladislavdevlikamov/Desktop/game/game/hh2.png')
bg = pygame.image.load('/Users/vladislavdevlikamov/Desktop/game/game/tr.png')
apple_image = pygame.image.load('/Users/vladislavdevlikamov/Desktop/game/game/apple.png')
mushroom_image = pygame.image.load('/Users/vladislavdevlikamov/Desktop/game/game/mushroom.png')
bird_left = pygame.image.load('/Users/vladislavdevlikamov/Desktop/game/game/bird.png')
bird_right = pygame.image.load('/Users/vladislavdevlikamov/Desktop/game/game/bird1.png')
trampoline = pygame.image.load('/Users/vladislavdevlikamov/Desktop/game/game/trampoline.png')
banan_image = pygame.image.load('/Users/vladislavdevlikamov/Desktop/game/game/banana.png')

class person(object):
    def __init__(self, x, y, car_speed, isJump, jumpCount, left):
        self.x = x
        self.y = y
        self.car_speed = car_speed
        self.isJump = isJump
        self.isTramp = False
        self.jumpCount = jumpCount
        self.jumpTramp = jumpCount
        self.left = left
        self.hitbox = pygame.Rect(self.x, self.y + 8, 61, 43)
        self.visible = True
        self.score = 0
    def draw(self):
        if self.left == True:
            if self.visible == True:
                gameDisplay.blit(carImg_left, (self.x,self.y))
        else:
            if self.visible == True:
                gameDisplay.blit(carImg_right, (self.x,self.y))
        self.hitbox = pygame.Rect(self.x, self.y + 8, 61, 43)
        #pygame.draw.rect(gameDisplay, (255, 0, 0), self.hitbox, 2)

class apple(object):
    def __init__(self, x, y, visible):
        self.x = x
        self.y = y
        self.visible = visible
        self.hitbox = pygame.Rect(self.x, self.y - 1, 61, 63)
    def draw(self):
        if self.visible == True:
            gameDisplay.blit(apple_image, (self.x, self.y))
        self.hitbox = pygame.Rect(self.x, self.y - 1, 61, 63)
        #pygame.draw.rect(gameDisplay, (255, 0, 0), self.hitbox, 2)

class mushroom(object):
    def __init__(self, x, y, visible):
        self.x = x
        self.y = y
        self.visible = visible
        self.hitbox = (self.x, self.y + 2, 61, 54)
    def draw(self):
        if self.visible == True:
            gameDisplay.blit(mushroom_image, (self.x, self.y))
        self.hitbox = (self.x, self.y + 2, 61, 54)
        #pygame.draw.rect(gameDisplay, (255, 0, 0), self.hitbox, 2)

class banana(object):
    def __init__(self, x, y, visible):
        self.x = x
        self.y = y
        self.visible = visible
        self.hitbox = (self.x, self.y + 2, 61, 54)
    def draw(self):
        if self.visible == True:
            gameDisplay.blit(banan_image, (self.x, self.y))
        self.hitbox = (self.x, self.y + 2, 61, 54)
        #pygame.draw.rect(gameDisplay, (255, 0, 0), self.hitbox, 2)

class bird(object):
    def __init__(self, x, y, speed):
        self.x = x
        self.y = y
        self.neg = 1
        self.speed = speed
        self.hitbox = pygame.Rect(self.x, self.y + 2, 61, 54)
        self.visible = True
    def draw(self):
        if self.x + self.speed*self.neg >= display_width - 60:
            self.neg = -1
        if self.x + self.speed*self.neg <= 0:
            self.neg = 1
        self.x += self.speed*self.neg
        if self.neg == 1:
            if self.visible == True:
                gameDisplay.blit(bird_right, (self.x, self.y))
        else:
            if self.visible == True:
                gameDisplay.blit(bird_left, (self.x, self.y))
        self.hitbox = pygame.Rect(self.x, self.y + 2, 61, 54)
        #pygame.draw.rect(gameDisplay, (255, 0, 0), self.hitbox, 2)

class tramp(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.visible = True
        self.hitbox = pygame.Rect(self.x, self.y + 2, 63, 24)
    def draw(self):
        gameDisplay.blit(trampoline, (self.x, self.y))
        #pygame.draw.rect(gameDisplay, (255, 0, 0), self.hitbox, 2)

def end():
    one_apple.visible = False
    second_apple.visible = False
    one_mushroom.visible = False
    second_mushroom.visible = False
    yozhyk.visible = False
    bird.visible = False
    text = font.render("End Game", 1, (0, 0, 0))
    gameDisplay.blit(text, (350, 350))


yozhyk = person(10, display_height*0.7, 10, False, 10, False)

one_apple = apple(250, display_height*0.7, True)
second_apple = apple(600, display_height*0.7, True)
one_mushroom = mushroom(100, display_height*0.7, True)
second_mushroom = mushroom(400, display_height*0.7, True)
banan = banana(500, display_height*0.1, True)
tramp = tramp(500, display_height*0.7 + 8)
bird = bird(10, display_height*0.4, 10)

score = 0

font = pygame.font.SysFont("comiscans", 30, bold=True, italic=False)

while not crashed:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            crashed = True

    keys = pygame.key.get_pressed()
    if keys[pygame.K_LEFT] and yozhyk.x > yozhyk.car_speed:
        yozhyk.left = True
        yozhyk.x -= yozhyk.car_speed
    if keys[pygame.K_RIGHT] and yozhyk.x < display_width - yozhyk.car_speed - 60:
        yozhyk.left = False
        yozhyk.x += yozhyk.car_speed
    if not(yozhyk.isJump):
        if keys[pygame.K_SPACE]:
            yozhyk.isJump = True
    else:
        if yozhyk.jumpCount >= -10:
            neg = 1
            if yozhyk.jumpCount < 0:
                neg = -1
            yozhyk.y -= (yozhyk.jumpCount ** 2) * 0.5 * neg
            yozhyk.jumpCount -= 1
        else:
            yozhyk.isJump = False
            yozhyk.jumpCount = 10
    if yozhyk.isTramp:
        if yozhyk.jumpTramp >= -10:
            neg = 1
            if yozhyk.jumpTramp < 0:
                neg = -1
            yozhyk.y -= (yozhyk.jumpTramp ** 2) * neg
            yozhyk.jumpTramp -= 1
        else:
            yozhyk.isTramp = False
            yozhyk.jumpTramp = 10

    gameDisplay.fill(white)
    gameDisplay.blit(bg, (0, 0))

    if yozhyk.hitbox.colliderect(one_apple.hitbox) and one_apple.visible == True:
        one_apple.visible = False
        yozhyk.score += 1
    if yozhyk.hitbox.colliderect(second_apple.hitbox) and second_apple.visible == True:
        second_apple.visible = False
        yozhyk.score += 1
    if yozhyk.hitbox.colliderect(banan.hitbox) and banan.visible == True:
        banan.visible = False
        yozhyk.score += 1
    if yozhyk.hitbox.colliderect(one_mushroom.hitbox) and one_mushroom.visible == True:
        one_mushroom.visible = False
        yozhyk.score -= 1
    if yozhyk.hitbox.colliderect(second_mushroom.hitbox) and second_mushroom.visible == True:
        second_mushroom.visible = False
        yozhyk.score -= 1
    if yozhyk.hitbox.colliderect(bird.hitbox):
        yozhyk.score -= 1
    if yozhyk.hitbox.colliderect(tramp.hitbox):
        yozhyk.isTramp = True

    one_apple.draw()
    second_apple.draw()
    one_mushroom.draw()
    second_mushroom.draw()
    banan.draw()
    yozhyk.draw()
    bird.draw()
    tramp.draw()
        
    text = font.render("Score: " + str(yozhyk.score), 1, (0, 0, 0))
    gameDisplay.blit(text, (650, 10))
    pygame.display.update()
    clock.tick(60)

pygame.quit()
quit()