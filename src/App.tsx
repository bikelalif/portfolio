import { BrowserRouter, Routes, Route, useNavigate, useParams } from 'react-router-dom';
import { Header } from './components/Header';
import { Navigation } from './components/Navigation';
import { About } from './components/About';
import { Education } from './components/Education';
import { Experience } from './components/Experience';
import { Skills } from './components/Skills';
import { Portfolio } from './components/Portfolio';
import { Contact } from './components/Contact';
import { Footer } from './components/Footer';
import { ProjectPage } from './components/ProjectPage';

function HomePage() {
  const navigate = useNavigate();

  return (
    <div className="min-h-screen bg-gradient-to-br from-slate-900 via-slate-800 to-slate-900">
      <Header />
      <Navigation />
      <main className="max-w-6xl mx-auto px-4 py-8 space-y-12">
        <About />
        <Education />
        <Experience />
        <Skills />
        <Portfolio onProjectClick={(slug) => navigate(`/projet/${slug}`)} />
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

export default function App() {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<HomePage />} />
        <Route path="/projet/:slug" element={<ProjectPageWrapper />} />
      </Routes>
    </BrowserRouter>
  );
}
