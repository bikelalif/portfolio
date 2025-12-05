import { ArrowLeft, Github, ExternalLink, Calendar, CheckCircle, Wrench, Target, Terminal as TerminalIcon } from 'lucide-react';
import { useState } from 'react';
import { ImageWithFallback } from './figma/ImageWithFallback';
import { WebTerminal } from './WebTerminal';

interface ProjectPageProps {
  slug: string;
  onBack: () => void;
}

// Projets avec démo terminal (console)
const terminalProjects = ["jeu-de-cartes-c"];

// Données des projets (à connecter avec le backend Flask plus tard)
const projectsData: Record<string, {
  title: string;
  full_description: string;
  image: string;
  images: string[];
  tags: string[];
  technologies: string[];
  features: string[];
  challenges: string[];
  github: string;
  demo: string;
  date: string;
}> = {
  "sevent-gestion-evenements": {
    title: "SEvent - Gestion d'Événements",
    full_description: "SEvent est une application web complète permettant de gérer, visualiser et filtrer des événements à venir (concerts, sport, culture, etc.).\n\nLes événements sont stockés dans une base SQLite et importés depuis des fichiers JSON. L'application propose une interface moderne avec tri automatique par date, filtres par catégorie et un système d'authentification complet.\n\nLes utilisateurs peuvent créer un compte, ajouter des événements à leurs favoris et gérer leur agenda personnel.",
    image: "/sevent_logo.png",
    images: ["/sevent_logo.png"],
    tags: ["Python", "Flask", "SQLite", "HTML/CSS"],
    technologies: ["Python 3", "Flask", "SQLite", "Jinja2", "HTML5", "CSS3", "JavaScript"],
    features: [
      "Affichage des événements triés par date",
      "Import d'événements depuis JSON",
      "Filtres par catégorie (concerts, sport, culture)",
      "Système d'authentification (inscription/connexion)",
      "Gestion des favoris et agenda personnel",
      "Interface responsive et moderne"
    ],
    challenges: [
      "Validation automatique des dates",
      "Sécurisation de l'authentification",
      "Optimisation des requêtes SQLite"
    ],
    github: "https://github.com/bikelalif/SEvent",
    demo: "http://localhost:5002",
    date: "2024-2025"
  },
  "bilocal-gestion-bureaux": {
    title: "BiLOCAL - Gestion de Bilocalisation",
    full_description: "BiLOCAL est un logiciel de gestion de bilocalisation développé dans le cadre du cours GELO à l'ENSIIE.\n\nLe projet simule la gestion de bureaux pour une école d'ingénieur répartie sur deux sites. Il implémente plusieurs patrons de conception : Patron Stratégie (3 stratégies différentes pour rendre un bureau) et Patron Observer (Notification des employés lors des changements).\n\nLe système gère les places fixes, les places de passage et leurs affectations.",
    image: "/bilocal.png",
    images: ["/bilocal.png", "/bilocal_uml.png"],
    tags: ["Java", "Maven", "Design Patterns", "UML"],
    technologies: ["Java 11+", "Maven", "JUnit", "UML", "Modélisation"],
    features: [
      "Gestion des bureaux et places (fixes/passage)",
      "Affectation d'employés aux places",
      "3 stratégies de restitution de bureau",
      "Notifications automatiques aux employés",
      "Modélisation UML complète",
      "Tests unitaires JUnit"
    ],
    challenges: [
      "Implémentation correcte des Design Patterns",
      "Gestion des contraintes métier complexes",
      "Modélisation UML cohérente"
    ],
    github: "https://github.com/bikelalif/bilocal-gestion-bureaux",
    demo: "",
    date: "2024-2025"
  },
  "pharmaplan-gestion-planning": {
    title: "PharmaPlan - Planning Pharmacie",
    full_description: "PharmaPlan est une application de gestion de planning développée pour une pharmacie.\n\nL'application permet aux différents utilisateurs (employés, gérants, administrateurs) de gérer les plannings de travail de manière sécurisée. Elle intègre un système d'authentification avec hachage bcrypt et une gestion fine des permissions.\n\nLe logiciel est packagé en .exe via Inno Setup pour une installation facile sans prérequis Python.",
    image: "/pharmaplan_logo.png",
    images: ["/pharmaplan_logo.png"],
    tags: ["Python", "PyQt5", "SQLite", "bcrypt"],
    technologies: ["Python 3", "PyQt5", "SQLite", "bcrypt", "Inno Setup"],
    features: [
      "Gestion des plannings hebdomadaires",
      "3 rôles utilisateurs avec permissions",
      "Authentification sécurisée (bcrypt)",
      "Interface graphique PyQt5",
      "Export des plannings",
      "Installation .exe autonome"
    ],
    challenges: [
      "Sécurisation des données sensibles",
      "Gestion des rôles et permissions",
      "Packaging de l'application"
    ],
    github: "https://github.com/bikelalif/pharmaplan-gestion-planning",
    demo: "",
    date: "2025"
  },
  "expressions-javafx": {
    title: "Expressions JavaFX",
    full_description: "Application de calcul et manipulation d'expressions mathématiques développée en Java avec interface graphique JavaFX.\n\nLe projet implémente un parser complet pour analyser des expressions algébriques, les évaluer et les afficher sous forme d'arbre syntaxique. Il supporte les variables, les assignations et les opérations binaires/unaires.\n\nL'interface JavaFX permet une visualisation claire des expressions et de leur évaluation en temps réel.",
    image: "/expressions_javafx.png",
    images: ["/expressions_javafx.png"],
    tags: ["Java", "JavaFX", "Parser", "POO"],
    technologies: ["Java 11+", "JavaFX 20", "JUnit", "Maven/Eclipse"],
    features: [
      "Parsing d'expressions mathématiques",
      "Évaluation avec gestion des variables",
      "Affichage en arbre syntaxique",
      "Interface graphique JavaFX moderne",
      "Gestion des erreurs de syntaxe",
      "Tests unitaires complets"
    ],
    challenges: [
      "Implémentation du parser récursif",
      "Gestion des priorités d'opérateurs",
      "Architecture MVC propre"
    ],
    github: "https://github.com/bikelalif/expressions-javafx",
    demo: "",
    date: "2024-2025"
  },
  "editeur-texte-ocaml": {
    title: "Éditeur de Texte OCaml",
    full_description: "Éditeur de texte interactif développé en OCaml avec interface graphique utilisant la bibliothèque Graphics.\n\nLe projet implémente une structure de données basée sur les zippers fonctionnels pour une manipulation efficace du texte. Cette structure permet des opérations d'insertion, suppression et navigation en temps constant.\n\nL'éditeur supporte les raccourcis clavier standard et offre une expérience d'édition fluide.",
    image: "/editeur_ocaml.png",
    images: ["/editeur_ocaml.png"],
    tags: ["OCaml", "Graphics", "Zippers", "Fonctionnel"],
    technologies: ["OCaml", "Graphics", "Unix", "Makefile"],
    features: [
      "Édition de texte interactive",
      "Navigation avec raccourcis clavier",
      "Structure de données zipper optimisée",
      "Interface graphique native",
      "Insertion et suppression de caractères",
      "Gestion des sauts de ligne"
    ],
    challenges: [
      "Maîtrise du paradigme fonctionnel",
      "Implémentation des zippers",
      "Intégration avec la bibliothèque Graphics"
    ],
    github: "https://github.com/bikelalif/editeur-texte-ocaml",
    demo: "",
    date: "2024-2025"
  },
  "jeu-de-cartes-c": {
    title: "Jeu de Cartes en C",
    full_description: "Jeu de cartes interactif développé en C avec une architecture modulaire.\n\nLe projet implémente un jeu complet avec gestion des cartes, des joueurs, du plateau et des règles. Chaque module est documenté avec Doxygen pour générer une documentation HTML automatique.\n\nLe Makefile permet une compilation facile et la génération de la documentation.",
    image: "/jeu_cartes_c.png",
    images: ["/jeu_cartes_c.png"],
    tags: ["C", "Makefile", "Doxygen", "Algorithmique"],
    technologies: ["C", "Makefile", "Doxygen", "GCC"],
    features: [
      "Gestion complète des cartes et joueurs",
      "Système de tours de jeu",
      "Interface console interactive",
      "Stratégies de jeu",
      "Documentation Doxygen complète",
      "Compilation automatisée"
    ],
    challenges: [
      "Gestion de la mémoire en C",
      "Architecture modulaire",
      "Documentation exhaustive"
    ],
    github: "https://github.com/bikelalif/jeu-de-cartes-c",
    demo: "",
    date: "2024-2025"
  }
};

export function ProjectPage({ slug, onBack }: ProjectPageProps) {
  const [selectedImage, setSelectedImage] = useState(0);
  const [showTerminal, setShowTerminal] = useState(false);
  const project = projectsData[slug];
  const hasTerminalDemo = terminalProjects.includes(slug);

  if (!project) {
    return (
      <div className="min-h-screen flex items-center justify-center">
        <div className="text-center">
          <h1 className="text-2xl text-white mb-4">Projet non trouvé</h1>
          <button
            onClick={onBack}
            className="flex items-center gap-2 text-blue-400 hover:text-blue-300 transition-colors"
          >
            <ArrowLeft className="w-5 h-5" />
            Retour au portfolio
          </button>
        </div>
      </div>
    );
  }

  return (
    <div className="min-h-screen">
      {/* Header avec navigation retour */}
      <header className="bg-slate-900/80 backdrop-blur-lg border-b border-slate-700/50 sticky top-0 z-50">
        <div className="max-w-6xl mx-auto px-4 py-4">
          <button
            onClick={onBack}
            className="flex items-center gap-2 text-slate-300 hover:text-white transition-colors group"
          >
            <ArrowLeft className="w-5 h-5 group-hover:-translate-x-1 transition-transform" />
            <span>Retour au portfolio</span>
          </button>
        </div>
      </header>

      {/* Contenu du projet */}
      <main className="max-w-6xl mx-auto px-4 py-8">
        {/* Titre et métadonnées */}
        <div className="mb-8">
          <div className="flex items-center gap-3 text-slate-400 mb-3">
            <Calendar className="w-4 h-4" />
            <span>{project.date}</span>
          </div>
          <h1 className="text-4xl font-bold text-white mb-4">{project.title}</h1>
          <div className="flex flex-wrap gap-2 mb-6">
            {project.tags.map((tag, index) => (
              <span
                key={index}
                className="bg-blue-600/20 text-blue-300 px-3 py-1 rounded-full text-sm border border-blue-500/30"
              >
                {tag}
              </span>
            ))}
          </div>
        </div>

        {/* Galerie d'images */}
        <div className="mb-12">
          <div className="aspect-video rounded-2xl overflow-hidden mb-4 bg-slate-800 flex items-center justify-center">
            <ImageWithFallback
              src={project.images[selectedImage]}
              alt={project.title}
              className="max-w-full max-h-full object-contain p-4"
            />
          </div>
          <div className="flex gap-3 overflow-x-auto pb-2">
            {project.images.map((img, index) => (
              <button
                key={index}
                onClick={() => setSelectedImage(index)}
                className={`flex-shrink-0 w-24 h-16 rounded-lg overflow-hidden border-2 transition-all ${
                  selectedImage === index
                    ? 'border-blue-500 ring-2 ring-blue-500/50'
                    : 'border-slate-700 hover:border-slate-500'
                }`}
              >
                <ImageWithFallback
                  src={img}
                  alt={`${project.title} ${index + 1}`}
                  className="w-full h-full object-cover"
                />
              </button>
            ))}
          </div>
        </div>

        {/* Description et détails */}
        <div className="grid lg:grid-cols-3 gap-8">
          {/* Colonne principale */}
          <div className="lg:col-span-2 space-y-8">
            {/* Description */}
            <section className="bg-slate-800/50 backdrop-blur-sm rounded-2xl p-6 border border-slate-700/50">
              <h2 className="text-xl font-semibold text-white mb-4">À propos du projet</h2>
              <p className="text-slate-300 leading-relaxed whitespace-pre-line">
                {project.full_description}
              </p>
            </section>

            {/* Fonctionnalités */}
            <section className="bg-slate-800/50 backdrop-blur-sm rounded-2xl p-6 border border-slate-700/50">
              <h2 className="text-xl font-semibold text-white mb-4 flex items-center gap-2">
                <CheckCircle className="w-5 h-5 text-emerald-400" />
                Fonctionnalités
              </h2>
              <ul className="space-y-3">
                {project.features.map((feature, index) => (
                  <li key={index} className="flex items-start gap-3 text-slate-300">
                    <span className="w-1.5 h-1.5 bg-emerald-400 rounded-full mt-2 flex-shrink-0"></span>
                    <span>{feature}</span>
                  </li>
                ))}
              </ul>
            </section>

            {/* Défis techniques */}
            <section className="bg-slate-800/50 backdrop-blur-sm rounded-2xl p-6 border border-slate-700/50">
              <h2 className="text-xl font-semibold text-white mb-4 flex items-center gap-2">
                <Target className="w-5 h-5 text-amber-400" />
                Défis techniques
              </h2>
              <ul className="space-y-3">
                {project.challenges.map((challenge, index) => (
                  <li key={index} className="flex items-start gap-3 text-slate-300">
                    <span className="w-1.5 h-1.5 bg-amber-400 rounded-full mt-2 flex-shrink-0"></span>
                    <span>{challenge}</span>
                  </li>
                ))}
              </ul>
            </section>
          </div>

          {/* Sidebar */}
          <div className="space-y-6">
            {/* Technologies */}
            <section className="bg-slate-800/50 backdrop-blur-sm rounded-2xl p-6 border border-slate-700/50">
              <h2 className="text-lg font-semibold text-white mb-4 flex items-center gap-2">
                <Wrench className="w-5 h-5 text-blue-400" />
                Technologies
              </h2>
              <div className="flex flex-wrap gap-2">
                {project.technologies.map((tech, index) => (
                  <span
                    key={index}
                    className="bg-slate-700/50 text-slate-300 px-3 py-1.5 rounded-lg text-sm border border-slate-600/50"
                  >
                    {tech}
                  </span>
                ))}
              </div>
            </section>

            {/* Liens */}
            <section className="bg-slate-800/50 backdrop-blur-sm rounded-2xl p-6 border border-slate-700/50">
              <h2 className="text-lg font-semibold text-white mb-4">Liens</h2>
              <div className="space-y-3">
                <a
                  href={project.github}
                  target="_blank"
                  rel="noopener noreferrer"
                  className="flex items-center gap-3 text-slate-300 hover:text-white bg-slate-700/50 hover:bg-slate-700 px-4 py-3 rounded-xl transition-all group"
                >
                  <Github className="w-5 h-5" />
                  <span>Voir le code source</span>
                  <ExternalLink className="w-4 h-4 ml-auto opacity-0 group-hover:opacity-100 transition-opacity" />
                </a>
                {project.demo && project.demo !== "" && (
                  <a
                    href={project.demo}
                    target="_blank"
                    rel="noopener noreferrer"
                    className="flex items-center gap-3 text-slate-300 hover:text-white bg-green-600/20 hover:bg-green-600/30 border border-green-500/30 px-4 py-3 rounded-xl transition-all group"
                  >
                    <ExternalLink className="w-5 h-5 text-green-400" />
                    <span>Lancer la démo web</span>
                    <ExternalLink className="w-4 h-4 ml-auto opacity-0 group-hover:opacity-100 transition-opacity" />
                  </a>
                )}
                {/* Terminal demo désactivé temporairement - à réactiver après hébergement
                {hasTerminalDemo && (
                  <button
                    onClick={() => setShowTerminal(true)}
                    className="w-full flex items-center gap-3 text-slate-300 hover:text-white bg-purple-600/20 hover:bg-purple-600/30 border border-purple-500/30 px-4 py-3 rounded-xl transition-all group"
                  >
                    <TerminalIcon className="w-5 h-5 text-purple-400" />
                    <span>Lancer dans le terminal</span>
                    <ExternalLink className="w-4 h-4 ml-auto opacity-0 group-hover:opacity-100 transition-opacity" />
                  </button>
                )}
                */}
              </div>
            </section>
          </div>
        </div>

        {/* Modal Terminal - désactivé temporairement
        {showTerminal && hasTerminalDemo && (
          <div className="fixed inset-0 z-50 flex items-center justify-center p-4 bg-black/80 backdrop-blur-sm">
            <div className="w-full max-w-4xl">
              <WebTerminal
                projectSlug={slug}
                projectName={project.title}
                onClose={() => setShowTerminal(false)}
              />
            </div>
          </div>
        )}
        */}
      </main>
    </div>
  );
}
