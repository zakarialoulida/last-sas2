#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
typedef struct
{
    int jour;
    int mois;
    int annee;
} date;

typedef struct
{
    int identifiant;
    char titre[100];
    char description[800];
    date deadline;
    date dateCreation;
    char status[100];
} tache;

int taille = 0;
int dernierID=200;

void ajoutertache(tache m[])
{ 
    printf("Entrez le titre de la tache : ");
    scanf(" %[^\n]", m[taille].titre);

    printf("Entrez la description de la tache : ");
    scanf(" %[^\n]", m[taille].description);

    printf("Entrez votre deadline : \n");

    printf("sous forme (JJ/mm/annee) : ");
    scanf("%d/%d/%d", &m[taille].deadline.jour, &m[taille].deadline.mois, &m[taille].deadline.annee);

    printf("Entrez le statut de la tache (a realiser/en cours de realisation/finalisee)\n ");
    printf("1 - a realiser \n");
    printf("2 - en cours de  realisation \n");
    printf("3 - finalisee\n");
    printf("entrer votre choix  :");
    int choix;
    scanf(" %d", &choix);
switch (choix)
{
case 1:
  strcpy(m[taille].status,"a realiser ");
    break;
    case 2:
     strcpy(m[taille].status,"en cours de realisation");
    break;
     case 3:
       strcpy(m[taille].status,"finalisee");
     break;
default:
    break;
}
   time_t creationTime = time(NULL);
    struct tm *creationDate = localtime(&creationTime);
    m[taille].dateCreation.jour = creationDate->tm_mday;
    m[taille].dateCreation.mois = creationDate->tm_mon + 1;
    m[taille].dateCreation.annee = creationDate->tm_year + 1900;
    m[taille].identifiant = dernierID++; 

    printf("Votre ID est : %d\n", m[taille].identifiant);

    taille++;
}

void ajouterplusieurtache(tache m[])
{
    int nbr;
    printf("Entrez le nombre de taches  ajouter : ");
    scanf("%d", &nbr);

    for (int i = 0; i < nbr; i++)
    {
        ajoutertache(m);
    }
}

void affiche_trialphabet(tache m[], int n)
{
    for (int i = 1; i < n; i++)
    {
        tache cmd = m[i];
        int j = i - 1;

        while (strcmp(cmd.titre, m[j].titre) < 0 && j >= 0)
        {
            m[j + 1] = m[j];
            j--;
        }

        m[j + 1] = cmd;
    }
}
void affich(tache m)
{
    printf("Identifiant : %d\n", m.identifiant);
    printf("Titre de la tache : %s", m.titre);
    printf("Description : %s", m.description);
    printf("Deadline : %d/%d/%d\n", m.deadline.jour, m.deadline.mois, m.deadline.annee);
    printf("Date de Creation est: %d/%d/%d\n", m.dateCreation.jour, m.dateCreation.mois, m.dateCreation.annee);
    printf("Statut : %s\n", m.status);

    printf("-----------------------------\n");
}

void affichplus(tache m[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Identifiant : %d\n", m[i].identifiant);
        printf("Titre de la tache : %s\n", m[i].titre);
        printf("Description : %s\n", m[i].description);
        printf("Deadline : %d/%d/%d\n", m[i].deadline.jour, m[i].deadline.mois, m[i].deadline.annee);
        printf("Date de Creation est: %d/%d/%d\n", m[i].dateCreation.jour, m[i].dateCreation.mois, m[i].dateCreation.annee);
        printf("Statut : %s\n", m[i].status);
        printf("-----------------------------\n");
    }
}

void trierParDeadline(tache m[], int n)
{
    for (int i = 1; i < n; i++)
    {
        tache tacheCourante = m[i];
        int j = i - 1;

        int dateCourante = tacheCourante.deadline.annee * 10000 + tacheCourante.deadline.mois * 100 + tacheCourante.deadline.jour;

        while (j >= 0 && (m[j].deadline.annee * 10000 + m[j].deadline.mois * 100 + m[j].deadline.jour) > dateCourante)
        {
            m[j + 1] = m[j];
            j--;
        }

        m[j + 1] = tacheCourante;
    }
}
void dead_linebetween3day(tache taches[])
{
    int i;
    int delai_jour;
    int jours;
    int tab[taille];
    time_t seconds = time(NULL);
    struct tm datecourante = *localtime(&seconds);
    int Year = (datecourante.tm_year + 1900);
    int Month = (datecourante.tm_mon + 1);
    int Day = datecourante.tm_mday;

    for (i = 0; i < taille; i++)
    {
        jours = taches[i].deadline.annee * 365 + taches[i].deadline.mois * 30 + taches[i].deadline.jour;
        delai_jour = jours - (Year * 365 + Month * 30 + Day);
        tab[i] = delai_jour;
    }
    for (int i = 0; i < taille; i++)
    {
        if (tab[i] == 0)
        {
            printf("|id : %d\n |Titre : %s |  \n |description :%s  est : Aujourdui\n", taches[i].identifiant, taches[i].titre,taches[i].description);
        }
        else if (tab[i] <= 3 && tab[i]>0 )
        {
            printf("|id : %d \n |Titre : %s   \n |description :%s   \n |Deadline ds : %d  jours\n", taches[i].identifiant, taches[i].titre,taches[i].description, tab[i]);
        }
     /*   else if( tab[i]<0){
            printf("id : %d | Titre : %s | Deadlinejoursdeja epuisee\n", taches[i].identifiant, taches[i].titre);
        }else{

        }*/

    }
}
int supprimertacheparID(tache m[], int *taille)
{
    int id;
    printf("Entrer l ID de la tache a supprimer : ");
    scanf("%d", &id);
    int index = -1;

    for (int i = 0; i < *taille; i++)
    {
        if (m[i].identifiant == id)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        for (int i = index; i < *taille - 1; i++)
        {
            m[i] = m[i + 1];
        }
        (*taille)--;
    }
    else
    {
        printf("Identifiant non trouve.\n");
    }

    return *taille;
}


void rechercheparid(tache m[])
{int identif;
    printf("entrer ID a modifier");
    scanf("%d", &identif);
    for (int i = 0; i < taille; i++)
    {
        if (m[i].identifiant == identif)
        {
            affich(m[i]);
            break;
        }
    }
     printf("tache introuvable\n");
}
void recherchepartitre(tache m[])
{
    char rechtitre[100];
    printf("entrer le titre a rechercher :");
    scanf(" %[^\n]", rechtitre);
    for (int i = 0; i < taille; i++)
    {
        if (strcmp(m[i].titre, rechtitre) == 0)
        {
            affich(m[i]);
            break;
        }
    }
     printf("tache introuvable\n");
}

void modifierdescrip(tache m[])
{
    int index = -1; 
    int identif;
    printf("Entrer ID que vous vouler  modifier sa description :");
    scanf("%d", &identif);
    for (int i = 0; i < taille; i++)
    {
        if (m[i].identifiant == identif)
        {
            index = i;
            break;
        }
    }

    if (index != -1) ////juste pour verifier si l'ID existe ou non
    { 
        char newdescrip[800];
        printf("donner la  nouvelle  description : ");
        scanf(" %[^\n]", newdescrip);
        strcpy(m[index].description, newdescrip);
    }
    else
    {
        printf("Identifiant non trouve.\n");
    }
}

void modifierdeadline(tache m[])
{
    int identif;
    printf("Entrer ID que vous vouler  modifier sa deadline:");
    scanf("%d", &identif);
    int index = -1;

    for (int i = 0; i < taille; i++)
    {
        if (m[i].identifiant == identif)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        int jour, mois, annee;
        printf("Donner la nouvelle date sous forme (JJ/MOIS/ANNEE) : ");
        scanf("%d/%d/%d", &jour, &mois, &annee);
        m[index].deadline.jour = jour;
        m[index].deadline.mois = mois;
        m[index].deadline.annee = annee;
    }
    else
    {
        printf("Identifiant non trouve.\n");
    }
}

void modifierstatus(tache m[])
{
    int identif;
    printf("Entrer ID que vous vouler  modifier son status :");
    scanf("%d", &identif);
    int index = -1;

    for (int i = 0; i < taille; i++)
    {
        if (m[i].identifiant == identif)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        char status[100];
        printf("Modifier le statut (a realiser/en cours de realisation/finalisee) : ");
        scanf(" %[^\n]", status);
        strcpy(m[index].status, status);
    }
    else
    {
        printf("Identifiant non trouve.\n");
    }
}
void afficherNombreTotalTaches(tache m[])
{
    printf("Le nombre total de taches est : %d\n", taille);
}
void afficherNombreTachesCompletesEtIncompletes(tache m[])
{
    int complet = 0, incomplet = 0;

    for (int i = 0; i < taille; i++)
    {
        if (strcmp(m[i].status, "finalisee") == 0)
        {
            complet++;
        }
        else
        {
            incomplet++;
        }
    }

    printf("Nombre de taches completes : %d\n", complet);
    printf("Nombre de taches incompletes : %d\n", incomplet);
}
void deadlinerest(tache taches[])
{
    time_t seconds = time(NULL);
    struct tm datecourante = *localtime(&seconds);
    int Year = (datecourante.tm_year + 1900);
    int Month = (datecourante.tm_mon + 1);
    int Day = datecourante.tm_mday;

    for (int i = 0; i < taille; i++)
    {
        int jours = taches[i].deadline.annee * 365 + taches[i].deadline.mois * 30 + taches[i].deadline.jour;
        int delai_jour = jours - (Year * 365 + Month * 30 + Day);
        if (delai_jour>=0){
        printf("Identifiant : %d\n", taches[i].identifiant);
        printf("Titre de la tache : %s\n", taches[i].titre);
        printf("Description : %s\n", taches[i].description);
        printf("Deadline : %d/%d/%d\n", taches[i].deadline.jour, taches[i].deadline.mois, taches[i].deadline.annee);
        printf("Statut : %s\n", taches[i].status);
        printf("Nombre de jours restants jusqu'au delai : %d\n", delai_jour);
        printf("-----------------------------\n");
        }
        else
        {
        break;

        }
        
    }
}

int main()
{
    tache M[100];

    // ajouterplusieurtache(M);

    int choice, options1, options2, options3, options4;
    int a; 
    do
    {
          start :


        // system("Cls");
        printf("\n\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~Menu~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        printf("\t\t\t\t\t1. Ajouter une tache \n");
        printf("\t\t\t\t\t2. Ajouter plusieurs taches \n");
        printf("\t\t\t\t\t3. afficher les taches \n");
        printf("\t\t\t\t\t4. Modifier un tache\n");
        printf("\t\t\t\t\t5. Supprimer une tache par identifiant\n");
        printf("\t\t\t\t\t6. Rechercher les taches\n");
        printf("\t\t\t\t\t7. Statistiques  \n");
        printf("\t\t\t\t\t8. Exit\n");
        printf("\n\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~Menu~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        printf("Entrer votre choix: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            ajoutertache(M);
            break;
        case 2:
            ajouterplusieurtache(M);
            break;
        case 3:
               {

            printf("\t\t\t\t\t1. Trier les taches par ordre alphabetique \n");
            printf("\t\t\t\t\t2. Trier les par deadline \n");
            printf("\t\t\t\t\t3. Afficher les taches dont le deadline est dans 3 jours ou moins\n");
            printf("\t\t\t\t\t4. retour au menu principal \n");
            printf("Entrer votre choix: ");
            scanf("%d", &options1);

            switch (options1)
            {

            case 1:
                affiche_trialphabet(M, taille);
                affichplus(M,taille);
                break;
            case 2:
                trierParDeadline(M, taille);
                affichplus(M,taille);
                break;
            case 3:
                dead_linebetween3day(M);

                break;
            case 4:
              goto start;
                break;
            default:
                printf("exit");
                break;
            }
            break;}
        case 4:
            printf("\t\t\t\t\t1. Modifier la description d'une tâche. \n");
            printf("\t\t\t\t\t2. Modifier le statut d une tâche. \n");
            printf("\t\t\t\t\t3. Modifier la deadline d une tâche.\n");
            printf("\t\t\t\t\t4. retour au menu principal \n");
            
            printf("Enter your choice: ");
            scanf("%d",&options2);
            switch (options2)
            {
            case 1:
                modifierdescrip(M);
                break;
            case 2:
                modifierstatus(M);
            case 3:
                modifierdeadline(M);
            case 4:
                goto start;
            default:
                break;
            }
            break;
        case 5:
            taille = supprimertacheparID(M, &taille);
            break;
        case 6:

          {


            printf("\t\t\t\t\t1. Rechercher une tache par son Identifiant \n");
            printf("\t\t\t\t\t2. Rechercher une tache par son Titre \n");
            printf("\t\t\t\t\t3. Retour au menu principal \n");
            printf("Enter your choice: ");
            scanf("%d",&options3);
            switch (options3)
            {
            case 1:
            rechercheparid(M);
            break;
            case 2:
                   recherchepartitre(M);
                   break;
            case 3:
            goto start;
                break;

            default:
                break;
            }}
         break;
        case 7:
            {
                printf("\t\t\t\t\t1. Afficher le nombre total des taches. \n");
            printf("\t\t\t\t\t2. Afficher le nombre de taches completes et incompletes. \n");
            printf("\t\t\t\t\t3. Afficher le nombre de jours restants jusqu'au delai de chaque tache. \n");
            printf("\t\t\t\t\t4. Retour au menu principal \n");
            printf("Enter your choice: ");
            scanf("%d",&options4);
            switch (options4)
            {
            case 1:
                 afficherNombreTotalTaches(M);
              break;
            case 2:
                afficherNombreTachesCompletesEtIncompletes(M);
               break;
            case 3:
                deadlinerest(M);
                break;
            case 4:
            goto start;
            default:
                break;
            }}

            break;
            case 8:
                break;
        default:
            printf("Invalid choice, please try again.\n");
        }
        
        printf("veuillez Quitter l'application \n  1- oui \n 2- non \n Entrer votre choix (1/2):");
        scanf("%d",&a);
    } while (a==2);
    return 0;
}
