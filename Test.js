const Options = {
    Hostname: '0.0.0.0',
    Port: 8000
};

const Application = CHTTPL.CreateServer();

Application.Get('/', (Request, Response) => {
    Response.Send('Hello World!', 'text/html', 500);
});

Application.Listen(Options, () => {
    Console.Log(`Server is running on ${Options.Hostname}:${Options.Port}`);
});