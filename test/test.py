from t_types    import SeqCompare, TestUnit, InputEvent, TIME_DELTA_MS
from printer    import print_seq_compare, print_test_name, print_seq_name, print_error, print_event
from t_io       import write_event, sequence_reader, sequence_writer
from printer    import print_error
from sequence   import logic_sequences, bad_macro_seq
from subprocess import Popen
from threading  import Thread, Event
import time
import random

def compare_sequence(write_seq: list[TestUnit], out_seq: list[TestUnit], target_seq: list[TestUnit]) -> None:
    target_len = len(target_seq)
    out_len    = len(out_seq)

    if target_len != out_len:
        print_error(f"Not equal length: target_len = {target_len}, out_len = {out_len}")
        return

    for unit_idx in range(target_len):
        write_unit  = write_seq[unit_idx]
        out_unit    = out_seq[unit_idx]
        target_unit = target_seq[unit_idx]

        code_pass : bool = out_unit.event.code  == target_unit.event.code
        value_pass: bool = out_unit.event.value == target_unit.event.value
        time_pass : bool = abs(out_unit.time_passed_ms - target_unit.time_passed_ms) < TIME_DELTA_MS

        seq_compare: SeqCompare = SeqCompare(write_unit, out_unit, target_unit, code_pass, value_pass, time_pass)

        print_seq_compare(seq_compare)

def test_logic(subp: Popen) -> None:
    print_test_name("Logic")

    stop_read_sig: Event = Event()

    try:
        for seq in logic_sequences:
            out_seq: list[TestUnit] = []

            time_start_ms: int = int(time.perf_counter() * 1000)
            Thread(target=sequence_reader, args=[subp, stop_read_sig, out_seq, time_start_ms]).start()

            sequence_writer(subp, seq.write_seq)

            time.sleep(1)

            stop_read_sig.set()

            print_seq_name(seq.name)
            compare_sequence(seq.write_seq, out_seq, seq.target_seq)
    except Exception as e:
        stop_read_sig.set()
        print_error(str(e))

def get_time_for_ev() -> tuple[int, int]:
    t: float = time.time()
    sec: int = int(t)
    usec: int = int((t - sec) * 1_000_000)
    return sec, usec

def random_event_tuple() -> list[InputEvent]:
    """
    Return:
        One key tap. 4 valid to send events: key_up syn_ev key_down syn_ev.
        No time set
    """
    rand_code = random.randint(1, 255)

    events: list[InputEvent] = []

    events.append(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= rand_code, value= 1))
    events.append(InputEvent(seconds= 0, useconds= 0, ev_type= 0, code= 0, value= 0))
    events.append(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= rand_code, value= 0))
    events.append(InputEvent(seconds= 0, useconds= 0, ev_type= 0, code= 0, value= 0))

    return events

def test_stream(subp: Popen, event_count: int, sleep_ms: int, suspend: bool) -> None:
    print_test_name("Stream")

    sleep_sec: int = int(sleep_ms / 1000)
    stop_read_sig: Event = Event()

    stream_out: list[InputEvent] = []

    try:
        Thread(target=sequence_reader, args=[subp, stop_read_sig, stream_out]).start()

        for _ in range(int(event_count / 4)):
            events = random_event_tuple()

            for ev in events:
                time.sleep(sleep_sec)
                seconds, useconds = get_time_for_ev()
                ev.seconds  = seconds
                ev.useconds = useconds
                write_event(subp, ev)

        time.sleep(1)
        stop_read_sig.set()

    except Exception as e:
        stop_read_sig.set()
        print_error(str(e))
        return

    if not suspend:
        for ev in stream_out:
            print_event(ev)

    test_logic(subp)

def test_bad_macro(subp: Popen, suspend: bool) -> None:
    print_test_name("Bad Macro")

    stop_read_sig: Event = Event()

    stream_out: list[InputEvent] = []

    try:
        Thread(target=sequence_reader, args=[subp, stop_read_sig, stream_out]).start()

        sequence_writer(subp, bad_macro_seq)

        time.sleep(1)
        stop_read_sig.set()

    except Exception as e:
        stop_read_sig.set()
        print_error(str(e))

    if not suspend:
        for ev in stream_out:
            print_event(ev)

    test_logic(subp)

def test_bad_byte(subp: Popen) -> None:
    return
