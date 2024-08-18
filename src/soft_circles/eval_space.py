from typing import TYPE_CHECKING, Iterable

from .soft_circles_module import (
    add_force_conveyor_to_eval_space,
    add_soft_circle_to_eval_space,
    delete_eval_space,
    get_address_from_capsule,
    make_eval_space,
    remove_soft_circle_from_eval_space,
    tick_eval_space,
)

if TYPE_CHECKING:
    from .soft_circle import Soft_Circle
    from .force_conveyor import Force_Conveyor
    from .soft_circles_module import EvalSpaceReference

class Eval_Space():
    def __init__(self, *, x_size:float = 100, y_size:float = 100, x_divs:int = 100, y_divs:int = 100):
        self._reference:'EvalSpaceReference' = make_eval_space(x_size,y_size,x_divs,y_divs)
        self._sc_map:dict[int,'Soft_Circle'] = {}
    def soft_circles(self) -> Iterable['Soft_Circle']:
        return self._sc_map.values()
    def add(self,*args:'Soft_Circle'):
        for sc in args:
            self._sc_map[get_address_from_capsule(sc._reference)] = sc
            add_soft_circle_to_eval_space(self._reference,sc._reference)
    def remove(self,*args:'Soft_Circle'):
        for sc in args:
            del self._sc_map[get_address_from_capsule(sc._reference)]
            remove_soft_circle_from_eval_space(self._reference,sc._reference)
    def tick(self,dt:float,num_ticks:int = 1,/):
        tick_eval_space(self._reference,dt,num_ticks)
    def __del__(self):
        if hasattr(self,'_reference'):
            delete_eval_space(self._reference)
    def add_force(self,*args:'Force_Conveyor'):
        for arg in args:
            add_force_conveyor_to_eval_space(self._reference,arg._reference)
