#include <stdio.h> 
#include <stdlib.h> 
#include <wait.h> 
#include <sys/errno.h> 

#include  <fcntl.h> 
		    
#include  <unistd.h>
#include  <sys/ipc.h>
#include  <sys/sem.h> 
#include  <sys/stat.h>
#include  <sys/types.h> 
#include  <string.h>

#define  N_ORDENES 5
#define  N_chocolateros 3
#define N_Maquinas 5
#define SEM_Chocolatero 0
#define SEM_Maquina 1
#define SEM_Operario 2
#define SEM_Catador 3
#define SEM_Jefe 4

union semun {
	int val;
};

void inicializar(int);
void chocolatero (int,int,int,int,int);
void maquina(int, int,int);

//Variables globales
int chocolateros_en_fabrica = N_chocolateros;

int main()
{
	//Variables
	int sem;
	int cantidad_sem = 5;
	int r;
	int c, soyeste;
	int chocolateroLibre=0;
	int maquinaLibre=0;
	int chocolaterosD = chocolateros_en_fabrica;
	pid_t pid;
	union semun arg;
	struct sembuf arriba = {0, 1, 0};
	struct sembuf abajo = {0, -1, 0};


	//declarar la cantida de semaforos
	sem = semget(IPC_PRIVATE, cantidad_sem, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	
	//Creacion de semaforos
	if(sem == -1) {
	
		perror("Error inicializando semaforo \n");
		return -1;
	}

	//Creacion de semaforos
	for(int i = 0; i < cantidad_sem; i++) {
		arg.val = 1;
		r = semctl(sem, i, SETVAL, arg);
		
		if(r == -1){
			perror("Error inicializando semaforo \n");
			return -1;
		}
	}
	//Indicar los chocolateros y ordenes
	printf("Chocolateros: %i / Numero de ordenes: %i\n\n", N_chocolateros,N_ORDENES);

	//Loop para la cantidad de ordenes
	
/*Asignar N tareas a M chocolateros disponibles donde N > M
		Si solo hay 3 chocolateros, asignar a esos 3 chocolateros las
		ordenes restantes, pero no aumentar el número de chocolateros siempre 
		deben ser los mismo tres 
		*/
	for(c = 0; c < N_ORDENES; c++)
	{
		abajo.sem_num = SEM_Chocolatero;
			r = semop(sem, &abajo, 1);
			
			if(r == -1) {
				perror("error bajando el proceso Almacenar Bombones\n");
				return -1;
			}
          

            //Procesos
		chocolatero(1,chocolateroLibre,c,maquinaLibre,sem);

		maquinaLibre = (maquinaLibre+1)%N_Maquinas;
		chocolateroLibre =(chocolateroLibre+1)%chocolateros_en_fabrica;

	}
	return 0;
}

void maquina (int operacion, int maquina,int semaforo)
{

	int r;
	struct sembuf arriba = {0, 1, 0};
	struct sembuf abajo = {0, -1, 0};
	
	

	switch (operacion)
	{
	case 1/* encender maquina */:
		/* code */
		
		break;
	case 2/* Tambor */:
		/* code */
			printf("Maquina %i: 1. Tambor \n", maquina);
			printf("Maquina %i: 1.1 Mezclado homogeneo \n", maquina);
			printf("Maquina %i: 1.1.1 Carga de ingredientes \n", maquina);
        
		break;
	case 3/* Protocólo de limpieza */:

		/* code */
		
		break;
	case 4:
	{

	}
	case 5/* Almacenar */:
		/* code */

		break;
	
	default:
		break;
	}
}
void chocolatero (int operacion, int chocolatero, int orden,int machine,int semaforo)
{

	int r;
	struct sembuf arriba = {0, 1, 0};
	struct sembuf abajo = {0, -1, 0};
	
	

	switch (operacion)
	{
	case 1/* Rellenar el Chocolate */:
		/* code */
		printf("Chocolatero %i, Rellenando Máquina %i para la orden %i \n",chocolatero,machine,orden);
		printf("Rellenada la máquina , iniciando \n");

		/*Funcion para iniciar la máquina y su semaforo*/

		//Se abre el semaforo
		abajo.sem_num = SEM_Maquina;
		r = semop(semaforo, &arriba, 1);
		if(r==-1)
		{
			perror("Error, maquina  no enciende");
		}
		if(r==0)
		{
			maquina(1,machine,semaforo);
			
			//Se cierra el semaforo
			arriba.sem_num = SEM_Maquina;
			r = semop(semaforo, &arriba, 1);
			
			if(r == -1) {
				perror("Error apagando maquina\n");
				break;
			}	

			//Cuando se termina de hacer el chocolate termina aqui xd

			break;
		}
		break;
	case 2/* Hacer Chocolate */:
		/* code */
		printf("Chocolatero %i :Haciendo el bombón\n", chocolatero);
		printf("Chocolatero %i : Preparando el Relleno\n", chocolatero);
		printf("Chocolatero %i : Mezclando los ingredientes necesarios para el relleno\n", chocolatero);
		printf("Chocolatero %i : Rellenando los moldes con chocolate\n", chocolatero);
		printf("Chocolatero %i : Enfriando el chocolate\n", chocolatero);
		printf("Chocolatero %i : Rellenando los moldes con el relleno\n", chocolatero);
		printf("Chocolatero %i : Retirando el exceso de chocolate\n", chocolatero);
		printf("Chocolatero %i : Cubriendo los moldes con chocolate\n", chocolatero);
		printf("Chocolatero %i : Refrigerando los bombones\n", chocolatero);
		printf("Chocolatero %i : Desmoldeando\n", chocolatero);
		printf("Chocolatero %i : Decoración\n", chocolatero);
		printf("Chocolatero %i : Eligiendo el tipo de decoración\n", chocolatero);
		printf("Chocolatero %i : Aplicando la decoración\n", chocolatero);
        
		break;
	case 3/* Protocólo de limpieza */:

		/* code */
		printf("Chocolatero %i : 1.1. Preparando el área de trabajo\n", chocolatero);
            printf("Chocolatero %i : Colocándose la indumentaria necesaria\n", chocolatero);
            printf("Chocolatero %i :  Realizándose una ducha de desinfección\n", chocolatero);
            printf("Chocolatero %i :  Revisando que el área de la ducha esté limpia y desinfectada antes de su uso\n", chocolatero);
            printf("Chocolatero %i :  Revisando que haya jabón neutro en la ducha\n", chocolatero);
            printf("Chocolatero %i :  Duchándose\n", chocolatero);
            printf("Chocolatero %i :  Vistiéndose con el uniforme\n", chocolatero);
            printf("Chocolatero %i :  Revisando que el uniforme esté completo\n", chocolatero);
            printf("Chocolatero %i :  Revisando que el uniforme esté limpio\n", chocolatero);
            printf("Chocolatero %i :  Colocándose el uniforme\n", chocolatero);
            printf("Chocolatero %i :  Vistiéndose con el delantal\n", chocolatero);
            printf("Chocolatero %i :  Revisando que el delantal esté limpio\n", chocolatero);
            printf("Chocolatero %i :  Revisando que el delantal no esté dañado\n", chocolatero);
            printf("Chocolatero %i :  Colocándose el delantal\n", chocolatero);
            printf("Chocolatero %i :  Vistiéndose con la malla para el cabello\n", chocolatero);
            printf("Chocolatero %i : . Revisando que haya mallas para el cabello\n", chocolatero);
            printf("Chocolatero %i : . Colocándose la malla para el cabello\n", chocolatero);
            printf("Chocolatero %i : Colocándose la mascarilla\n", chocolatero);
            printf("Chocolatero %i : . Revisando que tengan mascarillas limpias en existencia\n", chocolatero);
            printf("Chocolatero %i : Colocándose los cubre botas desechables\n", chocolatero);
            printf("Chocolatero %i : . Revisando que los cubre botas estén intactos y nuevos\n", chocolatero);
            printf("Chocolatero %i :  Cerciorándose de que se han cumplimentado todos los pasos necesarios para una correcta vestimenta necesaria\n", chocolatero);
            printf("Chocolatero %i : Realizando una inspección final\n", chocolatero);
            printf("Chocolatero %i : Realizando un ajuste para comodidad\n", chocolatero);
            printf("Chocolatero %i : Verificando la limpieza del uniforme\n", chocolatero);
            printf("Chocolatero %i : 3. Revisando el cumplimiento de las Normas de Higiene\n", chocolatero);
            printf("Chocolatero %i : listando los utensilios de la mesa\n", chocolatero);
            printf("Chocolatero %i :  Revisando si algún utensilio ya no es óptimo para el trabajo\n", chocolatero);
            printf("Chocolatero %i :  Lavando los utensilios\n", chocolatero);
            printf("Chocolatero %i :  Limpiando los utensilios\n", chocolatero);
            printf("Chocolatero %i :  Desinfectando los utensilios\n", chocolatero);
            printf("Chocolatero %i :  Secando los utensilios\n", chocolatero);
            printf("Chocolatero %i :  Examinando que todos los utensilios estén en óptimas condiciones para el trabajo\n", chocolatero);
            printf("Chocolatero %i :  Cerciorándose de que se han cumplimentado al pie de la regla todos los pasos necesarios para una correcta limpieza y desinfección de los utensilios\n", chocolatero);    
			printf("Chocolatero %i :  Alistando los moldes en la mesa\n", chocolatero);
            printf("Chocolatero %i :  Realizando una inspección de los moldes para revisar que todos los moldes estén en óptimas condiciones\n", chocolatero);
            printf("Chocolatero %i :  Lavando los moldes\n", chocolatero);
            printf("Chocolatero %i :  Limpiando los moldes\n", chocolatero);
            printf("Chocolatero %i : Desinfectando los moldes\n", chocolatero);
            printf("Chocolatero %i : Secando los moldes\n", chocolatero);
            printf("Chocolatero %i : . Realizando una inspección para que los moldes cumplan las regulaciones de salud\n", chocolatero );
			printf("Chocolatero %i : Seleccionando una muestra para cata\n", chocolatero);
			printf("Chocolatero %i :  Enviando a Catador\n", chocolatero);
					/* Enviar a catador */
		break;
	case 5/* Almacenar */:
		/* code */
		printf("Chocolatero %i :  Almacenando los bombones\n", chocolatero);
		printf("Chocolatero %i : Empacando los bombones en un recipiente hermético\n", chocolatero);
		printf("Chocolatero %i : Enviando los bombones a almacenamiento\n", chocolatero);
		break;
	
	default:
		break;
	}
}


/* SEMAFOROS 
int r;
	struct sembuf arriba = {0, 1, 0};
	arriba.sem_num = SEM_Maquina;
	r = semop(semaforo, &arriba, 1);
	if(r==-1)
	{
		perror("Error, maquina  no enciende");
	}
	if(r==0)
	{
		//llamar proceso maquina
	}


*/
/*

 /////
            arriba.sem_num = SEM_HACER_BOMBONES;
			r = semop(sem, &arriba, 1);
			
			if(r == -1) {
				perror("error subiendo el proceso Hacer Bombones\n");
				return -1;
			}
			
			sleep(2);

            //Requerimientos de la Orden
            printf("Chocolatero %i: Accediendo al proceso empacar\n", chocolatero);

            abajo.sem_num = SEM_ALMACENAR_BOMBONES;
			r = semop(sem, &abajo, 1);
			
			if(r == -1) {
				perror("error bajando el proceso Almacenar Bombones\n");
				return -1;
			}
          

            //Procesos
            printf("Chocolatero %i : 1.4. Almacenando los bombones\n", chocolatero);
            printf("Chocolatero %i : 1.4.1. Empacando los bombones en un recipiente hermético\n", chocolatero);
            printf("Chocolatero %i : 1.4.2. Enviando los bombones a almacenamiento\n", chocolatero);
             if(isErrorOrNot() == 1) {
			//Interrupcion 1.3.2
            printf("Chocolatero %i: Interrupcion generada \n\n", chocolatero);
            printf("Chocolatero %i: 1.4.1.1: Error no hay recipientes\n", chocolatero);
            printf("Chocolatero %i: 1.4.1.2: Solicitar recipientes a bodega\n", chocolatero);
            printf("Chocolatero %i: 1.4.1.3: esperar\n", chocolatero); 
            printf("Chocolatero %i: 1.4.1.4: Han llegado los recipientes\n", chocolatero); 
            printf("Chocolatero %i: 1.4.1.5: Almacenado de bombones\n", chocolatero); 
			}
           
*/