import { BrowserRouter, Routes, Route, useNavigate, useParams } from 'react-router-dom';
import { Header } from './components/Header';
import { Navigation } from './components/Navigation';
import { About } from './components/About';
import { Education } from './components/Education';
import { Experience } from './components/Experience';
import { Skills } from './components/Skills';
import { Portfolio } from './components/Portfolio';
import { Documents } from './components/Documents';
import { Contact } from './components/Contact';
import { Footer } from './components/Footer';
import { ProjectPage } from './components/ProjectPage';
import { SeventDemo } from './components/SeventDemo';
import { LanguageProvider } from './contexts/LanguageContext';
import { LanguageSwitch } from './components/LanguageSwitch';

function HomePage() {
  const navigate = useNavigate();

  return (
    <div className="min-h-screen bg-gradient-to-br from-slate-900 via-slate-800 to-slate-900">
      <LanguageSwitch />
      <Header />
      <Navigation />
      <main className="max-w-6xl mx-auto px-4 py-8 space-y-12">
        <About />
        <Education />
        <Experience />
        <Skills />
        <Portfolio onProjectClick={(slug) => navigate(`/projet/${slug}`)} />
        <Documents />
        <Contact />
      </main>
      <Footer />
    </div>
  );
}

function ProjectPageWrapper() {
  const { slug } = useParams<{ slug: string }>();
  const navigate = useNavigate();

  if (!slug) {
    navigate('/');
    return null;
  }

  return (
    <div className="min-h-screen bg-gradient-to-br from-slate-900 via-slate-800 to-slate-900">
      <ProjectPage slug={slug} onBack={() => navigate('/')} />
    </div>
  );
}

function SeventDemoPage() {
  const navigate = useNavigate();

  return (
    <div className="min-h-screen bg-gradient-to-br from-slate-900 via-slate-800 to-slate-900">
      <LanguageSwitch />
      <div className="max-w-6xl mx-auto px-4 py-8">
        <button
          onClick={() => navigate('/')}
          className="mb-6 px-4 py-2 bg-slate-700 hover:bg-slate-600 text-white rounded-lg transition-colors"
        >
          ← Retour
        </button>
        <SeventDemo />
      </div>
      <Footer />
    </div>
  );
}

export default function App() {
  return (
    <LanguageProvider>
      <BrowserRouter>
        <Routes>
          <Route path="/" element={<HomePage />} />
          <Route path="/projet/:slug" element={<ProjectPageWrapper />} />
          <Route path="/demo/sevent" element={<SeventDemoPage />} />
        </Routes>
      </BrowserRouter>
    </LanguageProvider>
  );
}
