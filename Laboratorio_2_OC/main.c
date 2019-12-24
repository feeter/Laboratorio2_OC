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
#include <string.h>

#define _POSIX_SOURCE
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>


void listdir(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".DS_Store") == 0)
            continue;
        
        if (entry->d_type == DT_DIR) {
            char path[1024];
            
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%*s[%s]\n", indent, "", entry->d_name);
            listdir(path, indent + 2);
        } else {
            
            printf("%*s- %s\n", indent, "", entry->d_name);
        }
    }
    closedir(dir);
}

void getUserId()
{
    struct passwd *p;
    uid_t  uid;

    if ((p = getpwuid(uid = geteuid())) == NULL)
      perror("getpwuid() error");
    else {
      //puts("getpwuid() returned the following info for your userid:");
      //printf("  pw_name  : %s\n",       p->pw_name);
      printf("Id_usuario: %d ", (int) p->pw_uid);
      //printf("  pw_gid   : %d\n", (int) p->pw_gid);
      //printf("  pw_dir   : %s\n",       p->pw_dir);
      //printf("  pw_shell : %s\n",       p->pw_shell);
      printf("Id_programa: %d\n", (int)   getpid());
    }
    
    printf("\n");
    
}


int main(int argc, const char * argv[]) {
    getUserId();
    
    
    listdir("/Users/josigna.cp/Documents/USACH/Materias/Semestre 2/ORGANIZACIÓN DE COMPUTADORES/Laboratorio 2/Inicio/", 0);
    
    
    

    return 0;
}


