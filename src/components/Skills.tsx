import { Code2, Database, Palette, Wrench } from 'lucide-react';
import { useLanguage } from '../contexts/LanguageContext';

export function Skills() {
  const { t } = useLanguage();
  
  const skillCategories = [
    {
      icon: Code2,
      title: t('skills.languages'),
      skills: ["Python", "Java", "C", "JavaScript", "TypeScript", "SQL", "HTML/CSS", "PHP", "R", "OCaml", "Groovy"]
    },
    {
      icon: Wrench,
      title: t('skills.frameworks'),
      skills: ["React", "Flask", "JavaFX", "PyQt5", "Maven", "Git", "Docker", "VS Code"]
    },
    {
      icon: Database,
      title: t('skills.databases'),
      skills: ["PostgreSQL", "MySQL", "SQLite", "MongoDB"]
    },
    {
      icon: Palette,
      title: t('skills.spoken'),
      skills: [t('skills.french'), t('skills.english')]
    }
  ];

  return (
    <section id="skills" className="bg-slate-800/50 backdrop-blur-sm rounded-2xl shadow-xl p-8 border border-slate-700/50">
      <h2 className="mb-6 text-slate-200">{t('skills.title')}</h2>
      <div className="grid md:grid-cols-2 gap-6">
        {skillCategories.map((category, index) => {
          const Icon = category.icon;
          return (
            <div key={index} className="bg-gradient-to-br from-slate-700/30 to-slate-800/30 rounded-xl p-6 border border-slate-600/30 hover:border-slate-500/50 transition-all duration-300">
              <div className="flex items-center gap-3 mb-4">
                <div className="bg-gradient-to-r from-slate-600 to-slate-700 text-white p-2 rounded-lg shadow-lg">
                  <Icon className="w-5 h-5" />
                </div>
                <h3 className="text-white">{category.title}</h3>
              </div>
              <div className="flex flex-wrap gap-2">
                {category.skills.map((skill, skillIndex) => (
                  <span
                    key={skillIndex}
                    className="bg-slate-700/50 border border-slate-500/30 px-3 py-1 rounded-full text-sm text-gray-300 hover:bg-slate-600/50 hover:border-slate-400/50 transition-all"
                  >
                    {skill}
                  </span>
                ))}
              </div>
            </div>
          );
        })}
      </div>
    </section>
  );
}
