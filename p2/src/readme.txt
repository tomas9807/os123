-Pregunta 1: se modifico "proc.h", el archivo modificado se encuentra en "src/1/"
    Modificaciones:
        -Se agrego el header <sys/types.h>  en la linea 17.
        -Se agrego uid_t p_uid en la linea 21.


-Pregunta 2: se modifico "dmp_kernel.c","dmp.c","proto.h" los archivos modificado se encuentran en "src/2/"
    Modificaciones:
        -En "dmp.c" se edito la linea 22 por la funcion procesos_usuario_activo_dmp() es decir al presionar F4 esa funcion se invoca.
        -En "proto.h" se agrego en la linea 16  void procesos_usuario_activo_dmp, (void) .
        -En "dmp_kernel.c" se agrego en la linea 62 PUBLIC void procesos_usuario_activo_dmp() que es la funcion que imprime los procesos del usuario activo.