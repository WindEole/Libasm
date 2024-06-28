; ------------------------------------------- ;
; prototype = size_t ft_strlen(const char *s) ;
; ------------------------------------------- ;
; la fct strlen() renvoie le nb de caractères dans la chaîne s (sans compter le \0 final)

section .text		; le code devra être placé dans la section .text

global ft_strlen	; expose la fct ft_strlen pour qu'elle puisse être appelée depuis d'autres parties du programme 

ft_strlen:
	; Documentation : 
	; Cette fonction n'attend qu'un seul argument (chaine de caractères)
	; en convention d'appel x86-64, le 1er argument est passé dans le registre rdi
	; le registre rax va servir à stocker la longueur de la chaine.
	; en convention d'appel x86-64, la valeur retournée par une fct est stockée dans le registre rax

	; 1/ on vérifie si l'argument envoyé est un pointeur NULL

	; test	rdi, rdi	; teste si rdi est NULL
	; je	.end		; si le rdi est NULL -> terminer

	; 2/ on initialise le registre rax à 0 en effectuant un XOR (exclusif) entre rax et lui-même

	xor		rax, rax

	; 3/ on lance la boucle de comparaison / comptage

.loop:
	cmp 	byte [rdi + rax], 0		; compare le caractère actuel avec NULL (pointeur vers rdi + longueur rax)
	je		.end					; si le caractère est NULL -> terminer
	inc		rax 					; si le caractère n'est pas NULL -> incrémenter la longueur dans rax
	jmp 	.loop 					; boucle pour le caractère suivant

	; 4/ fin de la fonction : on retourne la longueur contenue dans le registre rax

.end:
	ret 							; retourne la longueur dans rax (convention de retour)