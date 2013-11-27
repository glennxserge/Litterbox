#ifndef ASSERT_H
#define ASSERT_H

#include <nds.h>
#include <stdio.h>

//! \file Assert.h
//! \author J Mills
//! \date 9/15/2013 

/*! This function is called by the ASSERT macro and reports failure 
 *  \param *file is the \__FILE\__ preprocessor value
 *  \param line is the \__LINE\__ preprocessor value
 *  \param *cond  is the expression evaluated 
 */
void assertFailed(char *file, int line, char *cond);

//! \name Assert Macros
//\{
//! converts a constant char array to a preprocessor string
#define STRING(a)	#a
//! checks the expression and throws assertFailed if it is false
#define ASSERT(expr) 							\
	if(!(expr)) {								\
		assertFailed(__FILE__, __LINE__, STRING(expr)); \
		while(1) {;} 							\
	}

//\}

#endif //ASSERT_H