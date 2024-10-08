from typing import Iterable

class BindException(Exception):
    ...

class _Es_Bindable:
    @property
    def eval_space(self) -> 'Eval_Space|None':
        ...
    def _on_bound(self,eval_space:'Eval_Space',/) -> None:
        ...
    def _on_unbound(self,eval_space:'Eval_Space',/) -> None:
        ...

class Soft_Circle(_Es_Bindable):
    m:float
    r:float
    f:float
    t:float
    k:float
    a:float
    b:float
    position:tuple[float,float]
    velocity:tuple[float,float]
    acceleration:tuple[float,float]
    is_immovable:bool
    is_tangible:bool
    oosb:int

class Force_Conveyor(_Es_Bindable):
    def callback(self,soft_circle:'Soft_Circle',/) -> tuple[float,float]:
        ...
    @classmethod
    def make_callback(cls) -> 'Force_Conveyor':
        ...
    @classmethod
    def make_soft_circle_gravity(cls,soft_circle:'Soft_Circle',strength:float,/) -> 'Force_Conveyor':
        ...
    @classmethod
    def make_point_force(cls,point:tuple[float,float],strength:float,/)->'Force_Conveyor':
        ...
    @classmethod
    def make_simple_drag(cls,c:float,/) -> 'Force_Conveyor':
        ...

class Keeper(_Es_Bindable):
    @classmethod
    def make_box(
        cls,
        mca: float,
        mct: float,
        left: float,
        up: float,
        right: float,
        down: float
    )->'Keeper':
        ...

class Eval_Space:
    oosb:int
    def __new__(cls,left:float,top:float,right:float,bottom:float,/) -> 'Eval_Space':
        ...
    def bind(self,bindable:_Es_Bindable,/) -> None:
        ...
    def unbind(self,bindable:_Es_Bindable,/) -> None:
        ...
    def tick(self,dt:float,num:int,/) -> None:
        ...
    def set_dim(self,tlx:float,tly:float,brx:float,bry:float,/) -> None:
        ...
    @property
    def bound(self) -> 'Iterable[_Es_Bindable]':
        ...
    @property
    def soft_circles(self) -> 'Iterable[Soft_Circle]':
        ...
    @property
    def force_conveyors(self) -> 'Iterable[Force_Conveyor]':
        ...
