import socket

HOST = '0.0.0.0'
PORT = 8080

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client:
    client.connect((HOST, PORT))

    message = 'ciallo~'
    client.sendall(message.encode('utf-8'))
    
    data = client.recv(1024)
    echo = data.decode('utf-8')
    
    print(f'echo: {echo}')