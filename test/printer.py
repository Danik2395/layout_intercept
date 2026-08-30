from t_types import SeqCompare

def print_test_name(name: str) -> None:
    name_formatted = f"\n\n---\nTest: {name}\n---\n"
    print(name_formatted)

def print_seq_name(name: str) -> None:
    name_formatted = f"### {name} ###"
    print(name_formatted)

def print_seq_compare(seq_comp: SeqCompare) -> None:
    send_unit     = seq_comp.send
    received_unit = seq_comp.received
    target_unit   = seq_comp.target

    GREEN = "\033[92m"
    RED   = "\033[91m"
    RESET = "\033[0m"

    w_label = 8
    w_col   = 10

    def fmt_status(is_pass: bool) -> str:
        status_str = "PASS" if is_pass else "FAIL"
        color = GREEN if is_pass else RED
        return f"{color}{status_str:>{w_col}}{RESET}"

    c_pass = seq_comp.code_pass
    t_pass = seq_comp.time_pass
    v_pass = seq_comp.value_pass

    #          received    target    status
    #code:           50        50      PASS
    #value:           1         1      PASS
    #time:           51        50      PASS
    #

    seq_formatted = f"""
    {"":<{w_label}} {"send":>{w_col}} {"received":>{w_col}} {"target":>{w_col}} {"status":>{w_col}}
    {"code:":<{w_label}} {send_unit.event.code:>{w_col}} {received_unit.event.code:>{w_col}} {target_unit.event.code:>{w_col}} {fmt_status(c_pass):^{w_col}}
    {"value:":<{w_label}} {send_unit.event.value:>{w_col}} {received_unit.event.value:>{w_col}} {target_unit.event.value:>{w_col}} {fmt_status(v_pass):^{w_col}}
    {"time:":<{w_label}} {send_unit.time_passed_ms:>{w_col}} {received_unit.time_passed_ms:>{w_col}} {target_unit.time_passed_ms:>{w_col}} {fmt_status(t_pass):^{w_col}}"""
    print(seq_formatted)

