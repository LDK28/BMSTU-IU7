def encode_file(enigma, filename, outfile):
    input_file = open(filename, 'rb')
    output_file = open(outfile, 'wb')
    byte = input_file.read(100)
    while byte:
        bytes_to_write = b""
        for symbol in byte:
            char = chr(symbol)
            char = enigma.encode(char)
            bytes_to_write += bytes([ord(char)])
        output_file.write(bytes_to_write)
        byte = input_file.read(100)
    input_file.close()
    output_file.close()
