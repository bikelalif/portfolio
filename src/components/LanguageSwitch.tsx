import { useLanguage } from '../contexts/LanguageContext';
import { Globe } from 'lucide-react';

export function LanguageSwitch() {
  const { language, setLanguage } = useLanguage();

  return (
    <button
      onClick={() => setLanguage(language === 'fr' ? 'en' : 'fr')}
      className="fixed top-4 right-4 z-50 flex items-center gap-2 bg-slate-700/80 backdrop-blur-sm hover:bg-slate-600 text-white px-3 py-2 rounded-full transition-all duration-300 shadow-lg hover:shadow-xl border border-slate-600/50"
      title={language === 'fr' ? 'Switch to English' : 'Passer en Français'}
    >
      <Globe className="w-4 h-4" />
      <span className="text-sm font-medium">{language === 'fr' ? 'EN' : 'FR'}</span>
    </button>
  );
}
