#ifndef STEMPLEADOS_H_INCLUDED
#define STEMPLEADOS_H_INCLUDED

typedef struct
{
    int id;
    char apellido [20];
    char nombre[20];
    char dni[10];
    char telefono [12];
    char mail [45];
    int estado;
} stEmpleado;



stEmpleado cargarUnEmpleado();
int cargarEmpleados (stEmpleado e[], int dim);
void mostrarUnEmpleado(stEmpleado e);
void mostrarEmpleados(stEmpleado e[], int v);
void cargarArchivoEmpleado(char nombreArchivo[]);
void mostrarArchivoEmpleado(char nombreArchivo[]);
void buscarporDatoInt(char nombreArchivo[], int dato);
void buscarPorEstado(char nombreArchivo[], int dato);
int incrementarId (char nombreArchivo[]);
int incrementarIdEmpleado (char nombreArchivo[]);
void buscarPorDni (char nombreArchivo[], char dni[]);
void buscarPorApellido (char nombreArchivo[], char apellido[]);
void modificarApellido(char nombreArchivo[], char apellido[]);
void modificarEstadoxId(char nombreArchivo[], int id);
void modificarMail(char nombreArchivo[], char mail[]);
void modificarEstadoxDni(char nombreArchivo[], char dni[]);



#endif // STEMPLEADOS_H_INCLUDED
