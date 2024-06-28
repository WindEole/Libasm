#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define GREY "\033[1;37m"
# define ORANGE "\033[38;2;255;165;0m"
# define RESET "\033[0m"


size_t		ft_strlen(char *str);
char		*ft_strcpy(char *dest, const char *src);
int			ft_strcmp(const char *first, const char *second);
ssize_t		ft_write(int fd, const void *buf, size_t count);
ssize_t		ft_read(int fd, void *buf, size_t count);
char 		*ft_strdup(const char *s);

void test_strdup(void)
{
	printf(ORANGE "=====================================================================\n");
	printf("=   Test de strdup :   =\n");
	printf("=====================================================================\n\n" RESET);

	char *src[] = {
		"",									// Chaîne vide
		"Ceci est une chaîne normale\n",	// Chaînes normales
		"Chaîne longue : aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n",		// Chaînes différente
		NULL								// Fin du tableau
	};

	char *test_title[] = {
		"On duplique une chaîne vide\n",
		"On duplique une chaîne normale\n",
		"On duplique une longue chaîne\n",
		NULL
	};

	char *ft_dest;
	char *std_dest;

	for (int i = 0; src[i] != NULL; i++)
	{
		printf(PURPLE "%s" RESET, test_title[i]);
		printf("Adresse de la chaîne source : %p\n", (void *)src[i]);
		ft_dest = ft_strdup(src[i]);
		if (ft_dest == NULL) {
			perror("malloc");
			return;
		}

		std_dest = strdup(src[i]);
		if (std_dest == NULL) {
			perror("malloc");
			free(ft_dest);
			return;
		}

		printf("Adresse de la chaîne destination (ft_strdup) : %p\n", (void *)ft_dest);
		printf("Adresse de la chaîne destination (strdup standard) : %p\n\n", (void *)std_dest);
		printf("ft_strdup : 		Destination = %s\n", ft_dest);
		printf("strdup standard :	Destination = %s", std_dest);
		if (strcmp(ft_dest, std_dest) == 0)
			printf(GREEN " |--> YOUPI C'EST BON !\n\n" RESET);
		else
			printf(RED " |--> HOUSTON, ON A UN PROBLEME...\n\n" RESET);
	}
	free(ft_dest);
	free(std_dest);
}

void test_read(void)
{
	printf(ORANGE "=====================================================================\n");
	printf("=   Test de read :   =\n");
	printf("=====================================================================\n\n" RESET);

	char buffer[100];
	int ft_res;
	int std_res;

	// Test lecture depuis stdin (utilisateur doit taper quelque chose) -------
	printf(PURPLE "Lecture depuis stdin (tapez quelque chose et appuyez sur Entrée) :\n\n" RESET);
	write(1, RESET, strlen(RESET)); // sinon write écrit en purple...

	errno = 0;
	ft_res = ft_read(0, buffer, 99);
	buffer[ft_res] = '\0'; // Ajouter un nul terminator à la fin de la chaîne
	int ft_errno = errno;
	printf("ft_read :	Return = %d, errno = %d, buffer = %s\n", ft_res, ft_errno, buffer);

	errno = 0;
	std_res = read(0, buffer, 99);
	buffer[std_res] = '\0';
	int std_errno = errno;
	printf("read standard :	Return = %d, errno = %d, buffer = %s\n", std_res, std_errno, buffer);

	if (ft_res == std_res && ft_errno == std_errno)
		printf(GREEN " |--> YOUPI C'EST BON !\n\n" RESET);
	else
		printf(RED " |--> HOUSTON, ON A UN PROBLEME...\n\n" RESET);

	// Test lecture depuis un fichier -----------------------------------------
	printf(PURPLE "Lecture depuis un fichier :\n\n" RESET);

	int fd = open("test_file.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Erreur lors de l'ouverture du fichier");
		return;
	}

	errno = 0;
	ft_res = ft_read(fd, buffer, 99);
	buffer[ft_res] = '\0';
	ft_errno = errno;
	printf("ft_read :	Return = %d, errno = %d, buffer = %s\n", ft_res, ft_errno, buffer);

	lseek(fd, 0, SEEK_SET); // Repositionner le descripteur de fichier au début

	errno = 0;
	std_res = read(fd, buffer, 99);
	buffer[std_res] = '\0';
	std_errno = errno;
	printf("read standard :	Return = %d, errno = %d, buffer = %s\n", std_res, std_errno, buffer);

	if (ft_res == std_res && ft_errno == std_errno)
		printf(GREEN " |--> YOUPI C'EST BON !\n\n" RESET);
	else
		printf(RED " |--> HOUSTON, ON A UN PROBLEME...\n\n" RESET);

	close(fd);

	// Test de errno en cas d'erreur (lecture depuis un fichier non valide)
	printf(PURPLE "Test de lecture depuis un fichier non valide\n\n" RESET);
	write(1, RESET, strlen(RESET));

	errno = 0;
	ft_res = ft_read(-1, buffer, 4);
	ft_errno = errno;

	errno = 0;
	std_res = read(-1, buffer, 4);
	std_errno = errno;

	printf("\nft_read :	Return = %d, errno = %d\n", ft_res, ft_errno);
	printf("read standard :	Return = %d, errno = %d", std_res, std_errno);
	if (ft_res == std_res && ft_errno == std_errno)
		printf(GREEN " |--> YOUPI C'EST BON !\n\n" RESET);
	else
		printf(RED " |--> HOUSTON, ON A UN PROBLEME...\n\n" RESET);
}

void test_write(void)
{
	printf(ORANGE "=====================================================================\n");
	printf("=   Test de write :   =\n");
	printf("=====================================================================\n\n" RESET);

	char *first[] = {
		"",									// Chaîne vide
		"Ceci est une chaîne normale\n",	// Chaînes normales
		"Chaîne longue : aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n",		// Chaînes différente
		NULL								// Fin du tableau
	};

	char *test_title[] = {
		"On écrit des chaînes vides",
		"On écrit des chaînes normales",
		"On écrit de longues chaînes",
		NULL
	};

	int ft_res;
	int std_res;
	int ft_errno;
	int std_errno;

	// Test d'écriture sur sortie std -----------------------------------------
	for (int i = 0; first[i] != NULL; i++)
	{
		printf(PURPLE "%s sur sortie standard\n\n" RESET, test_title[i]);
		write(1, RESET, strlen(RESET)); // sinon write écrit en purple... 

		errno = 0; // pour checker errno -> initialiser errno
		ft_res = ft_write(1, first[i], ft_strlen(first[i]));
		ft_errno = errno; // Sauvegarder errno après l'appel

		errno = 0; // pour checker errno -> initialiser errno
		std_res = write(1, first[i], strlen(first[i]));
		std_errno = errno; // Sauvegarder errno après l'appel

		printf("\nft_write : 		Return = %d, errno = %d\n", ft_res, ft_errno);
		printf("write standard :	Return = %d, errno = %d", std_res, std_errno);
		if (ft_res == std_res && ft_errno == std_errno)
			printf(GREEN " |--> YOUPI C'EST BON !\n\n" RESET);
		else
			printf(RED " |--> HOUSTON, ON A UN PROBLEME...\n\n" RESET);
	}

	// Test d'écriture dans un fichier ----------------------------------------
	printf(PURPLE "Ecriture sur un fichier\n\n" RESET);
	write(1, RESET, strlen(RESET)); // sinon write écrit en purple...

	int fd = open("test_file.txt", O_WRONLY);
	if (fd == -1)
	{
		perror("Erreur lors de l'ouverture du fichier");
		return;
	}

	errno = 0; // pour checker errno -> initialiser errno
	ft_res = ft_write(fd, "Il était une fois, la vie !\n", ft_strlen("Il était une fois, la vie !\n"));
	ft_errno = errno; // Sauvegarder errno après l'appel

	errno = 0; // pour checker errno -> initialiser errno
	std_res = write(fd, "Il était une fois, la vie !\n", ft_strlen("Il était une fois, la vie !\n"));
	std_errno = errno; // Sauvegarder errno après l'appel

	printf("\nft_write : 		Return = %d, errno = %d\n", ft_res, ft_errno);
	printf("write standard :	Return = %d, errno = %d", std_res, std_errno);
	if (ft_res == std_res && ft_errno == std_errno)
		printf(GREEN " |--> YOUPI C'EST BON !\n\n" RESET);
	else
		printf(RED " |--> HOUSTON, ON A UN PROBLEME...\n\n" RESET);
	
	close(fd);

	// Test de errno en cas d'erreur (écriture dans un fichier non valide) ----
	printf(PURPLE "Test d'écriture dans un fichier non valide\n\n" RESET);
	write(1, RESET, strlen(RESET));

	errno = 0;
	ft_res = ft_write(-1, "test", 4);
	ft_errno = errno;

	errno = 0;
	std_res = write(-1, "test", 4);
	std_errno = errno;

	printf("\nft_write :        Return = %d, errno = %d\n", ft_res, ft_errno);
	printf("write standard :  Return = %d, errno = %d", std_res, std_errno);
	if (ft_res == std_res && ft_errno == std_errno)
		printf(GREEN " |--> YOUPI C'EST BON !\n\n" RESET);
	else
		printf(RED " |--> HOUSTON, ON A UN PROBLEME...\n\n" RESET);
	return;
}

void test_strcmp(void)
{
	printf(ORANGE "=====================================================================\n");
	printf("=   Test de strcmp :   =\n");
	printf("=====================================================================\n\n" RESET);

	char *first[] = {
		"",								// Chaîne vide
		"",								// ch1 vide vs ch2 normale
		"chaine non vide",				// ch1 normale vs ch2 vide
		"same string",					// Chaînes identiques
		"First octet different",		// Chaînes différente
		"Interior octet different",		// Chaînes différentes
		"Chaîne très très très grande",
		"Chaîne petite",
		NULL							// Fin du tableau
	};

	char *second[] = {
		"",								// Chaîne vide
		"Chaine non vide",				// ch1 vide vs ch2 normale
		"",								// ch1 normale vs ch2 vide
		"same string",					// Chaînes identiques
		"first octet different",		// Chaînes différentes
		"Interior Octet different",		// Chaînes différente
		"Chaîne petite",
		"Chaîne très très très grande",
		NULL							// Fin du tableau
	};

	char *test_title[] = {
		"On compare deux chaînes vides\n",
		"ch1 vide vs ch2 normale\n",
		"ch1 normale vs ch2 vide\n",
		"On compare deux chaînes identiques\n",
		"On compare des chaînes différentes au 1er octet\n",
		"On compare des chaînes différentes à octet milieu\n",
		"Chaîne first plus longue que chaîne second\n",
		"Chaîne first plus petite que chaîne second\n",
		NULL
	};

	int ft_res;
	int std_res;

	for (int i = 0; first[i] != NULL; i++)
	{
		printf(PURPLE "%s" RESET, test_title[i]);
		printf("chaîne 1 = %s\nchaîne 2 = %s\n\n", first[i], second[i]);

		ft_res = ft_strcmp(first[i], second[i]);
		std_res = strcmp(first[i], second[i]);

		printf("ft_strcmp : 		Result = %d\n", ft_res);
		printf("strcmp standard :	Result = %d", std_res);
		if (ft_res == std_res)
		{
			printf(GREEN " |--> YOUPI C'EST BON ! ");
			if (ft_res > 0)
				printf("str1 plus grande que str2.\n\n" RESET);
			else if (ft_res < 0)
				printf("str1 plus petite que str2.\n\n" RESET);
			else if (ft_res == 0)
				printf("str1 et str2 sont égales.\n\n" RESET);
		}
		else
			printf(RED " |--> HOUSTON, ON A UN PROBLEME...\n\n" RESET);
	}

	printf(PURPLE "Test d'envoi de paramètres constants\n" RESET);

	printf(CYAN "résultats précalculés : \n" RESET);
	ft_res = ft_strcmp("ch1 normale vs ch2 vide", "");
	std_res = strcmp("ch1 normale vs ch2 vide", "");
	printf("str1 normale vs str2 vide :	%i=%i\n", ft_res, std_res);

	ft_res = ft_strcmp("", "");
	std_res = strcmp("", "");
	printf("str1 vide vs str2 vide :	%i=%i\n", ft_res, std_res);

	ft_res = ft_strcmp("", "ch1 vide vs ch2 normale");
	std_res = strcmp("", "ch1 vide vs ch2 normale");
	printf("str1 vide vs str2 normale :	%i=%i\n", ft_res, std_res);

	ft_res = ft_strcmp("chaine petite", "chaine beaucoup beaucoup plus grande");
	std_res = strcmp("chaine petite", "chaine beaucoup beaucoup plus grande");
	printf("str1 petite vs str2 grande :	%i=%i\n", ft_res, std_res);

	ft_res = ft_strcmp("chaine beaucoup beaucoup plus grande", "chaine petite");
	std_res = strcmp("chaine beaucoup beaucoup plus grande", "chaine petite");
	printf("str1 grande vs str2 petite :	%i=%i\n", ft_res, std_res);

	printf(CYAN "\nfonctions inline : \n" RESET);
	printf("str1 normale vs str2 vide :	%i=%i\n", ft_strcmp("12345678901", ""), strcmp("12345678901", ""));
	printf("str1 vide vs str2 vide :	%i=%i\n", ft_strcmp("", ""), strcmp("", ""));
	printf("str1 vide vs str2 normale :	%i=%i\n", ft_strcmp("", "12345678901"), strcmp("", "12345678901"));
	printf("str1 petite vs str2 grande :	%i=%i\n", ft_strcmp("123", "12345678901"), strcmp("123", "12345678901"));
	printf("str1 grande vs str2 petite :	%i=%i\n", ft_strcmp("12345678901", "1234"), strcmp("12345678901", "1234"));

	return;
}

int test_strcpy(void)
{
	printf(ORANGE "=====================================================================\n");
	printf("=   Test de strcpy :   =\n");
	printf("=====================================================================\n\n" RESET);


	char *ft_dest = NULL;
	char *std_dest = NULL; 

	char *src[] = {
		"",							// Chaîne vide
		"hello",					// Chaîne normale
		"this is a longer string",	// Chaîne plus longue
		NULL						// Fin du tableau
	};

	char *test_title[] = {
		"Chaîne vide\n",
		"Chaîne normale\n",
		"Chaîne plus longue\n",
		NULL
	};

	for (int i = 0; src[i] != NULL; i++)
	{
		printf(PURPLE "%s" RESET, test_title[i]);
		ft_dest = malloc(strlen(src[i]) + 1);
		if (ft_dest == NULL) {
			perror("malloc");
			return 1;
		}
		std_dest = malloc(strlen(src[i]) + 1);
		if (std_dest == NULL) {
			perror("malloc");
			free(ft_dest);
			return 1;
		}
		ft_dest = ft_strcpy(ft_dest, src[i]);
		std_dest = strcpy(std_dest, src[i]);

		printf("ft_strcpy : 		Destination = %s\n", ft_dest);
		printf("strcpy standard :	Destination = %s", std_dest);
		if (strcmp(ft_dest, std_dest) == 0)
			printf(GREEN " |--> YOUPI C'EST BON !\n\n" RESET);
		else
			printf(RED " |--> HOUSTON, ON A UN PROBLEME...\n\n" RESET);
	}

	free(ft_dest);
	free(std_dest);
	return 0;
}

void test_strlen(void)
{
	printf(ORANGE "=====================================================================\n");
	printf("=   Test de strlen :   =\n");
	printf("=====================================================================\n\n" RESET);

	char *strings[] = {
		"",							// Chaîne vide
		"hello",					// Chaîne normale
		"this is a longer string",	// Chaîne plus longue
		NULL						// Fin du tableau
	};

	char *test_title[] = {
		"Chaîne vide\n",
		"Chaîne normale\n",
		"Chaîne plus longue\n",
		NULL
	};

	for (int i = 0; strings[i] != NULL; i++)
	{
		printf(PURPLE "%s" RESET, test_title[i]);
		printf("ft_strlen : 		Length of '%s' is %zu.\n", strings[i], ft_strlen(strings[i]));
		printf("strlen standard :	Length of '%s' is %zu.", strings[i], strlen(strings[i]));
		if (strlen(strings[i]) == ft_strlen(strings[i]))
			printf(GREEN " |--> YOUPI C'EST BON !\n\n" RESET);
		else
			printf(RED " |--> HOUSTON, ON A UN PROBLEME...\n\n" RESET);
	}

	// CAS DU POINTEUR NULL : ATTENTION la fonction strlen std n'est pas protégée contre NULL -> Segfault... 
	// char *null_string = NULL;

	// printf(PURPLE "Test with NULL pointer\n" RESET);
	// printf("ft_strlen : Length of null_string is %zu.\n", ft_strlen(null_string));
	// printf("strlen standard : Length of null_string is %zu.", strlen(null_string));
	// if (strlen(null_string) == ft_strlen(null_string))
	// 	printf(GREEN " |--> YOUPI C'EST BON !\n\n" RESET);
	// else
	// 	printf(RED " |--> HOUSTON, ON A UN PROBLEME...\n\n" RESET);
}

int main()
{
	printf(GREEN "Let's test ! Please enter 'Return' between each test." RESET);
	getchar();

	test_strlen(); // Tester ft_strlen
	getchar();

	test_strcpy(); // Tester ft_strcpy
	getchar();

	test_strcmp(); // Tester ft_strcmp
	getchar();

	test_write(); // Tester ft_write
	getchar();

	test_read(); // Tester ft_read
	getchar();

	test_strdup(); // Tester ft_write
	printf(GREEN "End of tests ! Please enter 'Return' to quit." RESET);
	getchar();

	return 0;
}