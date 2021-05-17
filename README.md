# PS4BNB_C
  Programe C (niveau 1) de simulation du processus de création monétaire et de cheater.

## Compilation du programme
  - Pour compiler le programme en mode release (avec optimisation du compilateur), taper la commande ci-dessous dans un terminal à la racine du projet : 
  ```make
  make
  ```
  
- Pour compiler en mode debug il faudra taper dans le terminal :
```make
make DEBUG=yes
```
Quoi qu'il arrive, les fichiers objets (.o) seront stockés dans le dossier obj et l'exécutable se trouvera dans le dossier bin. Ces deux dossiers seront crée s'ils sont inexistants.

## Reconstruction du projet et nettoyage
  - Pour nettoyer le projet des fichiers objets (.o) taper à la racine du projet dans un terminal
  ```make
  make clean
  ```
  - En peut aussi avoir besoin de nettoyer les fichiers objets et de supprimer l'exécutable en même temps, la commande suivante répond à ce besoin :
  ```make
  make mrproper
  ```
  - Si l'on souhaite carrément reconstruire le projet de façon propre, on peut utiliser la commande suivante qui supprime les fichiers objets et l'exécutable et recompile le programme :
  ```make
  make remake
  ```
## Générer la documentation
  - Pour générer la documentation dans le dossier doc, il suffit de taper cette commande dans un terminal à la racine du projet :
  ```make
  make doc
  ```
  ***Attention ! pdflatex est nécessaire pour générer la documentation au format pdf ! Risque de message d'erreur si pdflatex n'est pas installé.
  Cependant si pdflatex n'est pas installé, la documentation html est quand même généré.***

  - Pour nettoyer le dossier de documentation sans supprimer le fichier de configurations, il suffit de taper la commande suivante :
  ```make
  make doc-clean
  ```
## Exécution du programme et paramétrage
  - Une fois compilé, le programme se trouve dans le dossier bin, pour l'exécuter rien de plus simple, à la racine du projet et dans un terminal, taper ceci :
  ```sh
  bin/simuBnb
  ```
  - Le fichiers de configuration `config.cfg` se trouvant à la racine permet le paramétrage de l'exécution du programme. Voici les paramètres disponible :
  - - Les champs relatifs à la blockchain :
  - - - `DIFFICULTY`    Définit la difficulté du minage, doit être un entier positif non nul.
  - - - `MAX_BLOCK`     Définit le nombre max de bloc que doit contenir la blockchain, doit être un entier positif non nul.
  - - - `MAX_USER`      Définit le nombre d'utilisateur crée pour la simulation, doit être un entier positif non nul.
  - - - `REWARD`        Définit la récompense initiale de la blockchain en satoBnb (donc un entier positif).
  - - - `BNB_HALVING`   Définit le nombre de bloc ou la récompense doit être divisé par 2, doit être un entier positif.

  - - Les champs relatifs aux transactions :
  - - - `MAX_TX_IN_BLOCK`   Définit le nombre max de transactions que peut contenir un bloc, doit être un entier positif non nul.
  - - - `MAX_TX_AMOUNT`     Définit le montant max généré en satoBnb des transactions, doit être un entier positif.

  - - Les champs relatifs à la blockchain :
  - - - `CHEATER_BLOCK`          Si définit à 0, le cheater block sera désactivé pendant l'exécution, le définir à 1 l'active durant l'exécution.
  - - - `CHEATER_TRANSACTION`    Si définit à 0, le cheater transaction sera désactivé pendant l'exécution, le définir à 1 l'active durant l'exécution.
  - - - `CHEATER_FREQUENCY`      Définit la fréquence d'activation des cheaters durant l'exécution du programme, doit être un réel entre 0 et 1, par exemple si définit à 0.1 la fréquence d'activation des cheaters est de 10%, si définit à 0, les cheaters seront automatiquement désativé même si les deux paramètres précédents sont définis sur 1.