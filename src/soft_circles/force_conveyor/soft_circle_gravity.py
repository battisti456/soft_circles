from typing import TYPE_CHECKING

from . import Force_Conveyor

from ..soft_circles_module import make_soft_circle_gravity

if TYPE_CHECKING:
    from ..soft_circle import Soft_Circle

class Soft_Circle_Gravity(Force_Conveyor):
    def __init__(self,sc:'Soft_Circle',g:float):
        super().__init__(make_soft_circle_gravity(sc._reference,g))