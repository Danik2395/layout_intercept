from t_types import InputEvent, BYTES_EV_FMT
import struct

def pack_event(event: InputEvent) -> bytes:
    return struct.pack(BYTES_EV_FMT, event.seconds, event.useconds, event.ev_type, event.code, event.value)

def unpack_event(event_bytes: bytes) -> InputEvent:
    seconds, useconds, ev_type, code, value = struct.unpack(BYTES_EV_FMT, event_bytes)
    return InputEvent(seconds, useconds, ev_type, code, value)
