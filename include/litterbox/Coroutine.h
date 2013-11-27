#ifndef CORO_H
#define CORO_H

//! \file Coroutine.h
//! \author J Mills
//! \date 9/15/2013 

//! \addtogroup grpCoroutine
//\{

/*! Coroutine hack for implementing an interrupted finite state machine.
 * Modeled after Duff's Device, this is really a temporary solution and shouldn't be taken too seriously.  Ideally, I 
 * will have time to come back and revist this using some sort of stack instead of abusing jumptables.
 */

//! \name Coroutines types
//\{
//! The context acts as a container for the function's variables, allows us to reenter the coroutine and maintain those values.
#define CORO_CONTEXT            void*
//! The address of a context which is passed as a parameter to a coroutine. This allows us to work around the function stack.
#define CORO_CONTEXT_PARAM      void*& conParam
//\}

//! \name Persistent parameter set
//\{
//! Starts the defintion of a struct which will contain parameters that we want to be persistent between function cycles.
#define CORO_CONTEXT_BEGIN      struct ConTag { int line
//! Closes off the param struct and assign it to the context.
#define CORO_CONTEXT_END(x)     }* x = (ConTag *)conParam
//\}

//! \name Coroutine Function Control
//\{
//! Allocates the context to the param struct if this is the first time the function is called, and then begins switch(line).
#define CORO_BEGIN(x)           if(!x) { x = (ConTag *)(conParam = (void *)(new ConTag)); x->line = 0; } \
                                if(x) switch(x->line) { case 0:;

//! Ends the coroutine and returns val, and then deletes the context.
#define CORO_END(val)           } delete (ConTag *)conParam; conParam = 0; return(val)
//! Ends the coroutine, and then deletes the context.
#define CORO_END_VOID           } delete (ConTag *)conParam; conParam = 0; return
//! Yields the coroutine and returns a val while maintaining the state for reentry.
#define CORO_YIELD(val)         do {\
                            ((ConTag*) *conParam)->line = __LINE__;\
                            return(val); case __LINE__:;\
                            } while (0)
//! Yields the coroutine and maintains the state for reentry.
#define CORO_YIELD_VOID         do {\
                            ((ConTag *)conParam)->line = __LINE__;\
                            return; case __LINE__:;\
                            } while (0)
//\}

//! \name Interrupts
//\{
//! For use outside a coroutine to kill it.  Stops the coroutine, returns a value, and deletes the context. 
#define CORO_STOP(value)        do { delete (ConTag *)conParam; conParam = 0; return (value); } while (0)
//! For use outside a coroutine to kill it.  Stops the coroutine and deletes the context. 
#define CORO_STOP_VOID          do { delete (ConTag *)conParam; conParam = 0; return; } while (0)
//! Aborts coroutine.
#define CORO_ABORT(ctx)         do { delete ctx; ctx = 0; } while (0)
//\}

//\}
#endif //CORO_H
