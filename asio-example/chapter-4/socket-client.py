import socket
from time import sleep

HOST = '127.0.0.1'
PORT = 8000

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = (HOST, PORT)
s.connect(server_address)
print('Connected to %s port ' + str(server_address))
try:
    sleep(2)
    msg = "Do Thu An\n"
    s.sendall(bytes(msg, "utf8"))
    data = s.recv(1024)
    print('Server: ', data.decode("utf8"))

    # msg = input('Client: ')
    # if msg == "quit":
    #     break
    # else:
    #     s.sendall(bytes(msg, "utf8"))

finally:
    s.close()
