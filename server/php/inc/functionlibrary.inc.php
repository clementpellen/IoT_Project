<!-- 
	03/11/2021
	server/php/inc/functionlibrary.php
	LIBRAIRIE DE L'ENSEMBLE DES FONCTIONS QUI
    SERONT APPELEES DANS LE CODE PHP.
-->

<?php

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

    // fonction qui verifie le timestamp pour s'assurer qu'il est bien different
    // du precedant et qu'on ne relaod pas les informations dans le vide
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

    function activateTrigger($conn) {
        $sql = "UPDATE modification_trigger SET modified = ?;";
		$stmt = mysqli_stmt_init($conn);
		if(!mysqli_stmt_prepare($stmt, $sql)) {
			header("location: ../../server?error=stmtfailed");
			exit();
		}

        $var = false;
		mysqli_stmt_bind_param($stmt, "i", $var);
		mysqli_stmt_execute($stmt);

		$resultData = mysqli_stmt_get_result($stmt);

		mysqli_stmt_close($stmt);
    }

    // arduino -> incremente un identifiant à chaque fois que il maj les infos dans la bdd
    // machines -> id / name / isOn
    // time_ranges -> id / engine id / start / end


    // function 
    