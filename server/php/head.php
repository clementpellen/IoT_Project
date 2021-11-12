<!-- 
	02/11/2021
	server/php/head.php
	CODE REQUIRE A CHAQUE DEBUT DE PAGE PHP AFIN
	DE NE PAS SE REPETER POUR LES DIFFERENTES PAGES
-->

<?php
	if(!isset($_SESSION)) { 
		session_start();
		require_once "inc/databasehandler.inc.php";
		require_once "inc/functionlibrary.inc.php";
		setTrigger($conn, true);
	}
?>

<!DOCTYPE html>

<html lang="fr" dir="ltr">

<head>
	<title>Checker</title>
	<meta charset="utf-8">
	<link rel="stylesheet" href="css/reset.css"  type="text/css"/>
	<link rel="stylesheet" href="css/style.css"  type="text/css"/>
	<!-- <link rel="icon" href="src/favicon.ico" type="image/x-icon" sizes="128x128"> -->

	<link rel="preconnect" href="https://fonts.gstatic.com">
	<link rel="preconnect" href="https://fonts.googleapis.com">
	<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
	<link href="https://fonts.googleapis.com/css2?family=Quicksand:wght@500&display=swap" rel="stylesheet">
</head>

<body>
