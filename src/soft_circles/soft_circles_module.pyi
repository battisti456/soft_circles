class Soft_Circle:
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
    @property
    def eval_space(self) -> 'Eval_Space':
        ...

class Eval_Space:
    def bind(self,*args:Soft_Circle) -> None:
        ...
    def unbind(self,soft_circle:Soft_Circle,/) -> None:
        ...
