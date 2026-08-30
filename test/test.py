from t_types    import SeqCompare, TestUnit, InputEvent, TIME_DELTA_MS
from printer    import print_seq_compare, print_test_name, print_seq_name
from t_io       import write_event, sequence_reader, sequence_writer
from sequence   import logic_sequences
from subprocess import Popen
from threading  import Thread, Event
import time

def compare_sequence(write_seq: list[TestUnit], out_seq: list[TestUnit], target_seq: list[TestUnit]) -> None:
    target_len = len(target_seq)

    if target_len != len(out_seq):
        print("Not equal length")
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

    for seq in logic_sequences:
        out_seq: list[TestUnit] = []

        stop_read_sig: Event = Event()
        time_start_ms: int = int(time.perf_counter() * 1000)
        Thread(target=sequence_reader, args=[subp, stop_read_sig, out_seq, time_start_ms])

        sequence_writer(subp, seq.write_seq)

        stop_read_sig.set()

        print_seq_name(seq.name)
        compare_sequence(seq.write_seq, out_seq, seq.target_seq)

def test_stream(subp: Popen, event_count: int, sleep_ms: int) -> None:
    return

def test_bad_macro(subp: Popen) -> None:
    return

def test_bad_byte(subp: Popen) -> None:
    return
