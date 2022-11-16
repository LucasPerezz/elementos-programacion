/* En la feria internacional del automóvil, una empresa autopartista que dispone de un stand registra
 la información de los visitantes interesados en sus productos. Por cada visitante se ingresa:

 •  Nombre y Apellido (texto de máximo 35 caracteres)
 •  DNI (entero)
 •  Localidad (texto de 40 caracteres máximo)
 •  Email (texto de máximo 20 caracteres)
 •  Fecha (estructura con día, mes y año)

Se solicita:

 a.  Realizar una función para ingresar la información por teclado hasta que se ingrese un visitante
  con nombre FIN. (se admite como máximo cargar 500 visitantes).

 b.  Una vez finalizado el ingreso de datos se debe generar un archivo llamado visitantes.dat que esté
 ordenado por localidad.

 c.  Tomando el archivo visitantes.dat se debe calcular y mostrar la cantidad de visitas recibidas por
  cada localidad y generar un archivo para cada una de ellos conteniendo la información de los visitantes
   para que dicho archivo puede ser enviado a la sucursal más cercada de forma de contactar a los interesados.
    Cada archivo generado será nombrado con Nombre de la Localidad.dat. */

#include <stdio.h>
#include <string.h>

typedef struct
{
    int dia;
    int mes;
    int anio;
} T_FECHA;

typedef struct
{
    char nomApe[36];
    int dni;
    char localidad[41];
    char email[21];
    T_FECHA fecha;
} T_VISITANTE;

int ingresarDatos(T_VISITANTE[], int);
void ordenarVector(T_VISITANTE[], int);
void generarArchivo(char[], T_VISITANTE[], int);
void generarArchivoxLocalidad(char[]);
void mostrarArchivo(char[]);

int main()
{
    T_VISITANTE vVisitante[500];
    int cant;
    cant = ingresarDatos(vVisitante, 500);
    ordenarVector(vVisitante, cant);
    generarArchivo("visitantes.dat", vVisitante, cant);
    generarArchivoxLocalidad("visitantes.dat");
    mostrarArchivo("francisco alvarez.dat");

    return 0;
}

int ingresarDatos(T_VISITANTE v[], int ce)
{
    int i;
    char nomApeAux[36];
    i = 0;
    printf("INGRESE SU NOMBRE Y APELLIDO\n");
    gets(nomApeAux);
    while(i < ce && strcmpi(nomApeAux, "FIN") != 0)
    {
        strcpy(v[i].nomApe, nomApeAux);
        printf("INGRESE SU DNI\n");
        scanf("%d", &v[i].dni);
        printf("INGRESE SU LOCALIDAD\n");
        fflush(stdin);
        gets(v[i].localidad);
        printf("INGRESE SU EMAIL\n");
        fflush(stdin);
        gets(v[i].email);
        printf("INGRESE DIA, MES Y ANIO\n");
        scanf("%d %d %d", &v[i].fecha.dia, &v[i].fecha.mes, &v[i].fecha.anio);
        fflush(stdin);
        i++;
        printf("INGRESE SU NOMBRE Y APELLIDO\n");
        gets(nomApeAux);
    }

    return i;
}

void ordenarVector(T_VISITANTE v[], int ce)
{
    int i, j;
    T_VISITANTE aux;
    for(i = 0; i < ce - 1; i++)
    {
        for(j = 0; j < ce - 1; j++)
        {
            if(strcmpi(v[j].localidad, v[j+1].localidad) > 0)
            {
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
    }
}

void generarArchivo(char nomArch[], T_VISITANTE v[], int ce)
{
    T_VISITANTE vis;
    int i;
    FILE*arch;
    arch = fopen(nomArch, "wb");
    if(arch == NULL)
    {
        printf("No se pudo abrir el archivo");
    }
    else
    {
        for(i = 0; i < ce; i++)
        {
            vis = v[i];
            fwrite(&vis, sizeof(T_VISITANTE), 1, arch);
        }

        fclose(arch);
    }
}

void generarArchivoxLocalidad(char nomArch[])
{
    T_VISITANTE vis;
    char localidadAux[41];
    char anteriorLocalidad[41];
    FILE*arch;
    FILE*arch2;
    arch = fopen(nomArch, "rb");
    if(arch == NULL)
    {
        printf("No se pudo abrir el archivo");
    }
    else
    {
        fread(&vis, sizeof(T_VISITANTE), 1, arch);
        while(!feof(arch))
        {
            strcpy(localidadAux, vis.localidad);
            strcpy(anteriorLocalidad, vis.localidad);
            strcat(localidadAux, ".dat");
            arch2 = fopen(localidadAux, "wb");
            while(strcmpi(anteriorLocalidad, vis.localidad) == 0 && !feof(arch))
            {
                fwrite(&vis, sizeof(T_VISITANTE), 1, arch2);
                fread(&vis, sizeof(T_VISITANTE), 1, arch);
            }
            fclose(arch2);
        }
        fclose(arch);
    }

}


void mostrarArchivo(char nomArch[])
{
    T_VISITANTE vis;
    FILE*arch;
    arch = fopen(nomArch, "rb");
    if(arch == NULL)
    {
        printf("No se pudo abrir el archivo");
    }
    else
    {
        fread(&vis, sizeof(T_VISITANTE), 1, arch);
        while(!feof(arch))
        {
            printf("\n\n\nNOMBRE Y APELLIDO: ");
            puts(vis.nomApe);
            printf("DNI: %d\n", vis.dni);
            printf("LOCALIDAD: ");
            puts(vis.localidad);
            printf("EMAIL: ");
            puts(vis.email);
            fread(&vis, sizeof(T_VISITANTE), 1, arch);
        }

        fclose(arch);
    }
}