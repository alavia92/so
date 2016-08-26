#include "tasks.h"

using namespace std;

void TaskCPU(int pid, vector<int> params) { // params: n
	uso_CPU(pid, params[0] - 1); // Uso el CPU n milisegundos.
}

void TaskIO(int pid, vector<int> params) { // params: ms_pid, ms_io,
	uso_CPU(pid, params[0]); // Uso el CPU ms_pid milisegundos.
	uso_IO(pid, params[1]); // Uso IO ms_io milisegundos.
}

void TaskAlterno(int pid, vector<int> params) { // params: ms_pid, ms_io, ms_pid, ...
	for(int i = 0; i < (int)params.size(); i++) {
		if (i % 2 == 0) uso_CPU(pid, params[i] - 1);
		else uso_IO(pid, params[i]);
	}
}

void TaskConsola(int pid, vector<int> params) {
	// params: n bmin bmax
	int random_num;

	for(int i = 0; i < params[0]; i++){
		random_num = params[1] + rand() % (params[2]-params[1] + 1);
		uso_IO(pid, random_num);
		uso_CPU(pid, 1);
	}
	return;
}

void TaskBatch(int pid, vector<int> params) {
	// params: total_cpu cant_bloqueos
	
	//PREGUNTAR!!!!!!!!! ES ASI EL ENUNCIADO??????

	int cpu_restante = params[0] - params[1] - 1;
	int random_num;
	while(params[1] > 0){
		random_num = rand() % (cpu_restante + 1);
		if(random_num > 0) uso_CPU(pid, random_num);
		cpu_restante = cpu_restante - random_num;
		uso_IO(pid, 2);
		params[1]--;
	}

	return;
}


void tasks_init(void) {
	/* Todos los tipos de tareas se deben registrar acá para poder ser usadas.
	 * El segundo parámetro indica la cantidad de parámetros que recibe la tarea
	 * como un vector de enteros, o -1 para una cantidad de parámetros variable. */
	register_task(TaskCPU, 1);
	register_task(TaskIO, 2);
	register_task(TaskAlterno, -1);
	register_task(TaskConsola, 3);
	register_task(TaskBatch, 2);
}
