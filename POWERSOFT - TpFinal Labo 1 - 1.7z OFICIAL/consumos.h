#ifndef CONSUMOS_H_INCLUDED
#define CONSUMOS_H_INCLUDED

typedef struct
{
    int reg;
    int idCliente;
    int day;
    int month;
    int year;
    int megaBytes;
}CON;


///Carga el consumo de un cliente
CON loadOneCon (CON con, CLI cli);
///Muestra los consumos de un cliente
void printOneCon (CON c);
///Carga la fecha de un consumo de un cliente para comparar con otro consumo
CON loadConDate (CLI cli);
///Muestra por consola el cliente y un consumo
void printConAndClient (CLI cli, CON con);
///Verifica que un consumo coincida con el otro
int verifyCon (CON conAux, CON con);
///
CON randCon (CON c);




#endif // CONSUMOS_H_INCLUDED





