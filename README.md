Valentin RENAUD / Aziz BENJEBALIA 

----------------------------------------------------------------------------------------------------------------------------------------------
PROJET SON 3TC - VOICE EXTRACTOR
----------------------------------------------------------------------------------------------------------------------------------------------

--	LIBRAIRIE MYDSP	--

Cette librairie a été générée après avoir appliqué le programme Faust suivant : 

import("stdfaust.lib");
music = _;
s = hslider("Audio",0.5,0,1,0.1);
v = hslider("FullAudio",0.5,0,1,0.1);
m = button("ApplyMono");
process = music*v - music*s*m <: _,_ ;

Cette librairie propose plusieurs fonctions mais il n'y en a une seule qui va être utilisée dans le programme principal et c'est la fonction setParamValue. C'est elle qui va permettre de définir les valeur de Audio, FullAudio et ApplyMono. Lorsque ces 3 valeurs seront connues, l'opération effectuée dans process pourra être réalisée afin d'obtenir une piste audio exclusivement instrumentale.


-- PROGRAMME PRINCIPAL	-- 

En premier lieu, 4 AudioConnection sont créés. Les 2 premiers permettent de faire le lien entre les fichiers WAV présent dans la carte SD et la librairie MyDsp, les 2 autres relient la sortie la librairie MyDsp à la prise jack.

La première fonction est indispensable puisqu'il s'agit de la fonction setup(), elle permet ici :
- l'initialisation la liaison série pour les échanges de données avec l'ordinateur ;
- allouer la mémoire nécessaire pour les connexions audio ;
- l'initialisation de l'audioshield ainsi que le réglage initial du volume sortant de la prise jack ;
- la déclaration du pin 4 comme étant en mode INPUT ;
- l'initialisation de la carte SD ainsi que la vérification de l'existence de potentiels fichiers.

La fonction playMusic() qui suit donne l'ordre à la carte de lire un fichier WAV et fait également appel à la fonction update() lorsqu'un fichier WAV est lu.

La fonction update(), elle, effectue plusieurs tâches notamment :
- l'affectation de la valeur du pin A1 (ici un potentiomètre) à Audio et FullAudio ce qui est logique puisqu'elles doivent avoir la même piste ;
- l'affectation de la valeur du pin 4 (donc 0 ou 1 car bouton) à ApplyMono.

La fonction loop() fait juste appel à la fonction playMusic.
	
