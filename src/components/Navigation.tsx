import { User, GraduationCap, Briefcase, Code, FolderGit2, Mail, Heart } from 'lucide-react';
import { useState, useEffect } from 'react';

export function Navigation() {
  const [activeSection, setActiveSection] = useState('about');

  const navItems = [
    { id: 'about', label: 'À Propos', icon: User },
    { id: 'education', label: 'Formation', icon: GraduationCap },
    { id: 'experience', label: 'Expérience', icon: Briefcase },
    { id: 'skills', label: 'Compétences', icon: Code },
    { id: 'portfolio', label: 'Projets', icon: FolderGit2 },
    { id: 'hobbies', label: 'Loisirs', icon: Heart },
    { id: 'contact', label: 'Contact', icon: Mail }
  ];

  useEffect(() => {
    const handleScroll = () => {
      const sections = navItems.map(item => ({
        id: item.id,
        element: document.getElementById(item.id)
      }));

      const scrollPosition = window.scrollY + 200;

      for (let i = sections.length - 1; i >= 0; i--) {
        const section = sections[i];
        if (section.element && section.element.offsetTop <= scrollPosition) {
          setActiveSection(section.id);
          break;
        }
      }
    };

    window.addEventListener('scroll', handleScroll);
    return () => window.removeEventListener('scroll', handleScroll);
  }, []);

  const scrollToSection = (id: string) => {
    const element = document.getElementById(id);
    if (element) {
      const offset = 100;
      const elementPosition = element.offsetTop - offset;
      window.scrollTo({
        top: elementPosition,
        behavior: 'smooth'
      });
    }
  };

  return (
    <nav className="sticky top-0 z-50 bg-slate-900/80 backdrop-blur-lg border-b border-slate-700/50 shadow-lg">
      <div className="max-w-6xl mx-auto px-4">
        <div className="flex justify-center items-center py-4 gap-2 overflow-x-auto">
          {navItems.map((item) => {
            const Icon = item.icon;
            const isActive = activeSection === item.id;
            return (
              <button
                key={item.id}
                onClick={() => scrollToSection(item.id)}
                className={`
                  flex items-center gap-2 px-4 py-2 rounded-full transition-all duration-300 whitespace-nowrap
                  ${isActive 
                    ? 'bg-gradient-to-r from-slate-600 to-slate-700 text-white shadow-lg shadow-slate-500/30 scale-105' 
                    : 'bg-slate-800/50 text-gray-300 hover:bg-slate-700/50 hover:text-white'
                  }
                `}
              >
                <Icon className="w-4 h-4" />
                <span className="text-sm">{item.label}</span>
              </button>
            );
          })}
        </div>
      </div>
    </nav>
  );
}
