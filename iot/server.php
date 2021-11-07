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

	$firstPourcentage = 78;
	$secondPourcentage = 25;
	$thirdPourcentage = 7;
	$machineIsOn = false;
?>

<!-- 
	Quand le trigger est activé faire un code js pour recharger la page 

	if(checkTrigger($conn)) {}

	// on repasse la detente à FALSE pour signifier que le changement a été prit en compte et que on attend le prochain
	activateTrigger($conn);
-->

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
		<!-- <svg class="machine-on-off" viewBox="0 0 14.2 20.6">
			<g transform="translate(-37.1 -88.9)">
				<path d="m46.7 
					88.9c-0.285-0.0043-0.468 0.213-0.468 0.213l-8.99 11.7s-0.308 
					0.34-0.141 0.716c0.167 0.376 0.547 0.363 0.547 0.363l5.52-4e-3 
					-2.17 6.71s-0.206 0.485 0.251 0.754c0.457 0.269 0.783-0.119 
					0.783-0.119l8.99-11.7s0.307-0.34 0.14-0.716c-0.167-0.376-0.547-0.363-0.547-0.363l-5.52 
					0.0041 2.17-6.71s0.206-0.485-0.251-0.754c-0.114-0.0672-0.22-0.0931-0.315-0.0946z"
				fill="<?= ($machineIsOn ? "var(--yellow)" : "var(--dark)")?>"/>
			</g>
		</svg> -->

</aside>
	<section id="info">
		<h1> &#128202 Infos Machines </h1>
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
		Reload à la mains
		Passer en mode edition et modifier les noms des machines
		modifier les informations d'emplacement pour les ajouter dans la bdd
	</section>
</main>

<?php 
	require("php/foot.php");
?>