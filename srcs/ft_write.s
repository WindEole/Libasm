; ---------------------------------------------------------------- ;
; prototype = ssize_t write(int fd, const void *buf, size_t count) ;
; ---------------------------------------------------------------- ;
; lit au maximum count octets dans la zone mémoire pointée par buf,
; et les écrit dans le fichier référencé par le descripteur fd.
; le nb d'octets écrits peut être inférieur à count si buf trop petit
; ou RLIMIT_SIZE atteinte
; valeur de retour -> nb d'octets écrits (0 = pas écriture / -1 = échec)
; maj errno : si retour = -1 | si count = 0 et fd normal -> codes d'erreur

; pour récupérer errno -> system call !!
; For that, you are allowed to call the extern ___error or __errno_location

; man 2 write : la section 2 du man est consacrée aux appels système. 
; donc on doit faire un appel système !


global ft_write				; expose la fct ft_write pour qu'elle puisse être appelée depuis d'autres parties du programme 
extern __errno_location		; on référence la variable errno_location prédéfinie

ft_write:
	; 1/ les arguments sont rangés par défaut dans RDI (destination fd) / RSI (source buf) / RCX (count)
	; 2/ on range le numéro d'appel système dans rax (write = 1)
	mov		rax, 1 			; on met 1 (nb du syscall write dans le kernel linux) dans rax
	syscall 				; cela effectue l'appel system désigné dans rax et si échec, met automatiquement à jour errno !
	cmp 	rax, 0 			; on compare le contenu de rax à 0
	jl		.error 			; saut conditionnel : si rax < 0 -> pb
	ret 					; on retourne le contenu de rax

.error:
	neg		rax					; rax s'est vu attribuer un signe negatif (car echec du syscall) et une valeur d'erreur. On veut la valeur d'erreur pour la mettre dans errno.
	mov 	r15, rax			; on sauvegarde la valeur de rax dans r15 (car rax va être écrasé par call)
	call 	__errno_location	; on récupère L'ADRESSE d'errno, qui va se placer dans rax
	mov		[rax], r15 			; [rax] -> on met la VALEUR de r15 à L'ADRESSE pointée par rax !!! donc ici : maj de errno_location
	mov		rax, -1 			; on met rax à -1 pour afficher au final une erreur standard de retour de write
	ret