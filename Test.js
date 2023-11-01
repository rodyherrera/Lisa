const Application = H2O;

Application.Get('/', () => {
    return 'Hello World';
});

Application.Listen(8080);