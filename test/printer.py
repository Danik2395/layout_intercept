from t_types import SeqCompare, InputEvent, RED, GREEN, RESET

W_LABEL = 8
W_COL   = 10

def print_error(err: str) -> None:
     print(f"\n{RED}{err}{RESET}\n")


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

    def fmt_status(is_pass: bool) -> str:
        status_str = "PASS" if is_pass else "FAIL"
        color = GREEN if is_pass else RED
        return f"{color}{status_str:>{W_COL}}{RESET}"

    c_pass = seq_comp.code_pass
    t_pass = seq_comp.time_pass
    v_pass = seq_comp.value_pass

    #          received    target    status
    #code:           50        50      PASS
    #value:           1         1      PASS
    #time:           51        50      PASS
    #

    seq_formatted = f"""
    {"":<{W_LABEL}} {"send":>{W_COL}} {"received":>{W_COL}} {"target":>{W_COL}} {"status":>{W_COL}}
    {"code:":<{W_LABEL}} {send_unit.event.code:>{W_COL}} {received_unit.event.code:>{W_COL}} {target_unit.event.code:>{W_COL}} {fmt_status(c_pass):^{W_COL}}
    {"value:":<{W_LABEL}} {send_unit.event.value:>{W_COL}} {received_unit.event.value:>{W_COL}} {target_unit.event.value:>{W_COL}} {fmt_status(v_pass):^{W_COL}}
    {"time:":<{W_LABEL}} {send_unit.time_passed_ms:>{W_COL}} {received_unit.time_passed_ms:>{W_COL}} {target_unit.time_passed_ms:>{W_COL}} {fmt_status(t_pass):^{W_COL}}"""
    print(seq_formatted)

def print_event(event: InputEvent) -> None:
    #time:    0      0
    #type:    1
    #code:    50
    #value:   1
    #

    ev_formatted = f"""
        {"time:":<{W_LABEL}} {event.seconds:>{W_COL}} {event.useconds:>{W_COL}}
        {"type:":<{W_LABEL}} {event.ev_type:>{W_COL}}
        {"code:":<{W_LABEL}} {event.code:>{W_COL}}
        {"value:":<{W_LABEL}} {event.value:>{W_COL}}"""

    print(ev_formatted)
