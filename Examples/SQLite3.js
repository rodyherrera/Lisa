(async () => {
    const DatabaseName = 'Database.db';
    const Database = SQLite3.Open(DatabaseName);

    if(Database !== SQLite3.OK){
        Console.Log('[ERROR] Database Failed To Open.');
        return;
    }

    Console.Log('[OK] Database Opened Successfully.');
    
    const CreateTable = SQLite3.Execute(Database, 'CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT, email TEXT)');
    if(CreateTable !== SQLite3.OK){
        Console.Log('[ERROR] Table Failed To Create');
        return;
    }
    
    Console.Log('[OK] Table Created Successfully');

    const Users = [
        {
            Username: 'codewithrodi',
            Password: '123456',
            Email: 'contact@codewithrodi.com'
        },
        {
            Username: 'idorhtiwedoc',
            Password: '654321',
            Email: 'admin@codewithrodi.com'
        }
    ];

    for(const User of Users){
        const Insert = SQLite3.Execute(Database, `INSERT INTO users (username, password, email) VALUES ('${User.Username}', '${User.Password}', '${User.Email}')`);
        if(Insert !== SQLite3.OK){
            Console.Log('[ERROR] Insert Failed');
            return;
        }
    }
  
    Console.Log('[OK] Insert Successfully');

    const Query = 'SELECT * FROM users;';
    const Statement = SQLite3.PrepareV2(Database, Query);

    while(SQLite3.Step(Statement) === SQLite3.ROW){
        const Username = SQLite3.ColumnText(Statement, 0);
        const Password = SQLite3.ColumnText(Statement, 1);
        const Email = SQLite3.ColumnText(Statement, 2);

        Console.Log(`[OK] Username: ${Username} Password: ${Password} Email: ${Email}`);
    }

    Console.Log('[OK] Query Successfully');

    const Finalize = SQLite3.Finalize(Statement);

    if(Finalize !== SQLite3.OK){
        Console.Log('[ERROR] Statement Failed To Finalize');
        return;
    }

    Console.Log('[OK] Statement Finalized Successfully');

    const Close = SQLite3.Close(Database);
    if(Close !== SQLite3.OK){
        Console.Log('[ERROR] Database Failed To Close');
        return;
    }

    Console.Log('[OK] Database Closed Successfully');

    const Remove = SQLite3.Remove('Database.db');

    Console.Log('[OK] Database Removed Successfully');
})();
