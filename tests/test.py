from unittest import TestCase, main
from random import random
import pygame

from soft_circles.soft_circle import Soft_Circle
from soft_circles.eval_space import Eval_Space
from soft_circles.force_conveyor.soft_circle_gravity import Soft_Circle_Gravity

X_SIZE = 1000
Y_SIZE = 1000
X_DIVS = 100
Y_DIVS = 100
NUM = 100
DT = 0.1
SKIP_DISPLAY = 5
TOTAL = 10000
G = 1000000000000000000

class Test(TestCase):
    def test_simple(self):
        es = Eval_Space(x_divs=X_DIVS,y_divs=Y_DIVS,x_size=X_SIZE,y_size=Y_SIZE)

        gs = Soft_Circle(m=1,r=50)
        es.add(gs)
        gsf = Soft_Circle_Gravity(gs,G)
        es.add_force(gsf)
        gs.is_immovable = True
        gs.position = (X_SIZE/2,Y_SIZE/2)
        for _ in range(NUM):
            sc = Soft_Circle(r=10)
            sc.position = (random()*X_SIZE,random()*Y_SIZE)
            es.add(sc)
        pygame.init()
        surf = pygame.display.set_mode([X_SIZE,Y_SIZE])
        for _ in range(int(TOTAL/SKIP_DISPLAY)):
            es.tick(DT,SKIP_DISPLAY)
            surf.fill("#000000")
            for sc in es.soft_circles():
                pygame.draw.circle(surf,"#ffffff",sc.position,sc.r,width=1)
                if not sc.velocity.is_zero():
                    pygame.draw.line(surf,"blue",sc.position,sc.position+sc.velocity,width=1)
                if not sc.acceleration.is_zero():
                    pygame.draw.line(surf,"red",sc.position,sc.position+sc.acceleration,width=1)
            pygame.display.flip()
            




if __name__ == '__main__':
    main()