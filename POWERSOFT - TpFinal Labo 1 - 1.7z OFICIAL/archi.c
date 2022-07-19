#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <windows.h>


#include "archi.h"
#include "clientes.h"
#include "Menu.h"
#include "consumos.h"
#include "centrarTitulos.h"


#define ANCHO 118
#define CANT 50




/** \brief Carga un cliente en un archivo.
 *
 * \param Nombre del archivo
 * \return No return
 *
 */
void loadArchivoClient (char archivo[])
{
    ///Abro el archivo en modo lectura y escritura.
    FILE *clients = fopen(archivo, "a+b");

    ///Creo variables que voy a utilizar.
    CLI c;

    int id;

    char opcion = 0;
    char agregar;

    ///Si el archivo abrio correctamente prosigo con la carga del cliente.
    if (clients)
        {
        ///Retorno el ultimo id cargado para autoincrementarlo.
        id = searchEndId(archivo);
        while (opcion != 27)
            {
            ///Ingreso el DNI del cliente que quiero cargar.
            system("cls");
            recuadro("CARGANDO EL CLIENTE");
            printf("\n>>> Ingrese el D.N.I.......: ");
            fflush(stdin);
            gets(c.dni);

            ///Si el DNI no se encuentra verifyDniInFile() retorna 0 y sigue con la carga normal.
            if (!verifyDniInFile(clients, c.dni))
                {
                ///Incremento el ID, se lo asigno al cliente y lo doy de alta.
                id++;
                c.id = id;
                c.baja = 0;

                ///Cargo los datos
                c = loadOneClient(c);
                system("cls");

                ///Le muestro al usuario por pantalla lo que cargo y le pregunto si desea cargarlo.
                recuadro("Desea ingresar este cliente? S/N");
                printOneClient(c);
                fflush(stdin);
                agregar = getch();
                system("cls");

                ///Si el usuario toca el boton 'S' le aviso al usuario que el cliente se cargo y le muestro los datos.
                if(agregar == 's' || agregar == 'S')
                    {
                    fwrite(&c, sizeof(CLI), 1, clients);
                    recuadro("CLIENTE DADO DE ALTA");
                    printOneClient(c);
                    }
                ///Si apreto otro boton diferente le aviso al usuario que el cliente no se cargo y muestro los datos.
                else
                    {
                    recuadro("NO SE DIO DE ALTA EL CLIENTE");
                    printOneClient(c);
                    id--;
                    }
                }
            ///Si verifyDniInFile() retorna 1 quiere decir que el cliente existe y el cursor quedo un registro siguiente a la del cliente existente.
            else
                {
                system("cls");

                ///Muevo el cursor un registro anterior para leer el cliente existente.
                fseek(clients, -1*sizeof(CLI), SEEK_CUR);
                fread(&c, sizeof(CLI), 1, clients);

                ///Lo muestro por pantalla.
                recuadro("CLIENTE YA CARGADO");
                printOneClient(c);
                }

            ///Le pregunto al ususario si quiere seguir cargando clientes
            printf("\n\nPresione [ESC] para salir o cualquier tecla para ingresar otro cliente---");
            opcion = getch();
            }
        }
    ///Si el archivo no abrio doy aviso de error por pantalla.
    else
        {
        errorMessagge(">>>[ERROR]<<< OCURRIO UN FALLO AL ABRIR EL ARCHIVO");
        getch();
        }

    ///Cierro el archivo para guardar cambios.
    fclose(clients);
}





/** \brief Muestra un archivo de clientes
 *
 * \param Nombre del archivo
 * \return No return
 *
 */
void printFileClients (char archivo[])
{
    ///Abro el archivo de clientes
    FILE *clients = fopen (archivo, "rb");

    CLI c;

    ///Si abrio correctamente prosigo
    if (clients)
        {

        ///Hago una lectura en la variable c (de tipo cliente), para mostrarlo por pantalla
        while (fread(&c, sizeof(CLI), 1, clients) > 0)
            {
            printOneClient(c);
            printf("\n=============================================");
            }
        }
    else
        {
        ///Si el archivo no se abrio doy aviso al usuario por pantalla.
        errorMessagge(">>>[ERROR]<<< OCURRIO UN FALLO AL ABRIR EL ARCHIVO");
        }

    ///Cierro el archivo para guardar cambios.
    fclose(clients);

    getch();
}





/** \brief Verifica si un ID se encuentra en el archivo
 *
 * \param Puntero a una estructura FILE
 * \param El ID que desea buscar
 * \return Flag (1 si se encontro, 0 si no existe)
 *
 */
int verifyIdInFile (FILE *archivo, int id)
{
    ///Muevo el cursor al principio del archivo
    rewind(archivo);

    CLI c;

    int flag = 0;

        ///Mientras que flag sea 0 y sigan habiendo datos para leer recorro
        while (!flag && fread(&c, sizeof(CLI), 1, archivo) > 0)
            {
            ///Si el cliente tiene el mismo ID que el que le mande por parametro, flag cambia a 1 y corta el ciclo de lectura
            if (c.id == id)
                {
                flag = 1;
                }
            }

    ///Retorno el resultado de la busqueda
    return flag;
}





/** \brief Verifica si un DNI enviado por parametro existe en el archivo.
 *
 * \param Puntero a una estructura FILE
 * \param El dni que se desea buscar
 * \return Flag (1 si se encontro, 0 si no existe)
 *
 */
int verifyDniInFile (FILE *clients, char dni[])
{
    ///Muevo el cursor al principio del archivo
    rewind(clients);

    CLI cAux;

    int flag = 0;

    ///Mientras flag = 0 y sigan habiendo registros, sigo leyendo.
    while (!flag && fread(&cAux, sizeof(CLI), 1, clients) > 0)
        {
        ///Si el dni del cliente coincide con el mandado por parametro, corta el ciclo y cambia el valor de flag a 1.
        if (strcmp(cAux.dni, dni) == 0)
            {
            flag = 1;
            }
        }


    ///Retorno el resultado de la busqueda
    return flag;
}





/** \brief Busca en el archivo un DNI que quiera el usuario y lo muestra por pantalla.
 *
 * \param Nombre del archivo.
 * \return No return.
 *
 */
void searchXDni (char archivo[])
{
    ///Abro el archivo en modo lectura
    FILE *clients = fopen(archivo, "rb");
    CLI c;

    ///Si se abrio correctamente prosigo con la busqueda
    if (clients)
        {
        ///Le pido al usuario que ingrese el DNI que quiera buscar
        recuadro("BUSCANDO CLIENTE POR D.N.I.");
        printf("\n>>>Ingrese el D.N.I. a buscar: ");
        fflush(stdin);
        gets(c.dni);
        system("cls");

        ///Si verifyDniInFile retorna 1 encontro al cliente y el cursor se encuentra 1 posicion adelante.
        if (verifyDniInFile(clients, c.dni))
            {
            ///Muevo el cursor 1 posicion atras y hago nuevamente la lectura en la variable c.
            fseek(clients, -1*sizeof(CLI), SEEK_CUR);
            fread(&c, sizeof(CLI), 1, clients);

            ///Muestro por pantalla al cliente buscado con ese D.N.I.
            recuadro("CLIENTE ENCONTRADO");
            printOneClient(c);
            }
        else
            {
            ///Si verifyDniInFile retorno 0 el cliente no existe y le aviso al usuario por pantalla.
            errorMessagge(">>>[ERROR]<<< NO EXISTE NINGUN CLIENTE CON ESE D.N.I.");
            }
        }
    else
        {
        ///Si el archivo no abrio correctamente doy aviso al usuario por pantalla.
        errorMessagge(">>>[ERROR]<<< OCURRIO UN FALLO AL ABRIR EL ARCHIVO");
        }


    ///Cierro el archivo para guardar los cambios.
    fclose(clients);

    getch();
}





/** \brief Busca en el archivo un cliente por ID y lo muestra por pantalla
 *
 * \param Nombre del archivo
 * \return No return
 *
 */
void searchXId (char archivo[])
{
    ///Abro el archivo en modo lectura.
    FILE *clients = fopen(archivo, "rb");
    CLI c;

    ///Si el archivo abrio correctamente prosigo con la busqueda.
    if (clients)
        {
        ///Le pido al usuario que ingrese el ID que desea buscar.
        recuadro("BUSCANDO CLIENTE POR ID");
        printf("\n>>>Ingrese el ID del cliente: ");
        scanf("%d", &c.id);
        system("cls");

        ///Si existe la funcion verifyIdInFile retorna 1 y el cursor queda un registro siguiente a la del cliente encontrado.
        if (verifyIdInFile(clients, c.id))
                {
                ///Muevo el cursor un registro anterior para hacer denuevo la lectura.
                fseek(clients, -1*sizeof(CLI), SEEK_CUR);
                fread(&c, sizeof(CLI), 1, clients);

                ///Muestro el cliente por pantalla.
                recuadro("CLIENTE ENCONTRADO");
                printOneClient(c);
                }
            else
                {
                ///Si verifiIdInFile retorna 0 el cliente no existe y le aviso al usuario por pantalla.
                errorMessagge(">>>[ERROR]<<< NO EXISTE NINGUN CLIENTE CON ESE ID");
                }
        }
    else
        {
        ///Si el archivo no abrio doy un mensalle de error por pantalla.
        errorMessagge(">>>[ERROR]<<< OCURRIO UN FALLO AL ABRIR EL ARCHIVO");
        }


    ///Cierro el archivo para guardar cambios.
    fclose(clients);

    getch();
}






/** \brief Busca en el archivo clientes por el nombre y los muestra por pantalla
 *
 * \param Nombre del archivo
 * \return No return
 *
 */
void searchXName (char archivo[])
{
    ///Abro el archivo en modo lectura.
    FILE *clientes = fopen(archivo, "rb");

    ///Creo variables que voy a usar.
    CLI c;

    int flag = 0;
    char name[50];

    ///Si el archivo abrio correctamente prosigo con la busqueda.
    if (clientes)
        {
        ///Le pido al usuario que ingrese el nombre del cliente que quiera buscar.
        recuadro("BUSCANDO CLIENTE POR NOMBRE");
        printf("\n>>>Ingrese el nombre del cliente: ");
        fflush(stdin);
        gets(name);
        system("cls");

        ///Hago una portada de "CLIENTES CON ESE NOMBRE" para mostrarselo al usuario
        recuadro("CLIENTES CON ESE NOMBRE");
        ///Hago la lectura del archivo,
        while (fread(&c, sizeof(CLI), 1, clientes) > 0)
            {
            ///Si el nombre del cliente coincide con el nombre que ingreso el usuario flag=1 y los muestro por pantalla
            if (strcmpi(c.name, name) == 0)
                {
                flag = 1;
                printOneClient(c);
                printf("\n======================================================");
                }
            }
            ///En caso de que flag=0 quiere decir que no existia ningun cliente con ese nombre y doy aviso por pantalla.
        if (!flag)
            {
            system("cls");
            errorMessagge(">>>[ERROR]<<< NO EXISTE NINGUN CLIENTE CON ESE NOMBRE");
            }
        }
    else
        {
        ///Si el archivo no se abrio doy un mensaje de error por pantalla.
        errorMessagge(">>>[ERROR]<<< OCURRIO UN FALLO AL ABRIR EL ARCHIVO");
        }

    ///Cierro el archivo para guardar cambios.
    fclose(clientes);

    getch();
}




/** \brief Busca en el archivo clientes por apellido y los muestra por consola
 *
 * \param Nombre del archivo
 * \return No return
 *
 */
void searchXSurname (char archivo[])
{
    ///Abro el archivo en modo lectura.
    FILE *clients = fopen(archivo, "rb");

    ///Creo variables que voy a usar.
    CLI c;

    int flag = 0;
    char surname[50];

    ///Si el archivo abrio correctamente prosigo con la busqueda.
    if (clients)
        {
        ///Le pido al usuario el apellido del cliente que desea buscar.
        recuadro("BUSCANDO CLIENTE POR APELLIDO");
        printf("\n>>>Ingrese el apellido del cliente: ");
        fflush(stdin);
        gets(surname);
        system("cls");

        ///Hago una portada de "CLIENTES CON ESE APELLIDO" y lo muestro por pantalla.
        recuadro("CLIENTES CON ESE APELLIDO");

        ///Hago la lectura de los clientes.
        while (fread(&c, sizeof(CLI), 1, clients) > 0)
            {
            ///Si el apellido del cliente coincide con el apellido ingresado por el usuario flag=1 y muestro el cliente por pantalla.
            if (strcmpi(c.apellido, surname) == 0)
                {
                flag = 1;
                printOneClient(c);
                printf("\n====================================================");
                }
            }
        ///Si flag=0 quiere decir que no habia un cliente con ese apellido y doy aviso por pantalla.
        if (!flag)
            {
            system("cls");
            errorMessagge(">>>[ERROR]<<< NO EXISTE NINGUN CLIENTE CON ESE APELLIDO");
            }
        }
    ///Si el archivo no se abrio doy un mensaje de error por pantalla.
    else
        {
        errorMessagge(">>>[ERROR]<<< OCURRIO UN FALLO AL ABRIR EL ARCHIVO");
        }

    ///Cierro el archivo para guardar cambios.
    fclose(clients);

    getch();
}


/** \brief Busca en el archivo un cliente por numero de celular y lo muestra por pantalla
 *
 * \param Nombre del archivo
 * \return No return
 *
 */
void searchXMobile (char archivo[])
{
    ///Abro el archivo en modo lectura.
    FILE *clients = fopen(archivo, "rb");

    ///Creo variables que voy a usar.
    CLI c;

    char numberPhone[50];
    int flag = 0;

    ///Si el archivo abrio correctamente prosigo con la busqueda del cliente.
    if (clients)
        {
        ///Le pido al ususario el celular del cliente que desea buscar.
        recuadro("BUSCANDO CLIENTE POR Nro DE CELULAR");
        printf("\n>>>Ingrese el celular a buscar: ");
        fflush(stdin);
        gets(numberPhone);
        system("cls");

        ///Hago la lectura de los clientes mientras que flag=0 y sigan habiendo clientes para leer.
        while (!flag && fread(&c, sizeof(CLI), 1 ,clients))
            {
            ///Si el celular del cliente es igual al del ingresado por el usuario flag=1 y corta el ciclo.
            if (strcmp(c.celular, numberPhone) == 0)
                {
                flag = 1;
                }
            }

        ///Si flag=1 el cliente existe y lo muestro por pantalla.
        if (flag)
            {
            recuadro("CLIENTE ENCONTRADO");
            printOneClient(c);
            }
        ///Si flag=0 el cliente no existe y doy aviso de error por pantalla.
        else
            {
            errorMessagge(">>>[ERROR]<<< NO EXISE NINGUN CLIENTE CON ESE NUMERO DE CELULAR");
            }
        }
    ///Si el archivo no se abrio doy aviso de error por pantalla.
    else
        {
        errorMessagge(">>>[ERROR]<<< OCURRIO UN FALLO AL ABRIR EL ARCHIVO");
        }

    ///Cierro el archivo para guardar cambios.
    fclose(clients);

    getch();
}




/** \brief Busca en el archivo el ID del cliente en el ultimo registro y lo retorna
 *
 * \param Nombre del archivo
 * \return ID del cliente en el ultimo registro
 *
 */
int searchEndId (char archivo [])
{
    ///Abro el archivo en modo lectura.
    FILE *client = fopen(archivo, "rb");

    ///Creo variables que voy a usar.
    CLI c;

    int id = 0;

    ///Si el archivo abrio correctamente prosigo con la busqueda
    if (client)
        {
        ///Muevo el cursor del archivo hasta una posicion antes del final.
        fseek(client, -1*sizeof(CLI), SEEK_END);
        ///Si hay algun cliente para leer fread devuelve un valor mayor a 0 y le asigno a la variable id el ID del cliente leido.
        ///En caso de que no haya ningun cliente para leer la variable id seguira valiendo 0.
        if(fread(&c, sizeof(CLI), 1, client) > 0)
            {
            id = c.id;
            }
        }
    ///Si el archivo no abrio doy aviso de error por pantalla.
    else
        {
        errorMessagge(">>>[ERROR]<<< OCURRIO UN FALLO AL ABRIR EL ARCHIVO");
        }

    ///Retorno el ultimo ID.
    return id;
}





/** \brief Busca en el archivo un cliente por ID y lo da de ALTA
 *
 * \param Nombre del archivo
 * \return No return
 *
 */
void regClients (char archivo[])
{
    ///Abro el archivo en modo lectura y escritura
    FILE *clients = fopen(archivo, "r+b");

    ///Creo variables que voy a usar.
    CLI c;

    char opcion;

    ///Si el archivo abrio correctamente porsigo con la busqueda.
    if (clients)
        {
        ///Le pido al usuario que ingrese el ID del cliente a buscar.
        printf(">>>Ingrese el id del cliente para dar de ALTA: ");
        scanf("%d", &c.id);
        system("cls");

        ///Si verifyIdInFile==1 el cliente existe y el cursor queda 1 registro siguiente del cliente buscado.
        if (verifyIdInFile(clients, c.id))
            {
            ///Muevo el cursor una posicion anterior y hago la lectura del cliente.
            fseek(clients, -1*sizeof(CLI), SEEK_CUR);
            fread(&c, sizeof(CLI), 1, clients);

            ///Si c.baja==1 el cliente esta dado de BAJA y muestro el cliente por pantalla.
            if (c.baja)
                {
                recuadro("CLIENTE ENCONTRADO");
                printOneClient(c);

                ///Le pregunto al usuario si desea dar de ALTA al cliente
                printf("\n\n>>>Desea dar de ALTA el cliente? (S/N)");
                opcion = getch();
                system("cls");

                ///Si presiona el boton 'S' sigue con la ALTA del cliente.
                if (opcion == 's' || opcion == 'S')
                    {
                    ///Igualo a c.baja a 0 para dar de ALTA el cliente.
                    c.baja = 0;

                    ///Muevo el cursor una posicion anterior a la del cliente buscado y modifico el estado.
                    fseek(clients, -1*sizeof(CLI), SEEK_CUR);
                    fwrite(&c, sizeof(CLI), 1, clients);

                    ///Aviso de la ALTA del cliente y le muestro el mismo por pantalla.
                    recuadro("CLIENTE DADO DE ALTA");
                    printOneClient(c);
                    }
                ///Si el usuario apreto un boton distinto de 'S' no se realiza ninguna modificacion y lo muestro por pantalla.
                else
                    {
                    recuadro("CLIENTE SIN MODIFICACION");
                    printOneClient(c);
                    }
                }
            ///Si c.baja==0 el cliente ya esta dado de alta y lo muestro por pantalla.
            else
                {
                recuadro("CLIENTE YA DADO DE ALTA");
                printOneClient(c);
                }
            }
        ///Si el ID ingresado no existe doy aviso de error por pantalla.
        else
            {
            errorMessagge(">>>[ERROR]<<< NO EXISTE NINGUN CLIENTE CON ESE ID");
            }
        }
    ///Si el archivo no abrio doy aviso de error por pantalla.
    else
        {
        errorMessagge(">>>[ERROR]<<< OCURRIO UN FALLO AL ABRIR EL ARCHIVO");
        }

    ///Cierro el archivo para guardar cambios.
    fclose(clients);

    getch();

}





/** \brief Muestra del archivo los clientes dados de alta
 *
 * \param Nombre del archivo
 * \return No return
 *
 */
void printRegClients (char archivo[])
{
    ///Abro el archivo en modo lectura.
    FILE *clients = fopen(archivo, "rb");

    ///Creo variables que voy a utilizar
    CLI c;

    int flag = 0;

    ///Si el archivo abrio correctamente prosigo con la muestra de clientes.
    if (clients)
        {
        ///Hago la lectura del archivo hasta que fread devuelva 0.
        while (fread(&c, sizeof(CLI), 1, clients) > 0)
            {
            ///Si c.baja==0 el cliente que leyo esta dado de alta, el valor de flag=1 y lo muestra por pantalla.
            if (!c.baja)
                {
                flag = 1;
                printOneClient(c);
                printf("\n====================================================");
                }
            }

        ///Si flag==0 no encontro ningun cliente y doy aviso de error por pantalla.
        if (!flag)
            {
            errorMessagge(">>>[ERROR]<<< NO EXISTE NINGUN CLIENTE DADO DE ALTA");
            }
        }
    ///Si el archivo no se abrio doy aviso de error por pantalla.
    else
        {
        errorMessagge(">>>[ERROR]<<< OCURRIO UN FALLO AL ABRIR EL ARCHIVO");
        }

    ///Cierro el archivo para guardar cambios.
    fclose(clients);

    getch();
}




/** \brief Busca en el archivo un cliente por su ID y lo da de BAJA
 *
 * \param Nombre del archivo
 * \return No return
 *
 */
void deregClient (char archivo[])
{
    ///Abro el archivo en modo lectura y escritura.
    FILE *clients = fopen(archivo, "r+b");

    ///Creo las variables que voy a utilizar.
    CLI c;
    char opcion = 0;

    ///Si el archivo abrio prosigo con la busqueda.
    if (clients)
        {
        ///Le pido al usuario que ingrese el ID del cliente para dar de BAJA.
        recuadro("BAJA DE UN CLIENTE");
        printf("\n>>>Ingrese el ID del cliente para dar de BAJA: ");
        scanf("%d", &c.id);
        system("cls");

        ///Si verifyIdInFile==1 encontro al cliente y el cursor esta un registro siguiente del cliente buscado.
        if (verifyIdInFile(clients, c.id))
            {
            ///Muevo el cursor un registro anterior y hago la lectura del cliente buscado.
            fseek(clients, -1*sizeof(CLI), SEEK_CUR);
            fread(&c, sizeof(CLI), 1, clients);

            ///Si c.baja==0 el cliente esta dado de ALTA y sigo con la BAJA del cliente.
            if (!c.baja)
                {
                ///Muestro por pantalla el cliente buscado.
                recuadro("CLIENTE ENCONTRADO");
                printOneClient(c);

                ///Le pregunto al usuario si realmente desea dar de BAJA el cliente.
                printf("\n\n>>>Desea dar de BAJA este cliente? (S/N)");
                fflush(stdin);
                opcion = getch();
                system("cls");

                ///Si presiono el boton 'S' sigue con la BAJA.
                if (opcion == 's' || opcion == 'S')
                    {
                    ///A c.baja le doy el valor de 1.
                    c.baja = 1;

                    ///Muevo el cursor un registro anterior y hago la modificacion del estado del cliente.
                    fseek(clients, -1*sizeof(CLI), SEEK_CUR);
                    fwrite(&c, sizeof(CLI), 1, clients);

                    ///Muestro por pantalla el cliente con la modificacion del estado.
                    recuadro("CLIENTE DADO DE BAJA");
                    printOneClient(c);
                    }
                ///Si el usuario no presiono 'S' doy aviso de que no hubo modificacion y muestro el cliente por pantalla.
                else
                    {
                    recuadro("CLIENTE SIN MODIFICACION");
                    printOneClient(c);
                    }
                }
            ///Si c.baja==1 el cliente ya esta dado de BAJA y lo muestro por pantalla
            else
                {
                recuadro("CLIENTE YA DADO DE BAJA");
                printOneClient(c);
                }
            }
        ///Si verifyIdInFile==0 el cliente no existe y doy aviso de error por pantalla.
        else
            {
            errorMessagge(">>>[ERROR]<<< NO EXISTE UN CLIENTE CON ESE ID");
            }

        }
    ///Si el archivo no abrio doy aviso de error por pantalla.
    else
        {
        errorMessagge(">>>[ERROR]<<< OCURRIO UN FALLO AL ABRIR EL ARCHIVO");
        }

    ///Cierro el archivo para guardar cambios.
    fclose(clients);

    getch();
}





/** \brief Muestra del archivo los clientes dados de BAJA
 *
 * \param Nombre del archivo
 * \return No return
 *
 */
void printDeregClients (char archivo[])
{
    ///Abro el archivo en modo lectura.
    FILE *clients = fopen(archivo, "rb");

    ///Creo variables que voy a utilizar.
    CLI c;
    int flag = 0;

    ///Si el archivo abrio correctamente prosigo con la muestra.
    if (clients)
        {
        ///Hago la lectura del archivo hasta que no hayan mas registros
        while (fread(&c, sizeof(CLI), 1, clients) > 0)
            {
            ///Si c.baja==1 el cliente esta dado de BAJA, cambio flag=1 y muestro el cliente por pantalla.
            if (c.baja == 1)
                {
                flag = 1;
                printOneClient(c);
                printf("\n====================================================");
                }
            }
        ///Si flag==0 no hay ningun cliente dado de BAJA y doy aviso de error por pantalla.
        if (!flag)
            {
            errorMessagge(">>>[ERROR]<<< NO HAY NINGUN CLIENTE DADO DE BAJA");
            }
        }
    ///Si el archivo no abrio doy aviso de error por pantalla.
    else
        {
        errorMessagge(">>>[ERROR]<<< OCURRIO UN FALLO AL ABRIR EL ARCHIVO");
        }

    ///Cierro el archivo para guardar cambios.
    fclose(clients);

    getch();
}






/** \brief Busca en el archivo un cliente por ID y modifica sus datos
 *
 * \param Nombre del archivo
 * \return No return
 *
 */
void customClient (char archivo[])
{
    ///Abro el archivo en modo lectura y escritura.
    FILE *clients = fopen(archivo, "r+b");

    ///Creo variables que voy a utilizar.
    CLI c;

    char opcion = 0;

    ///Si el archivo abrio correctamente prosigo con la busqueda.
    if (clients)
        {
        ///Le pido al usuario que ingrese el ID del cliente a buscar.
        recuadro("MODIFICAR CLIENTE");
        printf("\n>>>Ingrese el ID del cliente a modificar: ");
        scanf("%d", &c.id);
        system("cls");

        ///Si verifyIdInFile==1 encontro al cliente y el cursor se encuentra un registro siguiente del cliente buscado.
        if (verifyIdInFile(clients, c.id))
            {
            ///Muevo el cursor un registro anterior y hago la lectura del cliente.
            fseek(clients, -1*sizeof(CLI), SEEK_CUR);
            fread(&c, sizeof(CLI), 1, clients);

            ///Muestro por pantalla el cliente buscado.
            recuadro("CLIENTE ENCONTRADO");
            printOneClient(c);

            ///Le pregunto al usuario si desea modificar los datos del cliente.
            printf("\n\n>>>Desea modificar los datos del cliente? (S/N)");
            opcion = getch();
            system("cls");

            ///Si el usuario presiono el boton 'S' prosigo con la modificacion.
            if (opcion == 's' || opcion == 'S')
                {
                ///Muestro por pantalla que ya se estan modificando los datos.
                recuadro("MODIFICANDO CLIENTE");
                printf("\n");

                ///El usuario carga nuevamente los datos del cliente
                c = loadOneClient(c);
                system("cls");

                ///Muevo el cursor un registro anterior y hago la escritura para modificarlo.
                fseek(clients, -1*sizeof(CLI), SEEK_CUR);
                fwrite(&c, sizeof(CLI), 1, clients);

                ///Le aviso al usuario de la modificacion y muestro al cliente con los nuevos datos por pantalla.
                recuadro("CLIENTE MODIFICADO");
                printOneClient(c);
                }
            ///Si el usuario no presiono el boton 'S' el cliente no se modifica y doy aviso por pantalla.
            else
                {
                recuadro("CLIENTE SIN MODIFICACION");
                printOneClient(c);
                }
            }
        ///Si verifyDniInFile==0 el no existe un cliente con ese ID y doy aviso de error por pantalla.
        else
            {
            errorMessagge(">>>[ERROR]<<< NO EXISTE NINGUN CLIENTE CON ESE ID");
            }
        }
    ///Si el archivo no abrio doy aviso de error por pantalla.
    else
        {
        errorMessagge(">>>[ERROR]<<< OCURRIO UN FALLO AL ABRIR EL ARCHIVO");
        }

    ///Cierro el archivo para guardar cambios.
    fclose(clients);

    getch();
}





/** \brief Busca en el archivo un cliente por DNI y modifica su ID
 *
 * \param Nombre archivo CLIENTES
 * \return No return
 *
 */
void customIdClient (char archivo[])
{
    ///Abro el archivo en modo lectura y escritura.
    FILE *clients = fopen(archivo, "r+b");

    ///Creo variables que voy a utilizar
    CLI c;

    char opcion;

    ///Si abrio el archivo prosigo con la busqueda del cliente.
    if (clients)
        {
        ///Le pido al usuario el DNI del cliente que quiera modificarle el ID.
        recuadro("MODIFICAR ID");
        printf("\n\n>>> Ingrese el D.N.I. del cliente para modificar su ID: ");
        fflush(stdin);
        gets(c.dni);
        system("cls");

        ///Si verifyDniInFile==1 encontro el cliente y el cursor quedo un registro siguiente al del cliente buscado.
        if (verifyDniInFile(clients, c.dni))
            {
            ///Muevo el cursor un registro anterior y hago la lectura del cliente buscado.
            fseek(clients, -1*sizeof(CLI), SEEK_CUR);
            fread(&c, sizeof(CLI), 1, clients);

            ///Muestro por pantalla el cliente que el usuario busco.
            recuadro("CLIENTE ENCONTRADO");
            printOneClient(c);

            ///Le pregunto al usuario si esta seguro de modificar el ID de ese cliente.
            printf("\n\n>>> Desea modificar el ID(S/N)?");
            opcion = getch();
            Beep(400, 300);
            system("cls");

            ///Si el usuario presiono el boton 'S' prosigo con la modificacion.
            if (opcion == 's' || opcion == 'S')
                {
                ///Le muestro al usuario el cliente y le pido el ID al que desea cambiarlo.
                recuadro("MODIFICANDO ID");
                printOneClient(c);
                printf("\n\n>>> Ingrese el nuevo ID: ");
                scanf("%d", &c.id);
                system("cls");

                ///Muevo el cursor un registro anterior y hago una escritura para modificar el cliente.
                fseek(clients, -1*sizeof(CLI), SEEK_CUR);
                fwrite(&c, sizeof(CLI), 1, clients);

                ///Le muestro al usuario el cliente con la modificacion.
                recuadro("SE MODIFICO EL ID");
                printOneClient(c);
                }
            ///Si el usuario no presiono el boton 'S' le muestro por pantalla que no hubo modificacion.
            else
                {
                recuadro("CLIENTE SIN MODIFICACION");
                printOneClient(c);
                }
            }
        ///Si verifyDniInFile==0 el cliente con ese DNI no existe y doy aviso de error por pantalla.
        else
            {
            errorMessagge(">>>[ERROR]<<< NO EXISTE NINGUN CLIENTE CON ESE D.N.I.");
            }
        }
    ///Si el archivo no abrio doy aviso de error por pantalla.
    else
        {
        errorMessagge(">>>[ERROR]<<< OCURRIO UN FALLO AL ABRIR EL ARCHIVO");
        }

    ///Cierro el archivo para guardar cambios.
    fclose(clients);

    getch();
}






/** \brief Carga en un archivo el consumo de un cliente
 *
 * \param Nombre archivo CONSUMOS
 * \param Nombre archivo CLIENTES
 * \return No return
 *
 */
void loadConsumptions (char arCon[], char arCli[])
{
    ///Abro el archivo de consumos en modo lectura y escritura.
    FILE *consumptions = fopen(arCon, "r+b");
    ///Abro el archivo de clientes en modo lectura.
    FILE *clients = fopen(arCli, "rb");

    ///Creo variables que voy a utilizar.
    CLI cli;

    CON con;

    int reg;

    char opcion = 0;

    ///Si los archivos abrieron prosigo con la carga del consumo
    if (consumptions && clients)
        {
        ///Le asigno a reg el ultimo numero de registro cargado en el archivo de consumos.
        reg = returnEndConReg(arCon);
        ///Mientras el usuario no presione ESC sigo con la carga de consumos.
        while (opcion != 27)
            {
            ///Muevo el cursor de los archivos al principio.
            rewind(clients);
            rewind(consumptions);

            ///Le pido al usuario el ID del cliente al que quiere cargarle un consumo.
            system("cls");
            recuadro("CARGANDO CONSUMO");
            printf("\n>>> Ingrese el ID del cliente: ");
            scanf("%d", &cli.id);
            Beep(400, 300);
            system("cls");

            ///Si veryfyIdInFile==1 encontro el cliente y el cursor queda posicionado un registro siguiente a la del cliente buscado.
            if (verifyIdInFile(clients, cli.id))
                {
                ///Muevo el cursor un registro anterior y hago una lectura del cliente buscado.
                fseek(clients, -1*sizeof(CLI), SEEK_CUR);
                fread(&cli, sizeof(CLI), 1, clients);

                ///Le muestro al usuario el cliente buscado.
                recuadro("CLIENTE ENCONTRADO");
                printOneClient(cli);
                printf("\n\n");

                ///Incremento el numero del registro en 1 y se lo asigno a mi nuevo consumo.
                reg++;
                con.reg = reg;

                ///Le pido al usuario que ingrese la fecha y el consumo del usuario.
                con = loadOneCon(con, cli);
                Beep(400, 300);
                system("cls");

                ///Muestro al usuario el cliente y el consumo que va a ingresar.
                recuadro("CARGANDO CONSUMO");
                printConAndClient(cli, con);

                ///Le pregunto si realmente desea ingresar ese consumo a ese cliente.
                printf("\n\n>>>Desea ingresar el consumo (S/N)?");
                opcion = getch();
                Beep(400, 300);
                system("cls");

                ///Si presiona el boton 'S' prosigue con el ingreso
                if (opcion == 's' || opcion == 'S')
                    {
                    ///Si verifyFileCon==0 no hay otro consumo en esa fecha y sigue con el ingreso normal.
                    if (!verifyFileCon(consumptions, con))
                        {
                        ///Hago una escritura en el archivo para dejar el nuevo consumo ingresado.
                        fwrite(&con, sizeof(CON), 1, consumptions);

                        ///Le muestro al usuario que el consumo ya se cargo.
                        recuadro("SE INGRESO EL CONSUMO");
                        printConAndClient(cli, con);
                        }
                    ///Si verifyConFile==1 hay otro consumo en esa fecha y el cursor queda un registro siguiente al del consumo ya existente.
                    else
                        {
                        ///Decremento reg en 1 ya que no voy a agregar otro registro y el numero de registro queda con el de esa fecha.
                        reg--;
                        ///Agrego el consumo a esa fecha y hago la lectura de el consumo modificado.
                        loadConInDate(consumptions, con);
                        fread(&con, sizeof(CON), 1, consumptions);

                        ///Muestro por pantalla que se agrego ese consumo a uno ya existente.
                        recuadro("SE AGREGO EL CONSUMO A OTRO YA EXISTENTE");
                        printConAndClient(cli, con);
                        }
                    }
                ///Si el usuario no presiono 'S' muestro por pantalla que no se agrego el consumo.
                else
                    {
                    reg--;
                    recuadro("NO SE AGREGO EL CONSUMO");
                    printConAndClient(cli, con);
                    }
                }
            ///Si verifyIdInFile==0 el cliente con ese ID no existe y doy aviso de error por pantalla.
            else
                {
                errorMessagge(">>>[ERROR]<<< NO EXISTE NINGUN CLIENTE CON ESE ID");
                }

            ///Le pregunto al usuario si quiere seguir ingresando consumos.
            printf("\n\n\n>>>Presione [ESC] para salir o cualquier tecla para ingresar otro consumo---");
            opcion = getch();
            }
        }
    else
        {
        errorMessagge(">>>[ERROR]<<< OCURRIO UN FALLO AL ABRIR LOS ARCHIVOS");
        }

    ///Cierro el archivo de consumos para guardar cambios.
    fclose(consumptions);
    ///Cierro el archivo de clientes para guardar cambios.
    fclose(clients);

}





/** \brief Busca en el archivo el ultimo numero de registro de consumos
 *
 * \param Nombre archivo CONSUMOS
 * \return Numero del ultimo registro
 *
 */
int returnEndConReg (char archivo[])
{
    ///Abro el archivo en modo lectura.
    FILE *consumptions = fopen(archivo, "rb");

    ///Creo las variables que voy a utilizar.
    CON con;

    int reg = 0;

    ///Si el archivo abrio correctamente prosigo con la busqueda.
    if (consumptions)
        {
        ///Posiciono el cursor un registro antes del EOF.
        fseek(consumptions, -1*sizeof(CON), SEEK_END);

        ///Si fread > 0 significa que hay consumos en el archivo y le asigno a reg el numero del ultimo registro.
        ///En caso de que no existiera ningun consumo: reg==0.
        if (fread(&con, sizeof(CON), 1, consumptions) > 0)
            {
            reg = con.reg;
            }
        }
    ///Si el archivo no abrio doy aviso de error por pantalla.
    else
        {
        errorMessagge(">>>[ERROR]<<< OCURRIO UN FALLO AL ABRIR EL ARCHIVO");
        }

    ///Cierro el archivo para guardar cambios.
    fclose(consumptions);

    ///Retorno el numero del ultimo registro.
    return reg;
}





/** \brief Verifica en el archivo si un consumo ya existe
 *
 * \param Puntero a una estructura FILE
 * \param Consumo que desea verificar si existe
 * \return Flag (1 si existe, 0 si no existe)
 *
 */
int verifyFileCon (FILE *consumptions, CON con)
{
    ///Muevo el cursor del archivo al principio.
    rewind(consumptions);

    ///Creo variables que voy a utilizar.
    CON conAux;

    int flag = 0;

    ///Hago la lectura del archivo mientras flag=0 y sigan habiendo consumos para leer
    while (!flag && fread(&conAux, sizeof(CON), 1, consumptions) > 0)
        {
        ///Si verifyCon==1 el consumo ya existe, flag=1 y corto el ciclo.
        if (verifyCon(conAux, con))
            {
            flag = 1;
            }
        }

    ///Retorno el resultado de la busqueda.
    return flag;
}





/** \brief Agrega al archivo un consumo en uno ya existente
 *
 * \param Puntero a la estructura FILE
 * \param Consumo que se agregara al existente
 * \return No return
 *
 */
void loadConInDate (FILE *consumptions, CON c)
{
    ///Creo una variable consumo auxiliar para leer el consumo ya existente.
    CON cAux;

    ///Muevo el cursor un registro anterior y leo el consumo ya existente.
    fseek(consumptions, -1*sizeof(CON), SEEK_CUR);
    fread(&cAux, sizeof(CON), 1, consumptions);

    ///Le agrego al consumo nuevo, el consumo ya existente y le asigno el numero de registro tambien.
    c.megaBytes += cAux.megaBytes;
    c.reg = cAux.reg;

    ///Muevo el cursor un registro anterior y hago una escritura para modificar el consumo ya existente.
    fseek(consumptions, -1*sizeof(CON), SEEK_CUR);
    fwrite(&c, sizeof(CON), 1, consumptions);

    ///Muevo el cursor un registro anterior para dejarlo acomodado y segirlo usando en otras funciones.
    fseek(consumptions, -1*sizeof(CON), SEEK_CUR);
}


/** \brief Muestra del archivo todos los consumos de un cliente
 *
 * \param Nombre archivo CONSUMOS
 * \param Nombre archivo CLIENTES
 * \return No return
 *
 */
void printConClients (char arCon[], char arClient[])
{
    ///Abro los archivos de consumo y clientes en modo lectura.
    FILE *consumption = fopen(arCon, "rb");
    FILE *clients = fopen(arClient, "rb");

    ///Creo variables que voy a usar.
    CON con;
    CLI cli;

    int flag = 0;

    ///Si el archivo de consumos y clientes se abrieron correctamente prosigo con la muestra.
    if (consumption && clients)
        {
        ///Le pido al usuario el ID del cliente para ver sus consumos.
        recuadro("BUSCAR CONSUMOS");
        printf("\n>>>Ingrese el ID del cliente para mostrar sus consumos: ");
        scanf("%d", &cli.id);
        Beep(400, 300);
        system("cls");

        ///Si verifyIdInFile==1 el cliente existe y el cursor quedo un registro siguiente del cliente buscado.
        if (verifyIdInFile(clients, cli.id))
            {
            ///Muevo el cursor un registro anterior y hago la lectura del cliente buscado.
            fseek(clients, -1*sizeof(CLI), SEEK_CUR);
            fread(&cli, sizeof(CLI), 1, clients);

            ///Muestro por pantalla al cliente buscado.
            recuadro("CONSUMOS DEL CLIENTE");
            printOneClient(cli);


            ///Hago una lectura de los consumos mientras siga teniendo registros.
            while (fread(&con, sizeof(CON), 1, consumption) > 0)
                {
                ///Si el con.idCliente==cli.id significa que el consumo pertenece a ese cliente, asigno flag=1 y lo muestro por pantalla
                if (con.idCliente == cli.id)
                    {
                    flag = 1;
                    printf("\n_______________________________________________");
                    printOneCon(con);
                    }
                }

            ///Si flag==0 el cliente no tiene ningun consumo y doy aviso por pantalla.
            if (!flag)
                {
                printf("\n>>>El cliente no tiene ningun consumo en esa fecha");
                }

            }
        ///Si verifyIdInFile==0 el cliente con ese ID no existe y doy aviso de error por pantalla.
        else
            {
            errorMessagge(">>>[ERROR]<<< NO EXISTE NINGUN CLIENTE CON ESE ID");
            }
        }
    ///Si los archivos no abrieron doy aviso de error por pantalla.
    else
        {
        errorMessagge(">>>[ERROR]<<< OCURRIO UN FALLO AL ABRIR LOS ARCHIVOS");
        }

    ///Cierro los archivos de consumos y clientes.
    fclose(consumption);
    fclose(clients);

    getch();
}






/** \brief Busca en el archivo el consumo de un cliente en una fecha especifica y lo muestra por consola
 *
 * \param Nombre archivo CONSUMOS
 * \param Nombre archivo CLIENTES
 * \return No return
 *
 */
void searchConDate (char arCon[], char arCli[])
{
    ///Abro los archivos de consumos y clientes en modo lectura.
    FILE *consumptions = fopen(arCon, "rb");
    FILE *clients = fopen(arCli, "rb");

    ///Creo variables que voy a utilizar.
    CLI cli;

    CON con;

    ///Si los archivos abrieron correctamente prosigo con la busqueda.
    if (consumptions && clients)
        {
        ///Le pido al usuario el ID del cliente que desea buscar.
        recuadro("BUSCANDO CONSUMO");
        printf("\n>>> Ingrese el ID del cliente: ");
        scanf("%d", &cli.id);
        Beep(400, 300);
        system("cls");

        ///Si verifyIdInFile==1 el cliente se encontro y el cursor quedo un registro siguiente al del cliente buscado.
        if (verifyIdInFile(clients, cli.id))
            {
            ///Muevo el cursor un registro anterior y hago una lectura del cliente buscado.
            fseek(clients, -1*sizeof(CLI), SEEK_CUR);
            fread(&cli, sizeof(CLI), 1, clients);

            ///Muestro por pantalla el cliente.
            recuadro("CLIENTE ENCONTRADO");
            printOneClient(cli);
            printf("\n\n");
            ///Le pido al usuario la fecha del consumo que desea buscar.
            con = loadConDate(cli);
            Beep(400, 300);

            ///Si verifyFileCon==1 el consumo existe en esa fecha y el cursor queda un registro siguiente del consumo buscado.
            if (verifyFileCon(consumptions, con))
                {
                ///Muevo el cursor un registro hacia atras y hago una lectura del consumo buscado.
                fseek(consumptions, -1*sizeof(CON), SEEK_CUR);
                fread(&con, sizeof(CON), 1, consumptions);

                ///Le muestro al usuario el cliente con el consumo en esa fecha buscada.
                recuadro("CONSUMO EN LA FECHA INGRESADA");
                printConAndClient(cli, con);
                }
            ///Si verifyFileCon==0 el consumo no existe en esa fecha y doy aviso por pantalla.
            else
                {
                recuadro("EL CONSUMO EN ESA FECHA NO EXISTE");
                printOneClient(cli);
                }
            }
        ///Si verifyIdInFile==0 el cliente con ese ID no existe y doy aviso de error por pantalla.
        else
            {
            errorMessagge(">>>[ERROR]<<< NO EXISTE NINGUN CLIENTE CON ESE ID");
            }
        }
    ///Si los archivos no abrieron doy aviso de error por pantalla.
    else
        {
        errorMessagge(">>>[ERROR]<<< OCURRIO UN FALLO AL ABRIR LOS ARCHIVOS");
        }

    ///Cierro el archivo de consumos y clientes para guardar cambios.
    fclose(consumptions);
    fclose(clients);

    getch();
}





/** \brief Busca en el archivo un consumo y lo modifica.
 *
 * \param Nombre archivo CONSUMOS
 * \param Nombre archivo CLIENTES
 * \return No return
 *
 */
void customConClient (char arCon[], char arCli[])
{
    ///Abro el archivo de consumos en modo lectura y escritura.
    FILE *consumptions = fopen(arCon, "r+b");
    ///Abro el archivo de clientes en modo lectura.
    FILE *clients = fopen(arCli, "rb");

    ///Creo variables que voy a utilizar.
    CLI cli;

    CON con;

    char opcion = 0;

    ///Si los archivos se abrieron prosigo con la modificacion.
    if (consumptions && clients)
        {
        ///Le pido al usuario el ID del cliente que desea modificar su consumo.
        recuadro("MODIFICANDO CONSUMO");
        printf("\n>>> Ingrese el ID del cliente: ");
        scanf("%d", &cli.id);
        Beep(400, 300);
        system("cls");

        ///Si verifyIdInFile==1 encontro al cliente y el cursor quedo un registro siguiente al del cliente buscado.
        if (verifyIdInFile(clients, cli.id))
            {
            ///Muevo el cursor un registro anterior y hago una lectura del cliente buscado.
            fseek(clients, -1*sizeof(CLI), SEEK_CUR);
            fread(&cli, sizeof(CLI), 1, clients);

            ///Le muestro al usuario el cliente por pantalla.
            recuadro("CLIENTE ENCONTRADO");
            printOneClient(cli);
            printf("\n\n");

            ///Le pido al usuario que ingrese la fecha del consumo que desea modificar.
            con = loadConDate(cli);
            Beep(400, 300);
            system("cls");

            ///Si verifyFileCon==1 el consumo en esa fecha existe y el cursor queda un registro siguiente del consumo buscado.
            if (verifyFileCon(consumptions, con))
                {
                ///Muevo el cursor un registro anterior y hago la lectura del consumo buscado.
                fseek(consumptions, -1*sizeof(CON), SEEK_CUR);
                fread(&con, sizeof(CON), 1, consumptions);

                ///Le muestro al usuario el cliente y el consumo buscado por pantalla.
                recuadro("CONSUMO ENCONTRADO");
                printConAndClient(cli, con);

                ///Le pregunto al usuario si desea modificar el consumo.
                printf("\n\n>>>Desea modificar el consumo? (S/N)");
                opcion = getch();
                Beep(400, 300);
                system("cls");

                ///Si presiona el boton 'S' prosigue con la modificacion.
                if (opcion == 's' || opcion == 'S')
                    {
                    ///Le pido al usuario que ingrese el nuevo consumo.
                    recuadro("MODIFICANDO CONSUMO");
                    printf("\n>>> Ingrese el consumo para modificarlo (MB): ");
                    scanf("%d", &con.megaBytes);
                    system("cls");

                    ///Muevo el cursor un registro anterior y hago una escritura del consumo para modificarlo.
                    fseek(consumptions, -1*sizeof(CON), SEEK_CUR);
                    fwrite(&con, sizeof(CON), 1, consumptions);

                    ///Le muestro al ususario por pantalla el cliente con el consumo modificado.
                    recuadro("CONSUMO MODIFICADO");
                    printConAndClient(cli, con);
                    }
                ///Si el usuario no presiona 'S' le muestro por pantalla que no hubo modificacion en el consumo.
                else
                    {
                    recuadro("CONSUMO SIN MODIFICACION");
                    printConAndClient(cli, con);
                    }
                }
            ///Si verifyFileCon==0 el consumo en esa fecha no existe y doy aviso por pantalla.
            else
                {
                recuadro("NO EXISTE UN CONSUMO EN ESA FECHA");
                printOneClient(cli);
                }
            }
        ///Si verifyIdInFile==0 el cliente con ese ID no existe y doy aviso por pantalla.
        else
            {
            errorMessagge(">>>[ERROR]<<< NO EXISTE NINGUN CLIENTE CON ESE ID");
            }
        }
    ///Si los archivos no abrieron doy aviso de error por pantalla.
    else
        {
        errorMessagge(">>>[ERROR]<<< OCURRIO UN FALLO AL ABRIR LOS ARCHIVOS");
        }

    ///Cierro los archivos para guardar cambios.
    fclose(consumptions);
    fclose(clients);

    getch();
}





void writeRandCon (char archivo[], int cant)
{
    FILE *consumptions = fopen(archivo, "a+b");

    CON c;

    int reg = 0;

    int i = 0;

    if (consumptions)
        {
        reg = returnEndConReg (archivo);

        while (i < cant)
            {
            reg++;
            c.reg = reg;
            c = randCon(c);

            if(!verifyFileCon(consumptions, c))
                {
                fwrite(&c, sizeof(CON), 1, consumptions);
                }
            else
                {
                loadConInDate(consumptions, c);
                }
            i++;
            }
        }
    else
        {
        errorMessagge(">>>[ERROR]<<< OCURRIO UN FALLO AL ABRIR EL ARCHIVO");
        }

    fclose(consumptions);
}




void loadRandCon (char archivo[])
{
    int cant;

    recuadro("CARGANDO CONSUMOS ALEATORIOS");
    printf("\n>>> Ingrese la cantidad de consumos que quiera cargar: ");
    scanf("%d", &cant);
    system("cls");

    writeRandCon(archivo, cant);

    errorMessagge("SE CARGARON LOS CONSUMOS ALEATORIOS");

    getch();
}

