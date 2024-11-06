#include <stdio.h> //para el archivo 
#include <stdlib.h> //para las librerias 
#include <string.h> //para las cadenas de caracteres 

int main()
{
    FILE *archivoEntrada = fopen("./create1.txt", "r+"); //r+ para lectura y escritura del archivo texto
    if (archivoEntrada == NULL)
    {
        printf("Error al abrir el archivo para lectura.\n");
        return 1; //retorna a 1 si hay error
    }

    char linea[1000]; //variable para leer el archivo
    char codigoTraducido[1000] = ""; //variable para el archivo traducido //"" para que el archivo traducido inicie vacio

    while (fgets(linea, sizeof(linea), archivoEntrada) != NULL) //fgets lee el archivo linea por linea y lo almacena en la variable linea 
    {
        if (strstr(linea, "#incluir") != NULL) //strstr busca una cadena dentro de otra y si la encuentra la imprime en la variable linea y la copia en la variable codigoTraducido
        {
            strcat(codigoTraducido, "#include <stdio.h>\n"); //strcat concatena una cadena con otra y la copia en la variable codigoTraducido
        }
        else if (strstr(linea, "entero principal()") != NULL)
        {
            strcat(codigoTraducido, "int main()\n");
        }
        else if (strstr(linea, "imprimirf") != NULL)
        {
            strcat(codigoTraducido, "printf");
            strcat(codigoTraducido, strchr(linea, '(')); //strchr busca una cadena dentro de otra y la copia en la variable codigoTraducido
        }
        else if (strstr(linea, "escanearf") != NULL)
        {
            strcat(codigoTraducido, "scanf");
            strcat(codigoTraducido, strchr(linea, '(')); //'(') para que sepa donde termina la cadena
        }
        else if (strstr(linea, "retornar") != NULL)
        {
            strcat(codigoTraducido, "return ");
            strcat(codigoTraducido, strchr(linea, '0')); //strcat concatena en la variable codigoTraducido 
        }
        else
        {
            strcat(codigoTraducido, linea); //strcat concatena una cadena con otra y la copia en la variable codigoTraducido
        }
    }

    fclose(archivoEntrada);

    FILE *archivoSalida = fopen("./create2.c", "w"); //FILE para crear el archivo, * para apuntar al archivo, fopen abre el archivo y w es para escritura
    if (archivoSalida == NULL)
    {
        printf("Error al abrir el archivo para escritura.\n");
        return 1; 
    }

    fputs(codigoTraducido, archivoSalida); //fputs escribe una cadena en el archivo 
    fclose(archivoSalida); //fclose cierra el archivo

    printf("Transpilacion realizada.\n");

    return 0;
}   
