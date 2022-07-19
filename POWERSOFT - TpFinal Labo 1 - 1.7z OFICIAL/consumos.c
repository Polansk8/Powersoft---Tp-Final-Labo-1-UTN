#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "archi.h"
#include "clientes.h"
#include "consumos.h"





CON loadOneCon (CON con, CLI cli)
{
    con.idCliente = cli.id;


    printf(">>>Ingrese el dia: ");
    scanf("%d", &con.day);
    system("cls");
    while (con.day > 30 || con.day < 1)
        {
        printf(">>>[ERROR]<<< Cargue el dia desde 1 a 30: ");
        scanf("%d", &con.day);
        system("cls");
        }

    printf(">>>Ingrese el mes: ");
    scanf("%d", &con.month);
    system("cls");
    while (con.month > 12 || con.month < 1)
        {
        printf(">>>[ERROR]<<< Cargue el mes de 1 a 12: ");
        scanf("%d", &con.month);
        system("cls");
        }

    printf(">>>Ingrese el anio: ");
    scanf("%d", &con.year);
    system("cls");

    printf(">>>Ingrese el consumo del cliente (Mega bytes): ");
    scanf("%d", &con.megaBytes);

    return con;
}



void printOneCon (CON con)
{
    printf("\n              Registro: %d", con.reg);
    printf("\n                 Fecha: %02d/%02d/%d", con.day, con.month, con.year);
    printf("\n           Consumo(MB): %d", con.megaBytes);
}



CON loadConDate (CLI cli)
{
    CON con;

    con.idCliente = cli.id;

    printf(">>>Ingrese el dia: ");
    scanf("%d", &con.day);
    system("cls");

    while (con.day > 30 || con.day < 1)
        {
        printf(">>>[ERROR]<<< Cargue el dia desde 1 a 30: ");
        scanf("%d", &con.day);
        system("cls");
        }

    printf(">>>Ingrese el mes: ");
    scanf("%d", &con.month);
    system("cls");
    while (con.month > 12 || con.month < 1)
        {
        printf(">>>[ERROR]<<< Cargue el mes de 1 a 12: ");
        scanf("%d", &con.month);
        system("cls");
        }

    printf(">>>Ingrese el anio: ");
    scanf("%d", &con.year);
    system("cls");

    return con;
}





/** \brief Verifica si un consumo es igual con otro
 *
 * \param Estructura de consumo
 * \param Estructura de consumo
 * \return Flag (1 si son iguales, 2 si no son iguales)
 *
 */
int verifyCon (CON conAux, CON con)
{
    int flag = 0;

    ///Si el dia, mes, año, y el id de cliente son iguales cambio el valor flag=1.
    if (conAux.day == con.day && conAux.month == con.month && conAux.year == con.year && conAux.idCliente == con.idCliente)
        {
        flag = 1;
        }

    ///Retorno el resultado de la comparacion.
    return flag;
}



int returnRand (int max, int min)
{
    return rand() / (max-min) + min;
}


CON randCon (CON c)
{
    srand(time(NULL));

    c.idCliente = rand() % 29 + 1;

    c.day = rand() % 29 + 1;

    c.month = rand() % 11 + 1;

    c.year = rand()% 19 + 2003;

    c.megaBytes = rand() % 940;

    return c;
}








void printConAndClient (CLI cli, CON con)
{
    printOneClient(cli);
    printf("\n_____________________________________________________");
    printOneCon(con);
}


