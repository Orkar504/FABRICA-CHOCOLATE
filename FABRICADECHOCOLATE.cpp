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

	//Creacion de semaforos de manera automatica
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

void maquina (int operacion, int machine,int semaforo)
{

	int r;
	struct sembuf arriba = {0, 1, 0};
	struct sembuf abajo = {0, -1, 0};
	
	

	switch (operacion)
	{
	case 1/* encender maquina */:
		/* code */
		printf("Maquina %i: Encendiendose\n",machine);
		printf("Maquina %i: activando proceso\n",machine);
		maquina(2,machine,semaforo);
		
		break;
	case 2/* Tambor */:
		/* code */
			printf("Maquina %i: Tambor \n", machine);
			printf("Maquina %i:  Mezclado homogeneo \n", machine);
			printf("Maquina %i:  Activacion de mezclado\n",machine);
			printf("Maquina %i:  1 Inicio del motor y las aspas\n",machine);
			printf("Maquina %i:  Aire\n", machine);
			printf("Maquina %i: .1 Regulacion de la entrada de aire\n", machine);
			printf("Maquina %i: .2 Control de mezcla de aire\n", machine);
			printf("Maquina %i:  Refinando\n", machine);
			printf("Maquina %i: .1 Ajuste de intensidad de refinado\n", machine);
			printf("Maquina %i: .2 Control del proceso de refinado\n\n", machine);
			maquina(3,machine,semaforo);
        
		break;
	case 3/* Batidora */:

			printf("Maquina %i:  Batidora\n", machine);
			printf("Maquina %i:  Aspas\n" , machine);				
			printf("Maquina %i:  Diseño y mantenimiento\n", machine);
			printf("Maquina %i:  Inspeccion periodica de aspas\n", machine);
			printf("Maquina %i:  Control de velocidad\n", machine);
			printf("Maquina %i:  Ajuste de velocidad deseada\n", machine);
			printf("Maquina %i:  Tiempo de mezclado\n", machine);
			printf("Maquina %i:  Establecimiento del tiempo de mezclado\n", machine);	
			printf("Maquina %i:  Temporizacion de los intervalos del batido\n\n", machine);
			maquina(4,machine,semaforo);
		
		break;
	case 4/*Motor*/:
	{
		printf("Maquina %i: 3. Motor\n", machine);
		printf("Maquina %i: 3.1 Fuente de energia\n", machine);
		printf("Maquina %i: 3.1.2 Suministro de energia estable\n", machine);
		printf("Maquina %i: 3.2 Encendido/Apagado\n", machine);
		printf("Maquina %i: 3.2.1 Control del encendido y apagado\n", machine);
		printf("Maquina %i: 3.2.2 Disposicion de interruptores\n", machine);
		printf("Maquina %i: 3.3 Valvula\n", machine);
		printf("Maquina %i: 3.3.1 Control de la apertura y cierre de valvulas\n", machine);
		printf("Maquina %i: 3.3.2 Regulacion del flujo de liquido\n", machine);
		printf("Maquina %i: 3.4 Sensor del motor\n", machine);
		printf("Maquina %i: 3.4.1 Instlacion del sensor\n", machine);
		printf("Maquina %i: 3.4.2 Monitoreo de vibraciones y temperatura\n", machine);
		printf("Maquina %i: 3.5 Mantenimiento\n", machine);
		printf("Maquina %i: 3.5.1 Planificacion y ejecuccion del matenimiento\n", machine);
		printf("Maquina %i: 3.5.1.1 Programacion de mantenimientos periodicos\n", machine);
		printf("Maquina %i: 3.5.1.2 Asignacion de responsabilidaddes para el mantenimiento\n", machine);
		printf("Maquina %i: 3.5.1.3 Seguimiento y registro de trabajos realizados\n", machine);
		printf("Maquina %i: 3.5.1.4 Evaluacion de necesidad y actualizacion\n\n", machine);
		maquina(5,machine,semaforo);

	}
	case 5/* Mantenimiento */:
		/* code */
	
		printf("Maquina %i: 4. Mantenimiento\n", machine);
		printf("Maquina %i: 4.1 Lubricación de partes móviles\n", machine);
		printf("Maquina %i: 4.1.1 Identificación de puntos de lubricación\n", machine);
		printf("Maquina %i: 4.1.2 Aplicación de lubricantes adecuados\n", machine);
		printf("Maquina %i: 4.2 Inspección\n", machine);
		printf("Maquina %i: 4.2.1 Examen visual de componentes\n", machine);
		printf("Maquina %i: 4.2.2 Detección de desgaste o daños\n", machine);
		printf("Maquina %i: 4.2.2.1 Utilización de herramientas de medición\n", machine);
		printf("Maquina %i: 4.2.2.2 Evaluación de la necesidad de reemplazo o reparación\n", machine);
		printf("Maquina %i: 4.3 Limpieza de residuos\n", machine);
		printf("Maquina %i: 4.3.1 Remoción de residuos y partículas\n", machine);
		printf("Maquina %i: 4.3.2 Limpieza de áreas de difícil acceso\n", machine);
		maquina(6,machine,semaforo);

		break;
	

	case 6/* Mantenimiento */:
		/* code */
	
		printf("Maquina %i: 5.3.3.1 Recepción y revisión de la alerta\n", machine);
		printf("Maquina %i: 5.3.3.2 Solución de problemas identificados\n", machine);
		printf("Maquina %i: 5.3.4 Vertido de ingrediente especial\n", machine);
		printf("Maquina %i: 5.3.4.1 Identificación de densidad inadecuada\n", machine);
		printf("Maquina %i: 5.3.4.2 Preparación y vertido del ingrediente especial\n\n", machine);
		maquina(7,machine,semaforo);
		break;
	
	case 7 /*Sensor de Temperatura*/:

		printf("Maquina %i: 6. Sensor de temperatura\n", machine);
		printf("Maquina %i: 6.1 Ajuste de temperatura\n", machine);
		printf("Maquina %i: 6.1.1 Configuración de la temperatura deseada\n", machine);
		printf("Maquina %i: 6.2 Monitoreo continuo\n", machine);
		printf("Maquina %i: 6.2.1 Lecturas constantes de temperatura\n", machine);
		maquina(8,machine,semaforo);
		break;
	case 8/*Sensor de densidad*/:
		printf("machine %i: 7. Sensor de densidad\n", machine);
		printf("machine %i: 7.1 Calibrar sensor\n", machine);
		printf("machine %i: 7.1.1 Ajuste inicial del sensor\n", machine);
		printf("machine %i: 7.2 Medición de densidad\n", machine);
		printf("machine %i: 7.2.1 Registro de mediciones de densidad\n", machine);
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
		printf("Chocolatero %i : Seleccionando una muestra para cata\n", chocolatero);
		printf("Chocolatero %i :  Enviando a Catador\n", chocolatero);
        
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
