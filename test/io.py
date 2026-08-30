from test.types  import BYTES_EV_SIZE, TestUnit, InputEvent
from test.packer import pack_event, unpack_event
from subprocess  import Popen
from threading   import Event
import time

def sequence_reader(subp: Popen, stop_sig: Event, seq_out: list[TestUnit], start_time_ms: int) -> None:
    """
    Reads from subprocess to sequence_out.
    """
    if subp.stdout is None: return

    while not stop_sig.is_set():
        ev_bytes: bytes = subp.stdout.read(BYTES_EV_SIZE)

        if len(ev_bytes) < BYTES_EV_SIZE: return

        now_time_ms = int(time.time() * 1000)
        time_passed_ms: int = now_time_ms - start_time_ms

        event: InputEvent = unpack_event(ev_bytes)

        seq_out.append(TestUnit(event, time_passed_ms))

def write_event(subp: Popen, event: InputEvent) -> None:
    """
    Write single event to subprocess.
    """
    ev_bytes: bytes = pack_event(event)

    if subp.stdin is None: return

    subp.stdin.write(ev_bytes)

def sequence_writer(subp: Popen, seq: list[TestUnit]) -> None:
    """
    Writes to subprocess from sequence.
    """
    prev_ev_time_passed_sec: float = 0
    for unit in seq:
        time_passed_sec = unit.time_passed_ms / 1000
        sleep_time: float = time_passed_sec - prev_ev_time_passed_sec
        time.sleep(sleep_time)
        write_event(subp, unit.event)
        prev_ev_time_passed_sec = time_passed_sec
