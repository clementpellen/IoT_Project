<!-- 
	04/11/2021
	server/php/inc/functionlibrary.php
	ON CHARGE LES DONNEES DE LA BDD SI ELLES ONT CHANGE.
-->

<?php

	require_once "databasehandler.inc.php";
	require_once "functionlibrary.inc.php";

	// on récupère dans un boucle les informations de chaques machines
	for ($i = 1; $i < 4; $i++) {
		// on ajoute les informations à la session pour pouvoir les avoir sur la page d'affichage
		$_SESSION['engines'][$i] = getEngineInfos($conn, $i);
		
		// voir pour les ranger dans engines par odre croissant ou un truc du genre
		// call getTimeRanges avec l'id de la dernière time ranges pour ne pas les reload
		$_SESSION['engines'][$i]["time_ranges"] = getTimeRanges($conn, $i);
	}

	// on trie les dates une fois que on les a récup
	sortTimestamp();

	// on s'occupe de l'affichage des informations liées aux dates
	