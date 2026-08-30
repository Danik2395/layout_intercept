from test.types    import SeqCompare, TestUnit, InputEvent, TIME_DELTA_MS
from test.printer  import print_seq_compare, print_test_name, print_seq_name
from test.io       import write_event, sequence_reader, sequence_writer
from test.sequence import logic_sequences
from subprocess    import Popen
from threading     import Thread, Event
import time

def compare_sequence(write_seq: list[TestUnit], out_seq: list[TestUnit], target_seq: list[TestUnit]) -> None:
    target_len = len(target_seq)

    if target_len != len(out_seq):
        print("Not equal length")
        return

    for unit_idx in range(target_len):
        write_event  = write_seq[unit_idx].event
        out_event    = out_seq[unit_idx].event
        target_event = target_seq[unit_idx].event

        code_pass : bool = out_seq[unit_idx].event.code  == target_seq[unit_idx].event.code
        value_pass: bool = out_seq[unit_idx].event.value == target_seq[unit_idx].event.value
        time_pass : bool = abs(out_seq[unit_idx].time_passed_ms - target_seq[unit_idx].time_passed_ms) < TIME_DELTA_MS

        seq_compare: SeqCompare = SeqCompare(write_event, out_event, target_event, code_pass, value_pass, time_pass)

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
