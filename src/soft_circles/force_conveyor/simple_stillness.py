from . import Reaction


from ..soft_circles_module import make_simple_stillness

class Simple_Stillness(Reaction):
    def __init__(self,vel_on:float,force_off:float):
        super().__init__(make_simple_stillness(vel_on,force_off))