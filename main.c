#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct student
{
	char imie[40];
	char nazwisko[40];
	int index;
};


int main(int argc, char *argv[]) {	
	
	int a;
	FILE *fp, *pom;
	
	
	printf("1. View students   2.  Add new student\n3. Delete student number: \n4. Exit\nOption number: ");
		while(scanf("%d" ,&a) == 1)
		{
			if (a == 4)
				break;
		
		switch(a)
		{
			case 1 : 
				//wyswietlanie
				{
					if((fp = fopen("plik.txt", "rb")) == NULL)
					{
						printf("\nEmpty lsit\n");
					}
					
					struct student tmp;
					int i = 1;
					while (fread(&tmp, sizeof(struct student), 1, fp) != 0)
					{
						printf("%d %s %s %d\n", i, tmp.imie, tmp.nazwisko, tmp.index);
						i++;
					}
					
					if (i == 1)
						printf("\nLista jest pusta\n");
					
					fclose(fp);
					
				}
				
				break;
			
			case 2 :
				//dodanie
				{
				int nr_ind;
				
				struct student Student;
				
				printf("\nName: ");
				scanf("%s", Student.imie);
				printf("\nSurname: ");
				scanf("%s", Student.nazwisko);
				printf("\nIndex number: ");
				scanf("%d", &Student.index);

				
				//debug
				//printf("%s %s %d", Student.imie, Student.nazwisko, Student.index);
				
				if((fp = fopen("plik.txt", "ab")) == NULL)
				{
					printf("Error with opening file");
					exit(1);
				}
				
				fwrite(&Student, sizeof(struct student), 1, fp);
				
				fclose(fp);
			}
				break;
			case 3 :
				//Usuniecie
				{
					int ind;
					struct student tmp;
				
					
					printf("Enter index number of student to delete: ");
					scanf("%d", &ind);
					
					//otwieranie pliku glownego z strukturami
					if((fp = fopen("plik.txt", "rb")) == NULL)
					{
						printf("Error opening file");
						exit(1);
					}
					
					//tworzenie pliku tymczasowego 
					if((pom = fopen("temp_student.txt", "wb")) == NULL)
					{
						printf("Error opening file");
						exit(1);
					}
					
					int help = 0;
					//przepisywanie do pliku temp_student.txt struktur bez studenta o podanym indeksie
					while (fread(&tmp, sizeof(struct student), 1, fp) != 0)
					{
						if (tmp.index != ind)
						{
							fwrite(&tmp, sizeof(struct student), 1, pom);
							help++;	
						}
						else
						{
							help = -1;
						}
					}
					
					
					fclose(fp);
					fclose(pom);
					
					if (help == 0)
					{
						printf("\nEmpty list\n");
						break;
					}
					else if (help == -1)
					{
						printf("\nStudent deleted\n");
					}
					else
					{
						printf("\nThe student not found\n");
						break;
					}
					
					//zamiana trybu otwierania plikow
					if((fp = fopen("plik.txt", "wb")) == NULL)
					{
						printf("Error opening file");
						exit(1);
					}
					
					//zamiana trybu otwierania plikow
					if((pom = fopen("temp_student.txt", "rb")) == NULL)
					{
						printf("Error opening file");
						exit(1);
					}
					
					//przepisywanie do glownego pliku
					while (fread(&tmp, sizeof(struct student), 1, pom) != 0)
					{
					
						fwrite(&tmp, sizeof(struct student), 1, fp);	
					}
							
					fclose(fp);
					fclose(pom);
						
				}
				break;
				
				default :
					printf("There is no such option. Try again\n");
					break;
		
			
		}
		
		printf("\nOption number: ");
	
	}
	
	//usuwanie pliku temp_student.txt
	if(remove("temp_student.txt") == 0)
	{
	
	}
	
	fclose(fp);
	fclose(pom);
	
	return 0;
}
