#ifndef ARCHI_H_INCLUDED
#define ARCHI_H_INCLUDED


#include "clientes.h"
#include "consumos.h"

///Carga un archivo de clientes
void loadArchivoClient (char archivo[]);
///Verifica en el archivo si existe un DNI
int verifyDniInFile (FILE *clients, char dni[]);
///Muestra un archivo de clientes
void printFileClients (char archivo[]);
///Busca un cliente por DNI
void searchXDni (char archivo[]);
///Busca un cliente por ID
void searchXId (char archivo[]);
///Busca un cliente por nombre
void searchXName (char archivo[]);
///Busca un cliente por el apellido
void searchXSurname (char archivo[]);
///Busca un cliente por numero de celular
void searchXMobile (char archivo[]);
///Busca y retorna el ultimo ID de los clientes cargados
int searchEndId (char archivo []);
///Da de alta un cliente
void regClients (char archivo[]);
///Muestra lo clientes dados de alta
void printRegClients(char archivo[]);
///Da de baja un cliente
void deregClient (char archivo[]);
///Muestra los clientes dados de baja
void printDeregClients (char archivo[]);
///Modifica en el archivo todos los datos de un cliente
void customClient (char archivo[]);
///Modifica en el archivo el ID de un cliente
void customIdClient (char archivo[]);



///Carga un archivo con los consumos de un cliente
void loadConsumptions (char arCon[], char arCli[]);
///Agrega un consumo en un registro ya creado en la misma fecha
void loadConInDate (FILE *clientes, CON c);
///Muestra todos los consumos de un cliente
void printConClients (char arCon[], char arClient[]);
///Busca un consumo de una fecha especifica de un cliente
void searchConDate (char arCon[], char arCli[]);
///Modifica el consumo de un cliente
void customConClient (char arCon[], char arCli[]);
///Retorna el ultimo ID (registro) de los consumos
int returnEndConReg (char archivo[]);
///Verifica en el archivo si un consumo existe.
int verifyFileCon (FILE *archivo, CON con);
///
void writeRandCon (char archivo[], int value);


#endif // ARCHI_H_INCLUDED
