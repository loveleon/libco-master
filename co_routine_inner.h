/*
* Tencent is pleased to support the open source community by making Libco available.

* Copyright (C) 2014 THL A29 Limited, a Tencent company. All rights reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License"); 
* you may not use this file except in compliance with the License. 
* You may obtain a copy of the License at
*
*	http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, 
* software distributed under the License is distributed on an "AS IS" BASIS, 
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
* See the License for the specific language governing permissions and 
* limitations under the License.
*/


#ifndef __CO_ROUTINE_INNER_H__

#include "co_routine.h"
#include "coctx.h"
struct stCoRoutineEnv_t;
struct stCoSpec_t
{
	void *value;
};

//协程栈区
struct stStackMem_t
{
	stCoRoutine_t* occupy_co;//使用该栈的协程
	int stack_size;//栈大小
	char* stack_bp; //stack_buffer + stack_size//栈底 栈是从高地址向低地址增加（相对入栈方向）
	char* stack_buffer;//栈顶

};

//共享栈区
struct stShareStack_t
{
	unsigned int alloc_idx;//每个栈开始游标
	int stack_size;//栈空间
	int count;//栈个数
	stStackMem_t** stack_array;
};



struct stCoRoutine_t
{
	stCoRoutineEnv_t *env;//协程运行环境
	pfn_co_routine_t pfn;//协程执行的逻辑函数
	void *arg;//函数参数
	coctx_t ctx;//保存协程的下文环境

	char cStart;
	char cEnd;
	char cIsMain;
	char cEnableSysHook;//是否运行系统 hook，即非侵入式逻辑
	char cIsShareStack;//是否在共享栈模式

	void *pvEnv;

	//char sRunStack[ 1024 * 128 ];
	stStackMem_t* stack_mem;//协程运行时的栈空间


	//save satck buffer while confilct on same stack_buffer;
	char* stack_sp; //用来保存协程运行时的栈空间
	unsigned int save_size;
	char* save_buffer;

	stCoSpec_t aSpec[1024];

};



//1.env
void 				co_init_curr_thread_env();
stCoRoutineEnv_t *	co_get_curr_thread_env();

//2.coroutine
void    co_free( stCoRoutine_t * co );
void    co_yield_env(  stCoRoutineEnv_t *env );

//3.func



//-----------------------------------------------------------------------------------------------

struct stTimeout_t;
struct stTimeoutItem_t ;

stTimeout_t *AllocTimeout( int iSize );
void 	FreeTimeout( stTimeout_t *apTimeout );
int  	AddTimeout( stTimeout_t *apTimeout,stTimeoutItem_t *apItem ,uint64_t allNow );

struct stCoEpoll_t;
stCoEpoll_t * AllocEpoll();
void 		FreeEpoll( stCoEpoll_t *ctx );

stCoRoutine_t *		GetCurrThreadCo();
void 				SetEpoll( stCoRoutineEnv_t *env,stCoEpoll_t *ev );

typedef void (*pfnCoRoutineFunc_t)();

#endif

#define __CO_ROUTINE_INNER_H__
