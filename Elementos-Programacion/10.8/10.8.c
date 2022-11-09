//NO SE ME ACTUALIZA EL VECTOR

#include<stdio.h>
#include <string.h>

typedef struct
{
    int dni;
    char nomApe[21];
    int pago;
} T_INSCRIPCION;

typedef struct
{
    char nomApe[21];
    int dni;
    int telefono;
} T_INTERESADOS;

int contarInscriptos(char[], int);
void leerAlumnosPagos(char[], int);
void copiarArchivo(char[], T_INSCRIPCION[],int);
int busqueda(T_INSCRIPCION[], int, int);
int agregarInscriptos(char[], T_INSCRIPCION[], int);
void actualizarArchivo(char[], T_INSCRIPCION[], int);
void mostrarArchivo(char[]);
//void mostrarArchivo2(char[]);


int main()
{
    int cant;
    int cantActualizada;
    int i;
    T_INSCRIPCION inscriptos[60];
    cant = contarInscriptos("INSCRIPTOS.dat", 60);
    leerAlumnosPagos("INSCRIPTOS.dat", cant);
    copiarArchivo("INSCRIPTOS.dat", inscriptos, cant);
    cantActualizada = agregarInscriptos("INTERESADOS.dat", inscriptos, cant);
    actualizarArchivo("INTERESADOS.dat", inscriptos, cantActualizada);
    for(i = 0; i < cant; i++)
    {
        printf("%d %d\n", inscriptos[i].dni, inscriptos[i].pago);

    }
    mostrarArchivo("INSCRIPTOS.dat");
 //   mostrarArchivo2("INTERESADOS.dat");
    return 0;
}

int contarInscriptos(char nomArch[], int ce)
{
    T_INSCRIPCION ins;
    int i;
    FILE* arch;
    arch = fopen(nomArch, "rb");
    if(arch == NULL)
    {
        printf("No se pudo abrir el archivo");
    }
    else
    {
        i = 0;
        fread(&ins, sizeof(T_INSCRIPCION), 1, arch);
        while(!feof(arch) && i < ce)
        {
            i++;
            fread(&ins, sizeof(T_INSCRIPCION), 1, arch);
        }
    }
    fclose(arch);

    return i;

}

void leerAlumnosPagos(char nomArch[], int ce)
{
    T_INSCRIPCION ins;
    int i;
    FILE*arch;
    arch = fopen(nomArch, "rb");
    if(arch == NULL)
    {
        printf("No se pudo abrir el archivo");
    }
    else
    {
        i = 0;
        fread(&ins, sizeof(T_INSCRIPCION), 1, arch);
        while(!feof(arch) && i < ce)
        {
            if(ins.pago == 1)
            {
                printf("DNI: %d \t", ins.dni);
                puts(ins.nomApe);
            }

            i++;
            fread(&ins, sizeof(T_INSCRIPCION), 1, arch);
        }

    }

    fclose(arch);
}


void copiarArchivo(char nomArch[], T_INSCRIPCION v[], int ce)
{
    T_INSCRIPCION ins;
    int i;
    FILE*arch;
    arch = fopen(nomArch, "rb");
    if(arch == NULL)
    {
        printf("No se pudo abrir el archivo");
    }
    else
    {
        i = 0;
        fread(&ins, sizeof(T_INSCRIPCION), 1, arch);
        while(!feof(arch) && i < ce)
        {
            v[i] = ins;
            i++;
            fread(&ins, sizeof(T_INSCRIPCION), 1, arch);
        }
    }

    fclose(arch);
}

int busqueda(T_INSCRIPCION v[], int ce, int bus)
{
    int i, pos;

    i = 0;
    pos = -1;

    while(i < ce && pos == -1)
    {
        if(v[i].dni == bus)
        {
            pos = i;
        }

        i++;
    }

    return pos;
}

int agregarInscriptos(char nomArch[], T_INSCRIPCION v[], int ce)
{
    int i;
    int dni, pos;
    T_INTERESADOS interesados;
    T_INSCRIPCION ins;
    FILE*arch;
    arch = fopen(nomArch, "ab");
    if(arch == NULL)
    {
        printf("No se pudo abrir el archivo");
    }
    else
    {
        printf("INGRESE DNI\n");
        scanf("%d", &dni);
        i = ce + 1;

        while(dni != -2)
        {
            pos = busqueda(v, ce, dni);
            if(pos != -1)
            {
                v[pos].pago = 1;
            }
            else
            {
                if(i < 60)
                {
                    fflush(stdin);
                    v[i].dni = dni;
                    printf("INGRESE NOMBRE\n");
                    gets(v[i].nomApe);
                    v[i].pago = 0;
                }
                else
                {
                printf("INGRESE DNI\n");
                scanf("%d", &interesados.dni);
                printf("INGRESE NOMBRE Y APELLIDO\n");
                fflush(stdin);
                gets(interesados.nomApe);
                printf("INGRESE NUMERO DE TELEFONO\n");
                scanf("%d", &interesados.telefono);
                fwrite(&interesados, sizeof(T_INTERESADOS), 1, arch);
                }
            }
            i++;
            printf("INGRESE DNI\n");
            scanf("%d", &dni);
        }

    }
    fclose(arch);

    return i;
}

void actualizarArchivo(char nomArch[], T_INSCRIPCION v[], int ce)
{
    int i;
    T_INSCRIPCION ins;
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
            fwrite(&v[i], sizeof(T_INSCRIPCION), 1, arch);
        }
    }


    fclose(arch);
}

void mostrarArchivo(char nomArch[])
{
    T_INSCRIPCION ins;
    FILE*arch;
    arch = fopen(nomArch, "rb");
    if(arch == NULL)
    {
        printf("No se pudo abrir el archivo");
    }
    else
    {
        fread(&ins, sizeof(T_INSCRIPCION), 1, arch);
        while(!feof(arch))
        {
            printf("DNI: %d \t PAGO: %d \t", ins.dni, ins.pago);
            puts(ins.nomApe);
            fread(&ins, sizeof(T_INSCRIPCION), 1, arch);
        }
    }
}

/*
void mostrarArchivo2(char nomArch[])
{
    T_INTERESADOS interesados;
    FILE*arch;
    arch = fopen(nomArch, "rb");
    if(arch == NULL)
    {
        printf("No se pudo abrir el archivo");
    }
    else
    {
        fread(&interesados, sizeof(T_INTERESADOS), 1, arch);
        while(!feof(arch))
        {
            printf("DNI: %d \t TELEFONO: %d \t", interesados.dni, interesados.telefono);
            puts(interesados.nomApe);
            fread(&interesados, sizeof(T_INTERESADOS), 1, arch);
        }
    }
} */

