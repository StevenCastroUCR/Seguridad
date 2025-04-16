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
        string idUser = utility.readInput("Digite nombre usuario : ", 20);
        if (!userExists(idUser )) {
            cout << "Error: El usuario no existe" << endl;
            continue;
        }

        string password = utility.readInput("Digite la contrasena: ", 20);
        
        usersFile.clear();
        usersFile.seekg(0, ios::beg);
        
        string start, user, pass;
        while (getUserData(usersFile, start, user, pass))
        {
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
        idUser = utility.readInput("Digite el nombre Usuario nuevo: ", 20);
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
        pass = utility.readInput("Digite la contrasena: ", 20);
        string cpass;
        cpass = utility.readInput("Digite la contrasena nuevamente: ", 20);
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
        isAdmin = utility.readInput("Es un usuario administrador ? 1-) Si , 2-) No: \n", 1);;

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
    string start, user, pass;

    while (getUserData(usersFile, start, user, pass))
    {
        if (user == userVerfication)
        {
            return true;
        }
    }
    return false;
}

/// @brief Obtiene los datos del usuario desde el archivo texto para verificar 
///         los pares de contraseña y tipo de usuario (admin, regular)
/// @param usersFile Archivo a leer
/// @param userType Tipo de usuario(regular, admin)
/// @param user Dato de usuario a verificar
/// @param pass Dato de contrasena a verificar
/// @return Regresa verdadero si la informacion concuerda con la introducida
bool Users::getUserData(ifstream &usersFile, string &userType, string &user, string &pass) {
    string line;
    while (getline(usersFile, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        line = xorCipher(line);
        istringstream iss(line);
        iss >> userType;

        if (userType == "admin") {
            iss >> user >> pass;
        } else {
            user = userType;
            iss >> pass;
        }

        return true;
    }
    return false;
}