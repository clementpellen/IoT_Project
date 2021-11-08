<!-- 
	04/11/2021
	server/php/inc/functionlibrary.php
	LIBRAIRIE DE L'ENSEMBLE DES FONCTIONS QUI
	SERONT APPELEES DANS LE CODE PHP
-->

<?php

	// verifie l'etat du trigger(gachette) pour s'assurer
	// que les informations ont bien changé afin de ne pas les recopier
	function checkTrigger($conn) {
		$sql = "SELECT modified FROM modification_trigger ;";
		$stmt = mysqli_stmt_init($conn);
		if(!mysqli_stmt_prepare($stmt, $sql)) {
			header("location: ../../server?error=stmtfailed");
			exit();
		}

		mysqli_stmt_execute($stmt);

		$resultData = mysqli_stmt_get_result($stmt);

		if($row = mysqli_fetch_assoc($resultData)) {
			return $row["modified"];
		}
		else {
			header("location: ../../server?error=stmtfailed");
			exit();
		}
		mysqli_stmt_close($stmt);
	}

	// activer le trigger de changement
	function setTrigger($conn, $state) {
		$sql = "UPDATE modification_trigger SET modified = ?;";
		$stmt = mysqli_stmt_init($conn);
		if(!mysqli_stmt_prepare($stmt, $sql)) {
			header("location: ../../server?error=stmtfailed");
			exit();
		}

		mysqli_stmt_bind_param($stmt, "i", $state);
		mysqli_stmt_execute($stmt);

		$resultData = mysqli_stmt_get_result($stmt);

		mysqli_stmt_close($stmt);
	}

	// récupérer les données dans la table engines de la bdd
	function getEngineInfos($conn, $engineId) {
		$sql = "SELECT * FROM engines WHERE (id = ?);";
		$stmt = mysqli_stmt_init($conn);
		if(!mysqli_stmt_prepare($stmt, $sql)) {
			header("location: ../../server?error=stmtfailed");
			exit();
		}

		mysqli_stmt_bind_param($stmt, "i", $engineId);
		mysqli_stmt_execute($stmt);

		$resultData = mysqli_stmt_get_result($stmt);

		if($row = mysqli_fetch_assoc($resultData)) {
			return $row;
		}
		else {
			$result = false;
			return $result;
		}
		mysqli_stmt_close($stmt);
	}

	// récupérer les données dans la table time_ranges de la bdd
	function getTimeRanges($conn, $engineId) {
		$sql = "SELECT * FROM time_ranges WHERE (engine_id = ?);";
		$stmt = mysqli_stmt_init($conn);
		if(!mysqli_stmt_prepare($stmt, $sql)) {
			header("location: ../../server?error=stmtfailed");
			exit();
		}

		mysqli_stmt_bind_param($stmt, "i", $engineId);
		mysqli_stmt_execute($stmt);

		$resultData = mysqli_stmt_get_result($stmt);

		// ici on utilise fetch_all et pas fetch_asssoc pour récupérer toutes les lignes de résultats et pas
		// une unique (on met en parametre le MYSQLI_ASSOC pour rester sur le meme format de tableau associatif)
		if($rows = mysqli_fetch_all($resultData, MYSQLI_ASSOC)) {
			return $rows;
		}
		else {
			$result = false;
			return $result;
		}
		mysqli_stmt_close($stmt);
	}

	// recréer un clef pour la hash et la comparer avec le token de sécurité
	function tokenIsValid($token, $tic) {
		// on crée un string unique et hardcodé
		$salt = "iotprojet";
		// on genère le hash avec la méthode md5 pour pouvoir le comparer à celui généré par l'ESP32 de la meme manière
		$key = md5($salt . $tic);
		// on return true ou false en fonction de l'équivalence entre les deux tokens
		return $key == $token;
	}

	// vérifier que la machine existe bien dans la bdd
	function engineExistInDb($conn, $engineId) {
		$sql = "SELECT * FROM engines WHERE id = ?;";
		$stmt = mysqli_stmt_init($conn);
		if(!mysqli_stmt_prepare($stmt, $sql)) {
			exit();
		}

		mysqli_stmt_bind_param($stmt, "i", $engineId);
		mysqli_stmt_execute($stmt);

		$resultData = mysqli_stmt_get_result($stmt);

		if($row = mysqli_fetch_assoc($resultData)) {
			return $row;
		}
		else {
			$result = false;
			return $result;
		}
		mysqli_stmt_close($stmt);
	}

	// ajouter les informations de l'ESP32 à la bdd
	function addTimeRangeInDb($conn, $engineId, $timestamp, $isOn) {
		$sql = "INSERT INTO time_ranges(engine_id, timestamp, is_on) VALUES (?,?,?);";

		$stmt = mysqli_stmt_init($conn);
		if(!mysqli_stmt_prepare($stmt, $sql)) {
			exit();
		}

		mysqli_stmt_bind_param($stmt, "isi", $engineId, $timestamp, $isOn);
		mysqli_stmt_execute($stmt);
		mysqli_stmt_close($stmt);
	}

	// mettre à jour l'information de state des machines dans la table engines de la bdd
	function updateEngineInDb($conn, $engineId, $isOn) {
		$sql = "UPDATE engines SET is_on= ? WHERE engines.id = ?;";

		$stmt = mysqli_stmt_init($conn);
		if(!mysqli_stmt_prepare($stmt, $sql)) {
			return false;
		}

		mysqli_stmt_bind_param($stmt, "ii", $isOn, $engineId);
		mysqli_stmt_execute($stmt);
		mysqli_stmt_close($stmt);

		return true;
	}

	// on trie le tableau de timestamp pour s'assurer que tt est dans le bon ordre
	function sortTimestamp() {
		// pour pouvoir modifier dans un foreach on doit utiliser une référence
		foreach ($_SESSION["engines"] as &$engine) {
			// si le mysqli_fetch_all return false alors on ne touche pas aux time_ranges
			if($engine["time_ranges"]) {
				// trie un tableau en utilisant une fonction de comparaison ici "cmp"
				usort($engine["time_ranges"], "cmp");
			}
		}
	}

	// fonction de comparaison qui fait la soustraction entre les timestamps
	function cmp($a, $b) {
		$a = strtotime($a["timestamp"]);
		$b = strtotime($b["timestamp"]);
		return $a - $b;
	}

	// récup la différence de temps de la précedante session
	function getPrevTimingSession($engineId) {
		if($_SESSION["engines"][$engineId]["time_ranges"] != false) {
			$a = end($_SESSION["engines"][$engineId]["time_ranges"]);
			$b = prev($_SESSION["engines"][$engineId]["time_ranges"]);
			return timestampToTime(cmp($a, $b));
		}
		else {
			return "aucun changement";
		}
		
	}

	// récup la différence de temps de la session
	function getTimingSession($engineId) {
		if($_SESSION["engines"][$engineId]["time_ranges"] != false) {
			$a = time();
			$b = end($_SESSION["engines"][$engineId]["time_ranges"]);
			$b = strtotime($b["timestamp"]);
			return timestampToTime($a-$b);
		}
		else {
			return "aucun changement";
		}
		
	}

	// convert into Years, Months, Days, Hours, Minutes and Seconds
	function timestampToTime($sec){
		$a = new DateTime("@0");
		$b = new DateTime("@$sec");
		$interval =  date_diff($a, $b);
		return $interval->format('%y ans %m mois %d jours %h h %i min %s sec');
	}

	// récup le pourcentage et afficher
	function getPourcentage($engineId) {
		
		$pourcentage = 0;
		$bufferOn = 0; $bufferOff = 0;
		$totalOff = 0; $totalOn = 0;
		$lastState = true;

		if($_SESSION["engines"][$engineId]["time_ranges"] != false) {
			// pour pouvoir modifier dans un foreach on doit utiliser une référence
			foreach ($_SESSION["engines"][$engineId]["time_ranges"] as &$time_range) {
				// si c'est on
				if($time_range["is_on"]) {
					$bufferOn = strtotime($time_range["timestamp"]);
					if($bufferOff != 0) {
						$totalOff = $bufferOn - $bufferOff;
					}
					$lastState = true;
				}
				// si c'est off
				else {
					$bufferOff = strtotime($time_range["timestamp"]);
					if($bufferOn != 0) {
						$totalOn = $bufferOff - $bufferOn;
					}
					$lastState = false;
				}
			}

			if($lastState) {
				$totalOn = time() - $bufferOn;
			}
			else {
				$totalOff = time() - $bufferOff;
			}

			$pourcentage = $totalOn / $totalOff;
			$pourcentage = number_format($pourcentage, 1, '.', '');
		}
		return $pourcentage;
	}