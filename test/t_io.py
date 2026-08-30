from t_types    import BYTES_EV_SIZE, TestUnit, InputEvent
from packer     import pack_event, unpack_event
from subprocess import Popen
from threading  import Event
import time
import os

def read_event(subp: Popen) -> InputEvent:
    """
    Reads single event from subp.

    Raise:
        Exception
    """
    if subp.stdout is None:
        raise Exception("read_event: stdout is None")

    ev_bytes: bytes = subp.stdout.read(BYTES_EV_SIZE)

    if len(ev_bytes) < BYTES_EV_SIZE:
        raise Exception("read_event: bad bytes to read from subp")

    return unpack_event(ev_bytes)

def sequence_reader(subp: Popen, stop_sig: Event, seq_out: list[TestUnit] | list[InputEvent], start_time_ms: int | None = None) -> None:
    """
    Reads from subprocess to sequence_out.

    Raise:
        Exception
    """
    if subp.stdout is None:
        raise Exception("suqeunce_reader: stdout is None")

    os.set_blocking(subp.stdout.fileno(), False)

    read_some: bool = False
    while not stop_sig.is_set():
        ev_bytes: bytes = subp.stdout.read(BYTES_EV_SIZE)

        if not ev_bytes: continue

        read_some = True

        if len(ev_bytes) < BYTES_EV_SIZE:
            raise Exception("suqeunce_reader: bad bytes to read from subp")

        event: InputEvent = unpack_event(ev_bytes)


        if start_time_ms is not None:
            now_time_ms = int(time.perf_counter() * 1000)
            time_passed_ms: int = now_time_ms - start_time_ms

            seq_out.append(TestUnit(event, time_passed_ms))
        else:
            seq_out.append(event)

    os.set_blocking(subp.stdout.fileno(), True)

    if not read_some:
        raise Exception("suqeunce_reader: no bytes read from subp")

def write_event(subp: Popen, event: InputEvent) -> None:
    """
    Write single event to subprocess.
    """
    ev_bytes: bytes = pack_event(event)

    if subp.stdin is None:
        raise Exception("suqeunce_reader: stdin is None")

    subp.stdin.write(ev_bytes)

def sequence_writer(subp: Popen, seq: list[TestUnit]) -> None:
    """
    Writes to subprocess from sequence.
    """
    try:
        prev_ev_time_passed_sec: float = 0
        for unit in seq:
            time_passed_sec = unit.time_passed_ms / 1000
            sleep_time: float = time_passed_sec - prev_ev_time_passed_sec
            time.sleep(sleep_time)
            write_event(subp, unit.event)
            prev_ev_time_passed_sec = time_passed_sec
    except:
        raise
