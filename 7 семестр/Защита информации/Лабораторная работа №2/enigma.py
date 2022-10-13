#!/usr/bin/env python3

import random


class Enigma:
    def __init__(self, random_seed=None):
        if random_seed is not None:
            random.seed(random_seed)
        self.__init_rotors__()
        self.__init_positions__()
        self.__init_reflector__()

    def __init_rotors__(self):
        symbols = [chr(i) for i in range(256)]
        self._rotors = [[], [], []]
        self._rotors[0] = symbols.copy()
        self._rotors[1] = symbols.copy()
        self._rotors[2] = symbols.copy()
        random.shuffle(self._rotors[0])
        random.shuffle(self._rotors[1])
        random.shuffle(self._rotors[2])

    def __init_positions__(self):
        start_roter = [
            random.randint(0, 255),
            random.randint(0, 255),
            random.randint(0, 255),
        ]
        self._pos = start_roter.copy()
        self._start_pos = start_roter.copy()

    def __init_reflector__(self):
        self._reflector = [None] * 256
        pairs = [i for i in range(256)]
        random.shuffle(pairs)
        for i in range(0, 256, 2):
            self._reflector[pairs[i]] = pairs[i + 1]
            self._reflector[pairs[i + 1]] = pairs[i]

    def reset_rotors_to_start(self):
        self._pos = self._start_pos.copy()

    def encode(self, string: str) -> str:
        result = ""
        for char in string:
            # roll
            self._pos[0] += 1
            if self._pos[0] == 255:
                self._pos[0] = 0
                self._pos[1] += 1
                if self._pos[1] == 255:
                    self._pos[1] = 0
                    self._pos[2] += 1
                    if self._pos[2] == 255:
                        self._pos[2] = 0
            # rotor I
            index = ord(char)
            index += self._pos[0]
            index %= 256
            index = ord(self._rotors[0][index])
            # rotor II
            index += self._pos[1]
            index %= 256
            index = ord(self._rotors[1][index])
            # rotor III
            index += self._pos[2]
            index %= 256
            index = ord(self._rotors[2][index])
            # reflector
            index -= self._pos[2]
            index %= 256
            index = self._reflector[index]
            # rotor III
            index += self._pos[2]
            index %= 256
            for i in range(256):
                if ord(self._rotors[2][i]) == index:
                    index = i
                    break
            # rotor II
            index -= self._pos[2]
            index %= 256
            for i in range(256):
                if ord(self._rotors[1][i]) == index:
                    index = i
                    break
            # rotor I
            index -= self._pos[1]
            index %= 256
            for i in range(256):
                if ord(self._rotors[0][i]) == index:
                    index = i
                    break
            # result
            index -= self._pos[0]
            index %= 256
            result += chr(index)
        return result


if __name__ == "__main__":
    enigma = Enigma()
    message = "Hello, world!"
    print("Message:", message)
    message = enigma.encode(message)
    print("Encoded message:", message)
    enigma.reset_rotors_to_start()
    message = enigma.encode(message)
    print("Message:", message)
