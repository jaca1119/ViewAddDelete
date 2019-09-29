#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct student
{
	char name[40];
	char surName[40];
	int index;
};


int main(int argc, char *argv[])
{
int a;
FILE *fp, *temporary;

//helper variables. Should use bool or boolean but before C99 standard for C language there wasn't bool
int isStudentsCreated = 0;
int isTemporaryCreated = 0;

printf("1. View students   2.  Add new student\n3. Delete student of index number: \n4. Exit\nOption number: ");

while(scanf("%d" ,&a) == 1)
{
    if (a == 4)
        break;

    switch(a)
    {
        case 1 :
        //displaying
        {
            if((fp = fopen("students.txt", "rb")) == NULL)
            {
                printf("\nEmpty list\n");
                isStudentsCreated = 0;
                break;
            }

            struct student tmp;
            int i = 0;
            while (fread(&tmp, sizeof(struct student), 1, fp) != 0)
            {
                printf("%d %s %s %d\n", i + 1, tmp.name, tmp.surName, tmp.index);
                i++;
            }

            if (i == 0)
                printf("\nThe list is empty\n");

            fclose(fp);
            break;
        }

        case 2 :
        //addition
        {
            char name[40];
            char surName[40];

            struct student Student;

            printf("\nName: ");
            scanf("%s", name);
            strcpy(Student.name, name);
            printf("\nSurname: ");
            scanf("%s", surName);
            strcpy(Student.surName, surName);
            printf("\nIndex number: ");
            scanf("%d", &Student.index);

            //debug
            //printf("%s %s %d", Student.name, Student.surName, Student.index);

            if((fp = fopen("students.txt", "ab")) == NULL)
            {
                printf("Error with opening file");
                exit(1);
            }

            fwrite(&Student, sizeof(struct student), 1, fp);

            isStudentsCreated = 1;

            fclose(fp);

            break;
        }

        case 3 :
        //deletion
        {
            int ind;
            struct student tmp;


            printf("Enter index number of student to delete: ");
            scanf("%d", &ind);

            //opening main file with structures
            if((fp = fopen("students.txt", "rb")) == NULL)
            {
                printf("Error opening file");
                exit(1);
            }

            //creating temporary file
            if((temporary = fopen("temp_students.txt", "wb")) == NULL)
            {
                printf("Error opening file");
                exit(1);
            }

            isTemporaryCreated = 1;

            int help = 0;

            //rewriting structures without selected student to temp_students.txt
            while (fread(&tmp, sizeof(struct student), 1, fp) != 0)
            {
                if (tmp.index != ind)
                {
                    fwrite(&tmp, sizeof(struct student), 1, temporary);
                    help++;
                }
                else
                {
                    help = -1;
                }
            }


            fclose(fp);
            fclose(temporary);

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

            //changing files open mode
            if((fp = fopen("students.txt", "wb")) == NULL)
            {
                printf("Error opening file");
                exit(1);
            }

            //changing files open mode
            if((temporary = fopen("temp_students.txt", "rb")) == NULL)
            {
                printf("Error opening file");
                exit(1);
            }

            //rewriting to main file
            while (fread(&tmp, sizeof(struct student), 1, temporary) != 0)
            {
                fwrite(&tmp, sizeof(struct student), 1, fp);
            }

            fclose(fp);
            fclose(temporary);

            break;
        }

        default :
            printf("There is no such option. Try again\n");
            break;


    }

    printf("\nOption number: ");
}

//deleting temporary file temp_students.txt
if(remove("temp_students.txt") != 0)
{
    //error removing file
}

//if file was not create, use of fclose will give error
if (isStudentsCreated)
{
    fclose(fp);
}

//if temporary file was not create, use of fclose will give error
if (isTemporaryCreated)
{
    fclose(temporary);
}

return 0;
}
