/**
 *	Ceno RTOS task 
 * 	
 * 2018-12-17 
 * neroyang
 * 
 * Copyright (C) 2018 CenoCloud. All Rights Reserved 
 *
 * Contract Information：
 * nerosoft@outlook.com
 * https://www.cenocloud.com
 */
#include "../include/os_api.h"

os_task_t* volatile osIdleTask;
uint32_t stackTaskIdle[40];

os_err_t os_init(void){
	uart_debug_print("[kernel] os init.\n\r");
	/**
	 * os objects container init
	 */
	os_err_t isOsObjectContainerInit = os_obj_container_init();
	if(isOsObjectContainerInit==OS_ERR){
		return isOsObjectContainerInit;
	}

	/**
	 * os idle task init
	 */
	os_err_t isOsIdleTaskInit = os_task_create(
		osIdleTask,
    	"taskIdle",
    	0,
    	stackTaskIdle,
    	sizeof(stackTaskIdle),
    	os_idle
	);
	
	if(isOsIdleTaskInit==OS_ERR){
		return isOsIdleTaskInit;
	}
}

os_err_t os_run(void){
	uart_debug_print("[kernel] os run.\n\r");
	/* callback to configure and start interrupts */
	os_on_startup();
	os_init();

    disable_irq();
    os_sched();
    enable_irq();
}

os_err_t os_idle(void){
	uart_debug_print("[kernel] os idle.\n\r");

}

os_err_t os_tick(void){
	// Traversing the tasks in queue
	os_task_t *t = (os_task_t *)osTaskQueue->elems;
	t->state = OS_STATE_READY;
	// while(t){
	// 	/* count down the timeout */
	// 	t->timeout--;
	// 	if (t->timeout == 0U) {
	// 		/* set task state */
	// 		t->state = OS_STATE_READY;	
	// 	}
	// 	t = t->next;
	// }
	
}

os_task_t* os_get_next_ready_from_task_queue(os_queue_t* queue){
	// get the first task from task queue sorted by priority
	 return (os_task_t *)osTaskQueue->elems;
}

os_err_t os_sched(void){
	uart_debug_print("[kernel] os sched.\n\r");
	if(os_queue_size(osTaskQueue)<=0U){
		osTaskNext = osIdleTask;
	}else{
		/* get first ready task from task queue, task queue is sorted by priority */
		osTaskNext = os_get_next_ready_from_task_queue(osTaskQueue);
	}
	// hard trigger
	*(uint32_t volatile *)0xE000ED04 = (1U << 28);
	/* trigger PendSV, if needed */
 	if (osTaskNext != osTaskCurr) {
		uart_debug_print("[kernel] PendSV trigger.\n\r");
		/* todo : this need be a hal function */
        *(uint32_t volatile *)0xE000ED04 = (1U << 28);
    }
}
