#include "../include/Menu.hh"
#include "../include/Screen.hh"
#include "../include/ICtrlUsuario.hh"
#include "../include/ICtrlCurso.hh"
#include "../include/Factory.hh"

#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <iostream>
#include <vector>

using namespace std;

Menu::Menu()
{
    this->option = 0;
    this->exit = false;
    this->state = START;
}

void Menu::menuLimits()
{
    setXY(cout, 0, 0);
    for (int i = 0; i <= 57; i++)
    {
        if (i == 0 || i == 57)
            cout << "+";
        else
            cout << "-";
    }
    for (int j = 2; j <= 57; j++)
    {
        for (int i = 0; i <= 58; i++)
            if (i == 0 || i == 58)
            {
                setXY(cout, i, j);
                cout << "|";
            }
        setXY(cout, 0, j);
    }
    setXY(cout, 0, 58);
    for (int i = 0; i <= 57; i++)
    {
        if (i == 0 || i == 57)
            cout << "+";
        else
            cout << "-";
    }
}

void Menu::loadSystem(bool &flag)
{
    vector<vector<string>> languageData;
    vector<vector<string>> userData;
    vector<vector<string>> studentData;
    vector<vector<string>> professorData;
    vector<vector<string>> courseData;
    vector<vector<string>> priorData;
    vector<vector<string>> lessonData;
    vector<vector<string>> exerciseData;
    vector<vector<string>> inscriptionData;
    vector<vector<string>> approvedExerciseData;
    vector<string> fileNames;
    vector<string> row;
    string line, word;

    fileNames.push_back("CVSs/Idiomas.csv");
    fileNames.push_back("CVSs/Usuarios.csv");
    fileNames.push_back("CVSs/Usuarios-Estudiantes.csv");
    fileNames.push_back("CVSs/Usuarios-Profesores.csv");
    fileNames.push_back("CVSs/Cursos.csv");
    fileNames.push_back("CVSs/Cursos-Previos.csv");
    fileNames.push_back("CVSs/Cursos-Lecciones.csv");
    fileNames.push_back("CVSs/Cursos-Lecciones-Ejercicios.csv");
    fileNames.push_back("CVSs/Inscripciones.csv");
    fileNames.push_back("CVSs/Inscripciones-EjerciciosAprobados.csv");

    for (unsigned int i = 0; i < fileNames.size(); i++)
    {
        fstream file(fileNames[i], ios::in);
        if (!flag)
            break;
        if (file.is_open())
        {
            flag = true;
            while (getline(file, line))
            {
                row.clear();
                stringstream str(line);
                while (getline(str, word, ';'))
                {
                    row.push_back(word);
                }
                switch (i)
                {
                case 0:
                    languageData.push_back(row);
                    break;
                case 1:
                    userData.push_back(row);
                    break;
                case 2:
                    studentData.push_back(row);
                    break;
                case 3:
                    professorData.push_back(row);
                    break;
                case 4:
                    courseData.push_back(row);
                    break;
                case 5:
                    priorData.push_back(row);
                    break;
                case 6:
                    lessonData.push_back(row);
                    break;
                case 7:
                    exerciseData.push_back(row);
                    break;
                case 8:
                    inscriptionData.push_back(row);
                    break;
                case 9:
                    approvedExerciseData.push_back(row);
                    break;
                }
            }
        }
        else
            flag = false;
        file.close();
    }

    if (!flag)
        return;

    Factory *f = Factory::getInstance();
    ICtrlCurso *cc = f->getICtrlCurso();
    ICtrlUsuario *cu = f->getICtrlUsuario();

    unsigned int languageRow = languageData.size();
    unsigned int userRow = userData.size();
    unsigned int studentRow = studentData.size();
    unsigned int professorRow = professorData.size();
    unsigned int courseRow = courseData.size();
    unsigned int priorRow = priorData.size();
    unsigned int lessonRow = lessonData.size();
    unsigned int exerciseRow = exerciseData.size();
    unsigned int inscriptionRow = inscriptionData.size();
    unsigned int approvedRow = approvedExerciseData.size();

    unsigned int languageCol = languageData[0].size();
    unsigned int courseCol = courseData[0].size();
    // unsigned int exerciseCol = exerciseData[0].size();

    for (unsigned int i = 1; i < languageRow; i++)
    {
        cu->altarIdioma(languageData[i][languageCol - 1]);
    }

    for (unsigned int i = 1; i < userRow; i++)
    {
        cu->IngresarDatosUsuario(userData[i][2], userData[i][3], userData[i][4], userData[i][5]);
        if (userData[i][1] == "E")
        {
            for (unsigned int j = 1; j < studentRow; j++)
            {
                if (studentData[j][0] == userData[i][0])
                {
                    cu->altarEstudiante(studentData[j][2], DTDate(studentData[j][1]));
                    break;
                }
            }
        }
        else
        {
            set<string> languages;
            for (unsigned int j = 1; j < professorRow; j++)
            {
                if (professorData[j][0] == userData[i][0])
                {
                    if (professorData[j][2] == "Si" || professorData[j][2] == " Si")
                        languages.insert(languageData[1][1]);
                    if (professorData[j][3] == "Si" || professorData[j][3] == " Si")
                        languages.insert(languageData[2][1]);
                    if (professorData[j][4] == "Si" || professorData[j][4] == " Si")
                        languages.insert(languageData[3][1]);
                    cu->seleccionarIdiomas(languages);
                    cu->altarProfesor(professorData[j][1]);
                    break;
                }
            }
        }
    }

    for (unsigned int i = 1; i < courseRow; i++)
    {
        Dificultad d;
        if (courseData[i][3] == "Avanzado")
            d = avanzado;
        if (courseData[i][3] == "Medio")
            d = medio;
        if (courseData[i][3] == "Principiante")
            d = principiante;
        string aux = courseData[i][4];
        aux = aux.substr(1);
        cc->seleccionarProfesor(userData[stoi(aux)][2]);
        cc->crearCurso(courseData[i][1], courseData[i][2], d);
        aux = courseData[i][5];
        aux = aux.substr(1);
        cc->seleccionarIdioma(languageData[stoi(aux)][1]);
        for (unsigned int j = 1; j < priorRow; j++)
        {
            if (priorData[j][1] == courseData[i][0])
            {
                aux = priorData[j][1];
                aux = aux.substr(1);
                vector<string> previas;
                previas.push_back(courseData[stoi(aux)][1]);
                cc->seleccionarPrevias(previas);
            }
        }
        for (unsigned int j = 1; j < lessonRow; j++)
        {
            if (lessonData[j][1] == courseData[i][0])
            {
                cc->crearLeccion(lessonData[j][2], lessonData[j][3]);
                for (unsigned int k = 1; k < exerciseRow; k++)
                {
                    if (exerciseData[k][1] == lessonData[j][0])
                    {
                        if (exerciseData[k][2] == "T")
                            cc->crearEjercicioTraducir(exerciseData[k][3], exerciseData[k][4], exerciseData[k][5]);
                        else
                        {
                            vector<string> solution;
                            aux = exerciseData[k][5];
                            unsigned int l = 0;
                            while (l < aux.size())
                            {
                                string aux2 = "";
                                while (aux[l] != ',' && l < aux.size())
                                {
                                    aux2 += aux[l];
                                    l++;
                                }
                                solution.push_back(aux2);
                                l += 2;
                            }
                            cc->crearEjercicioCompletar(exerciseData[k][3], exerciseData[k][4], solution);
                        }
                    }
                }
            }
        }
        if (courseData[i][courseCol - 1] == "Si")
            cc->habilitarCurso(courseData[i][1]);
    }

    for (unsigned int i = 1; i < inscriptionRow; i++)
    {
        string studName;
        string courseName;
        for (unsigned int j = 1; j < userRow; j++)
        {
            if (inscriptionData[i][1] == userData[j][0])
            {
                studName = userData[j][2];
                break;
            }
        }
        for (unsigned int j = 1; j < courseRow; j++)
        {
            if (inscriptionData[i][2] == courseData[j][0])
            {
                courseName = courseData[j][1];
                break;
            }
        }
        cc->listarCursosParaEstudiante(studName);
        cc->inscribirACurso(courseName, DTDate(inscriptionData[i][3]));
    }

    for (unsigned int i = 1; i < approvedRow; i++)
    {
        string studName;
        string courseName;
        string exName;
        string solution;
        string exID;
        for (unsigned int j = 1; j < inscriptionRow; j++)
        {
            if (approvedExerciseData[i][0] == inscriptionData[j][0])
            {
                for (unsigned int k = 1; k < userRow; k++)
                {
                    if (inscriptionData[j][1] == userData[k][0])
                    {
                        studName = userData[k][2];
                        break;
                    }
                }
                for (unsigned int k = 1; k < courseRow; k++)
                {
                    if (inscriptionData[j][2] == courseData[k][0])
                    {
                        courseName = courseData[k][1];
                        break;
                    }
                }
                break;
            }
        }
        for (unsigned int j = 1; j < exerciseRow; j++)
        {
            if (approvedExerciseData[i][1] == exerciseData[j][0])
            {
                exName = exerciseData[j][3];
                solution = exerciseData[j][5];
                break;
            }
        }
        for (unsigned int j = 1; j < exerciseRow; j++)
        {
            if (approvedExerciseData[i][1] == exerciseData[j][0])
            {
                if (exerciseData[j][2] == "R")
                {
                    for (unsigned int k = 0; k < solution.size(); k++)
                    {
                        if (solution[k] == ' ')
                        {
                            solution.erase(k, 1);
                            k--;
                        }
                    }
                    break;
                }
            }
        }
        /*
        for(unsigned int j = 0; j < solution.size(); j++){
            if(solution[j] == ' '){
                solution.erase(j,2);
                j--;
            }
        }*/
        cu->listarCursosNoAprobados(studName);
        cu->listarEjerciciosPendientes(courseName);
        cu->elegirEjercicio(exName);
        cu->resolverProblema(solution);
    }
}

void Menu::startMenu()
{
    clearScreen();
    setXY(cout, 24, 15);
    cout << "LABORATORIO 4";
    setXY(cout, 26, 17);
    cout << "GRUPO 64";
    setXY(cout, 15, 25);
    cout << "Ignacio Gonzalez : 53822718";
    setXY(cout, 15, 26);
    cout << "Dumas Bentancur : 51055288";
    setXY(cout, 15, 27);
    cout << "Matteo Cardozo : 54772433";
    setXY(cout, 15, 28);
    cout << "Miguel Barboza : 42313287";
    setXY(cout, 15, 29);
    cout << "Sergio Bengochea : 30012550";
    setXY(cout, 10, 35);
    cout << "Presione Enter para desplegar el menu...";
    this->menuLimits();
    setXY(cout, 50, 35);
    getchar();
    this->state = LOAD;
}

void Menu::showMenu()
{
    this->executeOption();
    while (!this->exit)
    {
        this->executeOption();
    }
}

void Menu::selectOption()
{
    setXY(cout, 19, 36);
    cin >> this->option;

    while (this->option < 1 || this->option > 17)
    {
        setXY(cout, 19, 36);
        cout << "                              ";
        setXY(cout, 19, 36);
        cin >> this->option;
    }
    if (this->option == 17)
    {
        this->exit = true;
        clearScreen();
    }
    this->option += 2;
    this->state = (State)this->option;
}

void Menu::executeOption()
{
    switch (this->state)
    {
    case START:
        this->startMenu();
        break;
    case LOAD:
        this->loader();
        break;
    case STATE0:
        this->showOptions();
        break;
    case OP1:
        this->AltaUsuario();
        break;
    case OP2:
        this->ConsultaUsuario();
        break;
    case OP3:
        this->AltaIdioma();
        break;
    case OP4:
        this->ConsultarIdiomas();
        break;
    case OP5:
        this->AltaCurso();
        break;
    case OP6:
        this->AgregarLeccion();
        break;
    case OP7:
        this->AgregarEjercicio();
        break;
    case OP8:
        this->HabilitarCurso();
        break;
    case OP9:
        this->EliminarCurso();
        break;
    case OP10:
        this->ConsultarCurso();
        break;
    case OP11:
        this->InscribirseACurso();
        break;
    case OP12:
        this->RealizarEjercicio();
        break;
    case OP13:
        this->ConsultarEstadisticas();
        break;
    case OP14:
        this->SuscribirseANotificaciones();
        break;
    case OP15:
        this->ConsultaNotificaciones();
        break;
    case OP16:
        this->EliminarSuscripciones();
        break;
    }
}

void Menu::showOptions()
{
    clearScreen();
    setXY(cout, 11, 10);
    cout << "Seleccione el caso de uso a probar:";
    setXY(cout, 15, 15);
    cout << "1. Alta de Usuario";
    setXY(cout, 15, 16);
    cout << "2. Consulta de Usuario";
    setXY(cout, 15, 17);
    cout << "3. Alta Idioma";
    setXY(cout, 15, 18);
    cout << "4. Consultar Idiomas";
    setXY(cout, 15, 19);
    cout << "5. Alta de Curso";
    setXY(cout, 15, 20);
    cout << "6. Agregar Leccion";
    setXY(cout, 15, 21);
    cout << "7. Agregar Ejercicio";
    setXY(cout, 15, 22);
    cout << "8. Habilitar Curso";
    setXY(cout, 15, 23);
    cout << "9. Eliminar Curso";
    setXY(cout, 15, 24);
    cout << "10. Consultar Curso";
    setXY(cout, 15, 25);
    cout << "11. Inscribirse a Curso";
    setXY(cout, 15, 26);
    cout << "12. Realizar Ejercicio";
    setXY(cout, 15, 27);
    cout << "13. Consultar Estadisticas";
    setXY(cout, 15, 28);
    cout << "14. Suscribirse a Notificaciones";
    setXY(cout, 15, 29);
    cout << "15. Consulta de Notificaciones";
    setXY(cout, 15, 30);
    cout << "16. Eliminar Suscripciones";
    setXY(cout, 15, 31);
    cout << "17. Salir";
    this->menuLimits();
    setXY(cout, 11, 36);
    cout << "Opcion: ";
    this->selectOption();
}

void Menu::loader()
{
    bool flag = true;
    int opt = 0;
    clearScreen();
    setXY(cout, 11, 20);
    cout << "Desea comenzar con datos precargados?";
    setXY(cout, 15, 25);
    cout << "1. Si";
    setXY(cout, 15, 26);
    cout << "2. No";
    setXY(cout, 11, 31);
    cout << "Opcion: ";
    this->menuLimits();
    while (opt != 1 && opt != 2)
    {
        setXY(cout, 19, 31);
        cout << "               ";
        setXY(cout, 19, 31);
        cin >> opt;
    }
    if (opt == 1)
    {
        this->loadSystem(flag);
        if (!flag)
        {
            clearScreen();
            setXY(cout, 11, 20);
            cout << "Error al cargar los datos";
            setXY(cout, 11, 25);
            cout << "Presione Enter para continuar...";
        }
        else
        {
            clearScreen();
            setXY(cout, 11, 20);
            cout << "Datos cargados correctamente";
            setXY(cout, 11, 25);
            cout << "Presione Enter para continuar...";
        }
        this->menuLimits();
        setXY(cout, 43, 25);
        getchar();
        getchar();
    }
    this->state = STATE0;
}

void Menu::AltaUsuario()
{
    // instanciar Factory
    Factory *fac = Factory::getInstance();
    ICtrlUsuario *cu = fac->getICtrlUsuario();

    // variables
    string nickname;
    string password;
    string nombre;
    string descripcion;
    set<string> nicknames;
    int tipo;

    // pedir en pantalla los datos del usuario
    // nickname
    clearScreen();
    cout << "Ingrese el nickname del usuario: " << endl;
    cin >> nickname;
    if (cin.peek() != EOF)
    {
        cin.ignore(256, '\n');
    }
    nicknames = cu->listarUsuarios();
    while (nicknames.find(nickname) != nicknames.end())
    {
        clearScreen();
        cout << "El nickname ya existe. Ingrese uno nuevo: " << endl;
        cin >> nickname;
        if (cin.peek() != EOF)
        {
            cin.ignore(256, '\n');
        }
    }

    // password
    clearScreen();
    cout << "Ingrese una contrasena de al menos 6 caracteres: " << endl;
    cin >> password;
    if (cin.peek() != EOF)
    {
        cin.ignore(256, '\n');
    }
    while (password.length() < 6)
    {
        clearScreen();
        cout << "La contrasena debe tener al menos 6 caracteres. Ingrese una nueva: " << endl;
        cin >> password;
        if (cin.peek() != EOF)
        {
            cin.ignore(256, '\n');
        }
    }

    // nombre
    clearScreen();
    // cin.ignore(256, '\n');
    cout << "Ingrese el nombre del usuario: " << endl;
    getline(cin, nombre);

    // descripcion
    clearScreen();
    // cin.ignore(256, '\n');
    cout << "Ingrese la descripcion: " << endl;
    getline(cin, descripcion);

    // creo usuario
    cu->IngresarDatosUsuario(nickname, password, nombre, descripcion);

    // tipo
    clearScreen();
    cout << "Seleccione el tipo de usuario:" << endl;
    cout << "1- Estudiante" << endl;
    cout << "2- Profesor" << endl;
    cin >> tipo;
    if (cin.peek() != EOF)
    {
        cin.ignore(256, '\n');
    }
    while (tipo != 1 && tipo != 2)
    {
        clearScreen();
        cout << "Opcion invalida. Debe seleccionar 1-Estudiante o 2-Profesor: ";
        cin >> tipo;
        if (cin.peek() != EOF)
        {
            cin.ignore(256, '\n');
        }
    }

    // alta de usuario
    if (tipo == 1)
    {
        // variables
        string pais;
        string date;

        // pais
        clearScreen();
        // cin.ignore(256, '\n');
        cout << "Ingrese el Pais de residencia: " << endl;
        getline(cin, pais);

        // fecha de nacimiento
        clearScreen();
        cout << "Ingrese la fecha de nacimiento con el formato dd/mm/aaaa: ";
        cin >> date;
        if (cin.peek() != EOF)
        {
            cin.ignore(256, '\n');
        }

        // alta de estudiante
        cu->altarEstudiante(pais, DTDate(date));
        cout << "El usuario fue creado correctamente. Presione Enter para continuar...";
        getchar();
    }
    else
    {
        // variables
        string instituto;
        set<string> idiomas;
        set<string> idiomasHablados;
        string aux;
        string lang;

        // instituto
        clearScreen();
        // cin.ignore(256, '\n');
        cout << "Ingrese el instituto donde trabaja: ";
        getline(cin, instituto);

        // idiomas
        clearScreen();
        idiomas = cu->listarIdiomas();
        if (idiomas.size() > 0)
        {
            cout << "Seleccione los idiomas que habla el profesor: ";
            for (set<string>::iterator it = idiomas.begin(); it != idiomas.end(); ++it)
            {
                cout << endl
                     << *it;
            }

            // idiomas hablados
            cout << endl;
            cout << "Ingrese los idiomas separados por ',' y un '.' para finalizar: (Ejemplo: Ingles,Frances.)" << endl;
            // cin.ignore(256, '\n');
            getline(cin, aux);

            while (aux == "." || aux == " ")
            {
                cout << endl;
                // cin.ignore(256, '\n');
                cout << "Debe ingresar al menos un idioma..." << endl;
                getline(cin, aux);
            }

            for (unsigned int i = 0; i < aux.length(); i++)
            {
                if (aux[i] != ',' && aux[i] != '.')
                {
                    lang += aux[i];
                }
                else
                {
                    idiomasHablados.insert(lang);
                    lang = "";
                }
            }

            // alta de profesor
            cu->seleccionarIdiomas(idiomasHablados);
            cu->altarProfesor(instituto);

            cout << "El usuario fue creado correctamente. Presione Enter para continuar...";
            getchar();
            // clearScreen();
        }
        else
        {
            cout << "No existen idiomas creados. Presione Enter para continuar..." << endl;
            getchar();
        }
    }
    this->state = STATE0;
}

void Menu::ConsultaUsuario()
{
    // instanciar Factory
    Factory *fac = Factory::getInstance();
    ICtrlUsuario *cu = fac->getICtrlUsuario();

    // variables
    set<string> usuarios;
    set<string>::iterator it;
    string nickname;
    string nombre;
    string descripcion;
    DTUsuario *usuario = NULL;

    // listar los usuarios
    clearScreen();
    cout << "Los usuarios disponibles para consultar son los siguientes...";
    usuarios = cu->listarUsuarios();
    for (it = usuarios.begin(); it != usuarios.end(); ++it)
    {
        cout << endl
             << *it;
    }

    // elegir usuario
    cout << endl
         << "Ingrese el nickname del usuario que desea consultar: ";
    cin >> nickname;

    // mostrar datos del usuario
    clearScreen();
    usuario = cu->seleccionarUsuario(nickname);
    nombre = usuario->getNombre();
    descripcion = usuario->getDescripcion();
    cout << "Nombre: " << nombre << endl;
    cout << "Descripcion: " << descripcion << endl;

    // casteo dinamico a profesor
    DTProfesor *profesor = dynamic_cast<DTProfesor *>(usuario);
    if (profesor != NULL)
    {
        string instituto;
        instituto = profesor->getInstituto();
        cout << "Instituto: " << instituto << endl;

        vector<string> idiomas;
        idiomas = profesor->getIdiomas();
        cout << "Idiomas: " << endl;

        vector<string>::iterator it;
        for (it = idiomas.begin(); it != idiomas.end(); ++it)
        {
            cout << *it << endl;
        }
    }
    else
    {
        // casteo dinamico a estudiante
        DTEstudiante *estudiante = dynamic_cast<DTEstudiante *>(usuario);
        if (estudiante != NULL)
        {
            string pais;
            pais = estudiante->getPaisResidencia();
            cout << "Pais: " << pais << endl;

            DTDate fechaDeNacimiento;
            fechaDeNacimiento = estudiante->getFechaNacimiento();
            int dia, mes, anio;
            dia = fechaDeNacimiento.getDay();
            mes = fechaDeNacimiento.getMonth();
            anio = fechaDeNacimiento.getYear();
            cout << "Fecha de nacimiento: " << dia << "/" << mes << "/" << anio << endl;
        }
    }

    cout << "Presione Enter para continuar...";
    getchar();
    getchar();
    this->state = STATE0;
}

void Menu::AltaIdioma()
{
    clearScreen();
    Factory *fac = Factory::getInstance();
    ICtrlUsuario *cu = fac->getICtrlUsuario();

    string nombre;

    cin.ignore(256, '\n');
    cout << "Ingrese el nombre del idioma a crear: " << endl;
    getline(cin, nombre);

    bool creado = cu->altarIdioma(nombre);

    if (creado)
    {
        cout << "El idioma fue creado correctamente. Presione Enter para continuar..." << endl;
    }
    else
    {
        cout << "El idioma ya existe. Presione Enter para continuar..." << endl;
    }
    getchar();
    this->state = STATE0;
}

void Menu::ConsultarIdiomas()
{
    Factory *fac = Factory::getInstance();
    ICtrlUsuario *cu = fac->getICtrlUsuario();

    set<string> idiomas;
    set<string>::iterator it;

    clearScreen();
    idiomas = cu->listarIdiomas();

    if (idiomas.size() > 0)
    {
        cout << "Los idiomas disponibles son los siguientes..." << endl;
        cout << endl;
        for (it = idiomas.begin(); it != idiomas.end(); ++it)
        {
            cout << *it << endl;
        }
    }
    else
    {
        cout << "No existen idiomas creados." << endl;
    }

    cout << endl;
    cout << "Presione Enter para continuar...";
    getchar();
    getchar();
    this->state = STATE0;
}

void Menu::AltaCurso()
{
    Factory *fact = Factory::getInstance();
    ICtrlCurso *iCC = fact->getICtrlCurso();

    vector<string> guardar;
    vector<string> listar;
    vector<int> guardarInt;
    string auxS;
    bool auxB;
    int op;

    listar = iCC->listarProfesores();
    if (listar.size() > 0)
    {
        clearScreen();
        op = 0;
        cout << "Elija un profesor: " << endl;
        for (vector<string>::iterator it = listar.begin(); it != listar.end(); ++it)
        {
            cout << op << "- " << (*it) << endl;
            op++;
        }
        cout << "Opcion: " << endl;
        cin >> op;
        if (cin.peek() != EOF)
        {
            cin.ignore(256, '\n');
        }
        iCC->seleccionarProfesor(listar[op]);
        listar.clear();

        clearScreen();
        cout << "Ingrese el nombre del curso: " << endl;
        // if(cin.peek()!=EOF){cin.ignore(256, '\n');}
        getline(cin, auxS);
        guardar.push_back(auxS);

        clearScreen();
        // cin.ignore(256, '\n');
        cout << "Ingrese la descripcion del curso: " << endl;
        getline(cin, auxS);
        guardar.push_back(auxS);

        clearScreen();
        cout << "Elija una opcion para la dificultad del curso: " << endl;
        cout << "0- Principiante" << endl;
        cout << "1- Intermedio" << endl;
        cout << "2- Dificil" << endl;
        cin >> op;
        if (cin.peek() != EOF)
        {
            cin.ignore(256, '\n');
        }

        clearScreen();
        auxB = iCC->crearCurso(guardar[0], guardar[1], Dificultad(op));
        while (!auxB)
        {
            cout << "El nombre ya esta en uso, elija otro: " << endl;
            // cin.ignore(256, '\n');
            getline(cin, auxS);
            auxB = iCC->crearCurso(auxS, guardar[1], Dificultad(op));
        }
        guardar.clear();

        clearScreen();
        listar = iCC->listarIdiomas();
        if (listar.size() > 0)
        {
            op = 0;
            cout << "Elija un idioma: " << endl;
            for (vector<string>::iterator it = listar.begin(); it != listar.end(); ++it)
            {
                cout << op << "- " << (*it) << endl;
                op++;
            }
            cout << "Opcion: " << endl;
            cin >> op;
            if (cin.peek() != EOF)
            {
                cin.ignore(256, '\n');
            }
            iCC->seleccionarIdioma(listar[op]);
            listar.clear();

            clearScreen();
            listar = iCC->listarCursosHabilitdos();
            vector<string> final;
            if (listar.size() > 0)
            {
                op = 1;
                cout << "Elija una opcion para agregar como previa: " << endl;
                cout << "0- No agregar previas" << endl;
                for (vector<string>::iterator it = listar.begin(); it != listar.end(); ++it)
                {
                    cout << op << "- " << (*it) << endl;
                    op++;
                }
                cout << endl;
                cout << "Opcion: " << endl;
                cin >> op;
                if (cin.peek() != EOF)
                {
                    cin.ignore(256, '\n');
                }
                if (op != 0)
                {
                    final.push_back(listar[op - 1]);
                    listar.erase(listar.begin() + op - 1);
                }
                // cout << listar.size() << endl;

                // cout << listar.size() << endl;
                while (op != 0)
                {
                    clearScreen();
                    cout << "Elija una opcion para agregar otra previa: " << endl;
                    op = 1;
                    cout << "0- No agregar mas previas" << endl;
                    for (vector<string>::iterator it = listar.begin(); it != listar.end(); ++it)
                    {
                        cout << op << "- " << (*it) << endl;
                        op++;
                    }
                    // imprime final;
                    /*int finalImp = 1;
                    for (vector<string>::iterator it = final.begin(); it != final.end(); ++it)
                    {
                        cout << finalImp << "- " << (*it) << endl;
                        finalImp++;
                    }*/

                    cout << endl;
                    cout << "Opcion: " << endl;
                    cin >> op;
                    if (cin.peek() != EOF)
                    {
                        cin.ignore(256, '\n');
                    }
                    if (op != 0)
                    {
                        if (listar[op - 1] != "")
                        {
                            final.push_back(listar[op - 1]);
                            // cout << listar.size() << endl;
                            listar.erase(listar.begin() + op - 1);
                            // cout << listar.size() << endl;
                        }
                    }
                }
                cout << "Previas agregadas: " << endl;
                int finalImp = 1;
                for (vector<string>::iterator it = final.begin(); it != final.end(); ++it)
                {
                    cout << finalImp << "- " << (*it) << endl;
                    finalImp++;
                }
                cout << "Presione Enter para continuar...";
                getchar();
                iCC->seleccionarPrevias(final);

                listar.clear();
                guardar.clear();
            }
            else
            {
                clearScreen();
                cout << "No existen cursos habilitados que puedan ser previas. Presione Enter para continuar...";
                getchar();
                this->state = STATE0;
            }

            clearScreen();
            cout << "0- Agregar leccion" << endl;
            cout << "1- No agregar lecciones" << endl;
            cout << endl;
            cout << "Opcion: ";
            cin >> op;
            if (cin.peek() != EOF)
            {
                cin.ignore(256, '\n');
            }
            while (op != 1)
            {
                clearScreen();
                // cin.ignore(256, '\n');
                cout << "Ingrese un tema para la leccion: " << endl;
                getline(cin, auxS);
                guardar.push_back(auxS);

                clearScreen();
                // cin.ignore(256, '\n');
                cout << "Ingrese un objetivo para la leccion: " << endl;
                getline(cin, auxS);
                guardar.push_back(auxS);

                iCC->crearLeccion(guardar[0], guardar[1]);
                guardar.clear();

                clearScreen();
                cout << "0- Agregar ejercicio a la leccion" << endl;
                cout << "1- No agregar ejercicio a la leccion" << endl;
                cout << endl;
                cout << "Opcion: ";
                cin >> op;
                if (cin.peek() != EOF)
                {
                    cin.ignore(256, '\n');
                }
                while (op != 1)
                {
                    clearScreen();
                    // cin.ignore(256, '\n');
                    cout << "Ingrese una descripcion para el ejercicio: " << endl;
                    getline(cin, auxS);
                    guardar.push_back(auxS);

                    clearScreen();
                    cout << "0- Agregar ejercicio de completar palabras" << endl;
                    cout << "1- Agregar ejercicio de traducir frase" << endl;
                    cout << "Opcion: ";
                    cin >> op;
                    if (cin.peek() != EOF)
                    {
                        cin.ignore(256, '\n');
                    }

                    if (op == 0)
                    {
                        clearScreen();
                        // cin.ignore(256, '\n');
                        cout << "Ingrese la frase a completar reemplazando las palabras a completar por tres guiones (\"---\"): " << endl;
                        getline(cin, auxS);
                        guardar.push_back(auxS);

                        clearScreen();
                        // cin.ignore(256, '\n');
                        cout << "Ingrese las palabras a completar todas seguidas separadas por una coma y sin espacios: " << endl;
                        getline(cin, auxS);
                        guardar.push_back(auxS);

                        string elem;
                        for (unsigned int i = 0; i < guardar[2].size(); ++i)
                        {
                            if (guardar[2][i] != ',')
                            {
                                elem += guardar[2][i];
                            }
                            else
                            {
                                listar.push_back(elem);
                                elem.clear();
                            }

                            if (i + 1 == guardar[2].size())
                            {
                                listar.push_back(elem);
                                elem.clear();
                            }
                        }

                        iCC->crearEjercicioCompletar(guardar[0], guardar[1], listar);
                        guardar.clear();
                        listar.clear();
                    }
                    else
                    {
                        clearScreen();
                        // cin.ignore(256, '\n');
                        cout << "Ingrese la frase a traducir: " << endl;
                        getline(cin, auxS);
                        guardar.push_back(auxS);

                        clearScreen();
                        // cin.ignore(256, '\n');
                        cout << "Ingrese las frase traducida: " << endl;
                        getline(cin, auxS);
                        guardar.push_back(auxS);

                        iCC->crearEjercicioTraducir(guardar[0], guardar[1], guardar[2]);
                        guardar.clear();
                    }

                    clearScreen();
                    cout << "0- Agregar otro ejercicio" << endl;
                    cout << "1- No agregar mas ejercicios" << endl;
                    cout << "Opcion: ";
                    cin >> op;
                    if (cin.peek() != EOF)
                    {
                        cin.ignore(256, '\n');
                    }
                }

                clearScreen();
                cout << "0- Agregar otra leccion" << endl;
                cout << "1- No agregar mas lecciones" << endl;
                cout << "Opcion: ";
                cin >> op;
                if (cin.peek() != EOF)
                {
                    cin.ignore(256, '\n');
                }
            }

            clearScreen();
            cout << "El curso fue creado correctamente. Presione Enter para continuar...";
            getchar();
            this->state = STATE0;
        }
        else
        {
            clearScreen();
            cout << "El profesores no conoce ningun idioma. Presione Enter para continuar...";
            getchar();
            this->state = STATE0;
        }
    }
    else
    {
        clearScreen();
        cout << "No existen profesores que puedan crear el curso. Presione Enter para continuar...";
        getchar();
        this->state = STATE0;
    }
}

void Menu::AgregarLeccion()
{
    Factory *Fac = Factory::getInstance();
    ICtrlCurso *ICC = Fac->getICtrlCurso();

    clearScreen();
    vector<string> cursos = ICC->listarCursosNoHabilitados();
    cout << "Los cursos disponibles para agregar lecciones son los siguientes: " << endl;
    cout << endl;
    int i = 0;
    for (vector<string>::iterator it = cursos.begin(); it != cursos.end(); ++it)
    {
        cout << i << ". " << *it << endl;
        i++;
    }
    cout << endl;
    cout << "Ingrese el numero del curso al que desea agregar una leccion: " << endl;
    int cursoAgregar;
    cin >> cursoAgregar;
    if (cin.peek() != EOF)
    {
        cin.ignore(256, '\n');
    }
    ICC->seleccionarCurso(cursos[cursoAgregar]);

    clearScreen();
    cout << "Ingrese el nombre de la leccion: " << endl;
    // cin.ignore(256, '\n');
    string nombreLeccion;
    getline(cin, nombreLeccion);

    clearScreen();
    cout << "Ingrese el objetivo de la leccion: " << endl;
    // cin.ignore(256, '\n');
    string objetivo;
    getline(cin, objetivo);

    ICC->crearLeccion(nombreLeccion, objetivo);

    clearScreen();
    cout << "La leccion fue creada correctamente. Si desea agregar un ejercicio, ingrese la letra 's'. De lo contrario, ingrese cualquier otra letra: " << endl;
    char opcion;
    cin >> opcion;
    if (cin.peek() != EOF)
    {
        cin.ignore(256, '\n');
    }

    while (opcion == 'S' || opcion == 's')
    {
        clearScreen();
        cout << "Ingrese el tipo de ejercicio que desea agregar: " << endl;
        cout << "1. Ejercicio de Completar" << endl;
        cout << "2. Ejercicio de Traducir" << endl;
        int tipoEjercicio;
        cin >> tipoEjercicio;
        if (cin.peek() != EOF)
        {
            cin.ignore(256, '\n');
        }
        if (tipoEjercicio == 1)
        {
            clearScreen();
            cout << "Ingrese la descripcion del ejercicio: " << endl;
            // cin.ignore(256, '\n');
            string descripcion;
            getline(cin, descripcion);

            clearScreen();
            cout << "Ingrese la oracion a completar: (las palabras a completar deben estar resaltadas con tres guiones) " << endl;
            // cin.ignore(256, '\n');
            string oracion;
            getline(cin, oracion);

            clearScreen();
            cout << "Ingrese las palabras a completar separadas por coma: " << endl;
            // cin.ignore(256, '\n');
            string solucion;
            getline(cin, solucion);

            vector<string> sol;
            string elem;
            for (unsigned int i = 0; i < solucion.size(); ++i)
            {
                if (solucion[i] != ',')
                {
                    elem += solucion[i];
                }
                else
                {
                    sol.push_back(elem);
                    elem.clear();
                }

                if (i + 1 == solucion.size())
                {
                    sol.push_back(elem);
                    elem.clear();
                }
            }

            ICC->crearEjercicioCompletar(descripcion, oracion, sol);
        }
        else
        {
            clearScreen();
            cout << "Ingrese la descripcion del ejercicio: " << endl;
            // cin.ignore(256, '\n');
            string descripcion;
            getline(cin, descripcion);

            clearScreen();
            cout << "Ingrese la oracion a traducir: " << endl;
            // cin.ignore(256, '\n');
            string oracion;
            getline(cin, oracion);

            clearScreen();
            cout << "Ingrese la traduccion de la oracion: " << endl;
            // cin.ignore(256, '\n');
            string traduccion;
            getline(cin, traduccion);

            ICC->crearEjercicioTraducir(descripcion, oracion, traduccion);
        }

        clearScreen();
        cout << "El ejercicio fue creado correctamente. Si desea agregar otro ejercicio, ingrese la letra  's'. De lo contrario, ingrese cualquier otra letra: " << endl;
        cin >> opcion;
        if (cin.peek() != EOF)
        {
            cin.ignore(256, '\n');
        }
    }

    clearScreen();
    cout << "La leccion fue creada correctamente. Presione Enter para continuar..." << endl;
    getchar();

    /* manera alternativa
    if (opcion == 'S')
    {
        cout << "Ingrese el tipo de ejercicio que desea agregar: " << endl;
        cout << "1. Ejercicio de Completar" << endl;
        cout << "2. Ejercicio de Traducir" << endl;
        int tipoEjercicio;
        cin >> tipoEjercicio;
        if (tipoEjercicio == 1)
        {

            cout << "Ingrese la descripcion del ejercicio: " << endl;
            cin.ignore(256, '\n');
            string descripcion;
            getline(cin, descripcion);

            cout << "Ingrese la oracion a completar: (las palabras a completar deben estar resaltadas con tres guiones) " << endl;
            cin.ignore(256, '\n');
            string oracion;
            getline(cin, oracion);

            cout << "Ingrese las palabras a completar separadas por coma: " << endl;
            cin.ignore(256, '\n');
            string solucion;
            getline(cin, solucion);

            vector<string> sol;
            string elem;
            for (unsigned int i = 0; i < solucion.size(); ++i)
            {
                if (solucion[i] != ',')
                {
                    elem += solucion[i];
                }
                else
                {
                    sol.push_back(elem);
                    elem.clear();
                }

                if (i + 1 == solucion.size())
                {
                    sol.push_back(elem);
                    elem.clear();
                }
            }

            ICC->crearEjercicioCompletar(descripcion, oracion, sol);

            cout << "El ejercicio fue creado correctamente. Presione Enter para continuar..." << endl;
            getchar();getchar();
        }
        else
        {
            cout << "Ingrese la descripcion del ejercicio: " << endl;
            cin.ignore(256, '\n');
            string descripcion;
            getline(cin, descripcion);

            cout << "Ingrese la oracion a traducir: " << endl;
            cin.ignore(256, '\n');
            string oracion;
            getline(cin, oracion);

            cout << "Ingrese la traduccion de la oracion: " << endl;
            cin.ignore(256, '\n');
            string traduccion;
            getline(cin, traduccion);

            ICC->crearEjercicioTraducir(descripcion, oracion, traduccion);

            cout << "El ejercicio fue creado correctamente. Presione Enter para continuar..." << endl;
            getchar();getchar();
        }
    }
    else
    {
        cout << "La leccion fue creada correctamente. Presione Enter para continuar..." << endl;
        getchar();getchar();
    }*/

    this->state = STATE0;
}

void Menu::AgregarEjercicio()
{
    // instanciar el controlador de curso
    Factory *Fac = Factory::getInstance();
    ICtrlCurso *ICC = Fac->getICtrlCurso();

    vector<string> cursos = ICC->listarCursosNoHabilitados();
    vector<string>::iterator it;

    clearScreen();
    cout << "Los cursos disponibles para agregar ejercicios son los siguientes: " << endl;
    cout << endl;
    for (it = cursos.begin(); it != cursos.end(); ++it)
    {
        cout << *it << endl;
    }
    cout << endl;
    cout << "Ingrese el nombre del curso al que desea agregar un ejercicio: " << endl;
    // cin.ignore(256, '\n');
    if (cin.peek() != EOF)
    {
        cin.ignore(256, '\n');
    }
    string cursoAgregar;
    getline(cin, cursoAgregar);

    vector<string> lecciones = ICC->listarLeccionesCurso(cursoAgregar);
    clearScreen();
    if (lecciones.size() == 0)
    {
        cout << "No existen lecciones en el curso seleccionado. Presione Enter para continuar..." << endl;
        getchar();
        this->state = STATE0;
    }
    else
    {
        cout << "Las lecciones disponibles para agregar ejercicios son las siguientes: " << endl;
        int i = 0;
        cout << endl;
        for (it = lecciones.begin(); it != lecciones.end(); ++it)
        {
            cout << "Leccion " << i << ". " << *it << endl;
            i++;
        }
        cout << endl;
        cout << "Ingrese el numero de la leccion a la que desea agregar un ejercicio: " << endl;
        unsigned int leccionAgregar;
        cin >> leccionAgregar;
        if (cin.peek() != EOF)
        {
            cin.ignore(256, '\n');
        }

        while (leccionAgregar < 0 || leccionAgregar > lecciones.size() - 1)
        {
            cout << "Ingrese una opcion valida: " << endl;
            cin >> leccionAgregar;
            if (cin.peek() != EOF)
            {
                cin.ignore(256, '\n');
            }
        }

        ICC->seleccionarLeccion(leccionAgregar);

        clearScreen();
        cout << "Ingrese el tipo de ejercicio que desea agregar: " << endl;
        cout << "1. Ejercicio de Completar" << endl;
        cout << "2. Ejercicio de Traducir" << endl;
        int tipoEjercicio;
        cin >> tipoEjercicio;
        if (cin.peek() != EOF)
        {
            cin.ignore(256, '\n');
        }

        while (tipoEjercicio != 1 && tipoEjercicio != 2)
        {
            cout << "Ingrese una opcion valida: " << endl;
            cin >> tipoEjercicio;
            if (cin.peek() != EOF)
            {
                cin.ignore(256, '\n');
            }
        }

        if (tipoEjercicio == 1)
        {
            clearScreen();
            cout << "Ingrese la descripcion del ejercicio: " << endl;
            // cin.ignore(256, '\n');
            string descripcion;
            getline(cin, descripcion);

            clearScreen();
            cout << "Ingrese la oracion a completar: (las palabras a completar deben estar resaltadas con tres guiones) " << endl;
            // cin.ignore(256, '\n');
            string oracion;
            getline(cin, oracion);

            clearScreen();
            cout << "Ingrese las palabras a completar separadas por coma: " << endl;
            // cin.ignore(256, '\n');
            string solucion;
            getline(cin, solucion);

            vector<string> sol;
            string elem;
            for (unsigned int i = 0; i < solucion.size(); ++i)
            {
                if (solucion[i] != ',')
                {
                    elem += solucion[i];
                }
                else
                {
                    sol.push_back(elem);
                    elem.clear();
                }

                if (i + 1 == solucion.size())
                {
                    sol.push_back(elem);
                    elem.clear();
                }
            }
            ICC->crearEjercicioCompletar(descripcion, oracion, sol);
        }
        else
        {
            clearScreen();
            cout << "Ingrese la descripcion del ejercicio: " << endl;
            // cin.ignore(256, '\n');
            string descripcion;
            getline(cin, descripcion);

            clearScreen();
            cout << "Ingrese la oracion a traducir: " << endl;
            // cin.ignore(256, '\n');
            string oracion;
            getline(cin, oracion);

            clearScreen();
            cout << "Ingrese la traduccion de la oracion: " << endl;
            // cin.ignore(256, '\n');
            string traduccion;
            getline(cin, traduccion);

            ICC->crearEjercicioTraducir(descripcion, oracion, traduccion);
        }

        clearScreen();
        cout << "El ejercicio fue creado correctamente. Presione Enter para continuar..." << endl;
        getchar();
        this->state = STATE0;
    }
}

void Menu::HabilitarCurso()
{
    Factory *fact = Factory::getInstance();
    ICtrlCurso *iCC = fact->getICtrlCurso();

    vector<string> listar;
    bool auxB;
    int op;

    listar = iCC->listarCursosNoHabilitados();
    if (listar.size() > 0)
    {
        clearScreen();
        op = 0;
        for (vector<string>::iterator it = listar.begin(); it != listar.end(); ++it)
        {
            cout << op << "- " << (*it) << endl;
            op++;
        }
        cout << "Opcion: " << endl;
        cin >> op;
        auxB = iCC->habilitarCurso(listar[op]);
        listar.clear();

        if (auxB)
        {
            clearScreen();
            cout << "El curso fue habilitado. Presione Enter para continuar...";
            getchar();
            getchar();
            this->state = STATE0;
        }
        else
        {
            clearScreen();
            cout << "El curso no cumple los requisitos para ser habilitado (debe tener al menos una leccion y todas ellas deben tener al menos un ejercicio). Presione Enter para continuar...";
            getchar();
            getchar();
            this->state = STATE0;
        }
    }
    else
    {
        clearScreen();
        cout << "No existen cursos deshabilitados. Presione Enter para continuar...";
        getchar();
        getchar();
        this->state = STATE0;
    }
}

void Menu::EliminarCurso()
{
    clearScreen();
    Factory *fact = Factory::getInstance();
    ICtrlCurso *iCC = fact->getICtrlCurso();

    vector<string> listar;
    string CursoAEliminar;

    listar = iCC->listarCursos();
    if (listar.size() > 0)
    {
        clearScreen();

        int i = 1;
        for (vector<string>::iterator it = listar.begin(); it != listar.end(); ++it)
        {
            cout << i << "- " << (*it) << endl;
            ++i;
        }
        cout << "Ingrese el curso a eliminar: " << endl;
        cin >> i;
        CursoAEliminar = listar[i - 1];
        iCC->deleteCourse(CursoAEliminar);
        clearScreen();
        cout << "El curso fue eliminado. Presione Enter para continuar...";
        getchar();
        getchar();
        this->state = STATE0;
    }
    else
    {
        clearScreen();
        cout << "No existen cursos para eliminar. Presione Enter para continuar...";
        getchar();
        this->state = STATE0;
    }
}

void Menu::ConsultarCurso()
{
    Factory *fact = Factory::getInstance();
    ICtrlCurso *iCC = fact->getICtrlCurso();

    vector<string> listar;
    unsigned int op;

    listar = iCC->listarCursos();

    if (listar.size() > 0)
    {
        clearScreen();
        op = 0;
        for (vector<string>::iterator it = listar.begin(); it != listar.end(); ++it)
        {
            cout << op << "- " << (*it) << endl;
            op++;
        }
        cout << "Opcion: " << endl;
        cin >> op;
        // cout << "llegue" << endl;
        while (op < 0 || op > listar.size() - 1)
        {
            cout << "Opcion incorrecta. Ingrese una opcion valida: " << endl;
            cin >> op;
        }
        cout << "llegue2" << listar[op] << endl;
        DTInfoCurso *info = iCC->consultarCurso(listar[op]);
        cout << "llegue3" << endl;

        listar.clear();
        if (info != NULL)
        {
            clearScreen();
            info->showInfoCurso();
            delete info;
            cout << endl;
            cout << "Presione Enter para continuar...";
            getchar();
            getchar();
            this->state = STATE0;
        }
        else
        {
            clearScreen();
            cout << "No existe el cursos. Presione Enter para continuar...";
            getchar();
            getchar();
            this->state = STATE0;
        }
    }
    else
    {
        clearScreen();
        cout << "No existen cursos. Presione Enter para continuar...";
        getchar();
        this->state = STATE0;
    }
}

void Menu::InscribirseACurso()
{
    clearScreen();
    Factory *fact = Factory::getInstance();
    ICtrlCurso *ICC = fact->getICtrlCurso();

    cout << "Ingrese el nickname del Estudiante: " << endl;
    string nickname;
    cin >> nickname;
    if (cin.peek() != EOF)
    {
        cin.ignore(256, '\n');
    }

    clearScreen();
    cout << "Los cursos disponibles son: " << endl;
    cout << endl;
    vector<DTInfoCursoIns> cursos = ICC->listarCursosParaEstudiante(nickname);
    // listar cursos y mostrarlos
    int i = 1;
    if (cursos.size() > 0)
    {
        for (vector<DTInfoCursoIns>::iterator it = cursos.begin(); it != cursos.end(); ++it)
        {
            Dificultad dif = it->getDifficulty();
            string dificultad;
            switch (dif)
            {
            case 0:
                dificultad = "Principiante";
                break;
            case 1:
                dificultad = "Medio";
                break;
            case 2:
                dificultad = "Avanzado";
                break;
            }
            cout << endl;
            cout << "Curso numero " << i << ": " << endl;
            i++;
            cout << "Nombre: " << it->getName() << endl;
            cout << "Descripcion: " << it->getDescription() << endl;
            cout << "Dificultad " << dificultad << endl;
            cout << "Cantidad de lecciones: " << it->getCantLecciones() << endl;
            cout << "Cantidad de Ejercicios: " << it->getCantEjerciciosTotal() << endl;
        }
        cout << endl;

        cout << "Ingrese el numero del curso al que desea inscribirse: " << endl;
        int indice;
        cin >> indice;
        if (cin.peek() != EOF)
        {
            cin.ignore(256, '\n');
        }

        clearScreen();
        cout << "Ingrese la fecha de inscripcion: dd/mm/aaaa: " << endl;
        string fecha;
        cin >> fecha;
        if (cin.peek() != EOF)
        {
            cin.ignore(256, '\n');
        }

        ICC->inscribirACurso(cursos[indice - 1].getName(), DTDate(fecha));

        clearScreen();
        cout << "El estudiante fue inscripto correctamente. Presione Enter para continuar...";
        getchar();
        this->state = STATE0;
    }
    else
    {
        clearScreen();
        cout << "No existen cursos disponibles para inscribirse. Presione Enter para continuar...";
        getchar();
        this->state = STATE0;
    }
}

void Menu::RealizarEjercicio()
{
    Factory *fact = Factory::getInstance();
    ICtrlUsuario *iCU = fact->getICtrlUsuario();

    vector<string> listar;
    string auxS;
    int op;

    clearScreen();
    cout << "Ingrese el nick del estudiante: " << endl;
    cin >> auxS;

    listar = iCU->listarCursosNoAprobados(auxS);

    if (listar.size() > 0)
    {
        clearScreen();
        op = 0;
        for (vector<string>::iterator it = listar.begin(); it != listar.end(); ++it)
        {
            cout << op << "- " << (*it) << endl;
            op++;
        }
        cout << "Opcion: " << endl;
        cin >> op;
        auxS = listar[op];
        listar.clear();

        listar = iCU->listarEjerciciosPendientes(auxS);
        if (listar.size() > 0)
        {
            clearScreen();
            op = 0;
            for (vector<string>::iterator it = listar.begin(); it != listar.end(); ++it)
            {
                cout << op << "- " << (*it) << endl;
                op++;
            }
            cout << "Opcion: " << endl;
            cin >> op;

            clearScreen();
            cout << "Ingrese la solucion al siguiente ejercicio: " << endl;
            cout << iCU->elegirEjercicio(listar[op]) << endl;
            listar.clear();
            cout << "Solucion: ";
            cin.ignore(256, '\n');
            getline(cin, auxS);

            clearScreen();
            if (iCU->resolverProblema(auxS))
            {
                cout << "Correcto, ejercicio aprobado. Presione Enter para continuar..." << endl;
            }
            else
            {
                cout << "Incorrecto, ejercicio no aprobado. Presione Enter para continuar..." << endl;
            }
            getchar();
            this->state = STATE0;
        }
        else
        {
            clearScreen();
            cout << "El estudiante no tiene ejercicios pendientes en el curso seleccionado. Presione Enter para continuar...";
            getchar();
            this->state = STATE0;
        }
    }
    else
    {
        clearScreen();
        cout << "El usuario no tiene cursos sin aprobar. Presione Enter para continuar...";
        getchar();
        this->state = STATE0;
    }
}

void Menu::ConsultarEstadisticas()
{
    Factory *fact = Factory::getInstance();
    ICtrlUsuario *iCU = fact->getICtrlUsuario();

    vector<string> listar;
    unsigned int op;

    clearScreen();
    cout << "Elija el tipo de estadistica: " << endl;
    cout << "0- Estadistica de estudiante" << endl;
    cout << "1- Estadistica de profesor" << endl;
    cout << "2- Estadistica de curso" << endl;
    // cout << "3- Estadistica de ejercicio" << endl;
    cout << "Opcion: " << endl;
    cin >> op;
    if (cin.peek() != EOF)
    {
        cin.ignore(256, '\n');
    }
    if (op == 0)
    {
        listar = iCU->listarEstudiantes();

        if (listar.size() > 0)
        {

            clearScreen();
            // cout << "Los estudiantes disponibles son: " << endl;
            op = 0;
            for (vector<string>::iterator it = listar.begin(); it != listar.end(); ++it)
            {
                cout << op << "- " << (*it) << endl;
                op++;
            }
            cout << "Opcion: " << endl;
            cin >> op;
            if (cin.peek() != EOF)
            {
                cin.ignore(256, '\n');
            }
            while (op < 0 || op > listar.size() - 1)
            {
                cout << "Opcion incorrecta. Ingrese una opcion valida: " << endl;
                cin >> op;
                if (cin.peek() != EOF)
                {
                    cin.ignore(256, '\n');
                }
            }

            vector<DTEstadisticaCursoEstudiante> dtEst = iCU->listarEstadisticasE(listar[op]);
            clearScreen();
            cout << "Las estadisticas del estudiante " << listar[op] << " son: " << endl
                 << endl;
            getchar();
            listar.clear();
            for (unsigned int i = 0; i < dtEst.size(); ++i)
            {
                cout << "El progreso del estudiante en el curso: " << dtEst[i].getCourse() << " es: " << dtEst[i].getProgress() << "%" << endl;
            }

            cout << endl;
            cout << "Presione Enter para continuar..." << endl;
            getchar();
            this->state = STATE0;
        }
        else
        {
            clearScreen();
            cout << "No existen estudiantes. Presione Enter para continuar...";
            getchar();
            this->state = STATE0;
        }
    }
    else if (op == 1)
    {
        listar = iCU->listarProfesores();
        if (listar.size() > 0)
        {
            clearScreen();
            op = 0;
            for (vector<string>::iterator it = listar.begin(); it != listar.end(); ++it)
            {
                cout << op << "- " << (*it) << endl;
                op++;
            }
            cout << "Opcion: " << endl;
            cin >> op;
            if (cin.peek() != EOF)
            {
                cin.ignore(256, '\n');
            }
            while (op < 0 || op > listar.size() - 1)
            {
                cout << "Opcion incorrecta. Ingrese una opcion valida: " << endl;
                cin >> op;
                if (cin.peek() != EOF)
                {
                    cin.ignore(256, '\n');
                }
            }
            vector<DTEstadisticaCurso> dtEst = iCU->listarEstadisticasP(listar[op]);

            clearScreen();
            cout << "Las estadisticas del profesor " << listar[op] << " son: " << endl
                 << endl;
            listar.clear();
            for (unsigned int i = 0; i < dtEst.size(); ++i)
            {
                cout << "Nombre del curso: " << dtEst[i].getName() << endl;
                cout << "Descripcion del curso: " << dtEst[i].getDescription() << endl;
                cout << "Idioma del curso: " << dtEst[i].getIdioma() << endl;

                op = dtEst[i].getDifficulty();
                if (op == 0)
                {
                    cout << "Dificultad del curso: Principiante" << endl;
                }
                else if (op == 1)
                {
                    cout << "Dificultad del curso: Media" << endl;
                }
                else if (op == 2)
                {
                    cout << "Dificultad del curso: Avanzado" << endl;
                }
                if (dtEst[i].getProgress() == -1)
                    cout << "Progreso: El curso no esta habilitado. " << endl;
                else if (dtEst[i].getProgress() == -2)
                    cout << "Progreso: El curso no tiene estudiantes inscriptos. " << endl;
                else
                    cout << "Progreso del curso: " << dtEst[i].getProgress() << endl;
                cout << endl;
            }

            cout << endl;
            cout << "Presione Enter para continuar..." << endl;
            getchar();
            this->state = STATE0;
        }
        else
        {
            clearScreen();
            cout << "No existen profesores. Presione Enter para continuar...";
            getchar();
            this->state = STATE0;
        }
    }
    else if (op == 2)
    {
        listar = iCU->listarCursos();
        if (listar.size() > 0)
        {
            clearScreen();
            op = 0;
            for (vector<string>::iterator it = listar.begin(); it != listar.end(); ++it)
            {
                cout << op << "- " << (*it) << endl;
                op++;
            }
            cout << "Opcion: " << endl;
            cin >> op;
            if (cin.peek() != EOF)
            {
                cin.ignore(256, '\n');
            }
            while (op < 0 || op > listar.size())
            {
                cout << "Opcion incorrecta. Ingrese una opcionvalida " << endl;
                cout << "Opcion: " << endl;
                cin >> op;
                if (cin.peek() != EOF)
                {
                    cin.ignore(256, '\n');
                }
            }
            DTEstadisticaCurso dtEst = iCU->listarEstadisticaC(listar[op]);
            listar.clear();

            clearScreen();
            cout << "Nombre del curso: " << dtEst.getName() << endl;
            cout << "Descripcion del curso: " << dtEst.getDescription() << endl;
            cout << "Idioma del curso: " << dtEst.getIdioma() << endl;

            op = dtEst.getDifficulty();
            if (op == 0)
            {
                cout << "Dificultad del curso: Principiante" << endl;
            }
            else if (op == 1)
            {
                cout << "Dificultad del curso: Media" << endl;
            }
            else if (op == 2)
            {
                cout << "Dificultad del curso: Avanzado" << endl;
            }
            if (dtEst.getProgress() == -1)
                cout << "Progreso: El curso no esta habilitado. " << endl;
            else if (dtEst.getProgress() == -2)
                cout << "Progreso: El curso no tiene estudiantes inscriptos. " << endl;
            else
                cout << "Progreso del curso: " << dtEst.getProgress() << endl;
            cout << endl;
            cout << "Presione Enter para continuar..." << endl;
            getchar();
            this->state = STATE0;
        }
        else
        {
            clearScreen();
            cout << "No existen cursos. Presione Enter para continuar..." << endl;
            getchar();
            this->state = STATE0;
        }
    }
    else
    {
        clearScreen();
        cout << "Opcion incorrecta. Presione Enter para continuar..." << endl;
        getchar();
        this->state = STATE0;
    }
}

void Menu::SuscribirseANotificaciones()
{
    Factory *fac = Factory::getInstance();
    ICtrlUsuario *cu = fac->getICtrlUsuario();

    clearScreen();
    string name;
    cout << "Ingrese su nickname: " << endl;
    cin >> name;
    if (cin.peek() != EOF)
    {
        cin.ignore(256, '\n');
    }
    vector<string> idiomas = cu->listarIdiomasNoSuscripto(name);
    if (idiomas.size() > 0)
    {
        clearScreen();
        cout << "Los idiomas disponibles son: " << endl;
        for (unsigned int i = 0; i < idiomas.size(); ++i)
        {
            cout << idiomas[i] << endl;
        }
        cout << endl;
        cout << "Ingrese los nombres de los idiomas a los que desea suscribirse, separados por coma: " << endl;
        string iter;
        cin >> iter;
        if (cin.peek() != EOF)
        {
            cin.ignore(256, '\n');
        }
        vector<string> idiomasSuscribir;
        string elem;
        for (unsigned int i = 0; i < iter.size(); ++i)
        {
            if (iter[i] != ',')
            {
                elem += iter[i];
            }
            else
            {
                idiomasSuscribir.push_back(elem);
                elem.clear();
            }

            if (i + 1 == iter.size())
            {
                idiomasSuscribir.push_back(elem);
                elem.clear();
            }
        }
        cu->suscribirse(idiomasSuscribir);

        clearScreen();
        cout << "El estudiante fue suscripto correctamente. Presione Enter para continuar...";
        getchar();
        this->state = STATE0;
    }
    else
    {
        clearScreen();
        cout << "No existen idiomas disponibles para suscribirse. Presione Enter para continuar...";
        getchar();
        this->state = STATE0;
    }
}

void Menu::ConsultaNotificaciones()
{
    Factory *fac = Factory::getInstance();
    ICtrlUsuario *cu = fac->getICtrlUsuario();

    clearScreen();
    cout << "Ingrese el Nickname de Usuario: ";
    string name;
    cin >> name;
    if (cin.peek() != EOF)
    {
        cin.ignore(256, '\n');
    }
    clearScreen();
    cout << "Las notificaciones del usuario " << name << " son: " << endl;
    vector<DTNotificacion> notificaciones = cu->listarNotificaciones(name);
    for (vector<DTNotificacion>::iterator it = notificaciones.begin(); it != notificaciones.end(); ++it)
    {
        cout << (it)->getNIdioma() << ": El curso " << (it)->getNCurso() << " fue creado." << endl;
    }

    cout << endl;
    cout << "Presione Enter para continuar..." << endl;
    getchar();
    this->state = STATE0;
}

void Menu::EliminarSuscripciones()
{
    Factory *fac = Factory::getInstance();
    ICtrlUsuario *cu = fac->getICtrlUsuario();

    clearScreen();
    string name;
    cout << "Ingrese su nickname: " << endl;
    cin >> name;
    if (cin.peek() != EOF)
    {
        cin.ignore(256, '\n');
    }
    clearScreen();
    vector<string> idiomas = cu->listarIdiomasSuscripto(name);
    cout << "Los idiomas a los que esta suscripto son los siguientes: " << endl;
    for (vector<string>::iterator it = idiomas.begin(); it != idiomas.end(); ++it)
    {
        cout << *it << endl;
    }
    cout << endl;
    cout << "Ingrese los nombres de los idiomas a los que desea desuscribirse, separados por coma: " << endl;
    string iter;
    cin >> iter;
    if (cin.peek() != EOF)
    {
        cin.ignore(256, '\n');
    }
    vector<string> idiomasDesuscribir;
    string elem;
    for (unsigned int i = 0; i < iter.size(); ++i)
    {
        if (iter[i] != ',')
        {
            elem += iter[i];
        }
        else
        {
            idiomasDesuscribir.push_back(elem);
            elem.clear();
        }

        if (i + 1 == iter.size())
        {
            idiomasDesuscribir.push_back(elem);
            elem.clear();
        }
    }
    cu->eliminarSuscripcion(idiomasDesuscribir);

    clearScreen();
    cout << "Las suscripciones fueron eliminadas correctamente. Presione Enter para continuar..." << endl;
    getchar();
    this->state = STATE0;
}

Menu::~Menu() {}
