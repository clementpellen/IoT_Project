-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Hôte : 127.0.0.1
-- Généré le : lun. 01 nov. 2021 à 18:16
-- Version du serveur : 10.4.21-MariaDB
-- Version de PHP : 8.0.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données : `factory`
--

-- --------------------------------------------------------

--
-- Structure de la table `engines`
--

CREATE TABLE `engines` (
  `id` smallint(5) UNSIGNED NOT NULL,
  `name` varchar(30) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Structure de la table `time_ranges`
--

CREATE TABLE `time_ranges` (
  `id` int(10) UNSIGNED NOT NULL,
  `beginning` timestamp NULL DEFAULT NULL,
  `ending` timestamp NULL DEFAULT NULL,
  `duration` time DEFAULT NULL,
  `state` tinyint(1) DEFAULT NULL COMMENT '0 : "time range in progress"\r\n1 : "time range finished"',
  `engine_id` smallint(5) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Index pour les tables déchargées
--

--
-- Index pour la table `engines`
--
ALTER TABLE `engines`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `time_ranges`
--
ALTER TABLE `time_ranges`
  ADD PRIMARY KEY (`id`),
  ADD KEY `constraint_engine_id` (`engine_id`);

--
-- AUTO_INCREMENT pour les tables déchargées
--

--
-- AUTO_INCREMENT pour la table `engines`
--
ALTER TABLE `engines`
  MODIFY `id` smallint(5) UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT pour la table `time_ranges`
--
ALTER TABLE `time_ranges`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- Contraintes pour les tables déchargées
--

--
-- Contraintes pour la table `time_ranges`
--
ALTER TABLE `time_ranges`
  ADD CONSTRAINT `constraint_engine_id` FOREIGN KEY (`engine_id`) REFERENCES `engines` (`id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
