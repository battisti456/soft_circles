from typing import NewType

Reference = NewType("Reference", object)

SoftCircleReference = NewType('SoftCircleReference', Reference)
EvalSpaceReference = NewType('EvalSpaceReference', Reference)
ForceConveyorReference = NewType('ForceConveyorReference', Reference)
ReactionReference = NewType("ReactionReference",ForceConveyorReference)


def make_soft_circle(m:float,r:float,f:float,t:float,k:float,a:float,b:float,/) -> SoftCircleReference:
    ...

def get_soft_circle_position(scr:SoftCircleReference,/) -> tuple[float,float]:
    ...

def set_soft_circle_position(scr:SoftCircleReference,position:tuple[float,float],/) -> None:
    ...

def get_soft_circle_velocity(scr:SoftCircleReference,/) -> tuple[float,float]:
    ...

def set_soft_circle_velocity(scr:SoftCircleReference,velocity:tuple[float,float],/) -> None:
    ...

def get_soft_circle_acceleration(scr:SoftCircleReference,/) -> tuple[float,float]:
    ...

def set_soft_circle_acceleration(scr:SoftCircleReference,acceleration:tuple[float,float],/) -> None:
    ...

def get_soft_circle_m(scr:SoftCircleReference,/) -> float:
    ...

def get_soft_circle_r(scr:SoftCircleReference,/) -> float:
    ...

def get_soft_circle_f(scr:SoftCircleReference,/) -> float:
    ...

def get_soft_circle_t(scr:SoftCircleReference,/) -> float:
    ...

def get_soft_circle_k(scr:SoftCircleReference,/) -> float:
    ...

def get_soft_circle_a(scr:SoftCircleReference,/) -> float:
    ...

def get_soft_circle_b(scr:SoftCircleReference,/) -> float:
    ...

def get_soft_circle_is_immovable(scr:SoftCircleReference,/) -> bool:
    ...

def set_soft_circle_is_immovable(scr:SoftCircleReference,value:bool,/) -> None:
    ...

def make_soft_circle_gravity(scr:SoftCircleReference,g:float,/) -> ForceConveyorReference:
    ...

def make_eval_space(x_size:float,y_size:float,x_divs:int,y_divs:int,/) -> EvalSpaceReference:
    ...

def add_soft_circle_to_eval_space(eval_space:EvalSpaceReference,soft_circle:SoftCircleReference,/) -> None:
    ...

def remove_soft_circle_from_eval_space(eval_space:EvalSpaceReference,soft_circle:SoftCircleReference,/) -> None:
    ...

def tick_eval_space(es:EvalSpaceReference,dt:float,num_ticks:int,/) -> None:
    ...

def add_force_conveyor_to_eval_space(esr:EvalSpaceReference,fcr:ForceConveyorReference,/) -> None:
    ...

def delete_soft_circle(sc:SoftCircleReference,/) -> None:
    ...

def delete_eval_space(es:EvalSpaceReference,/) -> None:
    ...

def get_address_from_capsule(ref:Reference,/) -> int:
    ...
