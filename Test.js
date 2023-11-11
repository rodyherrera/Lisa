const SocketServer = Network.WebSocketServer();

SocketServer.AddServerName('TestServer');

SocketServer.Listen('0.0.0.0', 8000, () => {
    Console.Log('Server is listening on port 8000');
});