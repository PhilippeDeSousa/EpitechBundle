# Dashboard

### Lancement:
```
$ ./up.sh
```

### Connection:
```
$ firefox localhost:8080
```

## Services et widgets:
### Service météo
```
Widget Météo        -> Permet de connaître la météo pour une ville
```
### Service Stock
```
Widget Stock        -> Permet de connaître la valeur d'une action
```
### Service Recherche
```
Widget Youtube      -> permet la recherche de chaînes youtubes
Widget Wikipédia    -> permet la recherche de pâges wikipédia
Widget Steam        -> permet la recherche du prix d'un jeu Steam
Widget Pays         -> permet la recherche d'informations sur un pays
```

### Fonctionnement du projet:

    Au lancement, le serveur se connecte à la base de donnée MongoDB
    lancée par docker ou locale.
    Par la suite, l'utilisateur peut créer un compte, puis se connecter afin de profiter de son dashboard.
    Sur celui-ci, il peut choisir quels services ajouter, puis ajouter ses widget.

### Ajout d'un widget:

    Afin d'ajouter un widget, il faut tout d'abord ajouter son modèle dans le fichier user.js
    Suite à ça, il faut créer son controller dans route.js, et finalement ajouter sa partie front dans le dossier views (en ejs).

### Philippe De Sousa & Marc Perez
