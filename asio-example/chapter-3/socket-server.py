import socket

HOST = '127.0.0.1'
PORT = 8001
protocol = "UDP"

if protocol=="TCP":
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
else: # UDP
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind((HOST, PORT))

if protocol=="TCP":
    s.listen(2)

if __name__=="__main__":
# while True:
    if protocol=="TCP":
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
                    msg = "ANoi"
                    client.sendall((msg + "\n").encode("utf-8"))
        finally:
            client.close()
            s.close()
    else: # UDP
        try:
            while True:
                data = s.recvfrom(1024)
                print(data)
                if data[0] == "":
                    print(s.close())
                    break
                else:
                    msg = "ANoi"
                    s.sendto((msg + "\n").encode("utf-8"), data[1])
                    print("sent!")
        finally:
            s.close()
