#!/usr/bin/env python3

import sys
import argparse
from enigma import Enigma
import message
import file
from exceptions import ParameterException


def create_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-f", "--file",
        required=False, type=str,
        help="file, that encode"
    )
    parser.add_argument(
        "-o", "--out",
        required=False, type=str, default="out",
        help="output file"
    )
    parser.add_argument(
        "-m", "--message",
        required=False, type=str,
        help="message for encode"
    )
    parser.add_argument(
        "-s", "--seed",
        required=False, type=int,
        help="seed for generate rotors and reflector"
    )
    return parser


def main():
    parser = create_parser()
    args = parser.parse_args(sys.argv[1:])
    enigma = Enigma(args.seed)
    if args.message is not None:
        message.encode_message(enigma, args.message)
    elif args.file is not None:
        file.encode_file(enigma, args.file, args.out)
    else:
        raise ParameterException(
            "Need message or file parameter, add -h to show help"
        )


if __name__ == "__main__":
    main()
