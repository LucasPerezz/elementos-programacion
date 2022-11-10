#include <stdio.h>
#include <string.h>

typedef struct
{
    char sector[16];
    int duracionLlamada;
    int tipoLlamada;
} T_LLAMADAS;

typedef struct
{
    int duracionLlamada;
    int tipoLlamada;
    float costo;
} T_VALOR;

typedef struct
{
    char sector[16];
    float total;
} T_TOTALxSECTOR;

void mostrarLlamadasSector(char[]);
void mayorSector(char[]);
void copiarArchivoAVector(char[], float[], int);
void gastoDeLlamadas(char[], char[], float[]);
void mostrarArchivo(char[]);

int main()
{
    float vCosto[3];
    mostrarLlamadasSector("LLAMADAS.dat");
    mayorSector("LLAMADAS.dat");
    copiarArchivoAVector("COSTOS.dat", vCosto, 3);
    gastoDeLlamadas("LLAMADAS.dat", "GASTOS.dat", vCosto);
    mostrarArchivo("GASTOS.dat");


    return 0;
}

void mostrarLlamadasSector(char nomArch[])
{
    T_LLAMADAS llam;
    int contLlamada;
    char sectorAnterior[16];
    FILE*arch;
    arch = fopen(nomArch, "rb");
    if(arch == NULL)
    {
        printf("No se pudo abrir el archivo");
    }
    else
    {
        printf("*********TIEMPO TOTAL DE LLAMADAS POR SECTOR************\n");
        fread(&llam, sizeof(T_LLAMADAS), 1, arch);
        while(!feof(arch))
        {
            contLlamada = 0;
            strcpy(sectorAnterior, llam.sector);
            while(strcmpi(sectorAnterior, llam.sector) == 0 && !feof(arch))
            {
                contLlamada++;
                fread(&llam, sizeof(T_LLAMADAS), 1, arch);
            }


            printf("\n\nCANTIDAD DE LLAMADAS: %d \t", contLlamada);
            puts(sectorAnterior);

        }
        fclose(arch);
    }
}

void mayorSector(char nomArch[])
{
    T_LLAMADAS llam;
    char maxSector[16];
    char sectorAnterior[16];
    int maxLlamada, totalLlamadaSector, band;
    FILE*arch;
    arch = fopen(nomArch, "rb");
    if(arch == NULL)
    {
        printf("No se pudo abrir el archivo");
    }
    else
    {
        band = 0;
        printf("***************MAYOR TIEMPO DE LLAMADAS****************\n");
        fread(&llam, sizeof(T_LLAMADAS), 1, arch);
        while(!feof(arch))
        {
            maxLlamada = 0;
            totalLlamadaSector = 0;
            strcpy(sectorAnterior, llam.sector);
            while(strcmpi(sectorAnterior, llam.sector) == 0 && !feof(arch))
            {
                totalLlamadaSector += llam.duracionLlamada;
                if(band = 0 || totalLlamadaSector > maxLlamada)
                {
                    strcpy(maxSector, llam.sector);
                    maxLlamada = totalLlamadaSector;
                    band = 1;
                }
                fread(&llam, sizeof(T_LLAMADAS), 1, arch);
            }


        }
            printf("\n\nTIEMPO DE LLAMADAS: %d \t", maxLlamada);
            puts(maxSector);
            printf("\n\n");

        fclose(arch);
    }
}

void copiarArchivoAVector(char nomArch[], float v[], int ce)
{
    float val;
    FILE*arch;
    arch = fopen(nomArch, "rb");
    if(arch == NULL)
    {
        printf("No se pudo abrir el archivo");
    }
    else
    {
        int i = 0;

        fread(&val, sizeof(val), 1, arch);
        while(!feof(arch))
        {
            v[i] = val;
            i++;
            fread(&val, sizeof(val), 1, arch);
        }

        fclose(arch);
    }
}

void gastoDeLlamadas(char nomArch[], char nomArch2[], float v[])
{
    T_LLAMADAS llam;
    T_VALOR val;
    T_TOTALxSECTOR total;
    char sectorAnterior[16];
    float costoSector;
    FILE*arch;
    FILE*arch2;
    arch = fopen(nomArch, "rb");
    arch2 = fopen(nomArch2, "wb");
    if(arch == NULL || arch2 == NULL)
    {
        printf("No se pudo abrir el archivo");
    }
    else
    {
        fread(&llam, sizeof(T_LLAMADAS), 1, arch);
        while(!feof(arch))
        {
            costoSector = 0;
            strcpy(sectorAnterior, llam.sector);
            while(strcmpi(sectorAnterior, llam.sector) == 0 && !feof(arch))
            {
                costoSector += llam.duracionLlamada * v[llam.tipoLlamada - 1];
                fread(&llam, sizeof(T_LLAMADAS), 1, arch);
            }

            total.total = costoSector;
            strcpy(total.sector, llam.sector);
            fwrite(&total, sizeof(T_TOTALxSECTOR), 1, arch2);
        }

        fclose(arch);
        fclose(arch2);
    }
}

void mostrarArchivo(char nomArch[])
{
    T_TOTALxSECTOR tot;
    FILE*arch;
    arch = fopen(nomArch, "rb");
    if(arch == NULL)
    {
        printf("No se pudo abrir el archivo");
    }
    else
    {
        printf("***************TOTAL DE GASTOS POR SECTOR**************\n");
        fread(&tot, sizeof(T_TOTALxSECTOR), 1, arch);
        while(!feof(arch))
        {
            puts(tot.sector);
            printf("TOTAL DEL SECTOR: $%.2f\n\n", tot.total);
            fread(&tot, sizeof(T_TOTALxSECTOR), 1, arch);
        }

        fclose(arch);
    }
}


