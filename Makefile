main: main.o sauvegarde.o partie.o menu.o linked_list_id.o linked_list_id_etat.o double_linked_list.o chargement.o
	gcc -o build/akinator build/main.o build/sauvegarde.o build/partie.o build/menu.o build/linked_list_id.o build/linked_list_id_etat.o build/double_linked_list.o build/chargement.o
	rm build/*.o -f

chargement.o: chargement.c chargement.h
	gcc -c chargement.c -o build/chargement.o
double_linked_list.o: double_linked_list.c double_linked_list.h
	gcc -c double_linked_list.c -o build/double_linked_list.o
linked_list_id.o: linked_list_id.c linked_list_id.h
	gcc -c linked_list_id.c -o build/linked_list_id.o
linked_list_id_etat.o: linked_list_id_etat.c linked_list_id_etat.h
	gcc -c linked_list_id_etat.c -o build/linked_list_id_etat.o
menu.o: menu.c menu.h
	gcc -c menu.c -o build/menu.o
partie.o: partie.c partie.h
	gcc -c partie.c -o build/partie.o
sauvegarde.o: sauvegarde.c sauvegarde.h
	gcc -c sauvegarde.c -o build/sauvegarde.o
main.o: main.c
	gcc -c main.c -o build/main.o

clean:
	rm build/*.o build/akinator -f