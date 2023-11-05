const Options = {
    Hostname: '0.0.0.0',
    Port: 8000
};

const Application = CHTTPL.CreateServer();

Application.Get('/u/:username', (Request, Response) => {
    Response.Send(JSON.stringify({
        Status: 200,
        Message: 'Hello World!'
    }), 'application/json', 200);
});

Application.Listen(Options, () => {
    Console.Log(`Server is running on ${Options.Hostname}:${Options.Port}`);
});