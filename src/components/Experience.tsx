import { Briefcase, X, Calendar, MapPin, CheckCircle, FileText } from 'lucide-react';
import { useState } from 'react';
import { ImageWithFallback } from './figma/ImageWithFallback';
import { useLanguage } from '../contexts/LanguageContext';

export function Experience() {
  const [selectedExperience, setSelectedExperience] = useState<number | null>(null);
  const { t } = useLanguage();

  const experiences = [
    {
      title: t('experience.idiatech.title'),
      company: t('experience.idiatech.company'),
      period: t('experience.idiatech.period'),
      location: t('experience.idiatech.location'),
      description: t('experience.idiatech.description'),
      image: "/idiatech_logo.png",
      tasks: [
        t('experience.idiatech.task1'),
        t('experience.idiatech.task2'),
        t('experience.idiatech.task3'),
        t('experience.idiatech.task4'),
        t('experience.idiatech.task5'),
        t('experience.idiatech.task6')
      ],
      technologies: ["Groovy", "Java", "Grimport IDE", "Fiddler", "APIs REST", "Maven", "Gradle"],
      achievements: [
        t('experience.idiatech.achievement1'),
        t('experience.idiatech.achievement2'),
        t('experience.idiatech.achievement3')
      ],
      reportUrl: "/rapport_stage.pdf"
    }
  ];

  return (
    <>
      <section id="experience" className="bg-slate-800/50 backdrop-blur-sm rounded-2xl shadow-xl p-8 border border-slate-700/50">
        <h2 className="mb-6 text-slate-200 flex items-center gap-3">
          <Briefcase className="w-8 h-8 text-slate-400" />
          {t('experience.title')}
        </h2>
        <div className="grid md:grid-cols-2 gap-6">
          {experiences.map((exp, index) => (
            <button
              key={index}
              onClick={() => setSelectedExperience(index)}
              className="group relative bg-gradient-to-br from-slate-700/50 to-slate-800/50 rounded-2xl p-6 border border-slate-600/50 hover:border-slate-500 transition-all duration-300 hover:shadow-2xl hover:shadow-slate-500/20 hover:scale-105 text-left overflow-hidden"
            >
              <div className="absolute inset-0 bg-gradient-to-br from-slate-600/10 to-slate-700/10 opacity-0 group-hover:opacity-100 transition-opacity duration-300"></div>
              <div className="relative z-10">
                <div className="flex items-center gap-2 text-slate-400 mb-3">
                  <Calendar className="w-4 h-4" />
                  <span className="text-sm">{exp.period}</span>
                </div>
                <h3 className="text-white mb-2">{exp.title}</h3>
                <p className="text-slate-400 mb-2">{exp.company}</p>
                <p className="text-gray-400 text-sm line-clamp-2">{exp.description}</p>
                <div className="mt-4 inline-flex items-center gap-2 text-sm text-slate-400 group-hover:text-slate-300">
                  <span>{t('experience.details')}</span>
                  <span className="group-hover:translate-x-1 transition-transform">→</span>
                </div>
              </div>
            </button>
          ))}
        </div>
      </section>

      {selectedExperience !== null && (
        <div className="fixed inset-0 bg-black/70 backdrop-blur-sm z-50 flex items-center justify-center p-4" onClick={() => setSelectedExperience(null)}>
          <div className="bg-slate-800 rounded-2xl max-w-3xl w-full max-h-[90vh] overflow-y-auto shadow-2xl border border-slate-600/50" onClick={(e) => e.stopPropagation()}>
            <div className="sticky top-0 bg-slate-800 border-b border-slate-600/50 p-6 flex items-start justify-between">
              <div>
                <h3 className="text-white mb-1">{experiences[selectedExperience].title}</h3>
                <p className="text-slate-400">{experiences[selectedExperience].company}</p>
              </div>
              <button
                onClick={() => setSelectedExperience(null)}
                className="text-gray-400 hover:text-white transition-colors p-2 hover:bg-slate-700 rounded-lg"
              >
                <X className="w-6 h-6" />
              </button>
            </div>
            
            <div className="h-64 overflow-hidden">
              <ImageWithFallback
                src={experiences[selectedExperience].image}
                alt={experiences[selectedExperience].company}
                className="w-full h-full object-cover"
              />
            </div>

            <div className="p-6 space-y-6">
              <div className="flex flex-wrap gap-4 text-sm text-gray-300">
                <div className="flex items-center gap-2">
                  <Calendar className="w-4 h-4 text-slate-400" />
                  <span>{experiences[selectedExperience].period}</span>
                </div>
                <div className="flex items-center gap-2">
                  <MapPin className="w-4 h-4 text-slate-400" />
                  <span>{experiences[selectedExperience].location}</span>
                </div>
              </div>

              <div>
                <h4 className="text-white mb-3">{t('experience.tasks')}</h4>
                <ul className="space-y-2">
                  {experiences[selectedExperience].tasks.map((task, idx) => (
                    <li key={idx} className="text-gray-300 flex items-start gap-2">
                      <CheckCircle className="w-5 h-5 text-slate-400 flex-shrink-0 mt-0.5" />
                      <span>{task}</span>
                    </li>
                  ))}
                </ul>
              </div>

              <div>
                <h4 className="text-white mb-3">{t('experience.technologies')}</h4>
                <div className="flex flex-wrap gap-2">
                  {experiences[selectedExperience].technologies.map((tech, idx) => (
                    <span
                      key={idx}
                      className="bg-slate-600/30 text-slate-300 px-3 py-1 rounded-full text-sm border border-slate-500/30"
                    >
                      {tech}
                    </span>
                  ))}
                </div>
              </div>

              <div>
                <h4 className="text-white mb-3">{t('experience.achievements')}</h4>
                <div className="space-y-2">
                  {experiences[selectedExperience].achievements.map((achievement, idx) => (
                    <div key={idx} className="flex items-center gap-2 text-gray-300">
                      <div className="w-2 h-2 bg-gradient-to-r from-slate-400 to-slate-500 rounded-full"></div>
                      <span>{achievement}</span>
                    </div>
                  ))}
                </div>
              </div>

              {experiences[selectedExperience].reportUrl && (
                <div className="pt-4 border-t border-slate-600/50">
                  <a
                    href={experiences[selectedExperience].reportUrl}
                    target="_blank"
                    rel="noopener noreferrer"
                    className="inline-flex items-center gap-2 bg-gradient-to-r from-slate-600 to-slate-700 hover:from-slate-500 hover:to-slate-600 text-white px-6 py-3 rounded-xl transition-all duration-300 shadow-lg hover:shadow-xl"
                  >
                    <FileText className="w-5 h-5" />
                    <span>{t('experience.report')}</span>
                  </a>
                </div>
              )}
            </div>
          </div>
        </div>
      )}
    </>
  );
}
