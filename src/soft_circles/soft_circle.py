from typing import TYPE_CHECKING

from .soft_circles_module import make_soft_circle, get_soft_circle_position, get_soft_circle_velocity, get_soft_circle_acceleration, delete_soft_circle

if TYPE_CHECKING:
    from .soft_circles_module import SoftCircleReference


class Soft_Circle(object):
    def __init__(self,*,m:float = 1, r:float = 1, f:float = 1, t:float = 1, k:float = 1, a:float = 1, b:float = 1):
        self.___reference:SoftCircleReference = make_soft_circle(m,r,f,t,k,a,b)
    @property
    def position(self) -> tuple[float,float]:
        return get_soft_circle_position(self.___reference)
    @property
    def velocity(self) -> tuple[float,float]:
        return get_soft_circle_velocity(self.___reference)
    @property
    def acceleration(self) -> tuple[float,float]:
        return get_soft_circle_acceleration(self.___reference)
    def __del__(self):
        delete_soft_circle(self.___reference)

