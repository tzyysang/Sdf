#ifndef SDFLEXER_H
#define SDFLEXER_H

/*
* Copyright 2019 Rochus Keller <mailto:me@rochus-keller.ch>
*
* This file is part of the Sdf (Standard Delay Format) parser library.
*
* The following is the license that applies to this copy of the
* library. For a license to use the library under conditions
* other than those described here, please email to me@rochus-keller.ch.
*
* GNU General Public License Usage
* This file may be used under the terms of the GNU General Public
* License (GPL) versions 2.0 or 3.0 as published by the Free Software
* Foundation and appearing in the file LICENSE.GPL included in
* the packaging of this file. Please review the following information
* to ensure GNU General Public Licensing requirements will be met:
* http://www.fsf.org/licensing/licenses/info/GPLv2.html and
* http://www.gnu.org/copyleft/gpl.html.
*/

#include <QObject>
#include <Sdf/SdfToken.h>
#include <QHash>
#include <QRegExp>

class QIODevice;

namespace Sdf
{
    class Errors;
    class FileCache;

    class Lexer : public QObject
    {
    public:
        explicit Lexer(QObject *parent = 0);

        void setStream( QIODevice*, const QString& sourcePath );
        bool setStream(const QString& sourcePath);
        void setErrors(Errors* p) { d_err = p; }
        void setCache(FileCache* p) { d_fcache = p; }
        void setIgnoreComments( bool b ) { d_ignoreComments = b; }
        void setPackComments( bool b ) { d_packComments = b; }

        Token nextToken();
        Token peekToken(quint8 lookAhead = 1);
        QList<Token> tokens( const QString& code );
        QList<Token> tokens( const QByteArray& code, const QString& path = QString() );
        static QByteArray getSymbol( const QByteArray& );
        static void parseComment( const QByteArray& str, int& pos, int& level );
    protected:
        Token nextTokenImp();
        int skipWhiteSpace();
        void nextLine();
        int lookAhead(int off = 1) const;
        Token token(TokenType tt, int len = 1, const QByteArray &val = QByteArray());
        Token identOrNumber();
        Token blockComment();
        Token lineComment();
        Token string();
    private:
        QIODevice* d_in;
        Errors* d_err;
        FileCache* d_fcache;
        QRegExp d_real;
        quint32 d_lineNr;
        quint16 d_colNr;
        QString d_sourcePath;
        QByteArray d_line;
        QList<Token> d_buffer;
        static QHash<QByteArray,QByteArray> d_symbols;
        Token d_lastToken;
        bool d_ignoreComments;  // don't deliver comment tokens
        bool d_packComments;    // Only deliver one Tok_Comment for /**/ instead of Tok_Lcmt and Tok_Rcmt
    };
}

#endif // SDFLEXER_H
