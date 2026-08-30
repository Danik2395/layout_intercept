from test       import test_logic, test_stream, test_bad_macro, test_bad_byte
from subprocess import Popen, PIPE
import argparse

def main() -> None:
    parser = argparse.ArgumentParser(description="layout_intercept tester")

    parser.add_argument(
            "--path",
            type=str,
            required=True,
            help="Path to the executable."
            )

    parser.add_argument(
            "--logic",
            action='store_true',
            help="Test logic and strapping of plugin."
            )

    parser.add_argument(
            "--stream",
            action='store_true',
            help="Test plugin on fast stream of input."
            )
    parser.add_argument(
            "--stream_count",
            type=int,
            default=1000,
            help="How many structs send in stream test."
            )
    parser.add_argument(
            "--stream_sleep",
            type=int,
            default=80,
            help="How much to sleep in stream test."
            )

    parser.add_argument(
            "--bad_macro",
            action='store_true',
            help="Test bad sequence of input."
            )

    parser.add_argument(
            "--bad_byte",
            action='store_true',
            help="Test bad input data (random bytes, not full structure)."
            )

    parser.add_argument(
            "--all",
            action='store_true',
            help="Run all tests."
            )

    args = parser.parse_args()

    exec = args.path

    run_test_logic    : bool = True if args.all else args.logic
    run_test_stream   : bool = True if args.all else args.stream
    run_test_bad_macro: bool = True if args.all else args.bad_macro
    run_test_bad_byte : bool = True if args.all else args.bad_byte

    stream_sleep: int = args.stream_sleep
    stream_count: int = args.stream_count

    subp = Popen([f"{exec}"], stdin=PIPE, stdout=PIPE, bufsize=0)

    if run_test_logic:
        test_logic(subp)

    if run_test_stream:
        test_stream(subp, stream_count, stream_sleep)

    if run_test_bad_macro:
        test_bad_macro(subp)

    if run_test_bad_byte:
        test_bad_byte(subp)

if __name__ == "__main__":
    main()
