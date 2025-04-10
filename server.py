import socket
from concurrent.futures import ThreadPoolExecutor

HOST = '0.0.0.0'
PORT = 8080

def handle(client: socket.socket, addr: tuple[str, int]):
    print(addr, 'connected.')
    tip_message = 'connected successfully!\nif you want to exit, enter \'exit\'\n'
    client.sendall(tip_message.encode('utf-8'))

    while True:
        data = client.recv(1024)
        if not data:
            break
        message = data.decode('utf-8')
        if message.startswith('exit'):
            tip_message = 'press \'ENTER\' to exit\n'
            client.sendall(tip_message.encode('utf-8'))
            break
        print(addr, ': ' + message)
        message = 'echo ' + message
        client.sendall(message.encode('utf-8'))
    
    print(addr, 'lost connection.')
    client.close()

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((HOST, PORT))
    server.listen()

    with ThreadPoolExecutor(max_workers = 100) as pool:
        cnt = 1
        while cnt != 0:
            client, addr = server.accept()
            pool.submit(handle, client, addr)
            cnt -= 1