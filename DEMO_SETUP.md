# Démo Interactive - SEvent

## Configuration

Pour utiliser la démo interactive de SEvent directement depuis le portfolio :

### Option 1 : Hébergement complet (recommandé pour production)

Hébergez SEvent séparément sur un service comme :
- Render (https://render.com) - Gratuit pour projets Flask
- Railway (https://railway.app)
- Heroku
- PythonAnywhere

Puis mettez à jour l'URL dans `src/components/SeventDemo.tsx` pour pointer vers votre instance hébergée.

### Option 2 : Démo locale avec contrôleur (développement)

1. **Installer les dépendances du contrôleur** :
   ```bash
   cd app/backend
   pip install flask flask-cors psutil
   ```

2. **Installer les dépendances de SEvent** :
   ```bash
   cd projets/sevent-gestion-evenements
   pip install -r requirements.txt
   ```

3. **Modifier le port de SEvent** :
   Dans `projets/sevent-gestion-evenements/app.py`, changez le port :
   ```python
   if __name__ == '__main__':
       app.run(host='0.0.0.0', port=5001, debug=True)  # Port 5001 au lieu de 5000
   ```

4. **Démarrer le contrôleur** :
   ```bash
   cd app/backend
   python demo_controller.py
   ```

5. **Accéder au portfolio** :
   - Ouvrez http://localhost:5000
   - Naviguez vers la page de démo SEvent
   - Cliquez sur "Lancer la démo"

### Option 3 : Version simplifiée (sans backend)

Si vous ne voulez pas de démo interactive, modifiez simplement `src/components/Portfolio.tsx` :

```typescript
{
  slug: "sevent-gestion-evenements",
  title: "SEvent - Gestion d'Événements",
  // ...
  demoUrl: null,  // Désactiver la démo
  demoInfo: "Voir sur GitHub"
}
```

## Lien direct en anglais

Pour partager un lien qui ouvre directement le site en anglais :
```
https://portfoliobilalkefif.netlify.app?lang=en
```

Pour français :
```
https://portfoliobilalkefif.netlify.app?lang=fr
```

## Notes

- La démo locale nécessite que Python et Flask soient installés
- Le contrôleur démarre/arrête automatiquement l'application SEvent
- Pour une utilisation en production, il est préférable d'héberger SEvent séparément
