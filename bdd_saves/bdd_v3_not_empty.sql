-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Hôte : 127.0.0.1:3306
-- Généré le : mer. 03 nov. 2021 à 20:40
-- Version du serveur :  5.7.31
-- Version de PHP : 7.3.21

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

DROP TABLE IF EXISTS `engines`;
CREATE TABLE IF NOT EXISTS `engines` (
  `id` smallint(5) UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` varchar(30) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `is_on` tinyint(1) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4;

--
-- Déchargement des données de la table `engines`
--

INSERT INTO `engines` (`id`, `name`, `is_on`) VALUES
(1, 'Machine 1', 1),
(2, 'Machine 2', 1),
(3, 'Machine 3', 0);

-- --------------------------------------------------------

--
-- Structure de la table `modification_trigger`
--

DROP TABLE IF EXISTS `modification_trigger`;
CREATE TABLE IF NOT EXISTS `modification_trigger` (
  `modified` tinyint(1) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Déchargement des données de la table `modification_trigger`
--

INSERT INTO `modification_trigger` (`modified`) VALUES
(0);

-- --------------------------------------------------------

--
-- Structure de la table `time_ranges`
--

DROP TABLE IF EXISTS `time_ranges`;
CREATE TABLE IF NOT EXISTS `time_ranges` (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `engine_id` smallint(5) UNSIGNED NOT NULL,
  `start` timestamp NOT NULL,
  `end` timestamp NOT NULL,
  PRIMARY KEY (`id`),
  KEY `constraint_engine_id` (`engine_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

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
