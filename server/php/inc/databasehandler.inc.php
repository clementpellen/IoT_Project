<!-- 
	02/11/2021
	server/php/inc/databasehandler.php
	CODE PHP POUR SE CONNECTER A LA BDD. IL EST
	APPELE POUR CHAQUE INTERACTION AVEC LA BDD
-->

<?php
	$dbServername = "localhost";
	$dbUsername = "root";
	$dbPassword = "";
	$dbName = "factory";

	$conn = mysqli_connect($dbServername,$dbUsername,$dbPassword,$dbName);

	$conn or die("<p>Error connecting to database: " .mysql_connect_error() . "</p>");