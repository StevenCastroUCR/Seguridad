#include "Users.h"

const int MAX_ATTEMPTS = 3;

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
    ifstream usersFile("users.txt");

    if (!usersFile)
    {
        cerr << "Error: No se encontro el archivo" << endl;
        return false;
    }

    while (true)
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
        int attempts;
        bool matchFound = false;
        while (getUserData(usersFile, start, user, pass, attempts))
        {
            if (idUser == user)
            {
                matchFound = true; 

                if (attempts >= MAX_ATTEMPTS) {
                    std::cout << "Cuenta bloqueada por demasiados intentos fallidos." << endl;
                    return false;
                }

                if (password == pass) {
                    isAdmin = (start == "admin");
                    updateUserAttempts(idUser, 0);
                    utility.log("login successful: " + idUser);
                    std::cout << (isAdmin ? "Cuenta Administrador " : "")
                        << "Bienvenido: " << idUser << "!" << endl;
                    return true;
                }
                else
                {
                    updateUserAttempts(idUser, attempts + 1);
                    utility.log("login error: " + idUser);
                    int remainingAttempts = MAX_ATTEMPTS - (attempts + 1);

                    std::cout << "Error: usuario o contrasena invalidos" << endl;
                    if (remainingAttempts > 0)
                    {
                        std::cout << "Intentos restantes: " << remainingAttempts << endl;
                    }
                    else
                    {
                        std::cout << "Agoto el numero de intentos" << endl;
                    }
                    
                    break;
                }
            }
        }
        if (!matchFound)
        {
            cout << "Error inesperado: No se pudo encontrar el usuario" << endl;
            return false;
        }
    }
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
            line = "admin " + idUser + " " + pass + " "+ "0";
            break;
        case 2:
            line = idUser + " " + pass + " "+ "0";
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
    int attempts;

    while (getUserData(usersFile, start, user, pass, attempts))
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
bool Users::getUserData(ifstream &usersFile, string &userType
    , string &user, string &pass, int &attempts) {
    string line;
    while (getline(usersFile, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        line = xorCipher(line);
        istringstream iss(line);
        iss >> userType;

        if (userType == "admin") {
            iss >> user >> pass >> attempts; 
        } else {
            user = userType;
            iss >> pass >> attempts;
        }

        return true;
    }
    return false;
}

void Users::updateUserAttempts(const string& username, int newAttempts)
{
    fstream file("users.txt", ios::in | ios::out);
    if (!file)
    {
        cerr << "Error: No se pudo abrir el archivo users.txt" << endl;
        return;
    }

    string line;
    streampos pos = file.tellg();

    while (getline(file, line))
    {
        streampos lineStart = pos;  // inicio de linea
        pos = file.tellg();         // inicio \n

        string decryptedLine = xorCipher(line);
        istringstream iss(decryptedLine);
        string role, user, pass;
        char attemptChar = '0';

        iss >> role;
        if (role == "admin")
        {
            iss >> user >> pass >> attemptChar;
        }
        else
        {
            user = role;
            role = "";
            iss >> pass >> attemptChar;
        }

        if (user == username)
        {
            // Si es > a 3 no incrementa
            int currentAttempts = attemptChar - '0';
            if (currentAttempts >= MAX_ATTEMPTS)
                return;

            int attemptToWrite = newAttempts;
            if (attemptToWrite > MAX_ATTEMPTS) attemptToWrite = MAX_ATTEMPTS;

            // cursor al final de linea '\n'
            file.seekp(lineStart + static_cast<streamoff>(line.length() - 1));
            char encryptedAttempt = xorCipher(string(1, '0' + attemptToWrite))[0];
            file.write(&encryptedAttempt, 1);
            break;
        }
    }

    file.close();
}