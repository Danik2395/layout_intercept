from t_types import TestUnit, InputEvent, LogicSeqUnit

logic_sequences: list[LogicSeqUnit] = [
        LogicSeqUnit(
            name= "Test sequence",
            write_seq= [
                TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 45, value= 1),
                         0),
                TestUnit(InputEvent(seconds= 0, useconds= 10000, ev_type= 0, code= 0, value= 0),
                         0),
                TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 45, value= 0),
                         50),
                TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                         50),

                TestUnit(InputEvent(seconds= 0, useconds= 100000, ev_type= 1, code= 21, value= 1),
                         100),
                TestUnit(InputEvent(seconds= 0, useconds= 100000, ev_type= 0, code= 0, value= 0),
                         100),
                TestUnit(InputEvent(seconds= 0, useconds= 150000, ev_type= 1, code= 21, value= 0),
                         150),
                TestUnit(InputEvent(seconds= 0, useconds= 150000, ev_type= 0, code= 0, value= 0),
                         150),
                ],
            target_seq = [
                TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 21, value= 1),
                         0),
                TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 0, code= 0, value= 0),
                         0),
                TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 21, value= 0),
                         50),
                TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                         50),

                TestUnit(InputEvent(seconds= 0, useconds= 100000, ev_type= 1, code= 21, value= 1),
                         100),
                TestUnit(InputEvent(seconds= 0, useconds= 100000, ev_type= 0, code= 0, value= 0),
                         100),
                TestUnit(InputEvent(seconds= 0, useconds= 150000, ev_type= 1, code= 21, value= 0),
                         150),
                TestUnit(InputEvent(seconds= 0, useconds= 150000, ev_type= 0, code= 0, value= 0),
                         150),
                ]
            ),
        LogicSeqUnit(
            name= "1. th key tap",
            write_seq= [
                TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 30, value= 1),
                         0),
                TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 0, code= 0, value= 0),
                         0),

                TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 30, value= 0),
                         50),
                TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                         50),
                ],
            target_seq = [
                TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 49, value= 1),
                         50),
                TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                         50),

                TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 49, value= 0),
                         50),
                TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                         50),
                ]
            ),
        LogicSeqUnit(
                name= "2. key tap",
                write_seq= [
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 35, value= 1),
                             0),
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 0, code= 0, value= 0),
                             0),

                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 35, value= 0),
                             50),
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                             50),
                    ],
                target_seq = [
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 21, value= 1),
                             0),
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 0, code= 0, value= 0),
                             0),

                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 21, value= 0),
                             50),
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                             50),
                    ]
                ),
        LogicSeqUnit(
                name= "3. resolv th to hold with normal key",
                write_seq= [
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 30, value= 1),
                             0),
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 0, code= 0, value= 0),
                             0),

                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 35, value= 1),
                             50),
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                             50),

                    TestUnit(InputEvent(seconds= 0, useconds= 100000, ev_type= 1, code= 35, value= 0),
                             100),
                    TestUnit(InputEvent(seconds= 0, useconds= 100000, ev_type= 0, code= 0, value= 0),
                             100),

                    TestUnit(InputEvent(seconds= 0, useconds= 150000, ev_type= 1, code= 30, value= 0),
                             150),
                    TestUnit(InputEvent(seconds= 0, useconds= 150000, ev_type= 0, code= 0, value= 0),
                             150),
                    ],
                target_seq = [
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 42, value= 1),
                             50),
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                             50),

                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 21, value= 1),
                             50),
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                             50),

                    TestUnit(InputEvent(seconds= 0, useconds= 100000, ev_type= 1, code= 21, value= 0),
                             100),
                    TestUnit(InputEvent(seconds= 0, useconds= 100000, ev_type= 0, code= 0, value= 0),
                             100),

                    TestUnit(InputEvent(seconds= 0, useconds= 150000, ev_type= 1, code= 42, value= 0),
                             150),
                    TestUnit(InputEvent(seconds= 0, useconds= 150000, ev_type= 0, code= 0, value= 0),
                             150),
                    ]
                ),
        LogicSeqUnit(
                name= "4. th key hold",
                write_seq= [
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 30, value= 1),
                             0),
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 0, code= 0, value= 0),
                             0),

                    TestUnit(InputEvent(seconds= 0, useconds= 250000, ev_type= 1, code= 35, value= 1),
                             250),
                    TestUnit(InputEvent(seconds= 0, useconds= 250000, ev_type= 0, code= 0, value= 0),
                             250),

                    TestUnit(InputEvent(seconds= 0, useconds= 300000, ev_type= 1, code= 35, value= 0),
                             300),
                    TestUnit(InputEvent(seconds= 0, useconds= 300000, ev_type= 0, code= 0, value= 0),
                             300),

                    TestUnit(InputEvent(seconds= 0, useconds= 350000, ev_type= 1, code= 30, value= 0),
                             350),
                    TestUnit(InputEvent(seconds= 0, useconds= 350000, ev_type= 0, code= 0, value= 0),
                             350),
                    ],
                target_seq = [
                    TestUnit(InputEvent(seconds= 0, useconds= 200000, ev_type= 1, code= 42, value= 1),
                             200),
                    TestUnit(InputEvent(seconds= 0, useconds= 200000, ev_type= 0, code= 0, value= 0),
                             200),

                    TestUnit(InputEvent(seconds= 0, useconds= 250000, ev_type= 1, code= 21, value= 1),
                             250),
                    TestUnit(InputEvent(seconds= 0, useconds= 250000, ev_type= 0, code= 0, value= 0),
                             250),

                    TestUnit(InputEvent(seconds= 0, useconds= 300000, ev_type= 1, code= 21, value= 0),
                             300),
                    TestUnit(InputEvent(seconds= 0, useconds= 300000, ev_type= 0, code= 0, value= 0),
                             300),

                    TestUnit(InputEvent(seconds= 0, useconds= 350000, ev_type= 1, code= 42, value= 0),
                             350),
                    TestUnit(InputEvent(seconds= 0, useconds= 350000, ev_type= 0, code= 0, value= 0),
                             350),
                    ]
                ),
        LogicSeqUnit(
                name= "5. fast typing",
                write_seq= [
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 35, value= 1),
                             0),
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 0, code= 0, value= 0),
                             0),

                    TestUnit(InputEvent(seconds= 0, useconds= 25000, ev_type= 1, code= 35, value= 0),
                             25),
                    TestUnit(InputEvent(seconds= 0, useconds= 25000, ev_type= 0, code= 0, value= 0),
                             25),

                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 30, value= 1),
                             50),
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                             50),

                    TestUnit(InputEvent(seconds= 0, useconds= 75000, ev_type= 1, code= 30, value= 0),
                             75),
                    TestUnit(InputEvent(seconds= 0, useconds= 75000, ev_type= 0, code= 0, value= 0),
                             75),
                    ],
                target_seq = [
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 21, value= 1),
                             0),
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 0, code= 0, value= 0),
                             0),

                    TestUnit(InputEvent(seconds= 0, useconds= 25000, ev_type= 1, code= 21, value= 0),
                             25),
                    TestUnit(InputEvent(seconds= 0, useconds= 25000, ev_type= 0, code= 0, value= 0),
                             25),

                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 49, value= 1),
                             50),
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                             50),

                    TestUnit(InputEvent(seconds= 0, useconds= 75000, ev_type= 1, code= 49, value= 0),
                             75),
                    TestUnit(InputEvent(seconds= 0, useconds= 75000, ev_type= 0, code= 0, value= 0),
                             75),
                    ]
                ),
        LogicSeqUnit(
                name= "6. fast typing with th only",
                write_seq= [
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 30, value= 1),
                             0),
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 0, code= 0, value= 0),
                             0),

                    TestUnit(InputEvent(seconds= 0, useconds= 25000, ev_type= 1, code= 31, value= 1),
                             25),
                    TestUnit(InputEvent(seconds= 0, useconds= 25000, ev_type= 0, code= 0, value= 0),
                             25),

                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 30, value= 0),
                             50),
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                             50),

                    TestUnit(InputEvent(seconds= 0, useconds= 75000, ev_type= 1, code= 31, value= 0),
                             75),
                    TestUnit(InputEvent(seconds= 0, useconds= 75000, ev_type= 0, code= 0, value= 0),
                             75),
                    ],
                target_seq = [
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 49, value= 1),
                             50),
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                             50),

                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 19, value= 1),
                             50),
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                             50),

                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 49, value= 0),
                             50),
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                             50),

                    TestUnit(InputEvent(seconds= 0, useconds= 75000, ev_type= 1, code= 19, value= 0),
                             75),
                    TestUnit(InputEvent(seconds= 0, useconds= 75000, ev_type= 0, code= 0, value= 0),
                             75),
                    ]
                ),
        LogicSeqUnit(
                name= "7. resolv th to hold with th key",
                write_seq= [
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 30, value= 1),
                             0),
                    TestUnit(InputEvent(seconds= 0, useconds= 10000, ev_type= 0, code= 0, value= 0),
                             0),

                    TestUnit(InputEvent(seconds= 0, useconds= 25000, ev_type= 1, code= 31, value= 1),
                             25),
                    TestUnit(InputEvent(seconds= 0, useconds= 25000, ev_type= 0, code= 0, value= 0),
                             25),

                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 31, value= 0),
                             50),
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                             50),

                    TestUnit(InputEvent(seconds= 0, useconds= 75000, ev_type= 1, code= 30, value= 0),
                             75),
                    TestUnit(InputEvent(seconds= 0, useconds= 75000, ev_type= 0, code= 0, value= 0),
                             75),
                    ],
                target_seq = [
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 42, value= 1),
                             50),
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                             50),

                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 19, value= 1),
                             50),
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                             50),

                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 19, value= 0),
                             50),
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                             50),

                    TestUnit(InputEvent(seconds= 0, useconds= 75000, ev_type= 1, code= 42, value= 0),
                             75),
                    TestUnit(InputEvent(seconds= 0, useconds= 75000, ev_type= 0, code= 0, value= 0),
                             75),
                    ]
                ),
        LogicSeqUnit(
                name= "8. double tap th key to repeat th.tap",
                write_seq= [
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 30, value= 1),
                             0),
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 0, code= 0, value= 0),
                             0),

                    TestUnit(InputEvent(seconds= 0, useconds= 25000, ev_type= 1, code= 30, value= 0),
                             25),
                    TestUnit(InputEvent(seconds= 0, useconds= 25000, ev_type= 0, code= 0, value= 0),
                             25),

                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 30, value= 1),
                             50),
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                             50),

                    TestUnit(InputEvent(seconds= 0, useconds= 300000, ev_type= 1, code= 30, value= 0),
                             300),
                    TestUnit(InputEvent(seconds= 0, useconds= 300000, ev_type= 0, code= 0, value= 0),
                             300),
                    ],
                target_seq = [
                    TestUnit(InputEvent(seconds= 0, useconds= 25000, ev_type= 1, code= 49, value= 1),
                             25),
                    TestUnit(InputEvent(seconds= 0, useconds= 25000, ev_type= 0, code= 0, value= 0),
                             25),

                    TestUnit(InputEvent(seconds= 0, useconds= 25000, ev_type= 1, code= 49, value= 0),
                             25),
                    TestUnit(InputEvent(seconds= 0, useconds= 25000, ev_type= 0, code= 0, value= 0),
                             25),

                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 49, value= 1),
                             50),
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                             50),

                    TestUnit(InputEvent(seconds= 0, useconds= 300000, ev_type= 1, code= 49, value= 0),
                             300),
                    TestUnit(InputEvent(seconds= 0, useconds= 300000, ev_type= 0, code= 0, value= 0),
                             300),
                    ]
                ),
        LogicSeqUnit(
                name= "9. resolv timer key to tap",
                write_seq= [
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 15, value= 1),
                             0),
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 0, code= 0, value= 0),
                             0),

                    TestUnit(InputEvent(seconds= 0, useconds= 100000, ev_type= 1, code= 15, value= 0),
                             100),
                    TestUnit(InputEvent(seconds= 0, useconds= 100000, ev_type= 0, code= 0, value= 0),
                             100),
                    ],
                target_seq = [
                    TestUnit(InputEvent(seconds= 0, useconds= 100000, ev_type= 1, code= 15, value= 1),
                             100),
                    TestUnit(InputEvent(seconds= 0, useconds= 100000, ev_type= 0, code= 0, value= 0),
                             100),

                    TestUnit(InputEvent(seconds= 0, useconds= 100000, ev_type= 1, code= 15, value= 0),
                             100),
                    TestUnit(InputEvent(seconds= 0, useconds= 100000, ev_type= 0, code= 0, value= 0),
                             100),
                    ]
                ),
        LogicSeqUnit(
                name= "10. resolv timer key to hold",
                write_seq= [
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 15, value= 1),
                             0),
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 0, code= 0, value= 0),
                             0),

                    TestUnit(InputEvent(seconds= 0, useconds= 250000, ev_type= 1, code= 15, value= 0),
                             250),
                    TestUnit(InputEvent(seconds= 0, useconds= 250000, ev_type= 0, code= 0, value= 0),
                             250),
                    ],
                target_seq = [
                    TestUnit(InputEvent(seconds= 0, useconds= 200000, ev_type= 1, code= 1, value= 1),
                             200),
                    TestUnit(InputEvent(seconds= 0, useconds= 200000, ev_type= 0, code= 0, value= 0),
                             200),

                    TestUnit(InputEvent(seconds= 0, useconds= 250000, ev_type= 1, code= 1, value= 0),
                             250),
                    TestUnit(InputEvent(seconds= 0, useconds= 250000, ev_type= 0, code= 0, value= 0),
                             250),
                    ]
                ),
        LogicSeqUnit(
                name= "11. alt alt test",
                write_seq= [
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 56, value= 1),
                             0),
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 0, code= 0, value= 0),
                             0),

                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 100, value= 1),
                             50),
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                             50),

                    TestUnit(InputEvent(seconds= 0, useconds= 100000, ev_type= 1, code= 100, value= 0),
                             100),
                    TestUnit(InputEvent(seconds= 0, useconds= 100000, ev_type= 0, code= 0, value= 0),
                             100),

                    TestUnit(InputEvent(seconds= 0, useconds= 150000, ev_type= 1, code= 56, value= 0),
                             150),
                    TestUnit(InputEvent(seconds= 0, useconds= 150000, ev_type= 0, code= 0, value= 0),
                             150),
                    ],
                target_seq = [
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 56, value= 1),
                             0),
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 0, code= 0, value= 0),
                             0),

                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 29, value= 1),
                             50),
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                             50),

                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 14, value= 1),
                             50),
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                             50),

                    TestUnit(InputEvent(seconds= 0, useconds= 100000, ev_type= 1, code= 29, value= 0),
                             100),
                    TestUnit(InputEvent(seconds= 0, useconds= 100000, ev_type= 0, code= 0, value= 0),
                             100),

                    TestUnit(InputEvent(seconds= 0, useconds= 100000, ev_type= 1, code= 14, value= 0),
                             100),
                    TestUnit(InputEvent(seconds= 0, useconds= 100000, ev_type= 0, code= 0, value= 0),
                             100),

                    TestUnit(InputEvent(seconds= 0, useconds= 150000, ev_type= 1, code= 56, value= 0),
                             150),
                    TestUnit(InputEvent(seconds= 0, useconds= 150000, ev_type= 0, code= 0, value= 0),
                             150),
                    ]
            ),
        LogicSeqUnit(
                name= "12. oneone test",
                write_seq= [
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 100, value= 1),
                             0),
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 0, code= 0, value= 0),
                             0),

                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 100, value= 0),
                             50),
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                             50),
                    ],
                target_seq = [
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 14, value= 1),
                             0),
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 0, code= 0, value= 0),
                             0),

                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 1, code= 14, value= 0),
                             50),
                    TestUnit(InputEvent(seconds= 0, useconds= 50000, ev_type= 0, code= 0, value= 0),
                             50),
                    ]
                ),
        LogicSeqUnit(
                name= "13. nav test",
                write_seq= [
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 58, value= 1),
                             0),
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 0, code= 0, value= 0),
                             0),

                    TestUnit(InputEvent(seconds= 0, useconds= 250000, ev_type= 1, code= 58, value= 0),
                             250),
                    TestUnit(InputEvent(seconds= 0, useconds= 250000, ev_type= 0, code= 0, value= 0),
                             250),
                    ],
                target_seq = [
                    ]
                ),
        LogicSeqUnit(
                name= "13. double th resolv to hold but first released earlier",
                write_seq= [
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 30, value= 1),
                             0),
                    TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 0, code= 0, value= 0),
                             0),

                    TestUnit(InputEvent(seconds= 0, useconds= 110000, ev_type= 1, code= 31, value= 1),
                             110),
                    TestUnit(InputEvent(seconds= 0, useconds= 110000, ev_type= 0, code= 0, value= 0),
                             110),

                    TestUnit(InputEvent(seconds= 0, useconds= 250000, ev_type= 1, code= 30, value= 0),
                             250),
                    TestUnit(InputEvent(seconds= 0, useconds= 250000, ev_type= 0, code= 0, value= 0),
                             250),

                    TestUnit(InputEvent(seconds= 0, useconds= 300000, ev_type= 1, code= 35, value= 1),
                             300),
                    TestUnit(InputEvent(seconds= 0, useconds= 300000, ev_type= 0, code= 0, value= 0),
                             300),

                    TestUnit(InputEvent(seconds= 0, useconds= 330000, ev_type= 1, code= 31, value= 0),
                             330),
                    TestUnit(InputEvent(seconds= 0, useconds= 330000, ev_type= 0, code= 0, value= 0),
                             330),

                    TestUnit(InputEvent(seconds= 0, useconds= 340000, ev_type= 1, code= 35, value= 0),
                             340),
                    TestUnit(InputEvent(seconds= 0, useconds= 340000, ev_type= 0, code= 0, value= 0),
                             340),
                    ],
                target_seq = [
                    TestUnit(InputEvent(seconds= 0, useconds= 200000, ev_type= 1, code= 42, value= 1),
                             200),
                    TestUnit(InputEvent(seconds= 0, useconds= 200000, ev_type= 0, code= 0, value= 0),
                             200),

                    TestUnit(InputEvent(seconds= 0, useconds= 250000, ev_type= 1, code= 42, value= 0),
                             250),
                    TestUnit(InputEvent(seconds= 0, useconds= 250000, ev_type= 0, code= 0, value= 0),
                             250),

                    TestUnit(InputEvent(seconds= 0, useconds= 300000, ev_type= 1, code= 19, value= 1),
                             300),
                    TestUnit(InputEvent(seconds= 0, useconds= 300000, ev_type= 0, code= 0, value= 0),
                             300),

                    TestUnit(InputEvent(seconds= 0, useconds= 300000, ev_type= 1, code= 21, value= 1),
                             300),
                    TestUnit(InputEvent(seconds= 0, useconds= 300000, ev_type= 0, code= 0, value= 0),
                             300),

                    TestUnit(InputEvent(seconds= 0, useconds= 330000, ev_type= 1, code= 19, value= 0),
                             330),
                    TestUnit(InputEvent(seconds= 0, useconds= 330000, ev_type= 0, code= 0, value= 0),
                             330),

                    TestUnit(InputEvent(seconds= 0, useconds= 340000, ev_type= 1, code= 21, value= 0),
                             340),
                    TestUnit(InputEvent(seconds= 0, useconds= 340000, ev_type= 0, code= 0, value= 0),
                             340),
                    ]
                ),
        ]

bad_macro_seq: list[TestUnit] = [
        TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 42, value= 1),
                 0),
        TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 42, value= 1),
                 5),
        TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 42, value= 1),
                 10),
        TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 42, value= 1),
                 15),
        TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 97, value= 0),
                 20),
        TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 97, value= 0),
                 25),
        TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 97, value= 0),
                 30),
        TestUnit(InputEvent(seconds= 0, useconds= 0, ev_type= 1, code= 97, value= 0),
                 35),
        ]
