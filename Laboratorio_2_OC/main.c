//
//  main.c
//  Laboratorio_2_OC
//  Organizacion de computadores
//  Fecha de entrega viernes 03/01/2020 hasta las 23:59
//  La entrega se realiza vía correo electrónico a viktor.tapia@usach.cl
//
//  Created by Jose Ignacio Campos Padilla on 11-12-19.
//  Copyright © 2019 Jose Ignacio Campos Padilla. All rights reserved.
//



#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

#define _POSIX_SOURCE
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <string.h>

char *gnu_basename(char *path)
{
    char *base = strrchr(path, '/');
    return base ? base+1 : path;
}

void contar(char* path, int margen, FILE* fp){
    //count the number of files and subdirectories
    int fileCount = 0;
    int dirCount = 0;
    DIR *dp;
    struct dirent *dir;

      int i;
      for(i = 1; i < 2; i++){
            dp = opendir(path);
            if(dp == NULL)
              continue;
            while((dir = readdir(dp)) != NULL){
                if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0 )
                    continue;
                
                
              if(dir->d_type == DT_REG){
                    fileCount++;
              }
              if(dir->d_type == DT_DIR)
                    dirCount++;
                
            }
          
          char *basec, *bname;
                       
         basec = strdup(path);
         bname = gnu_basename(basec);
           
          
         printf("Directorio %s contiene: %d Carpetas y %d Archivos\n", bname, dirCount, fileCount);
          fprintf (fp, "Directorio %s contiene: %d Carpetas y %d Archivos\n", bname, dirCount, fileCount);
      }

    closedir(dp);
}

int ContDir(const char *name, int margen, FILE* fp, int carpetas, int archivos)
{
    DIR* dirActual;
    struct dirent *entry;
    //int carpetas = 0, archivos = 0;
    char path[1024];
    

    if (!(dirActual = opendir(name)))
        return 0;

    while ((entry = readdir(dirActual)) != NULL)
    {
        
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 )
            continue;
        
        
        if (entry->d_type == DT_DIR) {
            
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name); // concatena la ruta a la subcarpeta
            //printf("%s\n", entry->d_name); // imprime el nombre de la carpeta actual por consola

            contar(path, margen + 2, fp);
            ContDir(path, 0, fp, carpetas, archivos);
            
        }
      
    }
    
    closedir(dirActual);
    
    
    return carpetas;
}

void listdir(const char *name, int margen, FILE* fp)
{
    DIR* dirActual;
    struct dirent *entry;
    

    if (!(dirActual = opendir(name)))
        return;

    while ((entry = readdir(dirActual)) != NULL)
    {
        
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || entry->d_type != DT_DIR)//strcmp(entry->d_name, ".DS_Store") == 0)
            continue;
        
        
        if (entry->d_type == DT_DIR) {
            char path[1024];
            
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name); // concatena la ruta completa
            printf("%*s%s\n", margen, "", entry->d_name); // imprime el nombre de la carpeta actual por consola
            fprintf(fp, "%*s%s\n", margen, "", entry->d_name); // escribe en el archivo fp el nombre de la carpeta actual
            

            //listdir(path, margen + 2, fp);
            listdir(path, 0, fp);
            
            char *basec, *bname;
            

            basec = strdup(name);
            bname = gnu_basename(basec);
            
            printf("%s\n", bname);
            fprintf(fp, "%s\n", bname); // escribe en el archivo fp el nombre de la carpeta actual
            
            
        } //else {
       //     // Archivos
       //     printf("%*s- %s\n", margen, "", entry->d_name);
       //     fprintf(fp, "%*s- %s\n", margen, "", entry->d_name);
        // }
    }
    
    closedir(dirActual);
}

FILE* CrearArchivo(char* ubicacion)
{
    
    FILE* fp = fopen(ubicacion,"w");
    
    
    return fp;
    
}

void CerrarArchivo(FILE* fp)
{
    fclose(fp);
}

void getUserId(FILE* fp)
{
    struct passwd *p;
    uid_t  uid;

    if ((p = getpwuid(uid = geteuid())) == NULL)
      perror("getpwuid() error");
    else {
      //puts("getpwuid() returned the following info for your userid:");
      //printf("  pw_name  : %s\n",       p->pw_name);
      printf("Id_usuario: %d ", (int) p->pw_uid);
        fprintf (fp, "Id_usuario: %d ", (int) p->pw_uid);
      //printf("  pw_gid   : %d\n", (int) p->pw_gid);
      //printf("  pw_dir   : %s\n",       p->pw_dir);
      //printf("  pw_shell : %s\n",       p->pw_shell);
      printf("Id_programa: %d\n", (int)   getpid());
        
        
        fprintf (fp, "Id_programa: %d\n", (int)   getpid());

    }
    
    printf("\n");
    
}




int main(int argc, const char * argv[]) {
    char* dirParaAnalizar = "/Users/josigna.cp/Documents/USACH/Materias/Semestre 2/ORGANIZACIÓN DE COMPUTADORES/Laboratorio 2/";
    
    FILE* fp = CrearArchivo("/Users/josigna.cp/Documents/USACH/Materias/Semestre 2/ORGANIZACIÓN DE COMPUTADORES/Recorrido.txt");
    
    getUserId(fp);
    listdir(dirParaAnalizar, 0, fp);
    
    CerrarArchivo(fp);
    
    /** Archivo Directorio.txt */
    
    fp = CrearArchivo("/Users/josigna.cp/Documents/USACH/Materias/Semestre 2/ORGANIZACIÓN DE COMPUTADORES/Directorio.txt");

    getUserId(fp);
    ContDir(dirParaAnalizar, 0, fp, 0, 0);


    CerrarArchivo(fp);
    

    
    

    
    
    return 0;
}


