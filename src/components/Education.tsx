import { GraduationCap, X, Calendar, MapPin, Award } from 'lucide-react';
import { useState } from 'react';
import { ImageWithFallback } from './figma/ImageWithFallback';
import { useLanguage } from '../contexts/LanguageContext';

export function Education() {
  const [selectedEducation, setSelectedEducation] = useState<number | null>(null);
  const { t } = useLanguage();

  const education = [
    {
      degree: t('education.laval.degree'),
      school: t('education.laval.school'),
      period: t('education.laval.period'),
      location: t('education.laval.location'),
      description: t('education.laval.description'),
      image: "/ulaval.png",
      details: [
        t('education.laval.detail1'),
        t('education.laval.detail2'),
        t('education.laval.detail3'),
        t('education.laval.detail4'),
        t('education.laval.detail5')
      ],
      achievements: [t('education.laval.achievement')]
    },
    {
      degree: t('education.ensiie.degree'),
      school: t('education.ensiie.school'),
      period: t('education.ensiie.period'),
      location: t('education.ensiie.location'),
      description: t('education.ensiie.description'),
      image: "/ensiie_logo.png",
      details: [
        t('education.ensiie.detail1'),
        t('education.ensiie.detail2'),
        t('education.ensiie.detail3'),
        t('education.ensiie.detail4'),
        t('education.ensiie.detail5')
      ],
      achievements: [t('education.ensiie.achievement')]
    },
    {
      degree: t('education.cpge.degree'),
      school: t('education.cpge.school'),
      period: t('education.cpge.period'),
      location: t('education.cpge.location'),
      description: t('education.cpge.description'),
      image: "/cpge_logo.jpg",
      details: [
        t('education.cpge.detail1'),
        t('education.cpge.detail2'),
        t('education.cpge.detail3'),
        t('education.cpge.detail4'),
        t('education.cpge.detail5')
      ],
      achievements: [t('education.cpge.achievement')]
    },
    {
      degree: t('education.bac.degree'),
      school: t('education.bac.school'),
      period: t('education.bac.period'),
      location: t('education.bac.location'),
      description: t('education.bac.description'),
      image: null,
      details: [
        t('education.bac.detail1'),
        t('education.bac.detail2'),
        t('education.bac.detail3')
      ],
      achievements: []
    }
  ];

  return (
    <>
      <section id="education" className="bg-slate-800/50 backdrop-blur-sm rounded-2xl shadow-xl p-8 border border-slate-700/50">
        <h2 className="mb-6 text-slate-200 flex items-center gap-3">
          <GraduationCap className="w-8 h-8 text-slate-400" />
          {t('education.title')}
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
                  <span>{t('education.details')}</span>
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
            
            {education[selectedEducation].image && (
              <div className="h-64 overflow-hidden bg-slate-700 flex items-center justify-center">
                <ImageWithFallback
                  src={education[selectedEducation].image}
                  alt={education[selectedEducation].school}
                  className="max-w-full max-h-full object-contain p-4"
                />
              </div>
            )}

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
                <h4 className="text-white mb-3">{t('education.program')}</h4>
                <ul className="space-y-2">
                  {education[selectedEducation].details.map((detail, idx) => (
                    <li key={idx} className="text-gray-300 flex items-start gap-2">
                      <span className="text-slate-400 mt-1">•</span>
                      <span>{detail}</span>
                    </li>
                  ))}
                </ul>
              </div>

              {education[selectedEducation].achievements.length > 0 && (
                <div>
                  <h4 className="text-white mb-3 flex items-center gap-2">
                    <Award className="w-5 h-5 text-slate-400" />
                    {t('education.achievements')}
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
              )}
            </div>
          </div>
        </div>
      )}
    </>
  );
}
