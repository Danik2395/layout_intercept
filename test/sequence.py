from t_types import TestUnit, InputEvent, LogicSeqUnit

logic_sequences: list[LogicSeqUnit] = [
        LogicSeqUnit(
            name= "Test sequence",
            write_seq= [
                TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 45, value= 1),
                         0),
                TestUnit(InputEvent(seconds= 0, useconds= 10000, ev_type= 0, code= 0, value= 0),
                         10),
                TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 45, value= 0),
                         50),
                TestUnit(InputEvent(seconds= 0, useconds= 60000, ev_type= 0, code= 0, value= 0),
                         60),

                TestUnit(InputEvent(seconds= 0, useconds= 100000, ev_type= 1, code= 21, value= 1),
                         100),
                TestUnit(InputEvent(seconds= 0, useconds= 110000, ev_type= 0, code= 0, value= 0),
                         110),
                TestUnit(InputEvent(seconds= 0, useconds= 150000, ev_type= 1, code= 21, value= 0),
                         150),
                TestUnit(InputEvent(seconds= 0, useconds= 160000, ev_type= 0, code= 0, value= 0),
                         160),
                ],
            target_seq = [
                TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 21, value= 1),
                         0),
                TestUnit(InputEvent(seconds= 0, useconds= 10000, ev_type= 0, code= 0, value= 0),
                         10),
                TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 21, value= 0),
                         50),
                TestUnit(InputEvent(seconds= 0, useconds= 60000, ev_type= 0, code= 0, value= 0),
                         60),

                TestUnit(InputEvent(seconds= 0, useconds= 100000, ev_type= 1, code= 21, value= 1),
                         100),
                TestUnit(InputEvent(seconds= 0, useconds= 110000, ev_type= 0, code= 0, value= 0),
                         110),
                TestUnit(InputEvent(seconds= 0, useconds= 150000, ev_type= 1, code= 21, value= 0),
                         150),
                TestUnit(InputEvent(seconds= 0, useconds= 160000, ev_type= 0, code= 0, value= 0),
                         160),
                ]
            ),
        ]

# test_bad_macro_seq: list[TestUnit] = [
#         TestUnit(InputEvent(seconds= , useconds= , type= , code= , value= ),
#                  ),
#         ]
