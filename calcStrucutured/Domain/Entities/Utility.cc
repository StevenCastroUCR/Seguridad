#include "Utility.h"

#include <iostream>
#include <string.h>



Utility::Utility()
{
}
Utility::~Utility()
{
}

/// @brief Solicita al usuario una entrada por consola con un mensaje de prompt.
///        La funcion valida que solo se haya ingresado una palabra y que no este vacia.
///        En caso de error, registra el evento en un log y solicita la entrada nuevamente.
/// @param prompt Mensaje que se muestra al usuario antes de ingresar el dato.
/// @return La palabra ingresada por el usuario.
string Utility:: readInput(const string &prompt, size_t maxLength)
{
    string input;
    while (true)
    {
        cout << prompt;
        getline(cin, input);

        if (input.length() > maxLength) {
            log("Error: Input exceeds maximum length");
            std::cout << "Error: La entrada excede el limite de " << maxLength << " caracteres. Intente de nuevo.\n";
            continue;
        }

        string sanitizedInput = sanitizeInput(input);
        if (sanitizedInput.empty()) {
            log("Error: Information not entered");
            std::cout << "Error: No ha digitado.\n";
        } else {
            istringstream iss(sanitizedInput);
            string word, leftover;
            iss >> word >> leftover;

            if (!leftover.empty())
            {
                log("Error invalid input");
                cout << "La entrada no es valida intelo de nuevo\n";
            }
            else
            {
                return word;
            }
        }
    }
}

/// @brief Registra un evento en un archivo de log llamado "log.txt".
///        El evento se guarda con una marca de tiempo.
/// @param event Descripcion del evento que se desea registrar.
void Utility:: log(const string &event)
{

    if (fs::exists(LOG_FILE) && fs::file_size(LOG_FILE) >= MAX_LOG_SIZE)
    {
        if (fs::exists(BACKUP_FILE))
        {
            fs::remove(BACKUP_FILE); 
        }
        fs::rename(LOG_FILE, BACKUP_FILE); 
    }

    ofstream logFile("log.txt", ios::app);
    if (!logFile)
    {
        cerr << "Error al abrir archivo" << endl;
        return;
    }

    time_t now = time(0);
    char *dt = ctime(&now);
    if (dt[strlen(dt) - 1] == '\n')
    {
        dt[strlen(dt) - 1] = '\0';
    }

    logFile << "[" << dt << "] " << event << endl;
}


string Utility::sanitizeInput(const std::string &input) {
    std::string sanitized;
    for (char c : input) {
        //  Permite alfanumerico y ciertos simbolos
        if (std::isalnum(c) || c == '_' || c == '-') {
            sanitized += c;
        }
        // TODO: Añadir condiciones
    }
    return sanitized;
}