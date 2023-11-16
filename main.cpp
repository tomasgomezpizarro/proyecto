#include <iostream>
#include <limits>
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;

// ESTRUCTURAS

struct Fecha {
    int dia, mes, anio;
};

struct Candidato {
    int dni;
    char nombre[20];
    char apellido[25];
    bool sexo; // true para hombre, false para mujer
    char partidoPolitico[50];
    Fecha fechaNacimiento;
    int cantidadDeVotos;
};

struct Votante {
    int dni;
    bool sexo; // true para hombre, false para mujer
    char nombre[20];
    Fecha fechaNacimiento;
    int votoCandidato;  
};

// FUNCIONES ÚTILES

int largo(int num){
    if (num == 0) {
        return 1;
    }
    int length = 0;
    while (num != 0) {
        num /= 10;
        length++;
    }
    return length;
}

int obtenerEdad(Fecha fechaNacimiento){
    int dia = 18, mes = 11, anio = 2023, anios;
    anios = anio - fechaNacimiento.anio;
    if (mes < fechaNacimiento.mes || (mes == fechaNacimiento.mes && dia < fechaNacimiento.dia)){
        anios --;
    }
    return anios;
}

int cantidadVotosEnBlanco(Votante votantes[], int cantVotantes){
    int cant = 0;
    for (int i = 0; i < cantVotantes; i++){
        if (votantes[i].votoCandidato == 0){
            cant++ ;
        }
    }
    return cant;
}

float porcentajeVotos(Candidato candidato, int cantVotantes, int votosEnBlanco){
    return (candidato.cantidadDeVotos/float(cantVotantes-votosEnBlanco));
}

string cadenaDeEspacios(int n){
    char cadenaDeEspacios[n + 1];  
    for (int i = 0; i < n; ++i) {
        cadenaDeEspacios[i] = ' ';
    }
    cadenaDeEspacios[n] = '\0';
    return cadenaDeEspacios;
}

string cadenaGenero(bool g){
    if (g){
        return "Masculino ";
    }
    return "Femenino  ";
}

void mostrarCandidatosConNumero(Candidato candidatos[], int cantCandidatos){
    cout << endl << "LISTA DE CANDIDATOS "<<endl;
    for (int i = 0; i < cantCandidatos ; i++){
        cout << i+1 << ")";
        cout << candidatos[i].nombre << " " <<candidatos[i].apellido << endl;
    }   
    cout << endl;
}

void calcularVotos(Candidato candidatos[], Votante votantes[], int cantCandidatos, int cantVotantes){    
    for (int i = 0; i<cantVotantes ;i++){
        if (votantes[i].votoCandidato!=0){
            candidatos[votantes[i].votoCandidato-1].cantidadDeVotos++;
        }
    }
}

// VALIDACIÓN
bool esNombreApellidoValido(const char *cadena) {
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (!isalpha(cadena[i]) && !isspace(cadena[i])) {
            return false;
        }
    }
    return true;
}

void pedirNombreApellido(char *nombreOApellido, int longitud) {
    do {
        cin.getline(nombreOApellido, longitud, '\n');
        if (!esNombreApellidoValido(nombreOApellido)) {
            cout << "Entrada invalida. Ingrese solo letras: ";
        }
    } while (!esNombreApellidoValido(nombreOApellido));
}


void pedirEntero(int &ent){
    while (!(cin >> ent) || cin.peek() != '\n'){
        cout << "Entrada no valida. Debe ingresar un numero entero. Vuelve a intentarlo: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void pedirMaxMin(int &ent, int max, int min){
    while (true){
        pedirEntero(ent);
        if (max >= ent && ent >= min) {break;}
        cout << "Entrada no valida. Debe ingresar un numero como minimo "<< min << " y como maximo "<< max <<". Vuelve a intentarlo: ";
    }
}

void pedirDni(int &dni, Candidato candidatos[], int cantCandidatos, Votante votantes[] = {}, int cantVotantes = 0){
    bool repetido;
    do {
        repetido = false;
        pedirMaxMin(dni, 1000000000, 10000);
        for (int i = 0; i < cantCandidatos; i++){
            if (candidatos[i].dni == dni){
                repetido = true;
                cout << "El DNI ya existe en la lista de candidatos. Vuelva a intentarlo: ";
            } 
        }

        for (int i = 0; i < cantVotantes; i++){
            if (votantes[i].dni == dni){
                repetido = true;
                cout << "El DNI ya existe en la lista de votantes. Vuelva a intentarlo. ";
            } 
        }

    } while (repetido);
}

void pedirGenero(bool &sexo){
    char entrada[10];
    while (true) {
        cin.getline(entrada, 10, '\n');
        entrada[0] = tolower(entrada[0]);
        if ((entrada[0] == 'm' || entrada[0] == 'f') && (strlen(entrada) == 1)) {
            sexo = (entrada[0] == 'm');
            break;
        } else {
            cout << "Entrada invalida. Por favor, ingrese 'M' o 'F': ";
        }
    }
}

bool mayorDe(Fecha nacimiento, int n){
    return (obtenerEdad(nacimiento) >= n);
}

bool esBisiesto(int anio) {
    return (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0));
}

bool fechaValida(Fecha nacimiento){
    int dia = 18, mes = 11, anio = 2023;
    int diasHasta[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (nacimiento.dia <= diasHasta[nacimiento.mes-1]){
        return true;
    }
    if (nacimiento.mes == 2 && esBisiesto(nacimiento.anio) && nacimiento.dia==29){
        return true;
    }
    return false;
}

// LEER DATOS

void leerCandidatos(Candidato candidatos[], int &cantCandidatos){
    cout << "Ingrese la cantidad de candidatos: ";
    pedirMaxMin(cantCandidatos, 20, 1);
    cout << "Ingrese la informacion de los candidatos..." <<endl << endl;
    for (int i = 0; i < cantCandidatos ; i++){
        cin.ignore();
        cout << "Ingrese el DNI del candidato " << i + 1 << ": ";
        pedirDni(candidatos[i].dni, candidatos, i);
        cin.ignore();
        cout << "Ingrese el nombre del candidato " << i + 1 << ": ";
        pedirNombreApellido(candidatos[i].nombre, 20);
        cout << "Ingrese el apellido del candidato " << i + 1 << ": ";
        pedirNombreApellido(candidatos[i].apellido, 25);
        cout << "Ingrese el sexo del candidato ('M' o 'F') " << i + 1 << ": ";
        pedirGenero(candidatos[i].sexo);
        cout << "Ingrese el partido politico del candidato " << i + 1 << ": ";
        cin.getline(candidatos[i].partidoPolitico, 50, '\n');
        while (true){
            cout << "Ingrese el anio de nacimiento del candidato " << i + 1 << ": ";
            pedirMaxMin(candidatos[i].fechaNacimiento.anio, 2005, 1900);
            cout << "Ingrese el mes de nacimiento del candidato " << i + 1 << ": ";
            pedirMaxMin(candidatos[i].fechaNacimiento.mes, 12, 1);
            cout << "Ingrese el dia de nacimiento del candidato " << i + 1 << ": ";
            pedirMaxMin(candidatos[i].fechaNacimiento.dia, 31, 1);
            if (!mayorDe(candidatos[i].fechaNacimiento, 18)){
                cout << "El candidato no es mayor de 18, vuelva a intentarlo. " << endl;
            } else{
                if (!fechaValida(candidatos[i].fechaNacimiento)){
                    cout << "La fecha no es valida. Vuelva a intentarlo. " << endl;
                } else{
                    break;
                }
            }
        }
        candidatos[i].cantidadDeVotos = 0;

    }
}

void leerVotantes(Candidato candidatos[], Votante votantes[], int &cantVotantes, int cantCandidatos){
    cout << "Ingrese la cantidad de votantes: ";
    pedirMaxMin(cantVotantes, 20, 1);
    cout << "Ingrese la informacion de los votantes..." <<endl <<endl;
    for (int i = 0; i < cantVotantes ; i++){
        cin.ignore();
        cout << "Ingrese el DNI del votante " << i + 1 << ": ";
        pedirDni(votantes[i].dni, candidatos, cantCandidatos, votantes, i);
        cin.ignore();
        cout << "Ingrese el sexo del votante ('M' o 'F') " << i + 1 << ": ";
        pedirGenero(votantes[i].sexo);
        cout << "Ingrese el nombre del votante " << i + 1 << ": ";
        pedirNombreApellido(votantes[i].nombre, 20);
        while (true){
            cout << "Ingrese el anio de nacimiento del votante " << i + 1 << ": ";
            pedirMaxMin(votantes[i].fechaNacimiento.anio, 2007, 1900);
            cout << "Ingrese el mes de nacimiento del votante " << i + 1 << ": ";
            pedirMaxMin(votantes[i].fechaNacimiento.mes, 12, 1);
            cout << "Ingrese el dia de nacimiento del votante " << i + 1 << ": ";
            pedirMaxMin(votantes[i].fechaNacimiento.dia, 31, 1);
            if (!mayorDe(votantes[i].fechaNacimiento, 16)){
                cout << "El votante no es mayor de 16, vuelva a intentarlo. " << endl;
            } else{
                if (!fechaValida(votantes[i].fechaNacimiento)){
                    cout << "La fecha no es valida. Vuelva a intentarlo. " << endl;
                } else{
                    break;
                }
            }
        }
        cout << "Ingrese el numero del candidato al cual voto ('0' para voto nulo): ";
        pedirMaxMin(votantes[i].votoCandidato, cantCandidatos, 0);

    }
}

// FUNCIONES PRINCIPALES DEL MENÚ

void mostrarCandidatos(Candidato candidatos[], Votante votantes[], int cantCandidatos, int cantVotantes){
    int votosEnBlanco = cantidadVotosEnBlanco(votantes, cantVotantes);

    cout << "DNI     |NOMBRE"<<cadenaDeEspacios(14)<<"|APELLIDO"<<cadenaDeEspacios(17)<<"|SEXO      "<<"|PARTIDO POLITICO"<<cadenaDeEspacios(34)<<"|NACIMIENTO   "<<"|VOTOS"<<endl;
    for (int i = 0; i < cantCandidatos ; i++){
        cout << candidatos[i].dni << cadenaDeEspacios(8-largo(candidatos[i].dni)) << "|";
        cout << candidatos[i].nombre << cadenaDeEspacios(20-strlen(candidatos[i].nombre)) << "|";
        cout << candidatos[i].apellido << cadenaDeEspacios(25-strlen(candidatos[i].apellido)) << "|";
        cout << cadenaGenero(candidatos[i].sexo) << "|";
        cout << candidatos[i].partidoPolitico << cadenaDeEspacios(50-strlen(candidatos[i].partidoPolitico)) << "|";
        cout << setw(2) << setfill('0') << candidatos[i].fechaNacimiento.dia << "/" << setw(2) << setfill('0') << candidatos[i].fechaNacimiento.mes<< "/" << candidatos[i].fechaNacimiento.anio << "   |";
        cout << porcentajeVotos(candidatos[i], cantVotantes, votosEnBlanco)*100 << " %";
        cout << endl;
    }
}

void buscarVotosPorCandidato(Candidato candidatos[], Votante votantes[], int cantCandidatos, int cantVotantes) {
    int dniCandidatoBuscado;
    cout << "Ingrese el DNI del candidato a buscar: ";
    pedirMaxMin(dniCandidatoBuscado, 10000000, 10000);

    int indiceCandidato = -1;
    for (int i = 0; i < cantCandidatos; i++) {
        if (candidatos[i].dni == dniCandidatoBuscado) {
            indiceCandidato = i;
            break;
        }
    }

    if (indiceCandidato == -1) {
        cout << "No se encontro un candidato con ese DNI." << endl;
    } else {
        cout << "Candidato encontrado: " << candidatos[indiceCandidato].nombre << " " << candidatos[indiceCandidato].apellido << endl;

        int hombresVotaron = 0;
        int mujeresVotaron = 0;

        for (int i = 0; i < cantVotantes; i++) {
            if (votantes[i].votoCandidato == indiceCandidato + 1) {
                if (votantes[i].sexo) {
                    hombresVotaron++;
                } else {
                    mujeresVotaron++;
                }
            }
        }

        cout << "Hombres que votaron por este candidato: " << hombresVotaron << endl;
        cout << "Mujeres que votaron por este candidato: " << mujeresVotaron << endl;
    }
}

void crearArchivoTerceraEdad(Votante votantes[], int cantVotantes) {
    ofstream archivoTerceraEdad("terceraedad.txt");

    archivoTerceraEdad << "Nombres y DNI de votantes con 70 años o más:" << endl;

    for (int i = 0; i < cantVotantes; i++) {
        int anioActual = 2023;  // Asumiendo que el año actual es 2023
        int edad = anioActual - votantes[i].fechaNacimiento.anio;

        if (edad >= 70) {
            archivoTerceraEdad << votantes[i].nombre << " - " << votantes[i].dni << endl;
        }
    }

    archivoTerceraEdad.close();
    cout << "Archivo terceraedad.txt creado exitosamente." << endl;
}

void crearArchivoGanador(Candidato candidatos[], Votante votantes[], int cantCandidatos, int cantVotantes) {
    int votosMaximos = 0; 
    int votosCandidato = 0;
    int ganadores[cantCandidatos];
    int cantGanadores = 0;

    for (int i = 0; i < cantCandidatos; i++) {
        votosCandidato = 0;
        for (int j = 0; j < cantVotantes; j++) {
            if (votantes[j].votoCandidato == i + 1) {
                votosCandidato++;
            }
        }

        if (votosCandidato > votosMaximos) {
            votosMaximos = votosCandidato;
            cantGanadores = 1;
            ganadores[0] = i;

        } else{
            if (votosCandidato == votosMaximos) {
                ganadores[cantGanadores] = i;
                cantGanadores ++;
            }
        }
    }
    ofstream archivoGanador("ganador.txt");
    if (cantGanadores > 1){
        archivoGanador << "Hay " << cantGanadores << " ganadores que obtuvieron una cantidad de " << votosMaximos << " votos ... " << endl;
        archivoGanador << "DNI     |NOMBRE"<<cadenaDeEspacios(14)<<"|APELLIDO"<<endl;
        for (int i = 0; i<cantGanadores; i++) {
            
            archivoGanador << candidatos[ganadores[i]].dni << cadenaDeEspacios(8-largo(candidatos[ganadores[i]].dni)) << "|";
            archivoGanador << candidatos[ganadores[i]].nombre << cadenaDeEspacios(20-strlen(candidatos[ganadores[i]].nombre)) << "|";
            archivoGanador << candidatos[ganadores[i]].apellido << endl;
        }   
    } else{
        archivoGanador << "Gano " << candidatos[ganadores[0]].nombre << " " << candidatos[ganadores[0]].apellido << " con DNI " << candidatos[ganadores[0]].dni << endl;
    }
    archivoGanador.close();
    cout << "Archivo 'ganador.txt' creado con exito." << endl;
}

void buscarVotanteYVoto(Candidato candidatos[], Votante votantes[], int cantVotantes){
    int dni;
    bool existe = false;
    while (!existe){
        cout << "Ingrese el DNI del votante para obtener su informacion: ";
        pedirMaxMin(dni, 1000000000, 10000);
        for (int i=0; i<cantVotantes; i++){
            if (votantes[i].dni == dni){
                existe = true;
                if (votantes[i].votoCandidato == 0){
                    cout << "(" << dni << ") con " << obtenerEdad(votantes[i].fechaNacimiento) << " anios voto en blanco" << endl;
                } else{
                    cout << "(" << dni << ") con " << obtenerEdad(votantes[i].fechaNacimiento) << " anios voto a " << candidatos[votantes[i].votoCandidato-1].nombre << " " <<candidatos[votantes[i].votoCandidato-1].apellido << endl;
                }
            }
        }
        if (!existe){
            cout << "No existe el DNI en la lista de votantes, vuelva a intentarlo. " << endl;
        }
    }
}

void listarNulos(Votante votantes[], int cantVotantes) {
    
    ofstream archivoNulos("nulos.txt");

    if (archivoNulos.is_open()) {
        archivoNulos << "DNI de votantes con voto Nulo:" << endl;

        for (int i = 0; i < cantVotantes; i++) {
            if (votantes[i].votoCandidato == 0) {
                archivoNulos << votantes[i].dni << endl;
            }
        }

        archivoNulos.close();

        cout << "Archivo 'nulos.txt' creado con los DNI de votantes con voto Nulo." << endl;
    } else {
        cout << "No se pudo abrir el archivo 'nulos.txt'." << endl;
    }
}

void ordenarYMostrarPorVotos(Candidato candidatos[], Votante votantes[], int cantCandidatos, int cantVotantes){
    Candidato copia[cantCandidatos];
    for (int i = 0; i < cantCandidatos; i++){
        strcpy(copia[i].nombre,candidatos[i].nombre);
        strcpy(copia[i].apellido,candidatos[i].apellido);
        copia[i].dni = candidatos[i].dni;
        copia[i].cantidadDeVotos = candidatos[i].cantidadDeVotos;
    }

    Candidato temp;
    bool cambio = true;
    while (cambio){
        cambio = false;
        for (int i = 0; i < cantCandidatos-1; i++){
            if (copia[i].cantidadDeVotos < copia[i+1].cantidadDeVotos){
                cambio = true;

                strcpy(temp.nombre, copia[i].nombre);
                strcpy(temp.apellido, copia[i].apellido);
                temp.dni = copia[i].dni;
                temp.cantidadDeVotos = copia[i].cantidadDeVotos;

                strcpy(copia[i].nombre, copia[i+1].nombre);
                strcpy(copia[i].apellido, copia[i+1].apellido);
                copia[i].dni = copia[i+1].dni;
                copia[i].cantidadDeVotos = copia[i+1].cantidadDeVotos;

                strcpy(copia[i+1].nombre, temp.nombre);
                strcpy(copia[i+1].apellido, temp.apellido);
                copia[i+1].dni = temp.dni;
                copia[i+1].cantidadDeVotos = temp.cantidadDeVotos;

            }
        }
    }

    cout << "DNI     |NOMBRE"<<cadenaDeEspacios(14)<<"|APELLIDO"<<cadenaDeEspacios(22)<<"|VOTOS"<<endl;
    for (int i = 0; i < cantCandidatos ; i++){
        cout << copia[i].dni << cadenaDeEspacios(8-largo(copia[i].dni)) << "|";
        cout << copia[i].nombre << cadenaDeEspacios(20-strlen(copia[i].nombre)) << "|";
        cout << copia[i].apellido << cadenaDeEspacios(25-strlen(copia[i].apellido)) << "|";
        cout << copia[i].cantidadDeVotos;
        cout << endl;
    }
}

void menu(Candidato candidatos[], Votante votantes[], int cantCandidatos, int cantVotantes){
    int opcion;

    while (true) {
        cout << endl;
        cout << "OPCIONES DEL MENU: " << endl;
        cout << "1. Mostrar candidatos." << endl;
        cout << "2. Buscar votos por candidato." << endl;
        cout << "3. Ver votantes con mas de 70 anios." << endl;
        cout << "4. Determinar ganador" << endl;
        cout << "5. Buscar votante y voto." << endl;
        cout << "6. Listar votos nulos" << endl;
        cout << "7. Ordenar y mostrar candidatos por votos." << endl;
        cout << endl;
        cout <<"Elija una opcion (1-7) (0 para cerrar el programa): ";
        pedirMaxMin(opcion, 7, 0);
        cout << endl;
        if (opcion == 0){break ;}
        switch (opcion)
        {
        case 1:
            mostrarCandidatos(candidatos, votantes, cantCandidatos, cantVotantes);
            break;
        case 2:
            buscarVotosPorCandidato(candidatos, votantes, cantCandidatos, cantVotantes);
            break;
        case 3:
            crearArchivoTerceraEdad(votantes, cantVotantes);
            break;
        case 4:
            crearArchivoGanador(candidatos, votantes, cantCandidatos, cantVotantes);
            break;
        case 5:
            buscarVotanteYVoto(candidatos, votantes, cantVotantes);
            break;
        case 6:
            listarNulos(votantes, cantVotantes);
            break;
        case 7:
            ordenarYMostrarPorVotos(candidatos, votantes, cantCandidatos, cantVotantes);
            break;
        }
    };

}

int main()
{
    int cantCandidatos, cantVotantes;
    Candidato candidatos[20];
    Votante votantes[100];

    cout << endl
         << "ELECCIONES 2023" << endl;

    leerCandidatos(candidatos, cantCandidatos);
    mostrarCandidatosConNumero(candidatos, cantCandidatos);
    leerVotantes(candidatos, votantes, cantVotantes, cantCandidatos);
    calcularVotos(candidatos, votantes, cantCandidatos, cantVotantes);
    menu(candidatos, votantes, cantCandidatos, cantVotantes);

    return 0;
}