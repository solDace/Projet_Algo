cmake_minimum_required(VERSION 3.21)
project(akinator-c C)

set(CMAKE_C_STANDARD 99)

add_executable(
        akinator
        main.c
        linked_list_id.c
        linked_list_id.h
        double_linked_list.c
        double_linked_list.h
        menu.c
        menu.h
        linked_list_id_etat.c
        linked_list_id_etat.h
        chargement.c
        chargement.h
        partie.c
        partie.h
        sauvegarde.c
        sauvegarde.h
        )
