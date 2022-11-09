#include <stdio.h>

typedef struct
{
    int numeroCanal;
    char programa[36];
    float rating;
} T_RATING;

typedef struct
{
    int numeroCanal;
    float promedio;
} T_PROMEDIO;

void mostrarArchivo(char[]);

int main()
{
    int canalAnterior, cantidadCanales, canalMasVisto, maxCanal;
    float totalRating, maxRating;
    T_RATING rating;
    T_PROMEDIO prom;
    FILE*arch;
    FILE*arch2;
    arch = fopen("RATING.dat", "rb");
    arch2 = fopen("PROMEDIO_RATING.dat", "wb");
    if(arch == NULL || arch2 == NULL)
    {
        printf("No se pudo abrir el archivo");
    }
    else
    {
        fread(&rating, sizeof(T_RATING), 1, arch);
        while(!feof(arch))
        {
            canalAnterior = rating.numeroCanal;
            totalRating = 0;
            cantidadCanales = 0;
            maxCanal = canalAnterior;
            maxRating = totalRating;
            while(canalAnterior == rating.numeroCanal && !feof(arch))
            {
                cantidadCanales++;
                totalRating += rating.rating;
                if(totalRating > maxRating)
                {
                    maxCanal = rating.numeroCanal;
                    maxRating = totalRating;
                }
                fread(&rating, sizeof(T_RATING), 1, arch);
            }

            if(totalRating < 15)
            {
                printf("CANAL: %d \t RATING: %.2f\n", rating.numeroCanal, totalRating);
            }


            prom.numeroCanal = canalAnterior;
            prom.promedio = totalRating / cantidadCanales;
            fwrite(&prom, sizeof(T_PROMEDIO), 1, arch2);

        }

            printf("\nCANAL MAS VISTO: %d\n", maxCanal);
        fclose(arch);
        fclose(arch2);
    }

    mostrarArchivo("PROMEDIO_RATING.dat");
}

void mostrarArchivo(char nomArch[])
{
    T_PROMEDIO prom;
    FILE*arch;
    arch=fopen(nomArch, "rb");
    if(arch==NULL)
    {
        printf("No se pudo abrir el archivo");
    }
    else
    {
        fread(&prom, sizeof(T_PROMEDIO), 1, arch);
        while(!feof(arch))
        {
            printf("CANAL: %d \t PROMEDIO: %.2f\n", prom.numeroCanal, prom.promedio);
            fread(&prom, sizeof(T_PROMEDIO), 1, arch);
        }


        fclose(arch);
    }
}
