#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>


#if __unix__ 		// per evitare errori a causa delle variabili d'ambiente ho deciso che il programma deve essere usato solo su unix
	#if !defined(checker) || !defined(g_lenght)

		/*		MACRO & COSTANTI	*/
		#define 	checker(x) 		if(x) {return EXIT_FAILURE;}
		#define 	g_length		1000				// max len x row file

		/*		Prototype		*/
		extern void 	_exit		(register int);
		int 		logging		(void);
		char 		*estrazione	(char[]);
		void 		f_read		(FILE*, char[]);

		/*		Struct			*/
		typedef struct{
			#define LEN 200				// buffer matricola
			#define TOT_MAX_X_FILE 200 		// buffer contenitore di matricole x file

			char matricola[TOT_MAX_X_FILE][LEN];	// vettore che contiene le matricole di un solo file
							        // ogni matricola e' rappresentata tramite puntatore

			int counter;				// lo uso come indice per muovermi all'interno del vettore multidimensionale matricola
		}matricole;
	
	#else
		#error, macro checker gia inizializzata
	#endif
#else
	#error programma compilabile solo da s.o. unix - like
#endif


int main(int argc, char *argv[]){
	setlocale(LC_CTYPE, " ");

	if(logging() == EXIT_FAILURE){
		perror("error");
		_exit(EXIT_FAILURE);
	}

	FILE
		*inp1 	= fopen("../flussi/77_gusers_export_alunni.txt", "r"),
		*inp2 	= fopen("../flussi/77_SIGMA_EXPORT_ALUNNI.txt", "r"),
		*out 	= fopen("../flussi/sync.txt", "w");
	

	checker(inp1 == NULL);
	checker(inp2 == NULL);
	checker(out == NULL);


	matricole
		xinp1 = {.counter = 0},	// contenitore delle matricole del file inp1
		xinp2 = {.counter = 0},	// contenitore delle matricole del file inp2
		xout;			// contenitore delle matricole del file sync


	char line[g_length];
	while(fgets(line, sizeof(line), inp1) != NULL){
		strcat(xinp1.matricola[xinp1.counter], line);
		xinp1.counter++;
	}

	return EXIT_SUCCESS;
}


int logging(){
	FILE *logg = fopen("../log/trace.log", "a");	
	checker(logg == NULL);

	time_t tempo;
	time(&tempo);

	fprintf(logg, "time: %ld -- local time: %s\n", tempo, ctime(&tempo));	
	fprintf(logg, "username: %s\n\n", getenv("USERNAME"));

	fclose(logg);	
	return EXIT_SUCCESS;
}



char *estrazione(char line[]){

	return *line;
}
