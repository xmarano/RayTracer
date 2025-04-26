![unitest](https://github.com/EpitechPromo2028/B-OOP-400-MAR-4-1-raytracer-selim.bouasker/actions/workflows/unitest.yml/badge.svg)
![criterion](https://github.com/EpitechPromo2028/B-OOP-400-MAR-4-1-raytracer-selim.bouasker/actions/workflows/unitest-criterion.yml/badge.svg)

# Raytracer – Checklist des fonctionnalités

## Fonctionnalités Obligatoires (Must)

- ✅ **Sphere** – La primitive sphère est implémentée et gérée correctement (classe `Sphere` avec intersection `hits` fonctionnelle).
- ✅ **Plane** – La primitive plan est implémentée (classe `Plane` avec méthode d’intersection opérationnelle).
- ✅ **Transformation – Translation** – Les objets peuvent être translatés (méthode `translate` définie dans `IPrimitive` et implémentée dans chaque primitive).
- ✅ **Lumière directionnelle** – La lumière directionnelle est présente (`DirectionalLight` avec intensité appliquée sur la couleur de base).
- ✅ **Lumière ambiante** – La lumière ambiante est gérée (`AmbientLight` fournit une illumination uniforme sur les objets).
- ✅ **Matériau couleur unie (FlatColor)** – Le matériau à couleur plate est implémenté (`FlatColor` retourne bien une couleur de base pour l’objet).
- ❌ **Configuration de la scène – Ajout des primitives** – Le chargement des primitives depuis le fichier `.cfg` n’est pas pleinement intégré (les objets ne sont ajoutés à la scène que partiellement/manuellement au lieu d’être créés dynamiquement depuis la config).
- ❌ **Configuration de la scène – Paramétrage des lumières** – Les lumières définies dans le fichier de config (ex. point light) ne sont pas toutes prises en compte (le code utilise des valeurs codées en dur pour l’ambiant et la directionnelle, et ignore les éventuelles lumières point dans le fichier).
- ✅ **Configuration de la scène – Caméra** – La caméra est configurée à partir du fichier (position, résolution et FOV sont bien utilisés pour initialiser la caméra de la scène, bien que l’orientation ne soit pas pleinement exploitée).
- ❌ **Interface – Sortie PPM sans GUI** – Le programme n’écrit pas directement une image PPM en sortie standard (il ouvre une fenêtre SFML pour afficher le rendu au lieu de produire uniquement un fichier PPM comme requis).

## Fonctionnalités Recommandées (Should)

- ✅ **Cylinder** – La primitive cylindre est implémentée (classe `Cylinder` avec calcul d’intersection, y compris une hauteur limitée).
- ✅ **Cone** – La primitive cône est implémentée (classe `Cone` avec calcul d’intersection, utilisant hauteur et rayon pour définir l’ouverture).
- ❌ **Transformation – Rotation** – Aucune rotation d’objet n’est gérée (pas de méthode pour appliquer une rotation aux primitives ou aux rayons de la caméra, la scène ne tient pas compte d’une orientation des objets).
- ❌ **Ombres portées (Drop shadows)** – Les ombres ne sont pas calculées (le moteur d’illumination ne teste pas l’occlusion des objets entre la source lumineuse et le point d’impact, donc pas d’ombres projetées).

## Fonctionnalités Optionnelles (Could)

- ✅ **Limited cylinder** – Les cylindres sont limités en hauteur (la classe `Cylinder` utilise un paramètre de hauteur pour restreindre l’intersection, fonction bonus implémentée).
- ✅ **Limited cone** – Les cônes sont limités en hauteur (la classe `Cone` prend en compte une hauteur finie pour limiter l’objet, implémentation bonus).
- ❌ **Torus** – Tore non implémenté.
- ❌ **Tanglecube** – Tanglecube non implémenté.
- ❌ **Triangles** – Primitives triangles non implémentées.
- ❌ **Fichier .OBJ** – Chargement de modèles `.obj` non supporté.
- ❌ **Fractals** – Fractales non implémentées.
- ❌ **Möbius strip** – Ruban de Möbius non implémenté.
- ❌ **Transformation – Scale** – Pas de mise à l’échelle des objets.
- ❌ **Transformation – Shear** – Pas de transformation de cisaillement.
- ❌ **Transformation – Matrice de transformation** – Pas de gestion générique de matrice de transformation.
- ❌ **Scene graph** – Pas de graphe de scène hiérarchique implémenté.
- ✅ **Multiple directional lights** – Support présent pour plusieurs lumières directionnelles (la scène peut contenir une liste de lumières et les contributions sont additionnées).
- ❌ **Multiple point lights** – Pas de support de lumières point multiples (aucune classe `PointLight` n’existe, les lumières point de la config sont ignorées).
- ❌ **Colored light** – Pas de couleur spécifique pour les lumières (les sources agissent uniquement via une intensité, sans teinte).
- ❌ **Modèle d’illumination de Phong** – Modèle de Phong non implémenté (pas de composantes spéculaires/réflexions calculées, juste couleur diffuse plate).
- ❌ **Ambient occlusion** – Occlusion ambiante non prise en charge.
- ❌ **Transparency** – Transparence des objets non gérée.
- ❌ **Refraction** – Réfraction non gérée.

## Analyse de l’Architecture

- ✅ **Interfaces pour objets et lumières** – Les interfaces obligatoires `IPrimitive` et `ILight` sont bien présentes et utilisées, ce qui assure un contrat commun pour toutes les primitives et sources de lumière.
- ❌ **Utilisation de design patterns (Factory, Builder, etc.)** – Peu ou pas de design patterns identifiables dans l’implémentation (par exemple, pas de Factory claire pour créer les objets depuis le fichier de config, ni d’autres patterns comme Observer ou State), là où au moins deux étaient attendus.
- ✅ **Organisation du code (modularité et extensibilité)** – Le projet est globalement bien structuré en modules (fichiers séparés par classe, usage d’espaces de noms, abstractions `IMaterial`/`IPrimitive` qui facilitent l’ajout de nouvelles formes ou matériaux). Cependant, l’intégration entre le parseur de config et la construction de la scène pourrait être améliorée pour une meilleure extensibilité (actuellement quelques valeurs sont en dur au lieu d’être dérivées de la config).
