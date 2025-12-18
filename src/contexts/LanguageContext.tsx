import { createContext, useContext, useState, ReactNode } from 'react';

type Language = 'fr' | 'en';

interface LanguageContextType {
  language: Language;
  setLanguage: (lang: Language) => void;
  t: (key: string) => string;
}

const translations: Record<Language, Record<string, string>> = {
  fr: {
    // Header
    'header.title': 'Étudiant Ingénieur en Génie Logiciel',
    
    // Navigation
    'nav.about': 'À Propos',
    'nav.education': 'Formation',
    'nav.experience': 'Expérience',
    'nav.skills': 'Compétences',
    'nav.projects': 'Projets',
    'nav.documents': 'Documents',
    'nav.contact': 'Contact',
    
    // About
    'about.title': 'À Propos',
    'about.description': "Étudiant en 2ème année à l'ENSIIE, spécialisé en génie logiciel (architecture logicielle, méthodes formelles, sécurité). Je m'oriente vers la",
    'about.cybersecurity': 'cybersécurité',
    'about.description2': "dès le semestre prochain avec un échange à l'Université Laval (Québec) et recherche un",
    'about.internship': 'stage dans ce domaine',
    'about.description3': ". Dynamique, rigoureux et créatif, je m'adapte rapidement aux situations et fais preuve d'un fort engagement dans mon travail.",
    
    // Education
    'education.title': 'Formation',
    'education.program': 'Programme',
    'education.achievements': 'Distinctions',
    'education.details': 'Voir les détails',
    
    // Education entries
    'education.laval.degree': 'Maîtrise en Informatique - Cybersécurité',
    'education.laval.school': 'Université Laval',
    'education.laval.period': 'Janvier - Mai 2026',
    'education.laval.location': 'Québec, Canada',
    'education.laval.description': 'Échange international - Spécialisation en cybersécurité',
    'education.laval.detail1': 'Qualité logicielle en informatique',
    'education.laval.detail2': 'Sécurité des logiciels',
    'education.laval.detail3': "Sécurité de l'Internet des objets",
    'education.laval.detail4': 'Apprentissage par réseau de neurones profonds',
    'education.laval.detail5': 'Concepts et applications de la chaîne de blocs',
    'education.laval.achievement': 'Échange international',
    
    'education.ensiie.degree': "Diplôme d'Ingénieur en Génie Logiciel",
    'education.ensiie.school': "ENSIIE - École Nationale Supérieure d'Informatique",
    'education.ensiie.period': '2024 - En cours',
    'education.ensiie.location': 'Évry, France',
    'education.ensiie.description': 'Architecture logicielle, méthodes formelles, sécurité du numérique',
    'education.ensiie.detail1': 'Génie logiciel',
    'education.ensiie.detail2': 'Langage objet avancé',
    'education.ensiie.detail3': 'Langage formel et vérification du logiciel',
    'education.ensiie.detail4': 'Programmation fonctionnelle avancée',
    'education.ensiie.detail5': 'Assembleur et compilation (sous-parcours Systèmes sûrs)',
    'education.ensiie.achievement': 'En cours',
    
    'education.cpge.degree': 'CPGE - Classes Préparatoires',
    'education.cpge.school': 'Lycée Albert Schweitzer',
    'education.cpge.period': '2021 - 2024',
    'education.cpge.location': 'Le Raincy, France',
    'education.cpge.description': 'Filière Physique-Chimie (PC) - Niveau Bac+2',
    'education.cpge.detail1': 'Mathématiques approfondies',
    'education.cpge.detail2': 'Physique et Chimie',
    'education.cpge.detail3': 'Informatique (Python, algorithmique)',
    'education.cpge.detail4': "Sciences de l'ingénieur",
    'education.cpge.detail5': 'Préparation aux concours des grandes écoles',
    'education.cpge.achievement': "Admission à l'ENSIIE",
    
    'education.bac.degree': 'Baccalauréat Général',
    'education.bac.school': 'Lycée Honoré de Balzac',
    'education.bac.period': '2018 - 2021',
    'education.bac.location': 'Mitry-Mory, France',
    'education.bac.description': 'Spécialités Physique-Chimie et Mathématiques',
    'education.bac.detail1': 'Spécialité Mathématiques',
    'education.bac.detail2': 'Spécialité Physique-Chimie',
    'education.bac.detail3': 'Option Mathématiques Expertes',
    
    // Experience
    'experience.title': 'Expérience',
    'experience.tasks': 'Missions',
    'experience.technologies': 'Technologies utilisées',
    'experience.achievements': 'Réalisations',
    'experience.details': 'Voir les détails',
    'experience.report': 'Voir le rapport de stage',
    
    'experience.idiatech.title': 'Stagiaire Développeur',
    'experience.idiatech.company': 'idIA tech',
    'experience.idiatech.period': 'Mai - Août 2025',
    'experience.idiatech.location': 'Montpezat, France',
    'experience.idiatech.description': "Développement de scripts clients et amélioration de l'IDE Grimport pour l'extraction automatisée de données e-commerce.",
    'experience.idiatech.task1': "Développement de scripts Grimport (Groovy/Java) pour automatiser l'import de catalogues fournisseurs",
    'experience.idiatech.task2': 'Rétro-ingénierie de sites web sources, extraction et transformation de données (web mining)',
    'experience.idiatech.task3': 'Contournement de Captchas et gestion des cookies de session',
    'experience.idiatech.task4': "Intégration d'APIs externes (OpenAI, antiCaptcha)",
    'experience.idiatech.task5': 'Analyse réseau avec Fiddler pour déboguer les requêtes HTTP',
    'experience.idiatech.task6': "Remise en état du débogueur de l'IDE Grimport (correction de code, dépendances, Gradle/Eclipse)",
    'experience.idiatech.achievement1': 'Scripts clients livrés et fonctionnels',
    'experience.idiatech.achievement2': 'Amélioration significative du débogueur IDE',
    'experience.idiatech.achievement3': 'Rapport de stage complet avec documentation technique',
    
    // Skills
    'skills.title': 'Compétences',
    'skills.languages': 'Langages de Programmation',
    'skills.frameworks': 'Frameworks & Outils',
    'skills.databases': 'Base de Données',
    'skills.spoken': 'Langues',
    'skills.french': 'Français (natif)',
    'skills.english': 'Anglais (avancé)',
    
    // Portfolio
    'portfolio.title': 'Projets',
    'portfolio.details': 'Voir le projet',
    'portfolio.features': 'Fonctionnalités',
    'portfolio.github': 'Voir sur GitHub',
    'portfolio.back': 'Retour',
    
    // Documents
    'documents.title': 'Documents',
    'documents.cv.title': 'Curriculum Vitae',
    'documents.cv.description': 'Téléchargez mon CV complet détaillant mon parcours académique et professionnel.',
    'documents.coverLetter.title': 'Lettre de Motivation',
    'documents.coverLetter.description': 'Ma lettre de motivation pour les opportunités de stage en cybersécurité.',
    'documents.view': 'Voir',
    'documents.download': 'Télécharger',
    'documents.comingSoon': 'Bientôt disponible',
    
    // Contact
    'contact.title': 'Contactez-moi',
    'contact.description': "Je suis actuellement étudiant ingénieur à l'ENSIIE et ouvert aux opportunités de stage. N'hésitez pas à me contacter !",
    'contact.email': 'Envoyer un email',
    
    // Footer
    'footer.rights': '© 2025 Bilal KEFIF. Tous droits réservés.',
    'footer.built': 'Développé avec React & Tailwind CSS',
  },
  en: {
    // Header
    'header.title': 'Software Engineering Student',
    
    // Navigation
    'nav.about': 'About',
    'nav.education': 'Education',
    'nav.experience': 'Experience',
    'nav.skills': 'Skills',
    'nav.projects': 'Projects',
    'nav.documents': 'Documents',
    'nav.contact': 'Contact',
    
    // About
    'about.title': 'About',
    'about.description': "Second-year student at ENSIIE, specializing in software engineering (software architecture, formal methods, security). I'm transitioning to",
    'about.cybersecurity': 'cybersecurity',
    'about.description2': "next semester with an exchange at Université Laval (Quebec) and seeking an",
    'about.internship': 'internship in this field',
    'about.description3': ". Dynamic, rigorous, and creative, I adapt quickly to new situations and demonstrate strong commitment in my work.",
    
    // Education
    'education.title': 'Education',
    'education.program': 'Program',
    'education.achievements': 'Achievements',
    'education.details': 'View details',
    
    // Education entries
    'education.laval.degree': "Master's in Computer Science - Cybersecurity",
    'education.laval.school': 'Université Laval',
    'education.laval.period': 'January - May 2026',
    'education.laval.location': 'Quebec, Canada',
    'education.laval.description': 'International exchange - Cybersecurity specialization',
    'education.laval.detail1': 'Software Quality in Computing',
    'education.laval.detail2': 'Software Security',
    'education.laval.detail3': 'Internet of Things Security',
    'education.laval.detail4': 'Deep Neural Network Learning',
    'education.laval.detail5': 'Blockchain Concepts and Applications',
    'education.laval.achievement': 'International exchange',
    
    'education.ensiie.degree': 'Engineering Degree in Software Engineering',
    'education.ensiie.school': 'ENSIIE - National School of Computer Science',
    'education.ensiie.period': '2024 - Present',
    'education.ensiie.location': 'Évry, France',
    'education.ensiie.description': 'Software architecture, formal methods, digital security',
    'education.ensiie.detail1': 'Software Engineering',
    'education.ensiie.detail2': 'Advanced Object-Oriented Programming',
    'education.ensiie.detail3': 'Formal Languages and Software Verification',
    'education.ensiie.detail4': 'Advanced Functional Programming',
    'education.ensiie.detail5': 'Assembly and Compilation (Secure Systems track)',
    'education.ensiie.achievement': 'In progress',
    
    'education.cpge.degree': 'CPGE - Preparatory Classes',
    'education.cpge.school': 'Lycée Albert Schweitzer',
    'education.cpge.period': '2021 - 2024',
    'education.cpge.location': 'Le Raincy, France',
    'education.cpge.description': 'Physics-Chemistry track (PC) - Bachelor level',
    'education.cpge.detail1': 'Advanced Mathematics',
    'education.cpge.detail2': 'Physics and Chemistry',
    'education.cpge.detail3': 'Computer Science (Python, algorithms)',
    'education.cpge.detail4': 'Engineering Sciences',
    'education.cpge.detail5': 'Preparation for elite engineering school entrance exams',
    'education.cpge.achievement': 'Admitted to ENSIIE',
    
    'education.bac.degree': 'High School Diploma',
    'education.bac.school': 'Lycée Honoré de Balzac',
    'education.bac.period': '2018 - 2021',
    'education.bac.location': 'Mitry-Mory, France',
    'education.bac.description': 'Physics-Chemistry and Mathematics specializations',
    'education.bac.detail1': 'Mathematics Specialization',
    'education.bac.detail2': 'Physics-Chemistry Specialization',
    'education.bac.detail3': 'Expert Mathematics Option',
    
    // Experience
    'experience.title': 'Experience',
    'experience.tasks': 'Tasks',
    'experience.technologies': 'Technologies used',
    'experience.achievements': 'Achievements',
    'experience.details': 'View details',
    'experience.report': 'View internship report',
    
    'experience.idiatech.title': 'Developer Intern',
    'experience.idiatech.company': 'idIA tech',
    'experience.idiatech.period': 'May - August 2025',
    'experience.idiatech.location': 'Montpezat, France',
    'experience.idiatech.description': 'Development of client scripts and improvement of the Grimport IDE for automated e-commerce data extraction.',
    'experience.idiatech.task1': 'Development of Grimport scripts (Groovy/Java) to automate supplier catalog imports',
    'experience.idiatech.task2': 'Reverse engineering of source websites, data extraction and transformation (web mining)',
    'experience.idiatech.task3': 'Captcha bypassing and session cookie management',
    'experience.idiatech.task4': 'Integration of external APIs (OpenAI, antiCaptcha)',
    'experience.idiatech.task5': 'Network analysis with Fiddler to debug HTTP requests',
    'experience.idiatech.task6': 'Restoration of Grimport IDE debugger (code fixes, dependencies, Gradle/Eclipse)',
    'experience.idiatech.achievement1': 'Client scripts delivered and functional',
    'experience.idiatech.achievement2': 'Significant improvement of IDE debugger',
    'experience.idiatech.achievement3': 'Complete internship report with technical documentation',
    
    // Skills
    'skills.title': 'Skills',
    'skills.languages': 'Programming Languages',
    'skills.frameworks': 'Frameworks & Tools',
    'skills.databases': 'Databases',
    'skills.spoken': 'Languages',
    'skills.french': 'French (native)',
    'skills.english': 'English (advanced)',
    
    // Portfolio
    'portfolio.title': 'Projects',
    'portfolio.details': 'View project',
    'portfolio.features': 'Features',
    'portfolio.github': 'View on GitHub',
    'portfolio.back': 'Back',
    
    // Documents
    'documents.title': 'Documents',
    'documents.cv.title': 'Resume',
    'documents.cv.description': 'Download my complete resume detailing my academic and professional background.',
    'documents.coverLetter.title': 'Cover Letter',
    'documents.coverLetter.description': 'My cover letter for cybersecurity internship opportunities.',
    'documents.view': 'View',
    'documents.download': 'Download',
    'documents.comingSoon': 'Coming Soon',
    
    // Contact
    'contact.title': 'Contact Me',
    'contact.description': "I'm currently an engineering student at ENSIIE and open to internship opportunities. Feel free to contact me!",
    'contact.email': 'Send an email',
    
    // Footer
    'footer.rights': '© 2025 Bilal KEFIF. All rights reserved.',
    'footer.built': 'Built with React & Tailwind CSS',
  }
};

const LanguageContext = createContext<LanguageContextType | undefined>(undefined);

export function LanguageProvider({ children }: { children: ReactNode }) {
  const [language, setLanguage] = useState<Language>('fr');

  const t = (key: string): string => {
    return translations[language][key] || key;
  };

  return (
    <LanguageContext.Provider value={{ language, setLanguage, t }}>
      {children}
    </LanguageContext.Provider>
  );
}

export function useLanguage() {
  const context = useContext(LanguageContext);
  if (!context) {
    throw new Error('useLanguage must be used within a LanguageProvider');
  }
  return context;
}
