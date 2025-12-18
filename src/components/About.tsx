import { useLanguage } from '../contexts/LanguageContext';

export function About() {
  const { t } = useLanguage();
  
  return (
    <section id="about" className="bg-slate-800/50 backdrop-blur-sm rounded-2xl shadow-xl p-8 border border-slate-700/50">
      <h2 className="mb-6 text-slate-200">{t('about.title')}</h2>
      <p className="text-gray-300 leading-relaxed">
        {t('about.description')} <strong className="text-white">{t('about.cybersecurity')}</strong> {t('about.description2')}
        <strong className="text-white"> {t('about.internship')}</strong>{t('about.description3')}
      </p>
    </section>
  );
}
