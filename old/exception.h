/*
	Name: exception.h
	Copyright: GPL 3.0
	Author: ������ 
	Date: 26/03/23 21:26
	Description: ģ���쳣 
*/

#ifndef RLC3_EXCEPTION_H
#define RLC3_EXCEPTION_H

//ģ���쳣 

#include"stdio.h"

char* ExceptionMessage = NULL;

#define THROW(message) ExceptionMessage = message;
#define CATCH if(ExceptionMessage!=NULL)
#define ERROR ExceptionMessage

#endif
