from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from ..soft_circles_module import ForceConveyorReference, ReactionReference


class _Force_Conveyor[T]():
    def __init__(self,fcr:T):
        self._reference:T = fcr

class Force_Conveyor(_Force_Conveyor['ForceConveyorReference']):
    ...

class Reaction(_Force_Conveyor['ReactionReference']):
    ...

