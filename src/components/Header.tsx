import { Mail, MapPin, Linkedin, Github } from 'lucide-react';
import { useLanguage } from '../contexts/LanguageContext';

export function Header() {
  const { t } = useLanguage();
  
  return (
    <header className="bg-gradient-to-r from-slate-800 via-slate-700 to-slate-800 text-white">
      <div className="max-w-6xl mx-auto px-4 py-16">
        <div className="text-center">
          <div className="w-48 h-48 mx-auto mb-6 rounded-full bg-white/10 backdrop-blur-sm flex items-center justify-center overflow-hidden border-4 border-white/30 shadow-2xl">
            <img src="/photo_profil.jpg" alt="Bilal KEFIF" className="w-full h-full object-cover" />
          </div>
          <h1 className="mb-2">Bilal KEFIF</h1>
          <p className="text-xl text-white/90 mb-6">{t('header.title')}</p>
          <div className="flex flex-wrap justify-center gap-4 text-sm">
            <div className="flex items-center gap-2 bg-white/10 backdrop-blur-sm px-4 py-2 rounded-full">
              <Mail className="w-4 h-4" />
              <span>bilalkefif243@gmail.com</span>
            </div>
            <div className="flex items-center gap-2 bg-white/10 backdrop-blur-sm px-4 py-2 rounded-full">
              <MapPin className="w-4 h-4" />
              <span>Paris, France</span>
            </div>
            <a 
              href="https://fr.linkedin.com/in/bilal-kefif-94400015a" 
              target="_blank" 
              rel="noopener noreferrer"
              className="flex items-center gap-2 bg-white/10 backdrop-blur-sm px-4 py-2 rounded-full hover:bg-white/20 transition-colors"
            >
              <Linkedin className="w-4 h-4" />
              <span>LinkedIn</span>
            </a>
            <a 
              href="https://github.com/bikelalif" 
              target="_blank" 
              rel="noopener noreferrer"
              className="flex items-center gap-2 bg-white/10 backdrop-blur-sm px-4 py-2 rounded-full hover:bg-white/20 transition-colors"
            >
              <Github className="w-4 h-4" />
              <span>GitHub</span>
            </a>
          </div>
        </div>
      </div>
    </header>
  );
}
