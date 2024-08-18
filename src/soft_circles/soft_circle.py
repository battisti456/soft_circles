from enum import Enum
from typing import TYPE_CHECKING

from .soft_circles_module import (
    delete_soft_circle,
    get_soft_circle_a,
    get_soft_circle_acceleration,
    get_soft_circle_b,
    get_soft_circle_f,
    get_soft_circle_is_immovable,
    get_soft_circle_k,
    get_soft_circle_m,
    get_soft_circle_out_of_scope_behavior,
    get_soft_circle_position,
    get_soft_circle_r,
    get_soft_circle_t,
    get_soft_circle_velocity,
    make_soft_circle,
    set_soft_circle_acceleration,
    set_soft_circle_is_immovable,
    set_soft_circle_out_of_scope_behavior,
    set_soft_circle_position,
    set_soft_circle_velocity,
)
from .vec2 import vec2

if TYPE_CHECKING:
    from .soft_circles_module import SoftCircleReference

class OOSB(Enum):
    KEEP_IN = 0
    IGNORE = 1


class Soft_Circle(object):
    def __init__(self,*,m:float = 1, r:float = 1, f:float = 1, t:float = 1, k:float = 1, a:float = 1, b:float = 1):
        self._reference:SoftCircleReference = make_soft_circle(m,r,f,t,k,a,b)
    @property
    def is_immovable(self) -> bool:
        return get_soft_circle_is_immovable(self._reference)
    @is_immovable.setter
    def is_immovable(self,value:bool,/):
        set_soft_circle_is_immovable(self._reference,value)
    @property
    def out_of_scope_behavior(self) -> OOSB:
        return OOSB(get_soft_circle_out_of_scope_behavior(self._reference))
    @out_of_scope_behavior.setter
    def out_of_scope_behavior(self,val:OOSB):
        set_soft_circle_out_of_scope_behavior(self._reference,val.value)
    @property
    def position(self) -> vec2:
        return vec2(get_soft_circle_position(self._reference))
    @position.setter
    def position(self,val:tuple[float,float],/):
        set_soft_circle_position(self._reference,val)
    @property
    def velocity(self) -> vec2:
        return vec2(get_soft_circle_velocity(self._reference))
    @velocity.setter
    def velocity(self,val:tuple[float,float],/):
        set_soft_circle_velocity(self._reference,val)
    @property
    def acceleration(self) -> vec2:
        return vec2(get_soft_circle_acceleration(self._reference))
    @acceleration.setter
    def acceleration(self,val:tuple[float,float]):
        set_soft_circle_acceleration(self._reference,val)
    @property
    def m(self) -> float:
        return get_soft_circle_m(self._reference)
    @property
    def r(self) -> float:
        return get_soft_circle_r(self._reference)
    @property
    def f(self) -> float:
        return get_soft_circle_f(self._reference)
    @property
    def t(self) -> float:
        return get_soft_circle_t(self._reference)
    @property
    def k(self) -> float:
        return get_soft_circle_k(self._reference)
    @property
    def a(self) -> float:
        return get_soft_circle_a(self._reference)
    @property
    def b(self) -> float:
        return get_soft_circle_b(self._reference)
    def __del__(self):
        if hasattr(self,'_reference'):
            delete_soft_circle(self._reference)

