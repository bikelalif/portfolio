import { Github, Linkedin, Mail } from 'lucide-react';

export function Footer() {
  const socialLinks = [
    { icon: Github, url: "https://github.com/bikelalif", label: "GitHub" },
    { icon: Linkedin, url: "https://fr.linkedin.com/in/bilal-kefif-94400015a", label: "LinkedIn" },
    { icon: Mail, url: "mailto:bilalkefif243@gmail.com", label: "Email" }
  ];

  return (
    <footer className="bg-slate-900 text-white py-12 mt-16 border-t border-slate-700/50">
      <div className="max-w-6xl mx-auto px-4">
        <div className="flex flex-col items-center gap-6">
          <div className="flex gap-4">
            {socialLinks.map((link, index) => {
              const Icon = link.icon;
              return (
                <a
                  key={index}
                  href={link.url}
                  target="_blank"
                  rel="noopener noreferrer"
                  className="bg-slate-800 p-3 rounded-full hover:bg-gradient-to-r hover:from-slate-600 hover:to-slate-700 transition-all duration-300 shadow-lg hover:shadow-slate-500/30"
                  aria-label={link.label}
                >
                  <Icon className="w-5 h-5" />
                </a>
              );
            })}
          </div>
          <div className="text-center text-gray-400 text-sm">
            <p>© 2025 Bilal KEFIF. Tous droits réservés.</p>
            <p className="mt-2">Développé avec React & Tailwind CSS</p>
          </div>
        </div>
      </div>
    </footer>
  );
}
