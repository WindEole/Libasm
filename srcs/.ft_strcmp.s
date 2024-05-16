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

	;xor		r8b, r8b
	;xor 	r9b, r9b
	;xor 	r8, r8
	;xor 	r9, r9
	xor 	rax, rax
	xor 	r9, r9
	xor 	rcx, rcx	; c'est le registre de compteur
	mov		rax, 0		; registre de retour

	; 2/ on lance la boucle de comparaison / comptage

	.loop:
	;	mov		r8b, byte [rdi + rcx]	; charge 1 octet de rdi(first) dans r8b
	;	test 	r8b, r8b 				; verifie si l'octet est nul
	;	jz		.end					; si nul, on termine.

		mov		al, byte [rdi + rcx]
		test	al, al
		jz		.end

		mov		r9b, byte [rsi + rcx]	; charge 1 octet de rdi(second) dans r9b
		test 	r9b, r9b 				; verifie si l'octet est nul
		jz		.end					; si nul, on termine.

		cmp 	al, r9b				; soustrait r9b de al
		;jne		.inequal				; si les caractères ne sont pas égaux -> on voit qui est + gd ou + pt
		jne		.end

		inc 	rcx 					; incrémente le registre compteur
		jmp 	.loop 					; boucle pour le caractère suivant

	; 3/ fin de la fonction : on retourne le contenu du registre rax

	;.inequal:
	;	cmp 	r8b, r9b				; soustrait r9b de r8b
	;	jg		.superior
	;	jmp		.inferior

	;.superior:
	;	mov			al, byte [rdi + rcx]
	;	sub			al, byte [rsi + rcx]
	;	ret

	;.inferior:
	;	mov			al, byte [rsi + rcx]
	;	sub			al, byte [rdi + rcx]
	;	mov			r8, 0
	;	sub			r8, rax
	;	mov 		rax, r8
	;	ret

	;.inequal:
	;	mov		al, byte [rdi + rcx]
	;	sub		al, byte [rsi + rcx]
	;	mov		r8, 0
	;	sub		r8, rax
	;	mov		rax, r8
	;	ret

	.end:
	;	mov		al, 0
		sub		rax, r9
		ret

