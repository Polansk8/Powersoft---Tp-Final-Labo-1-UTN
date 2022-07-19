#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>


#include "Menu.h"
#include "clientes.h"
#include "archi.h"
#include "centrarTitulos.h"


#define AR_CLIENTS "clientes.dat"
#define AR_CONSUM "consumpions.dat"

#define ANCHO 118



//C:\Users\pc\Desktop\Proyectos comprimidos\Trabajo Practico Final Laboratorio 1

void recuadro(char cabecera[])
{
    int i;
    printf("%c", 201);
    for (i=0;i<50;i++)
        {
        printf("%c", 205);
        }

    printf("%c\n", 187);
    printf("%c%32s%19c\n", 186, cabecera,186);
    printf("%c", 200);

    for (i=0;i<50;i++)
        {
        printf( "%c", 205);
        }

    printf("%c",188);
}





///Menu principal
void mainMenu()
{
    char opcion = 0;

    while (opcion != 27)
        {
        system("cls");
        printInMarg("POWERSOFT - CLIENTES");
        contarTitulo(">>>1) Apartado de clientes");
        contarTitulo(">>>2) Apartado de consumos");
        contarTitulo("ESC) Salir...");
        imprimirTecho(ANCHO);

        opcion = getch();
        Beep(400, 300);
        system("cls");

        switch (opcion)
            {
            case '1':
                clientMenu();
                break;
            case '2':
                consumMenu();
                break;
            case 27:
                opcion = 27;
                break;
            default:
                errorMessagge(">>>[ERROR]<<< INGRESO UNA OPCION NO VALIDA");
                getch();
                break;
            }
        }

}




///Menu de clientes
void clientMenu ()
{
    char opcion = 0;

    while (opcion != 27)
        {
        system("cls");
        printInMarg("APARTADO DE CLIENTES");
        contarTitulo("1) Ingresar un nuevo cliente");
        contarTitulo("2) Mostrar lista de clientes");
        contarTitulo("3) Buscar clientes");
        contarTitulo("4) Dar de alta o baja un cliente");
        contarTitulo("5) Modificar un cliente");
        contarTitulo("ESC) Volver al menu anterior");
        imprimirTecho(ANCHO);

        opcion = getch();
        Beep(400, 300);
        system("cls");

        switch (opcion)
            {
            case '1':
                loadArchivoClient(AR_CLIENTS);
                break;
            case '2':
                printClientsMenu();
                break;
            case '3':
                searchClientMenu();
                break;
            case '4':
                regDeregMenu();
                break;
            case '5':
                customClientsMenu();
                break;
            case 27:
                break;
            default:
                errorMessagge(">>>[ERROR]<<< INGRESO UNA OPCION NO VALIDA");
                getch();
                break;
            }
        }
}





///Menu para dar de alta o baja un cliente
void regDeregMenu ()
{
    char opcion = 0;

    while (opcion != 27)
        {
        system("cls");
        printInMarg("BAJA O ALTA MENU");
        contarTitulo("1) Alta de un cliente");
        contarTitulo("2) Baja de un cliente");
        contarTitulo("ESC) Volver al menu anterior");
        imprimirTecho(ANCHO);

        opcion = getch();
        Beep(400, 300);
        system("cls");

        switch (opcion)
            {
            case '1':
                regClients(AR_CLIENTS);
                break;
            case '2':
                deregClient(AR_CLIENTS);
                break;
            case 27:
                break;
            default:
                errorMessagge(">>>[ERROR]<<< INGRESO UNA OPCION NO VALIDA");
                getch();
                break;
            }
        }
}





///Menu de modificacion de clientes
void customClientsMenu ()
{
    char opcion = 0;

    while (opcion != 27)
        {
        system("cls");
        printInMarg("MODIFICAR CLIENTES MENU");
        contarTitulo("1) Modificar datos");
        contarTitulo("2) Modificar ID");
        contarTitulo("ESC) Volver al menu anterior");
        imprimirTecho(ANCHO);

        opcion = getch();
        Beep(400, 300);
        system("cls");

        switch(opcion)
            {
            case '1':
                customClient(AR_CLIENTS);
                break;
            case '2':
                customIdClient(AR_CLIENTS);
                break;
            case 27:
                break;
            default:
                errorMessagge(">>>[ERROR]<<< INGRESO UNA OPCION NO VALIDA");
                getch();
                break;
            }
        }
}






///Menu de mostrar clientes
void printClientsMenu ()
{
    char opcion = 0;

    while (opcion != 27)
        {
        system("cls");
        printInMarg("MUESTRA DE CLIENTES ");
        contarTitulo("1) Todos los clientes");
        contarTitulo("2) Clientes dados de alta");
        contarTitulo("3) Clientes dados de baja");
        contarTitulo("ESC) Volver al menu anterior");
        imprimirTecho(ANCHO);

        opcion = getch();
        Beep(400, 300);
        system("cls");

        switch(opcion)
            {
            case '1':
                recuadro("TODOS LOS CLIENTES");
                printFileClients(AR_CLIENTS);
                break;
            case '2':
                recuadro("CLIENTES DADOS DE ALTA");
                printRegClients(AR_CLIENTS);
                break;
            case '3':
                recuadro("CLIENTES DADOS DE BAJA");
                printDeregClients(AR_CLIENTS);
                break;
            case 27:
                break;
            default:
                errorMessagge(">>>[ERROR]<<< INGRESO UNA OPCION NO VALIDA");
                getch();
                break;
            }
        }
}





///Menu de busqueda de clientes
void searchClientMenu ()
{
    char opcion = 0;

    while (opcion != 27)
        {
        system("cls");
        printInMarg("BUSCAR CLIENTES");
        contarTitulo("1) Buscar cliente por DNI");
        contarTitulo("2) Buscar cliente por ID");
        contarTitulo("3) Buscar cliente por nombre");
        contarTitulo("4) Buscar cliente por apellido");
        contarTitulo("5) Buscar cliente por celular");
        contarTitulo("ESC) Volver al menu anterior");
        imprimirTecho(ANCHO);

        opcion = getch();
        Beep(400, 300);
        system("cls");

        switch (opcion)
            {
            case '1':
                searchXDni(AR_CLIENTS);
                break;
            case '2':
                searchXId(AR_CLIENTS);
                break;
            case '3':
                searchXName(AR_CLIENTS);
                break;
            case '4':
                searchXSurname(AR_CLIENTS);
                break;
            case '5':
                searchXMobile(AR_CLIENTS);
                break;
            case 27:
                break;
            default:
                errorMessagge(">>>[ERROR]<<< INGRESO UNA OPCION NO VALIDA");
                getch();
                break;
            }
        }
}






///Menu de consumos de clientes
void consumMenu ()
{
    char opcion = 0;



    while (opcion != 27)
        {
        system("cls");
        printInMarg("APARTADO DE CONSUMOS");
        contarTitulo("1) Cargar un consumo de un cliente");
        contarTitulo("2) Mostrar los consumos de un cliente");
        contarTitulo("3) Modificar los consumos de un cliente");
        contarTitulo("ESC) Volver al menu anterior");
        imprimirTecho(ANCHO);

        opcion = getch();
        Beep(400, 300);
        system("cls");

        switch (opcion)
            {
            case '1':
                loadConsumptions(AR_CONSUM, AR_CLIENTS);
                break;
            case '2':
                printConMenu();
                break;
            case '3':
                customConClient(AR_CONSUM, AR_CLIENTS);
                break;
            case '4':
                loadRandCon(AR_CONSUM);
                break;
            default:
                errorMessagge(">>>[ERROR]<<< INGRESO UNA OPCION NO VALIDA");
                getch();
                break;
            case 27:
                break;
            }
        }
}







///Menu de muestra de consumos
void printConMenu ()
{
    char opcion = 0;

    while (opcion != 27)
        {
        system("cls");
        printInMarg("MENU MUESTRA DE CONSUMOS");
        contarTitulo("1) Todos los consumos de un cliente");
        contarTitulo("2) Consumo de una fecha especifica");
        contarTitulo("ESC) Volver al menu anterior");
        imprimirTecho(ANCHO);

        opcion = getch();
        Beep(400, 300);
        system("cls");

        switch (opcion)
            {
            case '1':
                printConClients(AR_CONSUM, AR_CLIENTS);
                break;
            case '2':
                searchConDate(AR_CONSUM, AR_CLIENTS);
                break;
            case 27:
                break;
            default:
                errorMessagge(">>>[ERROR]<<< INGRESO UNA OPCION NO VALIDA");
                getch();
                break;
            }
        }
}
