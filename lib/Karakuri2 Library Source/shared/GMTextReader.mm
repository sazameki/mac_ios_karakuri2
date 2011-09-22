/*!
    @file   GMTextReader.cpp
    @author numata
    @date   09/07/29
 */

#include "GMTextReader.h"

#import <Foundation/Foundation.h>
#include <sstream>
#include "GMException.h"
#include <TargetConditionals.h>


/*!
    @method GMTextReader
    Constructor
 */
GMTextReader::GMTextReader(const std::string& filename)
{
    NSString* filenameStr = [[NSString alloc] initWithCString:filename.c_str() encoding:NSUTF8StringEncoding];
	NSString* path = [[NSBundle mainBundle] pathForResource:filenameStr ofType:nil];

    if (!path) {
        const char* errorFormat = "GMTextReader: Failed to load text named \"%s\". Please check the file existence.";
        throw GMException(errorFormat, filename.c_str());
    }

	mFileData = nil;
	if (path) {
		mFileData = [[NSData alloc] initWithContentsOfMappedFile:path];
		mLength = (unsigned)[(NSData*)mFileData length];
	}
	mPos = 0;
	[filenameStr release];
    
    mHasMoreLines = __readLine(&mNextLine);
}

/*!
    @method ~GMTextReader
    Destructor
 */
GMTextReader::~GMTextReader()
{
    [(NSData*)mFileData release];
}

bool GMTextReader::hasMoreLines() const
{
    return mHasMoreLines;
}

std::string GMTextReader::getNextLine()
{
    if (!mHasMoreLines) {
        throw GMException("GMTextReader: Attempted to read after EOF.");
    }
    
    std::string ret = mNextLine;
    mHasMoreLines = __readLine(&mNextLine);
    return ret;
}

bool GMTextReader::__readLine(std::string* str)
{
    if (!mFileData) {
		return false;
	}
	if (mPos >= mLength) {
		return false;
	}
	std::stringstream ret;
	unsigned char* p = (unsigned char*) [(NSData*)mFileData bytes];
	while (mPos < mLength) {
		if (p[mPos] == '\n') {
			mPos++;
			break;
		}
		ret << p[mPos];
		mPos++;
	}
	*str = ret.str();
	return true;    
}


