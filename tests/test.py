from unittest import TestCase, main
from random import random, seed
import pygame

from soft_circles.soft_circle import Soft_Circle, OOSB
from soft_circles.eval_space import Eval_Space
from soft_circles.force_conveyor.point_force import Point_Force
from soft_circles.force_conveyor.simple_drag import Simple_Drag

X_SIZE = 1000
Y_SIZE = 1000
X_DIVS = 100
Y_DIVS = 100
NUM = 10
DT = 0.001
SKIP_DISPLAY = 500
TOTAL = 20000000
G = 4
D = 1

class Test(TestCase):
    def test_simple(self):
        seed(1000)
        es = Eval_Space(x_divs=X_DIVS,y_divs=Y_DIVS,x_size=X_SIZE,y_size=Y_SIZE)

        gs = Soft_Circle()
        gs.r = 50
        gs.t = 100000

        es.bind(gs)
        gsf = Point_Force((X_SIZE/2,Y_SIZE/2),G)
        d = Simple_Drag(D)
        es.add_force(gsf)
        es.add_force(d)
        gs.is_immovable = True
        gs.position = (X_SIZE/2,Y_SIZE/2)
        for _ in range(NUM):
            sc = Soft_Circle()
            sc.r = 10
            sc.position = (random()*X_SIZE,random()*Y_SIZE)
            sc.out_of_scope_behavior = OOSB.KEEP_IN
            es.bind(sc)
        pygame.init()
        surf = pygame.display.set_mode([X_SIZE,Y_SIZE])
        for _ in range(int(TOTAL/SKIP_DISPLAY)):
            es.tick(DT,SKIP_DISPLAY)
            surf.fill("#000000")
            for sc in es.soft_circles():
                pygame.draw.circle(surf,"white" if sc.is_immovable else "yellow",sc.position,sc.r,width=1)
                if not sc.velocity.is_zero():
                    pygame.draw.line(surf,"blue",sc.position,sc.position+sc.velocity,width=1)
                if not sc.acceleration.is_zero():
                    pygame.draw.line(surf,"red",sc.position,sc.position+sc.acceleration,width=1)
            pygame.display.flip()
            pygame.event.pump()
        pygame.quit()
            




if __name__ == '__main__':
    main()