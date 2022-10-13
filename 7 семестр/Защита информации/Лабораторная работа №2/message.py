def encode_message(enigma, message):
    print("Message:'" + message +"'")
    message = enigma.encode(message)
    print("Encoded message:'" + message + "'")
