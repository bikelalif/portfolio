from flask import Flask, jsonify, request, send_from_directory
from flask_cors import CORS
from flask_sock import Sock
import os
import subprocess
import signal
import threading
import pty
import select
import pexpect

app = Flask(__name__)
CORS(app)
sock = Sock(app)

# Stockage des sessions terminales actives
terminal_sessions = {}

# Chemin vers l'image placeholder
IMAGE_PATH = "/image_noire.jpg"

# Stockage des processus de démo
demo_processes = {}

# Chemins des projets démo
DEMO_PROJECTS = {
    "sevent-gestion-evenements": {
        "path": "/home/bilal/portfolio/projets/sevent-gestion-evenements",
        "port": 5002,
        "command": "python app.py",
        "venv": "venv",
        "type": "web"
    }
}

# Projets avec démo terminal (C, Python console, etc.)
TERMINAL_PROJECTS = {
    "jeu-de-cartes-c": {
        "path": "/home/bilal/portfolio/projets/jeu-de-cartes-c",
        "compile_cmd": "make",
        "run_cmd": "./bin/projet",
        "description": "Jeu de cartes en C - bataille et blackjack"
    }
}

# ==================== DONNÉES DU PORTFOLIO - BILAL KEFIF ====================

# Informations personnelles
PERSONAL_INFO = {
    "name": "Bilal KEFIF",
    "title": "Étudiant Ingénieur en Informatique",
    "email": "bilalkefif243@gmail.com",
    "phone": "06 22 39 22 30",
    "location": "Villeparisis, France",
    "avatar": "👨‍💻",
    "about": """Étudiant en première année à l'ENSIIE, en formation d'ingénieur en informatique. 
    Dynamique, rigoureux et créatif, je m'adapte rapidement aux situations et fais preuve d'un fort engagement dans mon travail. 
    Je suis très familier avec les outils informatiques grâce à ma formation. 
    Je recherche actuellement un job étudiant afin de financer ma prochaine année d'étude."""
}

# Liens sociaux
SOCIAL_LINKS = {
    "github": "https://github.com/bilalkefif",
    "linkedin": "https://linkedin.com/in/bilal-kefif",
    "email": "mailto:bilalkefif243@gmail.com"
}

# Formation
EDUCATION = [
    {
        "id": 1,
        "degree": "Diplôme d'Ingénieur en Génie Logiciel",
        "school": "ENSIIE - École Nationale Supérieure d'Informatique pour l'Industrie et l'Entreprise",
        "period": "2024 - En cours",
        "location": "Évry, France",
        "description": "Formation d'ingénieur spécialisée en informatique et génie logiciel",
        "image": IMAGE_PATH,
        "details": [
            "Architecture logicielle et design patterns",
            "Développement d'applications web et mobiles",
            "Algorithmique avancée et structures de données",
            "Intelligence artificielle et Machine Learning",
            "Gestion de projets informatiques"
        ],
        "achievements": ["En cours"]
    },
    {
        "id": 2,
        "degree": "CPGE - Classes Préparatoires aux Grandes Écoles",
        "school": "Lycée Albert Schweitzer",
        "period": "2021 - 2024",
        "location": "Le Raincy, France",
        "description": "Filière Physique-Chimie (PC) - Niveau Bac+2",
        "image": IMAGE_PATH,
        "details": [
            "Mathématiques approfondies",
            "Physique et Chimie",
            "Informatique (Python, algorithmique)",
            "Sciences de l'ingénieur",
            "Préparation aux concours des grandes écoles"
        ],
        "achievements": ["Admission à l'ENSIIE"]
    },
    {
        "id": 3,
        "degree": "Baccalauréat Général",
        "school": "Lycée Honoré de Balzac",
        "period": "2018 - 2021",
        "location": "Mitry-Mory, France",
        "description": "Spécialités Physique-Chimie et Mathématiques",
        "image": IMAGE_PATH,
        "details": [
            "Spécialité Mathématiques",
            "Spécialité Physique-Chimie",
            "Option Mathématiques Expertes"
        ],
        "achievements": ["Mention Bien"]
    }
]

# Expériences professionnelles
EXPERIENCES = [
    {
        "id": 1,
        "title": "Chauffeur-Livreur & Opérateur",
        "company": "Air2jeux",
        "period": "Mai 2023 - En cours",
        "location": "Croissy-Beaubourg, France",
        "description": "Livraison et installation de structures gonflables pour événements",
        "image": IMAGE_PATH,
        "tasks": [
            "Conduite de véhicules utilitaires (20m³ hayon et 12m³)",
            "Livraison et installation chez les clients",
            "Montage et démontage de structures gonflables",
            "Relation client et service après-vente",
            "Gestion des plannings de livraison"
        ],
        "technologies": ["Logistique", "Relation client", "Permis B"],
        "achievements": ["Polyvalence", "Autonomie"]
    },
    {
        "id": 2,
        "title": "Opérateur de Production",
        "company": "Prodene Klint",
        "period": "Juillet - Août 2024",
        "location": "Croissy-Beaubourg, France",
        "description": "Travail en usine sur chaîne de production",
        "image": IMAGE_PATH,
        "tasks": [
            "Opérateur sur chaîne de production",
            "Préparateur de commandes",
            "Réglage de base des machines industrielles",
            "Contrôle qualité des produits",
            "Respect des normes de sécurité"
        ],
        "technologies": ["Machines industrielles", "Filmeuse", "Chaîne de production"],
        "achievements": ["Rigueur", "Travail en équipe"]
    }
]

# Compétences
SKILLS = [
    {
        "category": "Langages de Programmation",
        "icon": "code",
        "skills": ["Python", "Java", "C", "SQL", "HTML/CSS", "PHP", "R", "OCaml", "Groovy", "JavaScript"]
    },
    {
        "category": "Outils & Logiciels",
        "icon": "wrench",
        "skills": ["Microsoft Office", "Excel", "PowerPoint", "Git", "VS Code"]
    },
    {
        "category": "Compétences Techniques",
        "icon": "database",
        "skills": ["Algorithmique", "Bases de données", "Développement Web", "Programmation orientée objet"]
    },
    {
        "category": "Langues",
        "icon": "globe",
        "skills": ["Français (Langue maternelle)", "Anglais (Niveau avancé)"]
    }
]

# Projets Portfolio
PROJECTS = [
    {
        "id": 1,
        "slug": "portfolio-web",
        "title": "Portfolio Personnel",
        "short_description": "Site web portfolio responsive développé avec React et Flask",
        "full_description": """Portfolio personnel moderne développé avec React pour le frontend et Flask pour le backend.
        Ce projet présente mes compétences, formations et expériences de manière interactive.""",
        "image": IMAGE_PATH,
        "images": [IMAGE_PATH],
        "tags": ["React", "Flask", "Tailwind CSS"],
        "technologies": ["React", "TypeScript", "Flask", "Python", "Tailwind CSS"],
        "features": [
            "Design responsive",
            "API REST Flask",
            "Animations fluides",
            "Navigation intuitive"
        ],
        "challenges": [
            "Intégration frontend/backend",
            "Optimisation des performances"
        ],
        "github": "https://github.com/bilalkefif/portfolio",
        "demo": "#",
        "date": "2024"
    }
]

# Loisirs & Vie Personnelle
HOBBIES = [
    {
        "id": 1,
        "title": "Voyages",
        "icon": "plane",
        "description": "Découverte de nouvelles cultures et destinations",
        "image": IMAGE_PATH,
        "images": [IMAGE_PATH],
        "details": [
            "Exploration de différentes cultures",
            "Découverte de nouvelles cuisines",
            "Apprentissage de nouvelles langues",
            "Ouverture d'esprit"
        ],
        "interests": ["Culture", "Gastronomie", "Aventure"]
    }
]


# ==================== ROUTES API ====================

@app.route('/')
def home():
    return jsonify({
        "personal_info": PERSONAL_INFO,
        "social_links": SOCIAL_LINKS,
        "education": EDUCATION,
        "experiences": EXPERIENCES,
        "skills": SKILLS,
        "projects": PROJECTS,
        "hobbies": HOBBIES
    })

@app.route('/api/personal-info')
def get_personal_info():
    return jsonify(PERSONAL_INFO)

@app.route('/api/social-links')
def get_social_links():
    return jsonify(SOCIAL_LINKS)

@app.route('/api/education')
def get_education():
    return jsonify(EDUCATION)

@app.route('/api/education/<int:education_id>')
def get_education_by_id(education_id):
    for edu in EDUCATION:
        if edu['id'] == education_id:
            return jsonify(edu)
    return jsonify({"error": "Formation non trouvée"}), 404

@app.route('/api/experiences')
def get_experiences():
    return jsonify(EXPERIENCES)

@app.route('/api/experiences/<int:experience_id>')
def get_experience_by_id(experience_id):
    for exp in EXPERIENCES:
        if exp['id'] == experience_id:
            return jsonify(exp)
    return jsonify({"error": "Expérience non trouvée"}), 404

@app.route('/api/skills')
def get_skills():
    return jsonify(SKILLS)

@app.route('/api/projects')
def get_projects():
    short_projects = []
    for project in PROJECTS:
        short_projects.append({
            "id": project["id"],
            "slug": project["slug"],
            "title": project["title"],
            "description": project["short_description"],
            "image": project["image"],
            "tags": project["tags"],
            "github": project["github"],
            "demo": project["demo"]
        })
    return jsonify(short_projects)

@app.route('/api/projects/<slug>')
def get_project_by_slug(slug):
    for project in PROJECTS:
        if project['slug'] == slug:
            return jsonify(project)
    return jsonify({"error": "Projet non trouvé"}), 404

@app.route('/api/hobbies')
def get_hobbies():
    return jsonify(HOBBIES)

@app.route('/api/hobbies/<int:hobby_id>')
def get_hobby_by_id(hobby_id):
    for hobby in HOBBIES:
        if hobby['id'] == hobby_id:
            return jsonify(hobby)
    return jsonify({"error": "Loisir non trouvé"}), 404

@app.route('/api/contact', methods=['POST'])
def contact():
    data = request.get_json()
    required_fields = ['name', 'email', 'message']
    for field in required_fields:
        if field not in data or not data[field]:
            return jsonify({"error": f"Le champ {field} est requis"}), 400
    print(f"Message reçu de {data['name']} ({data['email']}): {data['message']}")
    return jsonify({"success": True, "message": "Message envoyé avec succès!"})

# ==================== ROUTES DÉMO ====================

@app.route('/api/demo/start/<slug>', methods=['POST'])
def start_demo(slug):
    """Démarre une démo de projet"""
    if slug not in DEMO_PROJECTS:
        return jsonify({"error": "Projet démo non disponible", "available": list(DEMO_PROJECTS.keys())}), 404
    
    project = DEMO_PROJECTS[slug]
    
    # Vérifier si déjà en cours
    if slug in demo_processes and demo_processes[slug].poll() is None:
        return jsonify({
            "success": True, 
            "message": "Démo déjà en cours",
            "url": f"http://localhost:{project['port']}"
        })
    
    try:
        # Construire la commande avec le venv
        venv_python = os.path.join(project['path'], project['venv'], 'bin', 'python')
        app_file = os.path.join(project['path'], 'app.py')
        
        # Lancer le processus
        env = os.environ.copy()
        process = subprocess.Popen(
            [venv_python, app_file],
            cwd=project['path'],
            env=env,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE
        )
        
        demo_processes[slug] = process
        
        return jsonify({
            "success": True,
            "message": f"Démo {slug} lancée",
            "url": f"http://localhost:{project['port']}",
            "pid": process.pid
        })
    except Exception as e:
        return jsonify({"error": str(e)}), 500

@app.route('/api/demo/stop/<slug>', methods=['POST'])
def stop_demo(slug):
    """Arrête une démo de projet"""
    if slug not in demo_processes:
        return jsonify({"error": "Aucune démo en cours pour ce projet"}), 404
    
    process = demo_processes[slug]
    if process.poll() is None:
        process.terminate()
        try:
            process.wait(timeout=5)
        except subprocess.TimeoutExpired:
            process.kill()
    
    del demo_processes[slug]
    return jsonify({"success": True, "message": f"Démo {slug} arrêtée"})

@app.route('/api/demo/status/<slug>')
def demo_status(slug):
    """Vérifie le statut d'une démo"""
    if slug not in DEMO_PROJECTS:
        return jsonify({"available": False, "running": False})
    
    project = DEMO_PROJECTS[slug]
    running = slug in demo_processes and demo_processes[slug].poll() is None
    
    return jsonify({
        "available": True,
        "running": running,
        "port": project['port'],
        "url": f"http://localhost:{project['port']}" if running else None
    })

@app.route('/api/demo/list')
def list_demos():
    """Liste toutes les démos disponibles"""
    demos = []
    for slug, project in DEMO_PROJECTS.items():
        running = slug in demo_processes and demo_processes[slug].poll() is None
        demos.append({
            "slug": slug,
            "port": project['port'],
            "running": running,
            "url": f"http://localhost:{project['port']}" if running else None,
            "type": "web"
        })
    # Ajouter les projets terminal
    for slug, project in TERMINAL_PROJECTS.items():
        demos.append({
            "slug": slug,
            "description": project['description'],
            "type": "terminal"
        })
    return jsonify(demos)

# ==================== ROUTES TERMINAL WEBSOCKET ====================

@app.route('/api/terminal/projects')
def list_terminal_projects():
    """Liste les projets disponibles en démo terminal"""
    projects = []
    for slug, config in TERMINAL_PROJECTS.items():
        projects.append({
            "slug": slug,
            "description": config['description'],
            "path": config['path']
        })
    return jsonify(projects)

@app.route('/api/terminal/compile/<slug>', methods=['POST'])
def compile_project(slug):
    """Compile un projet avant de lancer le terminal"""
    if slug not in TERMINAL_PROJECTS:
        return jsonify({"error": "Projet non trouvé"}), 404
    
    project = TERMINAL_PROJECTS[slug]
    
    try:
        result = subprocess.run(
            project['compile_cmd'],
            shell=True,
            cwd=project['path'],
            capture_output=True,
            text=True,
            timeout=30
        )
        
        if result.returncode == 0:
            return jsonify({
                "success": True,
                "message": "Compilation réussie",
                "output": result.stdout
            })
        else:
            return jsonify({
                "success": False,
                "message": "Erreur de compilation",
                "output": result.stderr or result.stdout
            }), 400
    except subprocess.TimeoutExpired:
        return jsonify({"error": "Timeout de compilation"}), 500
    except Exception as e:
        return jsonify({"error": str(e)}), 500

@sock.route('/ws/terminal/<slug>')
def terminal_websocket(ws, slug):
    """WebSocket pour terminal interactif avec pexpect"""
    if slug not in TERMINAL_PROJECTS:
        ws.send(f"\r\n\x1b[31mErreur: Projet '{slug}' non trouvé\x1b[0m\r\n")
        return
    
    project = TERMINAL_PROJECTS[slug]
    
    # Compiler d'abord
    ws.send(f"\x1b[33m🔨 Compilation du projet {slug}...\x1b[0m\r\n")
    
    try:
        compile_result = subprocess.run(
            project['compile_cmd'],
            shell=True,
            cwd=project['path'],
            capture_output=True,
            text=True,
            timeout=30
        )
        
        if compile_result.returncode != 0:
            ws.send(f"\x1b[31m❌ Erreur de compilation:\x1b[0m\r\n{compile_result.stderr or compile_result.stdout}\r\n")
            return
        
        ws.send(f"\x1b[32m✓ Compilation réussie!\x1b[0m\r\n")
        ws.send(f"\x1b[33m🚀 Lancement de {project['run_cmd']}...\x1b[0m\r\n\r\n")
        
    except Exception as e:
        ws.send(f"\x1b[31m❌ Erreur: {str(e)}\x1b[0m\r\n")
        return
    
    child = None
    stop_reading = threading.Event()
    ws_closed = threading.Event()
    
    try:
        # Construire le chemin absolu de l'exécutable
        run_cmd = project['run_cmd']
        if run_cmd.startswith('./'):
            run_cmd = os.path.join(project['path'], run_cmd[2:])
        
        print(f"[DEBUG] Lancement de: {run_cmd}")
        
        # Utiliser stdbuf pour désactiver le buffering ou script pour un pseudo-terminal
        # Lancer le processus avec pexpect
        child = pexpect.spawn(
            'stdbuf', ['-o0', '-e0', run_cmd],
            cwd=project['path'],
            encoding='utf-8',
            timeout=None,
            echo=False,
            env={**os.environ, 'TERM': 'xterm-256color'}
        )
        child.setwinsize(30, 100)
        
        # Thread pour lire la sortie du processus
        def read_output():
            try:
                while not stop_reading.is_set() and not ws_closed.is_set():
                    if not child.isalive():
                        # Lire les données restantes
                        try:
                            remaining = child.read()
                            if remaining:
                                ws.send(remaining)
                        except:
                            pass
                        break
                    
                    try:
                        data = child.read_nonblocking(size=1024, timeout=0.2)
                        if data:
                            ws.send(data)
                    except pexpect.TIMEOUT:
                        continue
                    except pexpect.EOF:
                        print("[DEBUG] EOF reçu")
                        break
                    except Exception as e:
                        print(f"[DEBUG] Erreur lecture: {e}")
                        if stop_reading.is_set() or ws_closed.is_set():
                            break
                        continue
            except Exception as e:
                print(f"[DEBUG] Thread error: {e}")
            finally:
                if not stop_reading.is_set() and not ws_closed.is_set():
                    try:
                        exitcode = child.exitstatus if child.exitstatus is not None else "?"
                        ws.send(f"\r\n\x1b[33m--- Programme terminé (code: {exitcode}) ---\x1b[0m\r\n")
                    except:
                        pass
        
        output_thread = threading.Thread(target=read_output)
        output_thread.daemon = True
        output_thread.start()
        
        # Recevoir les entrées du WebSocket (bloquant, sans timeout)
        while True:
            try:
                # ws.receive() bloque jusqu'à réception de données
                data = ws.receive()
                
                if data is None:
                    print("[DEBUG] WebSocket fermé par le client")
                    break
                
                # Envoyer l'entrée au processus
                if child.isalive():
                    child.send(data)
                else:
                    print("[DEBUG] Processus terminé, fermeture")
                    break
                    
            except Exception as e:
                print(f"[DEBUG] Exception ws.receive: {e}")
                break
        
    except Exception as e:
        print(f"[DEBUG] Exception principale: {e}")
        try:
            ws.send(f"\x1b[31m❌ Erreur: {str(e)}\x1b[0m\r\n")
        except:
            pass
    finally:
        print("[DEBUG] Nettoyage...")
        ws_closed.set()
        stop_reading.set()
        if child and child.isalive():
            try:
                child.terminate(force=True)
            except:
                pass

if __name__ == '__main__':
    app.run(debug=True, port=5001)
