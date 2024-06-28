; ---------------------------------------------------------------- ;
; prototype = int ft_strcmp(const char *first, const char *second) ;
; ---------------------------------------------------------------- ;
; comparer deux chaînes de caractères et de savoir si la première est inférieure, égale ou supérieure
; à la seconde. Cette comparaison sera réalisée en utilisant l'ordre lexicographique et donc, en tenant
; compte des valeurs numérique des codes ASCII des différents caractères comparés. 
; RETURN VALUE : 0 si les chaines sont égales, int negatif si chaine 1 < 2, int positif si chaine 1 > 2

section .text		; le code devra être placé dans la section .text

global ft_strcmp	; expose la fct ft_strcmp pour qu'elle puisse être appelée depuis d'autres parties du programme 

ft_strcmp:
	; Documentation : 
	; Cette fonction attend deux arguments (chaines de caractères)
	; en convention d'appel x86-64, le 1er argument est passé dans le registre rdi : chaine first
	; en convention d'appel x86-64, le 2eme argument est passé dans le registre rsi : chaine second
	; principe : on va mettre 1 caractère de second dans registre r8b, et comparer avec le caractère de first
	; dès que les caractères sont inégaux -> on retourne int neg ou pos.

	; 1/ on initialise les registres utiles à 0 en effectuant un XOR sur lui-même

	xor 	rax, rax	; registre de retour
	xor 	r8, r8
	xor 	rcx, rcx	; c'est le registre de compteur

	; 2/ on lance la boucle de comparaison / comptage

.loop
	mov		al, byte [rdi + rcx]	; charge 1 octet de rdi(first) dans al (futur rax !)
	mov		r8b, byte [rsi + rcx]	; charge 1 octet de rsi(second) dans r8b

	cmp 	al, 0 					; on compare 0 à l'octet al
	je 		.end 					; si c'est egal, go end

	cmp 	r8b, 0 					; on compare 0 à l'octet r8b
	je 		.end 					; si c'est egal, go end

	cmp 	al, r8b 				; on compare l'octet r8b a l'octet al
	jne 	.end 					; si c'est différent, go end

	inc 	rcx 					; incrémente le registre compteur
	jmp 	.loop 					; boucle pour le caractère suivant

.end:
	; 3/ on move les petits registres vers les grands avec movzx, pour récupérer le signe, et on soustrait les valeurs
	movzx 	rax, al 				; on move al dans rax (movzx copie un registre de taille inférieure dans un registre de plus grande taille)
	movzx 	rbx, r8b 				; on move r8b dans rbx
	sub 	rax, rbx 				; on soustrait rbx à rax, resultat dans rax
	ret