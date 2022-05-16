## BE-CHTI - Binôme : Hasson Hugo & Mousset Sarah
Partie ASM du BE CHTI

# Projet
Dans une première partie, nous avons conçu l'électronique nécessaire pour traiter la réception d'un signal émis par un pistolet laser sur une cible.
Dans cette seoconde partie, nous avons analysé ce signal reçu pour distinguer les différents pistolets (donc joueurs), puis nous avons pu créer le jeu lui-même en assembleur.

# Jeu
Une des cibles, de manière aléatoire, s'active et la LED associée s'allume pour l'indiquer. Dès qu'un joueur touche la cible, il gagne 1 ou 2 points selon la difficulté 
(et donc la taille de la cible), et un son est émis. La nouvelle cible active est de nouveau choisie de manière aléatoire (mais différente de la précédente),
et le jeu continue ainsi.

# Remarques sur nos tests
Nous eu accès à la malette lors du petit oral du BE pour tester nos affichages, utilisations des LEDs et seuil de détection du signal, seul le son n'a pas été testé. 
Pour nos tests avec la photodiode, nous avons remarqué que nous obtenions souvent 12 ou 14 points avec un seul tir. Cela est dû aux salves du laser, détectées plusieurs fois et donc traîtées comme plusieurs tirs. Ce problème est réglé lorsqu'on utilise la malette, puisque nous n'affectons qu'une seule fois les points avant de changer de cible.

# Petit mot de la fin
Merci M. Le Botlan d'être un si bon encadrant de TP. On aurait aimé vous avoir dans tous nos autres projets ! On espère que vous passerez de bonnes vacances et qu'on 
vous retrouvera l'année prochaine :D
