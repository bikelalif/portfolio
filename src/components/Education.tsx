import { GraduationCap, X, Calendar, MapPin, Award } from 'lucide-react';
import { useState } from 'react';
import { ImageWithFallback } from './figma/ImageWithFallback';

export function Education() {
  const [selectedEducation, setSelectedEducation] = useState<number | null>(null);

  const education = [
    {
      degree: "Diplôme d'Ingénieur en Génie Logiciel",
      school: "ENSIIE - École Nationale Supérieure d'Informatique",
      period: "2024 - En cours",
      location: "Évry, France",
      description: "Formation d'ingénieur spécialisée en informatique et génie logiciel",
      image: "/ensiie_logo.png",
      details: [
        "Architecture logicielle et design patterns",
        "Développement d'applications web et mobiles",
        "Algorithmique avancée et structures de données",
        "Intelligence artificielle et Machine Learning",
        "Gestion de projets informatiques"
      ],
      achievements: [
        "En cours"
      ]
    },
    {
      degree: "CPGE - Classes Préparatoires",
      school: "Lycée Albert Schweitzer",
      period: "2021 - 2024",
      location: "Le Raincy, France",
      description: "Filière Physique-Chimie (PC) - Niveau Bac+2",
      image: "/cpge_logo.jpg",
      details: [
        "Mathématiques approfondies",
        "Physique et Chimie",
        "Informatique (Python, algorithmique)",
        "Sciences de l'ingénieur",
        "Préparation aux concours des grandes écoles"
      ],
      achievements: [
        "Admission à l'ENSIIE"
      ]
    },
    {
      degree: "Baccalauréat Général",
      school: "Lycée Honoré de Balzac",
      period: "2018 - 2021",
      location: "Mitry-Mory, France",
      description: "Spécialités Physique-Chimie et Mathématiques",
      image: "/image_noire.jpg",
      details: [
        "Spécialité Mathématiques",
        "Spécialité Physique-Chimie",
        "Option Mathématiques Expertes"
      ],
      achievements: [
        "Mention Bien"
      ]
    }
  ];

  return (
    <>
      <section id="education" className="bg-slate-800/50 backdrop-blur-sm rounded-2xl shadow-xl p-8 border border-slate-700/50">
        <h2 className="mb-6 text-slate-200 flex items-center gap-3">
          <GraduationCap className="w-8 h-8 text-slate-400" />
          Formation
        </h2>
        <div className="grid md:grid-cols-2 gap-6">
          {education.map((edu, index) => (
            <button
              key={index}
              onClick={() => setSelectedEducation(index)}
              className="group relative bg-gradient-to-br from-slate-700/50 to-slate-800/50 rounded-2xl p-6 border border-slate-600/50 hover:border-slate-500 transition-all duration-300 hover:shadow-2xl hover:shadow-slate-500/20 hover:scale-105 text-left overflow-hidden"
            >
              <div className="absolute inset-0 bg-gradient-to-br from-slate-600/10 to-slate-700/10 opacity-0 group-hover:opacity-100 transition-opacity duration-300"></div>
              <div className="relative z-10">
                <div className="flex items-center gap-2 text-slate-400 mb-3">
                  <Calendar className="w-4 h-4" />
                  <span className="text-sm">{edu.period}</span>
                </div>
                <h3 className="text-white mb-2">{edu.degree}</h3>
                <p className="text-slate-400 mb-2">{edu.school}</p>
                <p className="text-gray-400 text-sm line-clamp-2">{edu.description}</p>
                <div className="mt-4 inline-flex items-center gap-2 text-sm text-slate-400 group-hover:text-slate-300">
                  <span>Voir les détails</span>
                  <span className="group-hover:translate-x-1 transition-transform">→</span>
                </div>
              </div>
            </button>
          ))}
        </div>
      </section>

      {selectedEducation !== null && (
        <div className="fixed inset-0 bg-black/70 backdrop-blur-sm z-50 flex items-center justify-center p-4" onClick={() => setSelectedEducation(null)}>
          <div className="bg-slate-800 rounded-2xl max-w-3xl w-full max-h-[90vh] overflow-y-auto shadow-2xl border border-slate-600/50" onClick={(e) => e.stopPropagation()}>
            <div className="sticky top-0 bg-slate-800 border-b border-slate-600/50 p-6 flex items-start justify-between">
              <div>
                <h3 className="text-white mb-1">{education[selectedEducation].degree}</h3>
                <p className="text-slate-400">{education[selectedEducation].school}</p>
              </div>
              <button
                onClick={() => setSelectedEducation(null)}
                className="text-gray-400 hover:text-white transition-colors p-2 hover:bg-slate-700 rounded-lg"
              >
                <X className="w-6 h-6" />
              </button>
            </div>
            
            <div className="h-64 overflow-hidden bg-slate-700 flex items-center justify-center">
              <ImageWithFallback
                src={education[selectedEducation].image}
                alt={education[selectedEducation].school}
                className="max-w-full max-h-full object-contain p-4"
              />
            </div>

            <div className="p-6 space-y-6">
              <div className="flex flex-wrap gap-4 text-sm text-gray-300">
                <div className="flex items-center gap-2">
                  <Calendar className="w-4 h-4 text-slate-400" />
                  <span>{education[selectedEducation].period}</span>
                </div>
                <div className="flex items-center gap-2">
                  <MapPin className="w-4 h-4 text-slate-400" />
                  <span>{education[selectedEducation].location}</span>
                </div>
              </div>

              <div>
                <h4 className="text-white mb-3">Programme</h4>
                <ul className="space-y-2">
                  {education[selectedEducation].details.map((detail, idx) => (
                    <li key={idx} className="text-gray-300 flex items-start gap-2">
                      <span className="text-slate-400 mt-1">•</span>
                      <span>{detail}</span>
                    </li>
                  ))}
                </ul>
              </div>

              <div>
                <h4 className="text-white mb-3 flex items-center gap-2">
                  <Award className="w-5 h-5 text-slate-400" />
                  Distinctions
                </h4>
                <div className="flex flex-wrap gap-2">
                  {education[selectedEducation].achievements.map((achievement, idx) => (
                    <span
                      key={idx}
                      className="bg-slate-600/30 text-slate-300 px-3 py-1 rounded-full text-sm border border-slate-500/30"
                    >
                      {achievement}
                    </span>
                  ))}
                </div>
              </div>
            </div>
          </div>
        </div>
      )}
    </>
  );
}
