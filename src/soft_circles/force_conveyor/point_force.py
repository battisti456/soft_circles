from . import Force_Conveyor

from ..soft_circles_module import make_point_force


class Point_Force(Force_Conveyor):
    def __init__(self,pos:tuple[float,float],f:float):
        super().__init__(make_point_force(pos[0],pos[1],f))