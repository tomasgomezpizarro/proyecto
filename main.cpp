#include <iostream>
#include <limits>
#include <cstring>
#include <iomanip> 
using namespace std;

// ESTRUCTURAS

struct Fecha {
    int dia, mes, anio;
};

struct Candidato {
    int dni;
    char nombre[20];
    char apellido[30];
    bool sexo; // 1 para hombre, 0 para mujer
    char partidoPolitico[50];
    Fecha fechaNacimiento;
};

struct Votante {
    int dni;
    bool sexo; // 1 para hombre, 0 para mujer
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

int obtenerEdad(Votante vot){
    int diaHoy = 18, mesHoy = 11, anio = 2023, anios;
    anios = anio - vot.fechaNacimiento.anio;
    if (mesHoy < vot.fechaNacimiento.mes || (mesHoy == vot.fechaNacimiento.mes && diaHoy < vot.fechaNacimiento.dia)){
        anios --;
    }
    return anios;
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
    cout << "LISTA DE CANDIDATOS "<<endl;
    for (int i = 0; i < cantCandidatos ; i++){
        cout << i+1 << ")";
        cout << candidatos[i].nombre << " " <<candidatos[i].apellido << endl;
    }   
    cout << endl;
}

// VALIDACIÓN

void pedirEntero(int &ent){
    while (!(cin >> ent)){
        cout << "Entrada no valida. Debe ingresar un numero entero. Vuelve a intentarlo: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void pedirDni(int &ent){
    while (true) {
        pedirEntero(ent);
        if (largo(ent) <= 8){
            break;
        }
        cout << "Entrada no valida. Debe ingresar un numero como maximo 8 digitos. Vuelva a intentarlo: ";
    }
}

void pedirMaxMin(int &ent, int max, int min){
    while (true){
        pedirEntero(ent);
        if (max >= ent && ent >= min) {break;}
        cout << "Entrada no valida. Debe ingresar un numero como minimo "<< min << " y como maximo "<< max <<". Vuelve a intentarlo: ";
    }
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
            cin.clear();
        }
    }
}

// LEER DATOS

void leerCandidatos(Candidato candidatos[], int &cantCandidatos){
    cout << "Ingrese la cantidad de candidatos: ";
    pedirMaxMin(cantCandidatos, 20, 1);
    cout << "Ingrese la informacion de los candidatos..." <<endl << endl;
    for (int i = 0; i < cantCandidatos ; i++){
        cin.ignore();
        cout << "Ingrese el DNI del candidato " << i + 1 << ": ";
        pedirDni(candidatos[i].dni);
        cin.ignore();
        cout << "Ingrese el nombre del candidato " << i + 1 << ": ";
        cin.getline(candidatos[i].nombre, 20, '\n');
        cout << "Ingrese el apellido del candidato " << i + 1 << ": ";
        cin.getline(candidatos[i].apellido, 30, '\n');
        cout << "Ingrese el sexo del candidato ('M' o 'F') " << i + 1 << ": ";
        pedirGenero(candidatos[i].sexo);
        cout << "Ingrese el partido politico del candidato " << i + 1 << ": ";
        cin.getline(candidatos[i].partidoPolitico, 50, '\n');
        cout << "Ingrese el anio de nacimiento del candidato " << i + 1 << ": ";
        pedirMaxMin(candidatos[i].fechaNacimiento.anio, 2005, 1900);
        cout << "Ingrese el mes de nacimiento del candidato " << i + 1 << ": ";
        pedirMaxMin(candidatos[i].fechaNacimiento.mes, 12, 1);
        cout << "Ingrese el dia de nacimiento del candidato " << i + 1 << ": ";
        pedirMaxMin(candidatos[i].fechaNacimiento.dia, 31, 1);

    }
}

void leerVotantes(Votante votantes[], int &cantVotantes, int cantCandidatos){
    cout << "Ingrese la cantidad de votantes: ";
    pedirMaxMin(cantVotantes, 20, 1);
    cout << "Ingrese la informacion de los votantes..." <<endl <<endl;
    for (int i = 0; i < cantVotantes ; i++){
        cin.ignore();
        cout << "Ingrese el DNI del votante " << i + 1 << ": ";
        pedirDni(votantes[i].dni);
        cin.ignore();
        cout << "Ingrese el sexo del votantes" << i + 1 << ": ";
        pedirGenero(votantes[i].sexo);
        cout << "Ingrese el nombre del votante " << i + 1 << ": ";
        cin.getline(votantes[i].nombre, 20, '\n');
        cout << "Ingrese el anio de nacimiento del votante " << i + 1 << ": ";
        pedirMaxMin(votantes[i].fechaNacimiento.anio, 2007, 1900);
        cout << "Ingrese el mes de nacimiento del votante " << i + 1 << ": ";
        pedirMaxMin(votantes[i].fechaNacimiento.mes, 12, 1);
        cout << "Ingrese el dia de nacimiento del votante " << i + 1 << ": ";
        pedirMaxMin(votantes[i].fechaNacimiento.dia, 31, 1);
        cout << "Ingrese el numero del candidato al cual voto ('0' para voto nulo)" << i + 1 << ": ";
        pedirMaxMin(votantes[i].votoCandidato, cantCandidatos, 0);

    }
}

// FUNCIONES PRINCIPALES DEL MENÚ

void mostrarCandidatos(Candidato candidatos[], Votante votantes[], int cantCandidatos, int cantVotantes){
    cout << "DNI     |NOMBRE"<<cadenaDeEspacios(14)<<"|APELLIDO"<<cadenaDeEspacios(22)<<"|SEXO      "<<"|PARTIDO POLITICO"<<cadenaDeEspacios(34)<<"|NACIMIENTO"<<endl;
    for (int i = 0; i < cantCandidatos ; i++){
        cout << candidatos[i].dni << cadenaDeEspacios(8-largo(candidatos[i].dni)) << "|";
        cout << candidatos[i].nombre << cadenaDeEspacios(20-strlen(candidatos[i].nombre)) << "|";
        cout << candidatos[i].apellido << cadenaDeEspacios(30-strlen(candidatos[i].apellido)) << "|";
        cout << cadenaGenero(candidatos[i].sexo) << "|";
        cout << candidatos[i].partidoPolitico << cadenaDeEspacios(50-strlen(candidatos[i].partidoPolitico)) << "|";
        cout << setw(2) << setfill('0') << candidatos[i].fechaNacimiento.dia << "/" << setw(2) << setfill('0') << candidatos[i].fechaNacimiento.mes<< "/" << candidatos[i].fechaNacimiento.anio;
        cout << endl;
    }
}

void buscarVotosPorCandidato(Candidato candidatos[], Votante votantes[], int cantCandidatos, int cantVotantes){

}
void crearArchivoTerceraEdad(Candidato candidatos[], Votante votantes[], int cantCandidatos, int cantVotantes){

}
void crearArchivoGanador(Candidato candidatos[], Votante votantes[], int cantCandidatos, int cantVotantes){

}
void buscarVotanteYVoto(Candidato candidatos[], Votante votantes[], int cantCandidatos, int cantVotantes){
    int dni;
    cout << "Ingrese el DNI del votante para obtener su informacion: ";
    pedirDni(dni);
    for (int i=0; i<cantVotantes; i++){
        if (votantes[i].dni == dni){
            cout << "(" << dni << ") con " << obtenerEdad(votantes[i]) << " anios voto a " << candidatos[votantes[i].votoCandidato].nombre << " " <<candidatos[votantes[i].votoCandidato].apellido << endl;
        }
    }
}
void listarNulos(Candidato candidatos[], Votante votantes[], int cantCandidatos, int cantVotantes){

}
void ordenarYMostrarPorVotos(Candidato candidatos[], Votante votantes[], int cantCandidatos, int cantVotantes){

}

void menu(Candidato candidatos[], Votante votantes[], int cantCandidatos, int cantVotantes){
    int opcion;
    void (*opciones[])(Candidato*, Votante*, int, int) = {mostrarCandidatos, buscarVotosPorCandidato, crearArchivoTerceraEdad, crearArchivoGanador, buscarVotanteYVoto, listarNulos, ordenarYMostrarPorVotos};

    cout << "OPCIONES DEL MENU: " << endl;
    cout << "1. Mostrar candidatos." << endl;
    cout << "2. Buscar votos por candidato." << endl;
    cout << "3. Ver votantes con mas de 70 anios." << endl;
    cout << "4. Determinar ganador" << endl;
    cout << "5. Buscar votante y voto." << endl;
    cout << "6. Listar votos nulos" << endl;
    cout << "7. Ordenar y mostrar candidatos por votos." << endl;
    cout << endl;

    while (true) {
        cout << "Elija una opcion (1-7) (0 para cerrar el programa): ";
        pedirMaxMin(opcion, 7, 0);
        if (opcion == 0){break ;}
        opciones[opcion-1](candidatos, votantes, cantCandidatos, cantVotantes);
    };

}

int main(){
    int cantCandidatos, cantVotantes;
    // Candidato candidatos[30];
    // Votante votantes[100];

    cout << "ELECCIONES 3023" << endl << endl ;

    // DATOS de prueba
    Candidato candidatos[5] = {
        {111111, "Candidato1", "Apellido1", 'M', "Partido1", {1, 1, 1990}},
        {222222, "Candidato2", "Apellido2", 'F', "Partido2", {2, 2, 1985}},
        {333333, "Candidato3", "Apellido3", 'M', "Partido3", {3, 3, 1980}},
        {444444, "Candidato4", "Apellido4", 'F', "Partido4", {4, 4, 1975}},
        {555555, "Candidato5", "Apellido5", 'M', "Partido5", {5, 5, 1970}},
    };
    cantCandidatos = 5;

    Votante votantes[5] = {
        {666666, 'M', "Votante1", {6, 6, 2003}, 1},
        {777777, 'F', "Votante2", {7, 7, 1995}, 2},
        {888888, 'M', "Votante3", {8, 8, 1990}, 3},
        {999999, 'F', "Votante4", {9, 9, 1985}, 4},
        {666666, 'M', "Votante5", {10, 10, 1980}, 5},
    };
    cantVotantes = 5;

    // leerCandidatos(candidatos, cantCandidatos);
    // mostrarCandidatosConNumero(candidatos, cantCandidatos);
    // leerVotantes(votantes, cantVotantes, cantCandidatos);
    menu(candidatos, votantes, cantCandidatos, cantVotantes);

    return 0;
}