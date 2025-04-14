#include "Users.h"

using namespace std;

Users::Users()
{

}
Users::~Users()
{

}

/// @brief Realiza la autenticacion del usuario pidiendo nombre y contrasena.
///        El usuario tiene hasta 3 intentos para ingresar correctamente.
///        Si el login es exitoso, se indica si es administrador.
/// @param isAdmin Referencia booleana que se actualiza a true si el usuario es admin.
/// @return true si la autenticacion fue exitosa, false en caso contrario.
bool Users::authentication(bool &isAdmin)
{
    int attempts = 0;
    const int maxAttempts = 3;

    ifstream usersFile("users.txt");

    if (!usersFile)
    {
        cerr << "Error: No se encontro el archivo" << endl;
        return false;
    }

    while (attempts < maxAttempts)
    {
        string idUser;
        string password;
        idUser = utility.readInput("Digite nombre usuario : ");
        password = utility.readInput("Digite la contrasena: ");

        string line;

        usersFile.clear();
        usersFile.seekg(0, ios::beg);

        while (getline(usersFile, line))
        {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            line = xorCipher(line);
            istringstream iss(line);
            string start, user, pass;
            iss >> start;

            if (start == "admin")
            {
                iss >> user >> pass;
            }
            else
            {
                user = start;
                iss >> pass;
            }

            if (idUser == user && password == pass)
            {
                isAdmin = (start == "admin");
                utility.log("login successful: " + idUser);
                cout << (isAdmin ? "Cuenta Administrador " : "")
                     << "Bienvenido: " << idUser << "!" << endl;
                return true;
            }
        }
        utility.log("login error: " + idUser);
        cout << "Error: usuario o contrasena invalidos" << endl;
        attempts++;
        if (attempts < maxAttempts)
        {
            cout << "Intentos restantes: " << (maxAttempts - attempts) << endl;
        }
    }

    cout << "Agoto el numero de intentos" << endl;
    return false;
};

/// @brief Crea un nuevo usuario solicitando nombre, contrasena y rol (admin o no).
///        Verifica si el usuario ya existe y valida que la contrasena se escriba dos veces.
///        Encripta los datos y los guarda en el archivo users.txt.
void Users::createUser()
{
    string idUser, pass;
    string isAdmin;
    string line;

    while (true)
    {
        idUser = utility.readInput("Digite el nombre Usuario nuevo: ");
        if (idUser.length() > 20)
        {
            utility.log("Error user creation, invalid user name");
            cout << " Nombre de usuario excede la longitud permitida(20 caracteres).\n";
            continue;
        }
        if (userExists(idUser))
        {
            utility.log("Error user creation, user already in use");
            cout << "Nombre de usuario ya existe\n";
            continue;
        }

        break;
    }

    while (true)
    {
        pass = utility.readInput("Digite la contrasena: ");
        if (pass.length() > 20)
        {
            utility.log("Error user creation, invalid password");
            cout << "Contrasena excede longitud permitida\n";
            continue;
        }
        string cpass;
        cpass = utility.readInput("Digite la contrasena nuevamente: ");
        if (!(pass == cpass))
        {
            utility.log("Error user creation, password mismatch");
            cout << "Las contrasenas no coinciden\n";
            continue;
        }
        break;
    }

    while (true)
    {
        isAdmin = utility.readInput("Es un usuario administrador ? 1-) Si , 2-) No: \n");;

        switch (stoi(isAdmin))
        {
        case 1:
            line = "admin " + idUser + " " + pass;
            break;
        case 2:
            line = idUser + " " + pass;
            break;
        default:
            cout << "Opcion invalida\n";
            continue;
        }
        break;
    }

    string encrypt = xorCipher(line);

    ofstream usersFile("users.txt", ios::app | std::ios::binary);
    if (!usersFile)
    {
        cerr << "Error al acceder a archivo!" << endl;
        return;
    }
    usersFile << encrypt << endl; 
    usersFile.close();
    utility.log("User added succesfully " + idUser);
    cout << "Usuario anadido correctamente\n";
};

/// @brief Verifica si un nombre de usuario ya existe en el archivo users.txt.
/// @param userVerfication Nombre del usuario a verificar.
/// @return true si el usuario ya existe, false si no.
bool Users::userExists(const string &userVerfication)
{
    ifstream usersFile("users.txt");
    string line;

    while (getline(usersFile, line))
    {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        string decryptedLine = xorCipher(line);
        istringstream iss(decryptedLine);
        string token;

        if (decryptedLine.find("admin") == 0)
        {
            iss >> token;
        }

        string existingLabel1;
        iss >> existingLabel1;

        if (existingLabel1 == userVerfication)
        {
            return true;
        }
    }
    return false;
}