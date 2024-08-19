from . import Force_Conveyor

from ..soft_circles_module import make_simple_drag


class Simple_Drag(Force_Conveyor):
    def __init__(self,c:float):
        super().__init__(make_simple_drag(c))