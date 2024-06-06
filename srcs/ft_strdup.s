; ------------------------------------------ ;
; prototype = char *ft_strdup(const char *s) ;
; ------------------------------------------ ;
; La fonction strdup() renvoie un pointeur sur une nouvelle chaîne de caractères
; qui est dupliquée depuis s. La mémoire occupée par cette nouvelle chaîne est
; obtenue en appelant malloc(3), et doit donc être libérée avec free(3).

; valeur de retour : renvoie un pointeur sur la chaîne dupliquée, ou NULL s'il n'y a pas assez de mémoire.
; màj errno !

; consigne : on peut call malloc !

section .text			; le code devra être placé dans la section .text
global ft_strdup		; expose la fct ft_strdup pour qu'elle puisse être appelée depuis d'autres parties du programme 
extern ft_strlen		; on référence les fct prédéfinies dont on a besoin
extern malloc
extern ft_strcpy

ft_strdup:
	; Documentation : 
	; Cette fonction attend un argument (chaine de caractères)
	; en convention d'appel x86-64, le 1er argument est passé dans le registre RDI

	; 1/ on veut la taille de notre chaine source, on incrémente sa taille de 1
	mov		r8, rdi 		; on met le pointeur de destination dans r9 (sauvegarde)
	call	ft_strlen		; on veut la taille de notre chaine (elle est dans rdi, son résultat sera dans rax)
	mov		rdi, rax		; maintenant rdi contient la longueur de la chaine s
	inc 	rdi 			; on incrémente avant allocation mémoire (pour le \0 terminal)

	; 2/ on malloc la taille de notre chaine + 1
	push	r8				; selon x86 calling convention, le registre n'est pas protégé, sa valeur n'est pas fiable après un call, donc on force sa sauvegarde
	call 	malloc			; malloc est appelé sur rdi, son résultat est dans rax
	cmp 	rax, 0 			; check si malloc a bien fonctionné (echec = NULL et pas de maj errno !)
	je		.null_ptr		; on s'arrête là si malloc échoue !
	pop 	r8				; on restaure le registre après le call

	; 3/ malloc ok -> on fait la copie !
	mov		rsi, r8 		; on met le pointeur source sauvegardé dans rsi
	mov 	rdi, rax		; on met le pointeur retour de malloc dans rdi
	call	ft_strcpy		; on copie rsi dans rdi. Pas de maj errno. Dans rax : ptr sur la chaine copiée
	ret

.null_ptr:
	ret
