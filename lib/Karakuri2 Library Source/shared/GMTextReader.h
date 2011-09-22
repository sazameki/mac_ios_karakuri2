/*!
    @file   GMTextReader.h
    @author numata
    @date   09/07/29
    
    Please write the description of this class.
 */

#ifndef __GM_TEXT_READER_H__
#define __GM_TEXT_READER_H__


#include "GMObject.h"
#include <string>


/*!
    @class  GMTextReader
    @group  System
    <p>UTF-8 形式のテキストファイルを、1行ずつ読み込むためのクラスです。</p>
    <p>改行コードには LF のみを用いてください。</p>
 */
class GMTextReader : public GMObject {

    void*       mFileData;	//!< Objective-C でファイルデータを表すオブジェクトへのポインタ
	unsigned	mLength;	//!< ファイルサイズ
	unsigned	mPos;		//!< ファイル上の現在の位置

    bool        mHasMoreLines;  //!< 読み込める対象があるかどうかのフラグ
    std::string mNextLine;      //!< 次にリターンする文字列
    
public:
    /*!
        @task コンストラクタ
     */
    
    /*!
        @method GMTextReader
        指定されたファイル名のテキストファイルを読み込み用に開きます。
     */
	GMTextReader(const std::string& filename);
	virtual ~GMTextReader();
  
public:
    /*!
        @task 基本の関数
     */
    /*!
        @method     getNextLine
        @abstract   次の行の文字列を読み込みます。行末の改行文字は含まれません。
     */
    std::string     getNextLine();

    /*!
        @method     hasMoreLines
        @abstract   getNextLine() 関数で読み込むことができる行が残っているかどうかをリターンします。
     */
    bool            hasMoreLines() const;
    
private:
	bool    __readLine(std::string* str);     // ファイルから文字列を1行分読み込み、与えられた string クラスのポインタに値を代入します。

};

#endif  //#ifndef __GM_TEXT_READER_H__

