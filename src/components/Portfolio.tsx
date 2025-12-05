import { ExternalLink, Github, ArrowRight, Play } from 'lucide-react';
import { ImageWithFallback } from './figma/ImageWithFallback';

interface PortfolioProps {
  onProjectClick: (slug: string) => void;
}

export function Portfolio({ onProjectClick }: PortfolioProps) {
  const projects = [
    {
      slug: "sevent-gestion-evenements",
      title: "SEvent - Gestion d'Événements",
      description: "Application web Flask pour gérer et visualiser des événements (concerts, sport, culture). Filtres, favoris et authentification.",
      image: "/sevent_logo.png",
      tags: ["Python", "Flask", "SQLite", "HTML/CSS"],
      github: "https://github.com/bikelalif/SEvent",
      demoUrl: "http://localhost:5002",
      demoInfo: "Démo locale disponible"
    },
    {
      slug: "bilocal-gestion-bureaux",
      title: "BiLOCAL - Gestion de Bureaux",
      description: "Logiciel de gestion de bilocalisation pour écoles d'ingénieurs. Patron Stratégie et Observer en Java.",
      image: "/bilocal.png",
      tags: ["Java", "Maven", "Design Patterns", "UML"],
      github: "https://github.com/bikelalif/bilocal-gestion-bureaux",
      demoUrl: null,
      demoInfo: null
    },
    {
      slug: "pharmaplan-gestion-planning",
      title: "PharmaPlan - Planning Pharmacie",
      description: "Application de gestion de planning pour pharmacie avec système de rôles et authentification sécurisée.",
      image: "/pharmaplan_logo.png",
      tags: ["Python", "PyQt5", "SQLite", "bcrypt"],
      github: "https://github.com/bikelalif/pharmaplan-gestion-planning",
      demoUrl: null,
      demoInfo: "📥 Télécharger .exe"
    },
    {
      slug: "expressions-javafx",
      title: "Expressions JavaFX",
      description: "Calculateur d'expressions mathématiques avec parsing, évaluation et affichage graphique en arbre.",
      image: "/expressions_javafx.png",
      tags: ["Java", "JavaFX", "Parser", "POO"],
      github: "https://github.com/bikelalif/expressions-javafx",
      demoUrl: null,
      demoInfo: "Application desktop"
    },
    {
      slug: "editeur-texte-ocaml",
      title: "Éditeur de Texte OCaml",
      description: "Éditeur de texte interactif avec interface graphique. Structure de données basée sur les zippers.",
      image: "/editeur_ocaml.png",
      tags: ["OCaml", "Graphics", "Zippers", "Fonctionnel"],
      github: "https://github.com/bikelalif/editeur-texte-ocaml",
      demoUrl: null,
      demoInfo: "Application desktop"
    },
    {
      slug: "jeu-de-cartes-c",
      title: "Jeu de Cartes en C",
      description: "Jeu de cartes interactif avec gestion des joueurs, plateau et stratégies. Documentation Doxygen.",
      image: "/jeu_cartes_c.png",
      tags: ["C", "Makefile", "Doxygen", "Algorithmique"],
      github: "https://github.com/bikelalif/jeu-de-cartes-c",
      demoUrl: null,
      demoInfo: "Application console"
    }
  ];

  return (
    <section id="portfolio" className="bg-slate-800/50 backdrop-blur-sm rounded-2xl shadow-xl p-8 border border-slate-700/50">
      <h2 className="mb-6 text-slate-200">Projets</h2>
      <div className="grid md:grid-cols-2 lg:grid-cols-3 gap-6">
        {projects.map((project, index) => (
          <div
            key={index}
            onClick={() => onProjectClick(project.slug)}
            className="group bg-slate-900/50 rounded-xl overflow-hidden border border-slate-600/30 hover:border-slate-500/50 hover:shadow-2xl hover:shadow-slate-500/10 transition-all duration-300 cursor-pointer"
          >
            <div className="h-48 overflow-hidden bg-slate-800 relative flex items-center justify-center">
              <ImageWithFallback
                src={project.image}
                alt={project.title}
                className="max-w-full max-h-full object-contain p-2 group-hover:scale-110 transition-transform duration-300"
              />
              <div className="absolute inset-0 bg-gradient-to-t from-slate-900 via-transparent to-transparent opacity-60"></div>
              {/* Overlay "Voir le projet" au survol */}
              <div className="absolute inset-0 bg-slate-900/80 flex items-center justify-center opacity-0 group-hover:opacity-100 transition-opacity duration-300">
                <span className="flex items-center gap-2 text-white font-medium">
                  Voir le projet
                  <ArrowRight className="w-5 h-5 group-hover:translate-x-1 transition-transform" />
                </span>
              </div>
            </div>
            <div className="p-5">
              <h3 className="text-white mb-2">{project.title}</h3>
              <p className="text-gray-400 text-sm mb-4">{project.description}</p>
              <div className="flex flex-wrap gap-2 mb-4">
                {project.tags.map((tag, tagIndex) => (
                  <span
                    key={tagIndex}
                    className="bg-slate-600/30 text-slate-300 px-2 py-1 rounded text-xs border border-slate-500/30"
                  >
                    {tag}
                  </span>
                ))}
              </div>
              <div className="flex gap-3 flex-wrap">
                <button
                  onClick={(e) => { e.stopPropagation(); window.open(project.github, '_blank'); }}
                  className="flex items-center gap-1 text-sm text-gray-400 hover:text-slate-300 transition-colors"
                >
                  <Github className="w-4 h-4" />
                  Code
                </button>
                
                {/* Bouton Démo */}
                {project.demoUrl && (
                  <button
                    onClick={(e) => { e.stopPropagation(); window.open(project.demoUrl, '_blank'); }}
                    className="flex items-center gap-1 text-sm text-green-400 hover:text-green-300 transition-colors"
                  >
                    <Play className="w-4 h-4" />
                    Démo
                  </button>
                )}
                {!project.demoUrl && project.demoInfo && (
                  <span className="flex items-center gap-1 text-sm text-gray-500">
                    <ExternalLink className="w-4 h-4" />
                    {project.demoInfo}
                  </span>
                )}
              </div>
            </div>
          </div>
        ))}
      </div>
    </section>
  );
}
