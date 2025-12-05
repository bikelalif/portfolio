#!/bin/bash

# Script pour pousser les projets sur GitHub
# Usage: ./push_to_github.sh <github_username>

USERNAME=${1:-"bilalkefif"}

echo "🚀 Push des projets sur GitHub pour $USERNAME"
echo "=============================================="

# Fonction pour initialiser et pousser un repo
push_project() {
    local dir=$1
    local repo_name=$2
    local description=$3
    
    echo ""
    echo "📁 Traitement de $repo_name..."
    cd "$dir"
    
    # Init git si nécessaire
    if [ ! -d ".git" ]; then
        git init
        echo "   ✓ Git initialisé"
    fi
    
    # Add et commit
    git add .
    git commit -m "Initial commit - $description" 2>/dev/null || echo "   (rien à commiter)"
    
    # Ajouter remote si pas présent
    if ! git remote | grep -q origin; then
        git remote add origin "https://github.com/$USERNAME/$repo_name.git"
        echo "   ✓ Remote ajouté: github.com/$USERNAME/$repo_name"
    fi
    
    echo "   → Pour pousser: cd $dir && git push -u origin main"
}

# Portfolio principal
push_project "/home/bilal/portfolio" "portfolio" "Portfolio personnel - React + Flask"

# SEvent
push_project "/home/bilal/portfolio/projets/sevent-gestion-evenements" "sevent-gestion-evenements" "Application de gestion d'événements - Flask"

# PharmaPlan
push_project "/home/bilal/portfolio/projets/pharmaplan-gestion-planning" "pharmaplan-gestion-planning" "Application de gestion de planning pharmacie - PyQt5"

# Jeu de cartes C
push_project "/home/bilal/portfolio/projets/jeu-de-cartes-c" "jeu-de-cartes-c" "Jeu de cartes en C - Bataille et Blackjack"

# Bilocal
push_project "/home/bilal/portfolio/projets/bilocal-gestion-bureaux" "bilocal-gestion-bureaux" "Application de gestion de bureaux - Django"

echo ""
echo "=============================================="
echo "✅ Projets préparés!"
echo ""
echo "📝 Étapes suivantes:"
echo "1. Créer les repos sur GitHub (github.com/new)"
echo "2. Exécuter pour chaque projet:"
echo "   git push -u origin main"
echo ""
echo "Ou utilise GitHub CLI (gh):"
echo "   gh repo create <nom-repo> --public --source=. --push"
