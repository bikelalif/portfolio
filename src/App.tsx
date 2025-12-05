import { useState } from 'react';
import { Header } from './components/Header';
import { Navigation } from './components/Navigation';
import { About } from './components/About';
import { Education } from './components/Education';
import { Experience } from './components/Experience';
import { Skills } from './components/Skills';
import { Portfolio } from './components/Portfolio';
import { Hobbies } from './components/Hobbies';
import { Contact } from './components/Contact';
import { Footer } from './components/Footer';
import { ProjectPage } from './components/ProjectPage';

export default function App() {
  const [currentProject, setCurrentProject] = useState<string | null>(null);

  // Si un projet est sélectionné, afficher sa page dédiée
  if (currentProject) {
    return (
      <div className="min-h-screen bg-gradient-to-br from-slate-900 via-slate-800 to-slate-900">
        <ProjectPage slug={currentProject} onBack={() => setCurrentProject(null)} />
      </div>
    );
  }

  return (
    <div className="min-h-screen bg-gradient-to-br from-slate-900 via-slate-800 to-slate-900">
      <Header />
      <Navigation />
      <main className="max-w-6xl mx-auto px-4 py-8 space-y-12">
        <About />
        <Education />
        <Experience />
        <Skills />
        <Portfolio onProjectClick={(slug) => setCurrentProject(slug)} />
        <Hobbies />
        <Contact />
      </main>
      <Footer />
    </div>
  );
}
