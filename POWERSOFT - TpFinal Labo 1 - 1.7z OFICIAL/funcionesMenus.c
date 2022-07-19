#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

#include "funcionesMenus.h"
#include "centrarTitulos.h"
#include "Menu.h"
#include "stEmpleados.h"
#include "gotoxy.h"


#define archivoEmpleados "ARCHIVO_EMPLEADO.DAT"


#define ANCHO 118
#define DIM 50


void mostrarMenuLogueo()
{
    int opcion = 0;
    int eleccionLogueo = 0;
    int eleccionOpcion = 0;
    int buscaPorId = 0, buscaPorEstado = 0;
    char buscaPorDni [12];
    char buscaPorApellido[DIM];
    char buscaPorNombre[DIM];
    char buscaPorTelefono[12];
    char buscaPorMail [45];
    char verificarUsu[DIM];
    char usuAdmin [DIM] = "admin";
    char usuEmpleado1 [DIM] = "aguera";
    char usuEmpleado2 [DIM] = "lochocki";
    char usuEmpleado3 [DIM] = "tambascia";
    char usuEmpleado4 [DIM] = "blanco";



    while (opcion != 27)
    {
        system("cls");
        hidecursor(0);
        system("COLOR 07");
        imprimirTecho(ANCHO);
        contarTitulo("SISTEMA DE GESTION POWERSOFT");
        imprimirTecho(ANCHO);
        contarTitulo("INGRESE EL NUMERO DEL USUARIO CON EL QUE SE QUIERE LOGUEAR");
        imprimirTecho(ANCHO);
        contarTitulo("1- LOGUARSE COMO ADMIN.");
        contarTitulo("2- LOGUEARSE COMO EMPLEADO.");
        contarTitulo("ESC) SALIR");
        imprimirTecho(ANCHO);

        eleccionLogueo = getch();
        Beep(400, 300);
        system("cls");

        switch(eleccionLogueo)
        {
        case '1':
            imprimirTecho(ANCHO);
            contarTitulo("LOGUEO DE ADMIN");
            imprimirTecho(ANCHO);
            contarTitulo("INGRESE NOMBRE DE USUARIO: ");
            imprimirTecho(ANCHO);
            fflush(stdin);
            gets(verificarUsu);
            system("cls");
            Beep(400, 300);

            if(strcmp(verificarUsu, usuAdmin) == 0)
            {
                system("COLOR 0B");
                errorMessagge("USUARIO LOGUEADO CORRECTAMENTE");
                getch();
                while(eleccionLogueo != 3)
                {
                    system("cls");
                    printInMarg("POWERSOFT - EMPLEADOS");
                    contarTitulo("ELIJA UNA OPCION:");
                    contarTitulo("1- ALTA DE EMPLEADO.");
                    contarTitulo("2- BAJA DE EMPLEADO.");
                    contarTitulo("3- MODIFICACION DE EMPLEADO.");
                    contarTitulo("4- CONSULTA DE EMPLEADO.");
                    contarTitulo("ESC- IR HACIA ATRAS.");
                    imprimirTecho(ANCHO);

                    eleccionOpcion = getch();
                    Beep(400, 300);
                    system("cls");

                    switch(eleccionOpcion)
                    {
                    case '1':
                        system("cls");
                        imprimirTecho(ANCHO);
                        contarTitulo("1- ALTA DE EMPLEADO.");
                        imprimirTecho(ANCHO);
                        cargarArchivoEmpleado(archivoEmpleados);
                        break;
                    case '2':
                        imprimirTecho(ANCHO);
                        contarTitulo("2- BAJA DE EMPLEADO.");
                        imprimirTecho(ANCHO);
                        contarTitulo("INDIQUE COMO DESEA BUSCAR AL EMPLEADO: ");
                        contarTitulo("1- BUSCAR POR ID.");
                        contarTitulo("2- BUSCAR POR DNI.");
                        contarTitulo("3- BUSCAR POR APELLIDO.");
                        imprimirTecho(ANCHO);
                        eleccionOpcion = getch();
                        Beep(400, 300);
                        system("cls");

                        switch(eleccionOpcion)
                        {
                        case '1':
                            imprimirTecho(ANCHO);
                            contarTitulo("INGRESE ID: ");
                            imprimirTecho(ANCHO);
                            fflush(stdin);
                            scanf("%i", &buscaPorId);
                            buscarporDatoInt(archivoEmpleados, buscaPorId);
                            imprimirTecho(ANCHO);
                            printf("\n");
                            modificarEstadoxId(archivoEmpleados, buscaPorId);
                            system("pause");
                            break;
                        case '2':
                            imprimirTecho(ANCHO);
                            contarTitulo("INGRESE DNI: ");
                            imprimirTecho(ANCHO);
                            fflush(stdin);
                            scanf("%s", &buscaPorDni);
                            buscarPorDni(archivoEmpleados, buscaPorDni);
                            imprimirTecho(ANCHO);
                            printf("\n");
                            modificarEstadoxDni(archivoEmpleados,buscaPorDni);
                            system("pause");
                            break;
                        case '3':
                            imprimirTecho(ANCHO);
                            contarTitulo("INGRESE APELLIDO: ");
                            imprimirTecho(ANCHO);
                            fflush(stdin);
                            scanf("%s", &buscaPorApellido);
                            buscarPorApellido(archivoEmpleados, buscaPorApellido);
                            imprimirTecho(ANCHO);
                            printf("\n");
                             modificarEstadoxApellido(archivoEmpleados,buscaPorApellido);
                             system("pause");

                        break;
                            default:
                                contarTitulo("OPCION INCORRECTA O INVALIDA.");
                        }
                        break;
                    case '3':
                        imprimirTecho(ANCHO);
                        contarTitulo("3- MODIFICACION DE EMPLEADO.");
                        imprimirTecho(ANCHO);
                        contarTitulo("INDIQUE COMO DESEA BUSCAR AL EMPLEADO: ");
                        contarTitulo("1- BUSCAR POR DNI.");
                        contarTitulo("2- BUSCAR POR APELLIDO.");
                        contarTitulo("3- BUSCAR POR ID.");
                        imprimirTecho(ANCHO);
                        eleccionOpcion = getch();
                        Beep(400, 300);
                        system("cls");

                        switch(eleccionOpcion)
                        {
                        case '1':
                            imprimirTecho(ANCHO);
                            contarTitulo("INGRESE DNI: ");
                            imprimirTecho(ANCHO);
                            scanf("%s", &buscaPorDni);
                            buscarPorDni(archivoEmpleados, buscaPorDni);
                            imprimirTecho(ANCHO);
                            printf("\n");
                            contarTitulo("1-MODFICAR DNI: ");
                            contarTitulo("2-MODFICAR APELLIDO: ");
                            contarTitulo("3-MODFICAR NOMBRE: ");
                            contarTitulo("4-MODFICAR TELEFONO: ");
                            contarTitulo("5-MODFICAR MAIL: ");
                            imprimirTecho(ANCHO);
                            eleccionOpcion =getch();
                            switch(eleccionOpcion)
                            {
                            case '1':
                                imprimirTecho(ANCHO);
                                contarTitulo("INGRESE DNI: ");
                                imprimirTecho(ANCHO);
                                fflush(stdin);
                                scanf("%s", &buscaPorDni);
                                modificarDni(archivoEmpleados, buscaPorDni);
                                system("pause");
                                system("cls");
                                break;
                            case'2':
                                imprimirTecho(ANCHO);
                                contarTitulo("INGRESE APELLIDO: ");
                                imprimirTecho(ANCHO);
                                fflush(stdin);
                                scanf("%s", &buscaPorApellido);
                                modificarApellido(archivoEmpleados, buscaPorApellido);
                                system("pause");
                                system("cls");
                                break;
                            case '3':
                                imprimirTecho(ANCHO);
                                contarTitulo("INGRESE NOMBRE: ");
                                imprimirTecho(ANCHO);
                                fflush(stdin);
                                scanf("%s", &buscaPorNombre);
                                modificarNombre(archivoEmpleados, buscaPorNombre);
                                system("pause");
                                system("cls");
                                break;
                            case '4':
                                imprimirTecho(ANCHO);
                                contarTitulo("INGRESE TELEFONO: ");
                                imprimirTecho(ANCHO);
                                fflush(stdin);
                                scanf("%s", &buscaPorTelefono);
                                modificarTelefono(archivoEmpleados, buscaPorTelefono);
                                system("pause");
                                system("cls");
                                break;
                            case 5:
                                imprimirTecho(ANCHO);
                                contarTitulo("INGRESE MAIL: ");
                                imprimirTecho(ANCHO);
                                fflush(stdin);
                                scanf("%s", &buscaPorMail);
                                modificarMail(archivoEmpleados, buscaPorMail);
                                system("pause");
                                system("cls");
                                break;
                            default:
                                contarTitulo("OPCION INCORRECTA O INVALIDA.");
                            }
                            break;

                        case '2':
                            imprimirTecho(ANCHO);
                            contarTitulo("INGRESE APELLIDO: ");
                            imprimirTecho(ANCHO);
                            scanf("%s", &buscaPorApellido);
                            buscarPorApellido(archivoEmpleados, buscaPorApellido);
                            imprimirTecho(ANCHO);
                            printf("\n");
                            contarTitulo("1-MODFICAR DNI: ");
                            contarTitulo("2-MODFICAR APELLIDO: ");
                            contarTitulo("3-MODFICAR NOMBRE: ");
                            contarTitulo("4-MODFICAR TELEFONO: ");
                            contarTitulo("5-MODFICAR MAIL: ");
                            imprimirTecho(ANCHO);
                            eleccionOpcion =getch();

                            switch(eleccionOpcion)
                            {
                            case '1':
                                imprimirTecho(ANCHO);
                                contarTitulo("INGRESE DNI: ");
                                imprimirTecho(ANCHO);
                                fflush(stdin);
                                scanf("%s", &buscaPorDni);
                                modificarDni(archivoEmpleados, buscaPorDni);
                                system("pause");
                                system("cls");
                                break;
                            case'2':
                                imprimirTecho(ANCHO);
                                contarTitulo("INGRESE APELLIDO: ");
                                imprimirTecho(ANCHO);
                                fflush(stdin);
                                scanf("%s", &buscaPorApellido);
                                modificarApellido(archivoEmpleados, buscaPorApellido);
                                system("pause");
                                system("cls");
                                break;
                            case '3':
                                imprimirTecho(ANCHO);
                                contarTitulo("INGRESE NOMBRE: ");
                                imprimirTecho(ANCHO);
                                fflush(stdin);
                                scanf("%s", &buscaPorNombre);
                                modificarNombre(archivoEmpleados, buscaPorNombre);
                                system("pause");
                                system("cls");
                                break;
                            case '4':
                                imprimirTecho(ANCHO);
                                contarTitulo("INGRESE TELEFONO: ");
                                imprimirTecho(ANCHO);
                                fflush(stdin);
                                scanf("%s", &buscaPorTelefono);
                                modificarTelefono(archivoEmpleados, buscaPorTelefono);
                                system("pause");
                                system("cls");
                                break;
                            case 5:
                                imprimirTecho(ANCHO);
                                contarTitulo("INGRESE MAIL: ");
                                imprimirTecho(ANCHO);
                                fflush(stdin);
                                scanf("%s", &buscaPorMail);
                                modificarMail(archivoEmpleados, buscaPorMail);
                                system("pause");
                                system("cls");
                                break;
                            default:
                                contarTitulo("OPCION INCORRECTA O INVALIDA.");
                            }

                            break;

                        case '3':
                            imprimirTecho(ANCHO);
                            contarTitulo("INGRESE ID: ");
                            imprimirTecho(ANCHO);
                            scanf("%i", &buscaPorId);
                            buscarporDatoInt(archivoEmpleados, buscaPorId);
                            imprimirTecho(ANCHO);
                            printf("\n");
                            contarTitulo("1-MODFICAR DNI: ");
                            contarTitulo("2-MODFICAR APELLIDO: ");
                            contarTitulo("3-MODFICAR NOMBRE: ");
                            contarTitulo("4-MODFICAR TELEFONO: ");
                            contarTitulo("5-MODFICAR MAIL: ");
                            imprimirTecho(ANCHO);
                            eleccionOpcion =getch();
                            switch(eleccionOpcion)
                            {
                            case '1':
                                imprimirTecho(ANCHO);
                                contarTitulo("INGRESE DNI: ");
                                imprimirTecho(ANCHO);
                                fflush(stdin);
                                scanf("%s", &buscaPorDni);
                                modificarDni(archivoEmpleados, buscaPorDni);
                                system("pause");
                                system("cls");
                                break;
                            case'2':
                                imprimirTecho(ANCHO);
                                contarTitulo("INGRESE APELLIDO: ");
                                imprimirTecho(ANCHO);
                                fflush(stdin);
                                scanf("%s", &buscaPorApellido);
                                modificarApellido(archivoEmpleados, buscaPorApellido);
                                system("pause");
                                system("cls");
                                break;
                            case '3':
                                imprimirTecho(ANCHO);
                                contarTitulo("INGRESE NOMBRE: ");
                                imprimirTecho(ANCHO);
                                fflush(stdin);
                                scanf("%s", &buscaPorNombre);
                                modificarNombre(archivoEmpleados, buscaPorNombre);
                                system("pause");
                                system("cls");
                                break;
                            case '4':
                                imprimirTecho(ANCHO);
                                contarTitulo("INGRESE TELEFONO: ");
                                imprimirTecho(ANCHO);
                                fflush(stdin);
                                scanf("%s", &buscaPorTelefono);
                                modificarTelefono(archivoEmpleados, buscaPorTelefono);
                                system("pause");
                                system("cls");
                                break;
                            case 5:
                                imprimirTecho(ANCHO);
                                contarTitulo("INGRESE MAIL: ");
                                imprimirTecho(ANCHO);
                                fflush(stdin);
                                scanf("%s", &buscaPorMail);
                                modificarMail(archivoEmpleados, buscaPorMail);
                                system("pause");
                                system("cls");
                                break;
                            default:
                                contarTitulo("OPCION INCORRECTA O INVALIDA.");
                            }
                            break;

                        default:
                            contarTitulo("OPCION INCORRECTA O INVALIDA.");
                            contarTitulo("TOQUE CUALQ. TECLA PARA IR HACIA ATRAS");
                            getch();
                        }
                        break;
                    case '4':
                        imprimirTecho(ANCHO);
                        contarTitulo("4- CONSULTA DE EMPLEADO.");
                        contarTitulo("INDIQUE COMO DESEA BUSCAR AL EMPLEADO: ");
                        imprimirTecho(ANCHO);
                        contarTitulo("1- BUSCAR POR ID.");
                        contarTitulo("2- BUSCAR POR DNI.");
                        contarTitulo("3- BUSCAR POR APELLIDO.");
                        contarTitulo("4- BUSCAR POR ESTADO.");
                        contarTitulo("5- MOSTRAR TODOS LOS EMPLEADOS.");
                        contarTitulo("ESC- IR HACIA ATRAS");
                        imprimirTecho(ANCHO);

                        eleccionOpcion = getch();
                        Beep(400, 300);
                        system("cls");
                        switch(eleccionOpcion)
                        {
                        case '1':
                            imprimirTecho(ANCHO);
                            contarTitulo("INGRESE ID: ");
                            imprimirTecho(ANCHO);
                            scanf("%i", &buscaPorId);
                            buscarporDatoInt(archivoEmpleados, buscaPorId);
                            system("pause");
                            system("cls");
                            break;
                        case '2':
                            imprimirTecho(ANCHO);
                            contarTitulo("INGRESE DNI: ");
                            imprimirTecho(ANCHO);
                            scanf("%s", &buscaPorDni);
                            buscarPorDni(archivoEmpleados, buscaPorDni);
                            system("pause");
                            system("cls");
                            break;
                        case '3':
                            imprimirTecho(ANCHO);
                            contarTitulo("INGRESE APELLIDO: ");
                            scanf("%s",&buscaPorApellido);
                            buscarPorApellido(archivoEmpleados,buscaPorApellido);
                            system("pause");
                            system("cls");
                            break;
                        case '4':
                            imprimirTecho(ANCHO);
                            contarTitulo("INGRESE ESTADO: ");
                            imprimirTecho(ANCHO);
                            scanf("%i", &buscaPorEstado);
                            buscarPorEstado(archivoEmpleados, buscaPorEstado);
                            system("pause");
                            system("cls");
                            break;
                        case '5':
                            mostrarArchivoEmpleado(archivoEmpleados);
                            getch();
                            break;
                        case 27:
                            break;
                        default:
                            errorMessagge("OPCION NO DISPONIBLE O INCORRECTA");
                            getch();
                        }
                        break;
                    case 27:
                        eleccionLogueo = 3;
                        break;
                    default:
                        errorMessagge("OPCION NO DISPONIBLE O INCORRECTA");
                        getch();
                    }
                }
            }
            else
            {
                system("cls");
                errorMessagge("USUARIO INEXISTENTE O INCORRECTO");
                getch();
            }
            break;
        case '2':
            printInMarg("LOGUEO DE EMPLEADO");
            contarTitulo("Por favor, ingrese el nombre de usuario ");
            imprimirTecho(ANCHO);
            printf("\n\n\n");
            printf("\t\t\t\t\t\t       ");
            fflush(stdin);
            gets(verificarUsu);
            system("cls");
            Beep(400, 300);

            if(strcmp(verificarUsu, usuEmpleado1) == 0 || strcmp(verificarUsu, usuEmpleado2) == 0 || strcmp(verificarUsu, usuEmpleado3) == 0 || strcmp(verificarUsu, usuEmpleado4) == 0)
            {
                system("COLOR 0E");
                errorMessagge("USUARIO LOUGUEADO CORRECTAMENTE");
                getch();
                mainMenu();
                eleccionLogueo = 0;
            }
            else
            {
                system("cls");
                errorMessagge("EL USUARIO INGRESADO NO EXISTE");
                getch();
            }
            break;
        case 27:
            opcion = 27;
            break;
        default:
            errorMessagge("OPCION NO DISPONIBLE O INCORRECTA");
            getch();
        }
    }

    int i = 0;

    printInMarg("Miembros del TP final Laboratorio 1");
    contarTitulo("Blanco Mariano     Tambascia Jessica");
    contarTitulo("Aguera Gonzalo      Lochocki Gonzalo");
    imprimirTecho(ANCHO);
    contarTitulo("GRACIAS POR UTILIZAR NUESTRO PROGRAMA :D");
    printInMarg("PRESIONE CUALQUIER TECLA PARA SALIR");

    while (!kbhit())
    {

        if (i)
        {
            system("COLOR 0E");
            i = 0;
        }
        else
        {
            system("COLOR E0");
            i = 1;
        }
        Beep(800,350);
        Beep(400,350);
        Sleep(400);
    }

}
