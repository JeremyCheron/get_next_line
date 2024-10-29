# 42 Get Next Line

Le but de get_next_line est de lire un fichier ligne par ligne sans charger l’ensemble du fichier en mémoire.

## Fonction principale get_next_line :

La fonction utilise un buffer pour lire le fichier par segments de taille BUFFER_SIZE.
Si le fichier ou la taille de buffer est incorrecte, elle retourne NULL.
La lecture est faite par l’intermédiaire de la fonction _fill_line.

## Fonction _fill_line :

Lit le fichier jusqu’à trouver un \n ou atteindre la fin du fichier.
Les données lues sont ajoutées à la variable filled, qui contient le texte accumulé.
Si une erreur de lecture survient, la mémoire est libérée et NULL est retourné.

## Fonction _set_line :

Sert à couper la ligne à chaque \n pour isoler la prochaine portion de texte à lire.
Elle conserve le reste du texte dans la variable old, pour être utilisé lors de l’appel suivant de get_next_line.

## Fonctions utilitaires :

ft_strlen, ft_strjoin, ft_strdup, et ft_substr : ces fonctions gèrent les opérations sur les chaînes de caractères, comme mesurer leur longueur, les joindre, les copier ou créer des sous-chaînes.
Ce fonctionnement permet d'appeler get_next_line plusieurs fois pour obtenir chaque ligne du fichier jusqu’à la fin.
