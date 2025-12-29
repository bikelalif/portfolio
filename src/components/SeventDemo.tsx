import { Github, ExternalLink, Code2, BookOpen, Star } from 'lucide-react';
import { useLanguage } from '../contexts/LanguageContext';

export function SeventDemo() {
  const { language } = useLanguage();

  const features = language === 'fr' ? [
    "Gestion complète d'événements (concerts, sport, culture)",
    "Système de filtres par catégorie",
    "Authentification et gestion des utilisateurs",
    "Système de favoris",
    "Interface moderne et responsive"
  ] : [
    "Complete event management (concerts, sports, culture)",
    "Category filter system",
    "User authentication and management",
    "Favorites system",
    "Modern and responsive interface"
  ];

  const technologies = ["Python", "Flask", "SQLite", "HTML/CSS", "JavaScript"];

  return (
    <div className="bg-slate-800/50 backdrop-blur-sm rounded-2xl shadow-xl p-8 border border-slate-700/50">
      <div className="flex items-center justify-between mb-6">
        <div>
          <h2 className="text-2xl font-bold text-slate-200 mb-2">
            SEvent - {language === 'fr' ? "Gestion d'Événements" : "Event Management"}
          </h2>
          <p className="text-gray-400">
            {language === 'fr' 
              ? "Application web Flask pour gérer et visualiser des événements" 
              : "Flask web application to manage and view events"}
          </p>
        </div>
      </div>

      {/* Image de présentation */}
      <div className="mb-6 rounded-lg overflow-hidden border border-slate-700 bg-slate-900">
        <img 
          src="/sevent_logo.png" 
          alt="SEvent" 
          className="w-full h-64 object-contain p-4"
        />
      </div>

      {/* Fonctionnalités */}
      <div className="mb-6">
        <h3 className="text-xl font-semibold text-white mb-3 flex items-center gap-2">
          <Star className="w-5 h-5 text-yellow-400" />
          {language === 'fr' ? "Fonctionnalités" : "Features"}
        </h3>
        <ul className="space-y-2">
          {features.map((feature, index) => (
            <li key={index} className="flex items-start gap-2 text-gray-300">
              <span className="text-green-400 mt-1">✓</span>
              {feature}
            </li>
          ))}
        </ul>
      </div>

      {/* Technologies */}
      <div className="mb-6">
        <h3 className="text-xl font-semibold text-white mb-3 flex items-center gap-2">
          <Code2 className="w-5 h-5 text-blue-400" />
          {language === 'fr' ? "Technologies" : "Technologies"}
        </h3>
        <div className="flex flex-wrap gap-2">
          {technologies.map((tech, index) => (
            <span
              key={index}
              className="bg-slate-600/30 text-slate-300 px-3 py-1 rounded-lg text-sm border border-slate-500/30"
            >
              {tech}
            </span>
          ))}
        </div>
      </div>

      {/* Message informatif */}
      <div className="mb-6 p-4 bg-blue-900/20 border border-blue-500/50 rounded-lg">
        <div className="flex items-start gap-3">
          <BookOpen className="w-5 h-5 text-blue-400 flex-shrink-0 mt-0.5" />
          <div>
            <p className="text-blue-300 font-medium mb-1">
              {language === 'fr' ? "À propos de cette démo" : "About this demo"}
            </p>
            <p className="text-blue-400 text-sm">
              {language === 'fr' 
                ? "Cette application est disponible en code source sur GitHub. Pour des raisons de sécurité et de coûts d'hébergement, la démo interactive n'est pas publiquement hébergée. Vous pouvez consulter le code source complet, les captures d'écran et la documentation technique via les liens ci-dessous."
                : "This application is available as source code on GitHub. For security and hosting cost reasons, an interactive demo is not publicly hosted. You can view the complete source code, screenshots, and technical documentation via the links below."}
            </p>
          </div>
        </div>
      </div>

      {/* Boutons d'action */}
      <div className="flex gap-3 flex-wrap">
        <a
          href="https://github.com/bikelalif/SEvent"
          target="_blank"
          rel="noopener noreferrer"
          className="flex items-center gap-2 px-6 py-3 bg-gradient-to-r from-slate-600 to-slate-700 hover:from-slate-500 hover:to-slate-600 text-white rounded-lg transition-all shadow-lg hover:shadow-slate-500/25"
        >
          <Github className="w-5 h-5" />
          {language === 'fr' ? "Voir le code source" : "View source code"}
        </a>
        <a
          href="https://github.com/bikelalif/SEvent#readme"
          target="_blank"
          rel="noopener noreferrer"
          className="flex items-center gap-2 px-6 py-3 bg-gradient-to-r from-blue-600 to-cyan-600 hover:from-blue-500 hover:to-cyan-500 text-white rounded-lg transition-all shadow-lg hover:shadow-blue-500/25"
        >
          <ExternalLink className="w-5 h-5" />
          {language === 'fr' ? "Documentation" : "Documentation"}
        </a>
      </div>
    </div>
  );
}
