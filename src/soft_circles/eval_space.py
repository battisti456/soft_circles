from typing import TYPE_CHECKING

from .soft_circles_module import make_eval_space, add_soft_circle_to_eval_space, remove_soft_circle_from_eval_space

if TYPE_CHECKING:
    from .soft_circles_module import EvalSpaceReference
    from .soft_circle import Soft_Circle

class Eval_Space():
    def __init__(self, *, x_size:float = 100, y_size:float = 100, x_divs:int = 100, y_divs:int = 100):
        self.___reference:EvalSpaceReference = make_eval_space(x_size,y_size,x_divs,y_divs)
    def add(self,*args:Soft_Circle):
        for sc in args:
            add_soft_circle_to_eval_space(self.___reference,sc.___reference)
    def remove(self,*args:Soft_Circle):
        for sc in args:
            remove_soft_circle_from_eval_space(self.___reference,sc.___reference)
