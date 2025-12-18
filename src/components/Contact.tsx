import { Mail, MessageSquare } from 'lucide-react';
import { useLanguage } from '../contexts/LanguageContext';

export function Contact() {
  const { t } = useLanguage();
  
  return (
    <section id="contact" className="bg-gradient-to-br from-slate-700 via-slate-600 to-slate-700 rounded-2xl shadow-2xl p-8 text-white border border-slate-500/30">
      <h2 className="mb-6 text-white flex items-center gap-3">
        <MessageSquare className="w-8 h-8" />
        {t('contact.title')}
      </h2>
      <p className="mb-6 text-white/90">
        {t('contact.description')}
      </p>
      <a
        href="mailto:bilalkefif243@gmail.com"
        className="inline-flex items-center gap-2 bg-white text-slate-700 px-6 py-3 rounded-lg hover:bg-gray-100 transition-colors shadow-lg"
      >
        <Mail className="w-5 h-5" />
        {t('contact.email')}
      </a>
    </section>
  );
}
