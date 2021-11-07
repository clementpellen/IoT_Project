<!-- 
	03/11/2021
	server/server.php
	CODE DE LA PAGE D'INTERFACE POUR AVOIR LES
	INFORMATIONS SUR LES MACHINES EN DIRECT
-->

<?php 
	require("php/head.php");

	// appel de la fonction pour charger les données
	include("php/inc/reloaddata.inc.php");

	$firstPourcentage =  getPourcentage(1);
	$secondPourcentage =  getPourcentage(2);
	$thirdPourcentage =  getPourcentage(3);
?>

<script>
    // toutes les secondes on appel la fonction pour refresh la page
	window.setInterval('refresh()', 1000); 	
	function refresh() {
		// on recharge la page
		window .location.reload();
    }
</script>

<main>
	<aside>
		<section id="engine1">
			<h1 style="float:right"><?= $_SESSION['engines']["1"]["is_on"] ? "&#9989" : "&#10060" ?></h1>
			<h1> &#128223 <?= $_SESSION['engines']["1"]["name"]?></h1>
			<span class="r"> Local 2 coté droit de la porte </span>
			<br>
			<br>
			<h2> &#128337 temps <?= $_SESSION['engines']["1"]["is_on"] ? "allumé" : "éteinte" ?> :</h2>
			<br>
			<span class="r"><?= getTimingSession(1) ?></span>
			<br>
			<h2> &#128281 temps de la dernière session :</h2>
			<br>
			<span class="r"><?= getPrevTimingSession(1) ?></span>
			<br>
			<h2> &#128198 date dernier changement :</h2> <?= $_SESSION['engines']["1"]["time_ranges"] != false ?
				end($_SESSION['engines']["1"]["time_ranges"])["timestamp"] : "aucun changement" ?>
		</section>
		<section id="engine2">
			<h1 style="float:right"><?= $_SESSION['engines']["2"]["is_on"] ? "&#9989" : "&#10060" ?></h1>
			<h1> &#128250 <?= $_SESSION['engines']["2"]["name"]?></h1>
			<span class="r"> Local 1 à coté du poteau central </span>
			<br>
			<br>
			<h2> &#128337 temps <?= $_SESSION['engines']["2"]["is_on"] ? "allumé" : "éteinte" ?> :</h2>
			<br>
			<span class="r"><?= getTimingSession(2) ?></span>
			<br>
			<h2> &#128281 temps de la dernière session :</h2>
			<br>
			<span class="r"><?= getPrevTimingSession(2) ?></span>
			<br>
			<h2> &#128198 date dernier changement :</h2> <?= $_SESSION['engines']["2"]["time_ranges"] != false ?
				end($_SESSION['engines']["2"]["time_ranges"])["timestamp"] : "aucun changement" ?>
		</section>
</aside>
	<section id="info">
		<h1> &#128202 Infos Machines </h1>
		<br>
		<br>
		<br>
		<div class="flex-wrapper">
			<div class="single-chart">
				<svg viewBox="0 0 36 36" class="circular-chart orange">
					<path class="circle-bg"
						d="M18 2.0845
							a 15.9155 15.9155 0 0 1 0 31.831
							a 15.9155 15.9155 0 0 1 0 -31.831"
					/>
					<path class="circle"
						stroke-dasharray="<?=$firstPourcentage?>, 100"
						d="M18 2.0845
							a 15.9155 15.9155 0 0 1 0 31.831
							a 15.9155 15.9155 0 0 1 0 -31.831"
					/>
					<text x="18" y="20.35" class="percentage">
						<?=$firstPourcentage?>%
					</text>
				</svg>
			</div>

			<div class="single-chart">
				<svg viewBox="0 0 36 36" class="circular-chart green">
					<path class="circle-bg"
					d="M18 2.0845
						a 15.9155 15.9155 0 0 1 0 31.831
						a 15.9155 15.9155 0 0 1 0 -31.831"
					/>
					<path class="circle"
					stroke-dasharray="<?=$secondPourcentage?>, 100"
					d="M18 2.0845
						a 15.9155 15.9155 0 0 1 0 31.831
						a 15.9155 15.9155 0 0 1 0 -31.831"
					/>
					<text x="18" y="20.35" class="percentage">
						<?=$secondPourcentage?>%
					</text>
				</svg>
			</div>

			<div class="single-chart">
				<svg viewBox="0 0 36 36" class="circular-chart blue">
					<path class="circle-bg"
						d="M18 2.0845
							a 15.9155 15.9155 0 0 1 0 31.831
							a 15.9155 15.9155 0 0 1 0 -31.831"
					/>
					<path class="circle"
						stroke-dasharray="<?=$thirdPourcentage?>, 100"
						d="M18 2.0845
							a 15.9155 15.9155 0 0 1 0 31.831
							a 15.9155 15.9155 0 0 1 0 -31.831"
					/>
					<text x="18" y="20.35" class="percentage">
						<?=$thirdPourcentage?>%
					</text>
				</svg>
			</div>
		</div>
	</section>
	<section id="engine3">
		<h1 style="float:right"><?= $_SESSION['engines']["3"]["is_on"] ? "&#9989" : "&#10060" ?></h1>
		<h1> &#128225 <?= $_SESSION['engines']["3"]["name"]?></h1>
		<span class="r"> Local 2 coté gauche de la porte </span>
		<br>
		<br>
		<h2> &#128337 temps <?= $_SESSION['engines']["3"]["is_on"] ? "allumé" : "éteinte" ?> :</h2>
		<br>
		<span class="r"><?= getTimingSession(3) ?></span>
		<br>
		<h2> &#128281 temps de la dernière session :</h2>
		<br>
		<span class="r"><?= getPrevTimingSession(3) ?></span>
		<br>
		<h2> &#128198 date dernier changement :</h2><?= $_SESSION['engines']["3"]["time_ranges"] != false ?
			end($_SESSION['engines']["3"]["time_ranges"])["timestamp"] : "aucun changement" ?>

	</section>
	<section id="truc">
		<h1> &#128291 Trucs en plus  </h1>
		<br>
		Reload à la mains<br>
		Passer en mode edition et modifier les noms des machines
		modifier les informations d'emplacement pour les ajouter dans la bdd<br>
	</section>
</main>

<?php 
	require("php/foot.php");
?>