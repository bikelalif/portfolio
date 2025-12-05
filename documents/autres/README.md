# Portfolio - Full Stack avec Flask Backend

## 🚀 Structure du projet

```
portfolio/
├── backend/                 # Backend Flask
│   ├── app.py              # Application principale Flask avec toutes les routes API
│   └── requirements.txt    # Dépendances Python
├── components/             # Composants React
│   ├── About.tsx
│   ├── Contact.tsx
│   ├── Education.tsx
│   ├── Experience.tsx
│   ├── Footer.tsx
│   ├── Header.tsx
│   ├── Hobbies.tsx         # Section Loisirs/Vie perso avec modal
│   ├── Navigation.tsx
│   ├── Portfolio.tsx       # Liste des projets (cliquables)
│   ├── ProjectPage.tsx     # Page dédiée pour chaque projet
│   └── Skills.tsx
├── styles/
│   └── globals.css
└── App.tsx                 # Application principale
```

## 🔧 Installation et lancement

### Backend Flask

```bash
cd backend

# Créer un environnement virtuel
python -m venv venv
source venv/bin/activate  # Linux/Mac
# ou
venv\Scripts\activate     # Windows

# Installer les dépendances
pip install -r requirements.txt

# Lancer le serveur
python app.py
```

Le backend sera accessible sur `http://localhost:5000`

### Frontend React

Le frontend utilise React avec TypeScript et Tailwind CSS. 
Il est conçu pour fonctionner avec Vite ou tout autre bundler React.

## 📡 API Endpoints

| Méthode | Endpoint | Description |
|---------|----------|-------------|
| GET | `/` | Toutes les données du portfolio |
| GET | `/api/personal-info` | Informations personnelles |
| GET | `/api/social-links` | Liens réseaux sociaux |
| GET | `/api/education` | Liste des formations |
| GET | `/api/education/<id>` | Détail d'une formation |
| GET | `/api/experiences` | Liste des expériences |
| GET | `/api/experiences/<id>` | Détail d'une expérience |
| GET | `/api/skills` | Compétences |
| GET | `/api/projects` | Liste des projets (résumé) |
| GET | `/api/projects/<slug>` | Détail complet d'un projet |
| GET | `/api/hobbies` | Liste des loisirs |
| GET | `/api/hobbies/<id>` | Détail d'un loisir |
| POST | `/api/contact` | Envoi d'un message de contact |

## ✏️ Personnalisation

Pour modifier tes informations, édite le fichier `backend/app.py` :

1. **PERSONAL_INFO** - Ton nom, email, téléphone, etc.
2. **SOCIAL_LINKS** - Tes liens GitHub, LinkedIn, etc.
3. **EDUCATION** - Tes formations
4. **EXPERIENCES** - Tes expériences pro
5. **SKILLS** - Tes compétences
6. **PROJECTS** - Tes projets (avec détails pour la page dédiée)
7. **HOBBIES** - Tes loisirs et centres d'intérêt

## 🎨 Fonctionnalités

- ✅ Design sobre avec dégradé gris/bleu foncé
- ✅ Section Loisirs/Vie perso avec modal et images
- ✅ Projets cliquables → page dédiée avec galerie
- ✅ Navigation sticky avec indicateur de section active
- ✅ Modals pour Formation et Expérience
- ✅ Backend Flask prêt pour la base de données
- ✅ API RESTful complète
- ✅ Design responsive

## 🔜 Pour aller plus loin

- Connecter le frontend au backend Flask (fetch API)
- Ajouter une base de données (SQLite, PostgreSQL)
- Implémenter l'envoi d'emails pour le formulaire de contact
- Déployer sur Heroku/Vercel/Railway
