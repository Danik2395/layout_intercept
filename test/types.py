from dataclasses import dataclass
import struct

BYTES_EV_FMT : str = "qqHHi"
BYTES_EV_SIZE: int = struct.calcsize(BYTES_EV_FMT)

TIME_DELTA_MS = 15

@dataclass
class InputEvent:
    """
    Attributes:
        seconds     : int
        useconds    : int
        ev_type     : int
        code        : int
        value       : int
    """
    seconds     : int
    useconds    : int
    ev_type     : int
    code        : int
    value       : int

@dataclass
class TestUnit:
    """
    Attributes:
        event         : InputEvent
        time_passed_ms: int
    """
    event         : InputEvent
    time_passed_ms: int

@dataclass
class LogicSeqUnit:
    """
    Attributes:
        name     : str
        write_seq: list[TestUnit]
        read_seq : list[TestUnit]
    """
    name      : str
    write_seq : list[TestUnit]
    target_seq: list[TestUnit]

@dataclass
class SeqCompare:
    """
    Attributes:
        send     : InputEvent
        received : InputEvent
        target   : InputEvent
        code_pass: bool
        time_pass: bool
    """
    send      : InputEvent
    received  : InputEvent
    target    : InputEvent
    code_pass : bool
    value_pass: bool
    time_pass : bool
