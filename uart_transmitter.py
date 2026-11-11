START = 7
AVOID = 117
KICK = 155
HOLD = 123
DANCE = 111
APPROACH = 156
EMPTY = 0


def build(event, direction, degree_of_confidence):
    byte_buffer = [
        START,
        event,
        direction,
        degree_of_confidence,
        EMPTY,
        EMPTY,
        EMPTY,
        EMPTY,
        EMPTY,
    ]

    def XOR_calc():
        xor_val = 0
        for value in byte_buffer[:8]:
            xor_val = xor_val ^ value
        return xor_val

    new_xor_val = XOR_calc()

    byte_buffer[8] = new_xor_val
    new_byte_buffer = bytearray(byte_buffer)
    return new_byte_buffer
