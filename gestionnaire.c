#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int C; // Capacité maximale d'éléments que peut contenir le magasin

typedef struct {
    char nom[50];
    char categorie[50];
    float prix;
    int quantite;
} Produit;


int main() {
    // Menu 
    printf("===================Bienvenue ! Il s'agit d'un gestionaire d'inventaire afin de permettre une meilleure organisation de votre magasin ==================\n");
    FILE *file = fopen("Gestionnaire.bin","ab+");
    int nombreDarticles = 0;
    
    // Demander la capacité maximale du magasin
    printf("Quelle est la capacite maximale de votre magasin ?\n");
    scanf("%d", &C);
    
    // Allouer de la mémoire pour l'inventaire
    Produit *inventaire = NULL;
    inventaire = (Produit *)malloc(C * sizeof(Produit));
    if (inventaire == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        return 1;
    }
    /*j'ai ecrie les fonctions dont on a besoin . Maintenant, j' aimerais qu'on reflechisses enssemble à comment les les faires fonctionner enssemble */

   // Libérer la mémoire allouée
    free(inventaire);
    // Affichage de l'inventaire actuellement présent dans le fichier
    printf("Voici l'inventaire actuelle de votre magasin \n");
    affichageInventaire(file);

    // Menu pour le choix de l'opération a effectuer 
    printf("Que souhaitez vous faire ? \n Tapez : \n 1- Ajouter des produits \n 2- Modifiez la quantite ou le prix \n 3- Supprimez les produits \n 4-Recherchez les produits \n ");
    int make;
    scanf("%d",&make);
    switch (make)
    {
    case 1:
        ajouterElements(file,inventaire,&nombreDarticles);
        break;
    case 2:
        modifierProduit(file,inventaire,&nombreDarticles);
        break;
    case 3:
        supprimerProduit(file,inventaire,&nombreDarticles);
        break;
    case 4:
        chercherProduit(inventaire,&nombreDarticles);
        break;
    }

    return 0;
}

/* Fonction pour ajouter des produits à l'inventaire.
 * Paramètres :
 * - inventaire[] : tableau dynamique contenant les produits.
 * - nombreDarticles : pointeur vers le nombre actuel d'articles.
 */
void ajouterElements(FILE *file,Produit inventaire[], int *nombreDarticles) {
    if (*nombreDarticles >= C) {
        printf("L'inventaire est plein. Impossible d'ajouter plus de produits.\n");
        return;
    } else {
        // Demander les informations du produit
        printf("Nom du produit: ");
        scanf("%s", inventaire[*nombreDarticles].nom);
        printf("Categorie: ");
        scanf("%s", inventaire[*nombreDarticles].categorie);
        printf("Prix: ");
        scanf("%f", &inventaire[*nombreDarticles].prix);
        printf("Quantite: ");
        scanf("%d", &inventaire[*nombreDarticles].quantite);

        printf("Produit ajoute avec succes !\n");
        (*nombreDarticles)++;
        fwrite(inventaire,sizeof(Produit),1,file);
    }
}

void chercherProduit(Produit inventaire[], int nombreDarticles) {
    int choix; // Choix de l'utilisateur : rechercher par nom ou catégorie
    char recherche[50]; // Nom ou catégorie à rechercher
    int produitTrouve = 0; // Indicateur si un produit a été trouvé

    // Demander à l'utilisateur s'il veut chercher par nom ou catégorie
    printf("Rechercher un produit :\n");
    printf("1. Par nom\n");
    printf("2. Par categorie\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    if (choix == 1) {
        printf("Entrez le nom du produit a rechercher : ");
        scanf("%s", recherche);
        for (int i = 0; i < nombreDarticles; i++) {
            if (strcmp(inventaire[i].nom, recherche) == 0) {
                printf("\nProduit trouve :\n");
                printf("Nom : %s\n", inventaire[i].nom);
                printf("Categorie : %s\n", inventaire[i].categorie);
                printf("Prix : %.2f\n", inventaire[i].prix);
                printf("Quantite : %d\n", inventaire[i].quantite);
                produitTrouve = 1;
            }
        }
    } 
    else if (choix == 2) {
        printf("Entrez la categorie à rechercher : ");
        scanf("%s", recherche);
        for (int i = 0; i < nombreDarticles; i++) {
            if (strcmp(inventaire[i].categorie, recherche) == 0) {
                printf("\nProduit trouve :\n");
                printf("Nom : %s\n", inventaire[i].nom);
                printf("Categorie : %s\n", inventaire[i].categorie);
                printf("Prix : %.2f\n", inventaire[i].prix);
                printf("Quantite : %d\n", inventaire[i].quantite);
                produitTrouve = 1;
            }
        }
    } 
    else {
        printf("Choix invalide. Veuillez entrer 1 ou 2.\n");
        return;
    }

    // Si aucun produit n'a été trouvé
    if (!produitTrouve) {
        printf("Aucun produit correspondant trouve dans l'inventaire.\n");
    }
}

void modifierProduit(FILE *file,Produit inventaire[], int nombreDarticles) {
    char nom[50];         // Nom du produit à modifier
    char categorie[50];   // Catégorie du produit à modifier
    int produitTrouve = 0; // Indicateur si le produit a été trouvé
    int choix;            // Choix de l'utilisateur pour modifier prix ou quantité

    printf("Entrez le nom du produit à modifier : ");
    scanf("%s", nom);
    printf("Entrez la catégorie du produit : ");
    scanf("%s", categorie);

    // Parcourir l'inventaire pour trouver le produit
    for (int i = 0; i < nombreDarticles; i++) {
        if (strcmp(inventaire[i].nom, nom) == 0 && strcmp(inventaire[i].categorie, categorie) == 0) {
            produitTrouve = 1; // Produit trouvé
            printf("\nProduit trouve :\n");
            printf("Nom : %s\n", inventaire[i].nom);
            printf("Categorie : %s\n", inventaire[i].categorie);
            printf("Prix actuel : %.2f\n", inventaire[i].prix);
            printf("Quantite actuelle : %d\n", inventaire[i].quantite);

            // Demander quelle modification effectuer
            printf("\nQue voulez-vous modifier ?\n");
            printf("1. Modifier le prix\n");
            printf("2. Modifier la quantité\n");
            printf("Votre choix : ");
            scanf("%d", &choix);

            if (choix == 1) {
                // Modifier le prix
                printf("Entrez le nouveau prix : ");
                scanf("%f", &inventaire[i].prix);
                printf("Le prix a été mis à jour avec succès.\n");
            } 
            else if (choix == 2) {
                // Modifier la quantité
                printf("Entrez la nouvelle quantite : ");
                scanf("%d", &inventaire[i].quantite);
                printf("La quantite a été mise à jour avec succes.\n");
            } 
            else {
                printf("Choix invalide.\n");
            }
            return; // Sortir après modification
        }
        fwrite(inventaire,sizeof(Produit),1,file);
    }

    // Si le produit n'a pas été trouvé
    if (!produitTrouve) {
        printf("Produit non trouve dans l'inventaire.\n");
    }
}

void supprimerProduit(FILE *file,Produit inventaire[], int *nombreDarticles) {
    char nom[50];         // Nom du produit à supprimer
    char categorie[50];   // Catégorie du produit à supprimer
    int produitTrouve = 0; // Indicateur si le produit a été trouvé

    printf("Entrez le nom du produit a supprimer : ");
    scanf("%s", nom);
    printf("Entrez la categorie du produit : ");
    scanf("%s", categorie);

    // Parcourir l'inventaire pour trouver le produit
    for (int i = 0; i < *nombreDarticles; i++) {
        if (strcmp(inventaire[i].nom, nom) == 0 && strcmp(inventaire[i].categorie, categorie) == 0) {
            produitTrouve = 1; // Produit trouvé
            printf("\nProduit trouve :\n");
            printf("Nom : %s\n", inventaire[i].nom);
            printf("Categorie : %s\n", inventaire[i].categorie);
            printf("Prix : %.2f\n", inventaire[i].prix);
            printf("Quantite : %d\n", inventaire[i].quantite);

            // Décalage des éléments suivants pour supprimer le produit
            for (int j = i; j < *nombreDarticles - 1; j++) {
                inventaire[j] = inventaire[j + 1]; // Décaler l'élément suivant
            }

            // Réduire la taille de l'inventaire
            (*nombreDarticles)--;

            printf("Produit supprime avec succès.\n");
            return; // Sortir après suppression
        }
    }

    // Si le produit n'a pas été trouvé
    if (!produitTrouve) {
        printf("Produit non trouvé dans l'inventaire.\n");
    }
    fwrite(inventaire,sizeof(Produit),1,file);
}

void sauvegarderInventaire(Produit inventaire[], int nombreDarticles) {
    FILE *fichier = fopen("inventaire.bin", "wb");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier pour la sauvegarde.\n");
        return;
    }else {
        // Sauvegarder le nombre d'articles
    fwrite(&nombreDarticles, sizeof(int), 1, fichier);

    // Sauvegarder les produits
    fwrite(inventaire, sizeof(Produit), nombreDarticles, fichier);
    printf("Inventaire sauvegardé avec succès.\n");

    }
}

void affichageInventaire(FILE *file) {
    Produit p;
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier pour le chargement.\n");
        return;
    }else
    {
        while (fread(&p, sizeof(Produit), 1, file) == 1) {
        printf("Nom : %s ; Catégorie : %s ; Prix : %.2f ; Quantité : %d\n", 
               p.nom, p.categorie, p.prix, p.quantite);
    }
        printf("Inventaire chargé avec succès.\n");
        
    }
}
