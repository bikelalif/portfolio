import { Heart, X, Camera, Plane, Music, BookOpen } from 'lucide-react';
import { useState } from 'react';
import { ImageWithFallback } from './figma/ImageWithFallback';

export function Hobbies() {
  const [selectedHobby, setSelectedHobby] = useState<number | null>(null);

  const hobbies = [
    {
      title: "Sport",
      icon: Camera,
      description: "Passion pour le sport et l'activité physique",
      image: "/image_noire.jpg",
      details: [
        "Pratique régulière du sport",
        "Maintien d'un mode de vie actif",
        "Dépassement de soi et discipline"
      ],
      interests: ["Fitness", "Sport collectif", "Course"]
    },
    {
      title: "Voyages",
      icon: Plane,
      description: "Découverte de nouvelles cultures et destinations",
      image: "/image_noire.jpg",
      details: [
        "Exploration de nouvelles destinations",
        "Découverte de cultures diverses",
        "Ouverture d'esprit et curiosité"
      ],
      interests: ["Europe", "Culture", "Gastronomie"]
    },
    {
      title: "Musique",
      icon: Music,
      description: "Écoute de musique variée",
      image: "/image_noire.jpg",
      details: [
        "Appréciation de différents genres musicaux",
        "Détente et concentration",
        "Découverte de nouveaux artistes"
      ],
      interests: ["Rap", "Pop", "R&B", "Hip-Hop"]
    },
    {
      title: "Technologie & Informatique",
      icon: BookOpen,
      description: "Veille technologique et apprentissage continu",
      image: "/image_noire.jpg",
      details: [
        "Suivi de l'actualité tech",
        "Apprentissage de nouveaux langages",
        "Projets personnels de programmation"
      ],
      interests: ["IA", "Développement", "Innovation"]
    }
  ];

  return (
    <>
      <section id="hobbies" className="bg-slate-800/50 backdrop-blur-sm rounded-2xl shadow-xl p-8 border border-slate-700/50">
        <h2 className="mb-6 text-slate-200 flex items-center gap-3">
          <Heart className="w-8 h-8 text-slate-400" />
          Loisirs & Vie Personnelle
        </h2>
        <div className="grid md:grid-cols-2 lg:grid-cols-4 gap-6">
          {hobbies.map((hobby, index) => {
            const Icon = hobby.icon;
            return (
              <button
                key={index}
                onClick={() => setSelectedHobby(index)}
                className="group relative bg-gradient-to-br from-slate-700/50 to-slate-800/50 rounded-2xl p-6 border border-slate-600/50 hover:border-slate-500 transition-all duration-300 hover:shadow-2xl hover:shadow-slate-500/20 hover:scale-105 text-left overflow-hidden"
              >
                <div className="absolute inset-0 bg-gradient-to-br from-slate-600/5 to-slate-700/5 opacity-0 group-hover:opacity-100 transition-opacity duration-300"></div>
                <div className="relative z-10">
                  <div className="w-12 h-12 bg-slate-600/30 rounded-full flex items-center justify-center mb-4 group-hover:bg-slate-600/50 transition-colors">
                    <Icon className="w-6 h-6 text-slate-400" />
                  </div>
                  <h3 className="text-white mb-2">{hobby.title}</h3>
                  <p className="text-gray-400 text-sm line-clamp-2">{hobby.description}</p>
                  <div className="mt-4 inline-flex items-center gap-2 text-sm text-slate-400 group-hover:text-slate-300">
                    <span>En savoir plus</span>
                    <span className="group-hover:translate-x-1 transition-transform">→</span>
                  </div>
                </div>
              </button>
            );
          })}
        </div>
      </section>

      {selectedHobby !== null && (
        <div className="fixed inset-0 bg-black/70 backdrop-blur-sm z-50 flex items-center justify-center p-4" onClick={() => setSelectedHobby(null)}>
          <div className="bg-slate-800 rounded-2xl max-w-3xl w-full max-h-[90vh] overflow-y-auto shadow-2xl border border-slate-600/50" onClick={(e) => e.stopPropagation()}>
            <div className="sticky top-0 bg-slate-800 border-b border-slate-600/50 p-6 flex items-start justify-between">
              <div className="flex items-center gap-3">
                {(() => {
                  const Icon = hobbies[selectedHobby].icon;
                  return <Icon className="w-6 h-6 text-slate-400" />;
                })()}
                <h3 className="text-white">{hobbies[selectedHobby].title}</h3>
              </div>
              <button
                onClick={() => setSelectedHobby(null)}
                className="text-gray-400 hover:text-white transition-colors p-2 hover:bg-slate-700 rounded-lg"
              >
                <X className="w-6 h-6" />
              </button>
            </div>
            
            <div className="h-64 overflow-hidden">
              <ImageWithFallback
                src={hobbies[selectedHobby].image}
                alt={hobbies[selectedHobby].title}
                className="w-full h-full object-cover"
              />
            </div>

            <div className="p-6 space-y-6">
              <div>
                <p className="text-gray-300 text-lg mb-4">{hobbies[selectedHobby].description}</p>
              </div>

              <div>
                <h4 className="text-white mb-3">À propos</h4>
                <ul className="space-y-2">
                  {hobbies[selectedHobby].details.map((detail, idx) => (
                    <li key={idx} className="text-gray-300 flex items-start gap-2">
                      <span className="text-slate-400 mt-1">•</span>
                      <span>{detail}</span>
                    </li>
                  ))}
                </ul>
              </div>

              <div>
                <h4 className="text-white mb-3">Centres d'intérêt</h4>
                <div className="flex flex-wrap gap-2">
                  {hobbies[selectedHobby].interests.map((interest, idx) => (
                    <span
                      key={idx}
                      className="bg-slate-600/30 text-slate-300 px-3 py-1 rounded-full text-sm border border-slate-500/30"
                    >
                      {interest}
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
