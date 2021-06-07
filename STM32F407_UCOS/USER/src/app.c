/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                             (c) Copyright 2013; Micrium, Inc.; Weston, FL
*
*                   All rights reserved.  Protected by international copyright laws.
*                   Knowledge of the source code may not be used to write a similar
*                   product.  This file may only be used in accordance with a license
*                   and should not be redistributed in any way.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                       IAR Development Kits
*                                              on the
*
*                                    STM32F429II-SK KICKSTART KIT
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : YS
*                 DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <includes.h>
#include "led.h"
#include "usart.h"
#include "os.h"
#include "os_cfg_app.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  APP_TASK_EQ_0_ITERATION_NBR              16u


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

                                                                /* ----------------- APPLICATION GLOBALS -------------- */
static  OS_TCB   AppTaskStartTCB;
static  CPU_STK  AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE];
                                                                /* ------------ FLOATING POINT TEST TASK -------------- */
static  OS_TCB       App_TaskEq0FpTCB;
static  CPU_STK      App_TaskEq0FpStk[APP_CFG_TASK_EQ_STK_SIZE];

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppTaskStart          (void     *p_arg);
static  void  AppTaskCreate         (void);
static  void  AppObjCreate          (void);

static  void  App_TaskEq0Fp         (void  *p_arg);             /* Floating Point Equation 0 task.                      */

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

OS_TCB ledTcb;	//
CPU_STK  ledStk[100];
		OS_ERR err;
OS_TCB printTcb;	//
CPU_STK  printStk[100];
	OS_MUTEX lock;
	int i=0;
void printMynote(void *no_arg){
while(1)
{
OSMutexPend(&lock,0,OS_OPT_PEND_BLOCKING,0,&err);
printf("I AM TASK1! I AM TASK1++!DO INC NOW I = %d\r\n",i++);
OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_DLY |
OS_OPT_TIME_HMSM_STRICT,&err);
OSMutexPost(&lock,OS_OPT_POST_NONE,&err);
}
}

void printMynum(void *no_arg){
	while(1){
OSMutexPend(&lock,0,OS_OPT_PEND_BLOCKING,0,&err);
printf("I AM TASK2! I AM TASK2++!DO INC NOW I = %d\r\n",i++);
OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_DLY |
OS_OPT_TIME_HMSM_STRICT,&err);
OSMutexPost(&lock,OS_OPT_POST_NONE,&err);
}
}


		#define EV_FLAG1       (1 << 1)// 事件1 bit0  结合下面的创建：发生为1
		OS_FLAG_GRP EventFlags;     //定义一个事件标志组 EventFlags
		OS_FLAGS flags_num;
		void task1(void *p_arg)
		{
			while(1)
			{
				OSFlagPend((OS_FLAG_GRP*)&EventFlags, //等待计数事件， bit2 为 1
(OS_FLAGS )EV_FLAG1,//bit2
(OS_TICK )0,
(OS_OPT )OS_OPT_PEND_FLAG_SET_ALL ,
(CPU_TS* )0,
(OS_ERR* )&err);
OSMutexPend (&lock,0,OS_OPT_PEND_NON_BLOCKING,0,&err);
printf("I AM TASK 1!I = %d\r\n",i++);
OSMutexPost(&lock,OS_OPT_POST_NONE,&err);
if(i>5){OSFlagPost((OS_FLAG_GRP*)&EventFlags, //发布“游戏结束”事件
(OS_FLAGS )EV_FLAG1,
(OS_OPT )OS_OPT_POST_FLAG_CLR,
(OS_ERR* )&err);
}
OSTimeDlyHMSM(0,0,2,0, OS_OPT_TIME_DLY|OS_OPT_TIME_HMSM_STRICT,&err);
			}
		}

		
		void task2(void *p_arg)
		{
			while(1)
			{
OSFlagPend((OS_FLAG_GRP*)&EventFlags, //等待“游戏结束”事件
(OS_FLAGS )EV_FLAG1,//bit2
(OS_TICK )0,
(OS_OPT )OS_OPT_PEND_FLAG_CLR_ALL ,
(CPU_TS* )0,
(OS_ERR* )&err);
OSMutexPend (&lock,0,OS_OPT_PEND_NON_BLOCKING,0,&err);
printf("I AM TASK 2!game over \r\n");
i=0;
OSMutexPost(&lock,OS_OPT_POST_NONE,&err); //发布计数事件
flags_num=OSFlagPost((OS_FLAG_GRP*)&EventFlags,
(OS_FLAGS )EV_FLAG1,
(OS_OPT )OS_OPT_POST_FLAG_SET,
(OS_ERR* )&err);
				OSTimeDlyHMSM(0,0,2,0, OS_OPT_TIME_DLY|OS_OPT_TIME_HMSM_STRICT,&err);
			}
		}
		
int main(void)
{
    OS_ERR  err;
	
    BSP_IntDisAll();                                            /* Disable all interrupts.                              */
    
    CPU_Init();                                                 /* Initialize the uC/CPU Services                       */
    Mem_Init();                                                 /* Initialize Memory Management Module                  */
    Math_Init();                                                /* Initialize Mathematical Module                       */
		BSP_Init();
		BSP_Tick_Init();
		usart_init();
		led_init();
	
    OSInit(&err);                                               /* Init uC/OS-III.                                      */

		OSSchedRoundRobinCfg(ENABLE,
				10,&err
	);

	OSMutexCreate (&lock,"lock",&err);
	
    OSTaskCreate((OS_TCB       *)&ledTcb,              /* Create the start task                                */
                 (CPU_CHAR     *)"led WUWUWU",
                 (OS_TASK_PTR   )task1,
                 (void         *)0u,
                 (OS_PRIO       )2,
                 (CPU_STK      *)&ledStk[100],
                 (CPU_STK_SIZE  )10,
                 (CPU_STK_SIZE  )100,
                 (OS_MSG_QTY    )10u,
                 (OS_TICK       )1u,
                 (void         *)NULL,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);
								 
		OSTaskCreate((OS_TCB       *)&printTcb,              /* Create the start task                                */
                 (CPU_CHAR     *)"print WUWUWU",
                 (OS_TASK_PTR   )task2,
                 (void         *)0u,
                 (OS_PRIO       )5,
                 (CPU_STK      *)&printStk[100],
                 (CPU_STK_SIZE  )10,
                 (CPU_STK_SIZE  )100,
                 (OS_MSG_QTY    )10u,
                 (OS_TICK       )1u,
                 (void         *)NULL,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);

		if(err != OS_ERR_NONE){
			printf("error!!");
		}OSFlagCreate(&EventFlags,
"task1",
EV_FLAG1,
&err);
    OSStart(&err);                                              /* Start multitasking (i.e. give control to uC/OS-III). */

    (void)&err;

    return (0u);
}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  AppTaskStart (void *p_arg)
{
    OS_ERR  err;


   (void)p_arg;

    BSP_Init();                                                 /* Initialize BSP functions                             */
    BSP_Tick_Init();                                            /* Initialize Tick Services.                            */


#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif

    BSP_LED_Off(0u);                                            /* Turn Off LEDs after initialization                   */

    APP_TRACE_DBG(("Creating Application Kernel Objects\n\r"));
    AppObjCreate();                                             /* Create Applicaiton kernel objects                    */

    APP_TRACE_DBG(("Creating Application Tasks\n\r"));
    AppTaskCreate();                                            /* Create Application tasks                             */


    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */

        BSP_LED_Toggle(1u);
        OSTimeDlyHMSM(0u, 0u, 0u, 100u,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);

        BSP_LED_Toggle(2u);
        OSTimeDlyHMSM(0u, 0u, 0u, 100u,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);

        BSP_LED_Toggle(3u);
        OSTimeDlyHMSM(0u, 0u, 0u, 100u,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);

        BSP_LED_Toggle(4u);
        OSTimeDlyHMSM(0u, 0u, 0u, 100u,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);

    }
}


/*
*********************************************************************************************************
*                                          AppTaskCreate()
*
* Description : Create application tasks.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTaskStart()
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  AppTaskCreate (void)
{
    OS_ERR  os_err;
    
                                                                /* ------------- CREATE FLOATING POINT TASK ----------- */
    OSTaskCreate((OS_TCB      *)&App_TaskEq0FpTCB,
                 (CPU_CHAR    *)"FP  Equation 1",
                 (OS_TASK_PTR  ) App_TaskEq0Fp, 
                 (void        *) 0,
                 (OS_PRIO      ) APP_CFG_TASK_EQ_PRIO,
                 (CPU_STK     *)&App_TaskEq0FpStk[0],
                 (CPU_STK_SIZE ) App_TaskEq0FpStk[APP_CFG_TASK_EQ_STK_SIZE / 10u],
                 (CPU_STK_SIZE ) APP_CFG_TASK_EQ_STK_SIZE,
                 (OS_MSG_QTY   ) 0u,
                 (OS_TICK      ) 0u,
                 (void        *) 0,
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP),
                 (OS_ERR      *)&os_err);
}


/*
*********************************************************************************************************
*                                          AppObjCreate()
*
* Description : Create application kernel objects tasks.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTaskStart()
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  AppObjCreate (void)
{

}


/*
*********************************************************************************************************
*                                             App_TaskEq0Fp()
*
* Description : This task finds the root of the following equation.
*               f(x) =  e^-x(3.2 sin(x) - 0.5 cos(x)) using the bisection mehtod
*
* Argument(s) : p_arg   is the argument passed to 'App_TaskEq0Fp' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  App_TaskEq0Fp (void  *p_arg)
{
    CPU_FP32    a;
    CPU_FP32    b;
    CPU_FP32    c;
    CPU_FP32    eps;
    CPU_FP32    f_a;
    CPU_FP32    f_c;
    CPU_FP32    delta;
    CPU_INT08U  iteration;
    RAND_NBR    wait_cycles;
        
    
    while (DEF_TRUE) {
        eps       = 0.00001;
        a         = 3.0; 
        b         = 4.0;
        delta     = a - b;
        iteration = 0u;
        if (delta < 0) {
            delta = delta * -1.0;
        }
        
        while (((2.00f * eps) < delta) || 
               (iteration    > 20u  )) {
            c   = (a + b) / 2.00f;
            f_a = (exp((-1.0) * a) * (3.2 * sin(a) - 0.5 * cos(a)));
            f_c = (exp((-1.0) * c) * (3.2 * sin(c) - 0.5 * cos(c)));
            
            if (((f_a > 0.0f) && (f_c < 0.0f)) || 
                ((f_a < 0.0f) && (f_c > 0.0f))) {
                b = c;
            } else if (((f_a > 0.0f) && (f_c > 0.0f)) || 
                       ((f_a < 0.0f) && (f_c < 0.0f))) {
                a = c;           
            } else {
                break;
            }
                
            delta = a - b;
            if (delta < 0) {
               delta = delta * -1.0;
            }
            iteration++;

            wait_cycles = Math_Rand();
            wait_cycles = wait_cycles % 1000;

            while (wait_cycles > 0u) {
                wait_cycles--;
            }

            if (iteration > APP_TASK_EQ_0_ITERATION_NBR) {
                APP_TRACE_INFO(("App_TaskEq0Fp() max # iteration reached\n"));
                break;
            }            
        }

        APP_TRACE_INFO(("Eq0 Task Running ....\n"));
        
        if (iteration == APP_TASK_EQ_0_ITERATION_NBR) {
            APP_TRACE_INFO(("Root = %f; f(c) = %f; #iterations : %d\n", c, f_c, iteration));
        }
    }
}
