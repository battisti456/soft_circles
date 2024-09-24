from unittest import TestCase, main
from random import random, seed
import pygame
import gc
from collections import defaultdict

from soft_circles.soft_circles_module import Soft_Circle, Eval_Space, Force_Conveyor
from soft_circles import OOSB


X_SIZE = 1000
Y_SIZE = 1000
NUM = 1
DT = 0.001
SKIP_DISPLAY = 500
TOTAL = 20000000
G = 0.001
D = 1

def add_tuples(v1:tuple[float,float],v2:tuple[float,float],/):
    return (v1[0]+v2[0],v1[1]+v2[1])

class Test(TestCase):
    def test_simple(self):
        before:dict[type,int] = defaultdict(int)
        for obj in gc.get_objects():
            before[type(obj)] += 1
        
        seed(1000)
        es = Eval_Space(0,0,X_SIZE,Y_SIZE)

        gs = Soft_Circle()
        gs.r = 50
        gs.t = 100000

        #es.bind(gs)
        es.bind(Force_Conveyor.make_point_force((X_SIZE/2,Y_SIZE/2),G))
        #es.bind(Force_Conveyor.make_simple_drag(D))
        es.oosb = OOSB.IGNORE
        gs.is_immovable = True
        gs.position = (X_SIZE/2,Y_SIZE/2)
        for _ in range(NUM):
            sc = Soft_Circle()
            sc.r = 10
            sc.position = ((random()/2+0.25)*X_SIZE,(random()/2+0.25)*Y_SIZE)
            sc.oosb = OOSB.KEEP_IN
            es.bind(sc)

        pygame.init()
        surf = pygame.display.set_mode([X_SIZE,Y_SIZE])
        for _ in range(int(TOTAL/SKIP_DISPLAY)):
            surf.fill("#000000")
            for sc in es.soft_circles:
                pygame.draw.circle(surf,"white" if sc.is_immovable else "yellow",sc.position,sc.r,width=1)
                if not sc.velocity == (0,0):
                    pygame.draw.line(surf,"blue",sc.position,add_tuples(sc.position,sc.velocity),width=1)
                if not sc.acceleration == (0,0):
                    pygame.draw.line(surf,"red",sc.position,add_tuples(sc.position,sc.acceleration),width=1)
            pygame.display.flip()
            pygame.event.pump()
            es.tick(DT,SKIP_DISPLAY)
        pygame.quit()
        after:dict[type,int] = defaultdict(int)
        for obj in gc.get_objects():
            after[type(obj)] += 1
        gc.collect()
        for tpe,after_val in after.items():
            val = after_val
            if tpe in before:
                val -= before[tpe]
            if val > 0:
                print(f"type = {tpe}, num = {val}")
            




if __name__ == '__main__':
    main()