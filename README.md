# IoT_Project

Bienvenue sur notre projet d'IoT d'optimisation de production d'usine

Auteurs :
- DESAUTEL Quentin
- PELLEN Clément

Les objectifs principaux de ce système sont :
- la gestion d'usine
- l'optimisation de production 
- la maintenance prédictive

Nous permettons avec notre solution à un gérant d'usine ou d'atelier de connaître la rentabilité de chacune de ses machines.
Le système embarqué étudie l'état de fonctionnement d'une machine (Allumée / Eteinte).
Il transmet en permanence cet état à un serveur qui réalise des statistiques de productivité de chacune des machines étudiées.

Lien du serveur : https://corner.soccer/iot/server.php


# Le Code 
dans engine_reader 📁,
↪ 4 dossiers .ino :

    - voltage_reader.ino : lit la tension en input et détermine si la machine est en fonctionnement
    - luminosity_reader.ino : lit la luminosité en input et détermine si la machine est en fonctionnement
    - acceleration_reader.ino : lit le mouvement en input et détermine si la machine est en fonctionnement
    - working_reader.ino : combine les features précédentes


# Le Montage

- 1 - Le processeur et la connexion : un Esp32
- 2 - La luminosité : une photorésistance
- 3 - Le mouvement : un MPU6050

