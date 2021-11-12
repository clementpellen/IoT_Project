<!-- 
	08/11/2021
	server/statement.php
	PHP CALL POUR AJOUTER LES INFORMATIONS RECOLTEES
	PAR L'ESP32 DANS LA BDD DE MANIERE SECURISEE
-->

<?php

	$token = $_POST["token"];
	$tic = intval($_POST["tic"]);

	require_once "php/inc/functionlibrary.inc.php";

	if(tokenIsValid($token, $tic)) {
		
		$engineId = intval($_POST["engine_id"]);
		$isOn = intval($_POST["is_on"]);
		$timestamp = date("Y-m-d H:i:s",time());

		require_once "php/inc/databasehandler.inc.php";

		// on récupère on vérifie que la machine existe dans la table
		// -> si c'est le cas on l'ajoute dans la bdd
		if(engineExistInDb($conn, $engineId) != false) {
			// on ajoute les infos que on a récupérer dans la bdd
			addTimeRangeInDb($conn, $engineId, $timestamp, $isOn);
			// on change le state de la machine dans la bdd
			updateEngineInDb($conn, $engineId, $isOn);
			// on active le trigger
			setTrigger($conn, true);
		}
		// -> si non alors on fait rien
		else {
			exit();
		}
	}
	else {
		header("location: ../../server?token=notvalid");
		exit();
	}