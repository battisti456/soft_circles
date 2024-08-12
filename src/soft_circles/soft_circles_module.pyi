from typing import NewType

SoftCircleReference = NewType('SoftCircleReference', object)
EvalSpaceReference = NewType('EvalSpaceReference', object)

type SoftCircleConstants = tuple[float,float,float,float,float,float,float]
"m, r, f, t, k, a, b"

def make_soft_circle(m:float,r:float,f:float,t:float,k:float,a:float,b:float,/) -> SoftCircleReference:
    ...

def get_soft_circle_position(scr:SoftCircleReference,/) -> tuple[float,float]:
    ...

def get_soft_circle_velocity(scr:SoftCircleReference,/) -> tuple[float,float]:
    ...

def get_soft_circle_acceleration(scr:SoftCircleReference,/) -> tuple[float,float]:
    ...

def get_soft_circle_constants(scr:SoftCircleReference,/) -> SoftCircleConstants:
    ...

def make_eval_space(x_size:float,y_size:float,x_divs:int,y_divs:int) -> EvalSpaceReference:
    ...

def add_soft_circle_to_eval_space(eval_space:EvalSpaceReference,soft_circle:SoftCircleReference) -> None:
    ...

def remove_soft_circle_from_eval_space(eval_space:EvalSpaceReference,soft_circle:SoftCircleReference) -> None:
    ...

def tick_eval_space(es:EvalSpaceReference,dt:float) -> None:
    ...