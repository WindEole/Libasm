; -------------------------------------------------------- ;
; prototype = char *ft_strcpy(char *dest, const char *src) ;
; -------------------------------------------------------- ;
; La  fonction  strcpy()  copie  la  chaîne pointée par src, y compris le
; caractère nul (« \0 ») final dans la chaîne pointée par dest. Les  deux
; chaînes  ne  doivent  pas se chevaucher. La chaîne dest doit être assez
; grande pour accueillir la copie.

section .text		; le code devra être placé dans la section .text
global ft_strcpy	; expose la fct ft_strcpy pour qu'elle puisse être appelée depuis d'autres parties du programme 

ft_strcpy:
	; Documentation : 
	; Cette fonction attend deux argument (chaines de caractères)
	; en convention d'appel x86-64, le 1er argument est passé dans le registre RDI (ce sera donc dest) RDI = Destination Index...
	; on va stocker le 2eme argument dans le registre RSI (ce sera src) RSI = Source Index... 
	; principe : on va prendre un caractère de la chaîne RSI, le mettre dans le registre al (le plus petit)
	; et, s'il n'est pas nul (\0), le mettre dans la chaîne RDI

	test 	rsi, rsi 		; on verifie si le pointeur source est null.
	je 		.null_ptr		; si src null on return. 
	test 	rdi, rdi 		; on verifie si le pointeur dest est null
	je		.null_ptr 		; si dest null on return. 
	mov		rax, rdi 		; on met le pointeur de destination dans rax

.copy_loop:
	mov		r8b, [rsi]		; charge l'octet depuis la src dans r8b
	test 	r8b, r8b		; vérifie si l'octet est nul (fin de chaîne)
	jz		.end			; si nul, terminer la copie
	mov		[rdi], r8b 		; copie l'octet dans la dest

	inc 	rsi 			; déplace le pointeur source au prochain octet
	inc 	rdi 			; déplace le pointeur dest au prochain octet
	jmp		.copy_loop		; boucle pour le prochain caractère (octet)

.null_ptr:
	ret

.end: 
	mov		byte [rdi], 0 	; ajoute le zéro de terminaison à la dest
	ret 					; retourne rax qui contient le ptr de destination RDI

