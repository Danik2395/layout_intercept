from test.types import TestUnit, InputEvent, LogicSeqUnit

logic_sequences: list[LogicSeqUnit] = [
        LogicSeqUnit(
            name= ,
            write_seq= [
                TestUnit(InputEvent(seconds= , useconds= , ev_type= , code= , value= ),
                         ),
                ],
            read_seq = [
                TestUnit(InputEvent(seconds= , useconds= , ev_type= , code= , value= ),
                         ),
                ]
            ),
        ]

test_bad_macro_seq: list[TestUnit] = [
        TestUnit(InputEvent(seconds= , useconds= , type= , code= , value= ),
                 ),
        ]
