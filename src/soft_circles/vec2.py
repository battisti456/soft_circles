from typing import override, Any
from math import sqrt

class _vec2_metaclass(type):
    def __init__(cls,name:str,bases:tuple[type,...],namespace:dict[str,Any]):
        cls.zero = cls((0,0))
        return type.__init__(cls,name,bases,namespace)

class vec2(tuple[float,float], metaclass = _vec2_metaclass):
    zero:'vec2'
    def __new__(cls,val:tuple[float,float],/):
        return tuple.__new__(#type:ignore
            cls,
            val
            )
    @override
    def __add__(self,other:tuple[float,float],/) -> 'vec2':
        return vec2((self[0]+other[0],self[1]+other[1]))
    def __radd__(self,other:tuple[float,float],/) -> 'vec2':
        return vec2((other[0]+self[0],other[1]+self[1]))
    def __sub__(self,other:tuple[float,float],/) -> 'vec2':
        return vec2((self[0]-other[0],self[1]-other[1]))
    def __rsub__(self,other:tuple[float,float],/) -> 'vec2':
        return vec2((other[0]-self[0],other[1]-self[1]))
    def __neg__(self,/) -> 'vec2':
        return vec2((-self[0],-self[1]))
    def __abs__(self,/) -> float:
        return sqrt(self[0]**2+self[1]**2)
    def dot(self,other:'vec2',/) -> float:
        return self[0]*other[0]+self[1]*other[1]
    def __mul__(self,val:float) -> 'vec2':
        return vec2((self[0]*val,self[1]*val))
    def __rmul__(self, val: float) -> 'vec2':
        return self*val
    def __truediv__(self,val:float) -> 'vec2':
        return vec2((self[0]/val,self[1]/val))
    def is_zero(self) -> bool:
        return self[0] == 0 and self[1] == 0