import { FileText, Download } from 'lucide-react';
import { useLanguage } from '../contexts/LanguageContext';

export function Documents() {
  const { t, language } = useLanguage();
  
  const documents = [
    {
      id: 'cv',
      title: t('documents.cv.title'),
      description: t('documents.cv.description'),
      icon: FileText,
      file: language === 'fr' ? '/cv_fr.pdf' : '/cv_en.pdf',
      color: 'from-blue-500 to-cyan-500'
    },
    {
      id: 'cover-letter',
      title: t('documents.coverLetter.title'),
      description: t('documents.coverLetter.description'),
      icon: FileText,
      file: language === 'fr' ? '/lettre_motivation_fr.pdf' : '/lettre_motivation_en.pdf',
      color: 'from-purple-500 to-pink-500'
    }
  ];

  return (
    <section id="documents" className="bg-slate-800/50 backdrop-blur-sm rounded-2xl shadow-xl p-8 border border-slate-700/50">
      <h2 className="mb-6 text-slate-200">{t('documents.title')}</h2>
      <div className="grid md:grid-cols-2 gap-6">
        {documents.map((doc) => {
          const Icon = doc.icon;
          return (
            <div
              key={doc.id}
              className="group relative bg-gradient-to-br from-slate-700/50 to-slate-800/50 p-6 rounded-xl border border-slate-600/50 hover:border-slate-500 transition-all duration-300 hover:shadow-lg hover:shadow-slate-500/20"
            >
              <div className="flex items-start gap-4">
                <div className={`p-3 rounded-lg bg-gradient-to-br ${doc.color} shadow-lg`}>
                  <Icon className="w-6 h-6 text-white" />
                </div>
                <div className="flex-1">
                  <h3 className="text-xl font-semibold text-white mb-2">
                    {doc.title}
                    {doc.comingSoon && (
                      <span className="ml-2 text-xs bg-yellow-500/20 text-yellow-300 px-2 py-1 rounded-full">
                        {t('documents.comingSoon')}
                      </span>
                    )}
                  </h3>
                  <p className="text-gray-300 text-sm mb-4">{doc.description}</p>
                  {!doc.comingSoon && (
                    <div className="flex gap-3">
                      <a
                        href={doc.file}
                        target="_blank"
                        rel="noopener noreferrer"
                        className="inline-flex items-center gap-2 px-4 py-2 bg-slate-600 hover:bg-slate-500 text-white rounded-lg transition-colors text-sm"
                      >
                        <FileText className="w-4 h-4" />
                        {t('documents.view')}
                      </a>
                      <a
                        href={doc.file}
                        download
                        className="inline-flex items-center gap-2 px-4 py-2 bg-gradient-to-r from-slate-600 to-slate-700 hover:from-slate-500 hover:to-slate-600 text-white rounded-lg transition-all text-sm"
                      >
                        <Download className="w-4 h-4" />
                        {t('documents.download')}
                      </a>
                    </div>
                  )}
                </div>
              </div>
            </div>
          );
        })}
      </div>
    </section>
  );
}
