import socket

HOST = '127.0.0.1'
PORT = 8001

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(2)

while True:
    client, addr = s.accept()

    try:
        print('Connected by', addr)
        while True:
            data = client.recv(1024)
            str_data = data.decode("utf8")
            if str_data == "":
                print(client.close())
                break
            else:
                print("Client: ", data)
                msg = input("Server: ")
                client.sendall((msg + "\n").encode("utf-8"))
    finally:
        client.close()
        s.close()
