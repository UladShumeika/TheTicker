//---------------------------------------------------------------------------
// Define to prevent recursive inclusion
//---------------------------------------------------------------------------
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

//---------------------------------------------------------------------------
// Ensure definitions are only used by the compiler, and not by the assembler
//---------------------------------------------------------------------------
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
  #include <stdint.h>
  extern uint32_t SystemCoreClock;
#endif

//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------
#define configUSE_PREEMPTION                    		1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 		1
#define configUSE_TICKLESS_IDLE                 		0
#define configCPU_CLOCK_HZ                       		( SystemCoreClock )
//#define configSYSTICK_CLOCK_HZ
#define configTICK_RATE_HZ                       		((TickType_t)1000)
#define configMAX_PRIORITIES                     		( 7 )
#define configMINIMAL_STACK_SIZE                 		((uint16_t)128)
#define configMAX_TASK_NAME_LEN                  		( 20 )
#define configUSE_16_BIT_TICKS                   		0
#define configIDLE_SHOULD_YIELD                 		1
#define configUSE_TASK_NOTIFICATIONS            		1
#define configTASK_NOTIFICATION_ARRAY_ENTRIES  			1
#define configUSE_MUTEXES                        		1
#define configUSE_RECURSIVE_MUTEXES						0
#define configUSE_COUNTING_SEMAPHORES          			0
#define configQUEUE_REGISTRY_SIZE                		10
#define configUSE_QUEUE_SETS                    		0
#define configUSE_TIME_SLICING      	            	1
#define configUSE_NEWLIB_REENTRANT              		1
#define configENABLE_BACKWARD_COMPATIBILITY     		1
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS 		0
//#define configUSE_MINI_LIST_ITEM             			0
#define configSTACK_DEPTH_TYPE                  		uint16_t
#define configMESSAGE_BUFFER_LENGTH_TYPE         		size_t
#define configHEAP_CLEAR_MEMORY_ON_FREE         		1
#define configENABLE_FPU                        		0
#define configENABLE_MPU                         		0

// Memory allocation related definitions
#define configSUPPORT_STATIC_ALLOCATION            	 	1
#define configSUPPORT_DYNAMIC_ALLOCATION           	 	1
#define configTOTAL_HEAP_SIZE                    		((size_t)15360)
#define configAPPLICATION_ALLOCATED_HEAP            	0
#define configSTACK_ALLOCATION_FROM_SEPARATE_HEAP   	0

// Hook function related definitions
#define configUSE_IDLE_HOOK                     		0
#define configUSE_TICK_HOOK                      		0
#define configCHECK_FOR_STACK_OVERFLOW          		0
#define configUSE_MALLOC_FAILED_HOOK          			0
#define configUSE_DAEMON_TASK_STARTUP_HOOK      		0
#define configUSE_SB_COMPLETED_CALLBACK         		0

// Run time and task stats gathering related definitions
#ifdef DEBUG
    #define configRECORD_STACK_HIGH_ADDRESS				1
  	#define configUSE_TRACE_FACILITY                	1
#endif

#define configGENERATE_RUN_TIME_STATS          			0
#define configUSE_STATS_FORMATTING_FUNCTIONS    		0

// Co-routine related definitions
#define configUSE_CO_ROUTINES                    		0
#define configMAX_CO_ROUTINE_PRIORITIES          		( 2 )

/* Software timer related definitions. */
#define configUSE_TIMERS                        		0
#define configTIMER_TASK_PRIORITY               		0
#define configTIMER_QUEUE_LENGTH                		0
#define configTIMER_TASK_STACK_DEPTH                	0

// Interrupt nesting behaviour configuration
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY   		15
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 	5
#define configKERNEL_INTERRUPT_PRIORITY 				( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 			( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

// Define to trap errors during development
#define configASSERT( x ) if ((x) == 0) {taskDISABLE_INTERRUPTS(); for( ;; );}

// Set the following definitions to 1 to include the API function, or zero to exclude the API function
#define INCLUDE_vTaskPrioritySet             			1
#define INCLUDE_vTaskCleanUpResources        			0
#define INCLUDE_uxTaskPriorityGet            			1
#define INCLUDE_vTaskDelete                  			1
#define INCLUDE_vTaskSuspend                 			1
#define INCLUDE_xResumeFromISR                  		0
#define INCLUDE_vTaskDelayUntil              			0
#define INCLUDE_vTaskDelay                   			1
#define INCLUDE_xTaskGetSchedulerState       			1
#define INCLUDE_xTaskGetCurrentTaskHandle       		0
#define INCLUDE_uxTaskGetStackHighWaterMark    			0
#define INCLUDE_uxTaskGetStackHighWaterMark2    		0
#define INCLUDE_xTaskGetIdleTaskHandle         			0
#define INCLUDE_eTaskGetState                   		0
#define INCLUDE_xEventGroupSetBitFromISR        		0
#define INCLUDE_xTimerPendFunctionCall          		0
#define INCLUDE_xTaskAbortDelay                 		0
#define INCLUDE_xTaskGetHandle                  		0
#define INCLUDE_xTaskResumeFromISR              		1

// Cortex-M specific definitions
#ifdef __NVIC_PRIO_BITS
	#define configPRIO_BITS		__NVIC_PRIO_BITS	// __BVIC_PRIO_BITS will be specified when CMSIS is being used
#else
 #define configPRIO_BITS         4
#endif

// Definitions that map the FreeRTOS port interrupt handlers to their CMSIS standard names
#define vPortSVCHandler    								SVC_Handler
#define xPortPendSVHandler 								PendSV_Handler

#define xPortSysTickHandler 							SysTick_Handler

#endif /* FREERTOS_CONFIG_H */
