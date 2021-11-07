<!-- 
	05/11/2021
	server/statement.php
	PHP CALL POUR AJOUTER LES INFORMATIONS RECOLTEES
	PAR L'ESP32 DANS LA BDD DE MANIERE SECURISEE
-->

<?php

	// if(isset($_POST["report"])) {

		$token = $_POST["token"];

		require_once "php/inc/functionlibrary.inc.php";

		if(tokenIsValid($token)) {
			
			$engineId = $_POST["engine_id"];
			$isOn = $_POST["is_on"];
			$timestamp = $_POST["timestamp"];

			require_once "php/inc/databasehandler.inc.php";

			// on récupère on vérifie que la machine existe dans la table
			// -> si c'est le cas on l'ajoute dans la bdd
			if(engineExistInDb($conn, $engineId) != false) {
				// on ajoute les infos que on a récupérer dans la bdd
				addTimeRangeInDb($conn, $engineId, $timestamp, $isOn);
				// on change le state de la machine dans la bdd
				updateEngineInDb($conn, $engineId, $isOn);
			}
			// -> si non alors on fait rien
			else {
				exit();
			}
		}
		else {
			exit();
		}
	// }
	// else {
	// 	header("location: server.php");
	// 	exit();
	// }