//
//  GMException.h
//  Game Framework
//
//  Created by numata on Jan 03, 2011.
//  Copyright 2010-2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_EXCEPTION_H__
#define __GM_EXCEPTION_H__


#include "GMObject.h"
#include <exception>
#include <string>


/*!
    @class  GMException
    @group  Error Handling
 */
class GMException : public std::exception, public GMObject {

protected:
    std::string     mMessage;
    
public:
    GMException() throw();
    GMException(const char* format, ...) throw();
    GMException(const std::string& message) throw();
    virtual ~GMException() throw();
    
public:
    virtual std::string getExceptionClassName() const;
    virtual const char* what() const throw();
    
};

/*!
    @class  GMArithmeticException
    @group  Error Handling
 */
class GMArithmeticException : public GMException {

public:
    GMArithmeticException() throw();
    GMArithmeticException(const char* format, ...) throw();
    GMArithmeticException(const std::string& message) throw();    
    
public:
    virtual std::string getExceptionClassName() const { return "GMArithmeticException"; }

};


/*!
    @class  GMInvalidOperationException
    @group  Error Handling
 */
class GMInvalidOperationException : public GMException {
    
public:
    GMInvalidOperationException() throw();
    GMInvalidOperationException(const char* format, ...) throw();
    GMInvalidOperationException(const std::string& message) throw();    
    
public:
    virtual std::string getExceptionClassName() const { return "GMInvalidOperationException"; }
    
};


/*!
    @class  GMOutOfMemoryException
    @group  Error Handling
 */
class GMOutOfMemoryException : public GMException {
    
public:
    GMOutOfMemoryException() throw();
    GMOutOfMemoryException(const char* format, ...) throw();
    GMOutOfMemoryException(const std::string& message) throw();    
    
public:
    virtual std::string getExceptionClassName() const { return "GMOutOfMemoryException"; }
    
};


#endif  //#ifndef __GM_EXCEPTION_H__


