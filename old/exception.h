/*
	Name: exception.h
	Copyright: GPL 3.0
	Author: 瞿相荣 
	Date: 26/03/23 21:26
	Description: 模拟异常 
*/

#ifndef RLC3_EXCEPTION_H
#define RLC3_EXCEPTION_H

//模拟异常 

#include"stdio.h"

char* ExceptionMessage = NULL;

#define THROW(message) ExceptionMessage = message;
#define CATCH if(ExceptionMessage!=NULL)
#define ERROR ExceptionMessage

#endif
