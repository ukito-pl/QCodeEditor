//
//  QCodeEditor - Widget to highlight and auto-complete code.
//  Copyright (C) 2016 Nicolas Kogler (kogler.cml@hotmail.com)
//
//  This file is part of QCodeEditor.
//
//  QCodeEditor is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with QCodeEditor.  If not, see <http://www.gnu.org/licenses/>.
//
//


#ifndef __KGL_QCODEEDITORHIGHLIGHTER_HPP__
#define __KGL_QCODEEDITORHIGHLIGHTER_HPP__


//
//  Included headers
//
#include <KGL/KGLConfig.hpp>
#include <KGL/Design/QSyntaxRule.hpp>
#include <KGL/Design/QCodeEditorDesign.hpp>
#include <QSyntaxHighlighter>
#include <QTextDocument>
#include <QObject>


namespace kgl {

    //
    // Forward declarations
    //
    class QCodeEditor;


    ///
    ///  @file      QCodeEditorHighlighter.hpp
    ///  @author    Nicolas Kogler
    ///  @date      October 5th, 2016
    ///  @class     QCodeEditorHighlighter
    ///  @brief     Highlights keywords, functions, ...
    ///
    class KGL_API QCodeEditorHighlighter : public QSyntaxHighlighter {
    Q_OBJECT
    public:

        ///
        ///  @fn    Constructor
        ///  @brief Initializes a new instance of QCodeEditorHighlighter.
        ///
        QCodeEditorHighlighter(QCodeEditor *parent);

        ///
        ///  @fn    Destructor
        ///  @brief Frees all resources allocated by QCodeEditorHighlighter.
        ///
        ~QCodeEditorHighlighter();


        ///
        ///  @fn    updateFormats
        ///  @brief Updates the text char formats.
        ///
        ///  Always call after setting new rules.
        ///
        void updateFormats();

        ///
        ///  @fn    setHighlighting
        ///  @brief Applies some visual styling to text in the current line.
        ///  @param start Start index to apply styling to
        ///  @param length Length of the text to style
        ///  @param format Format to apply
        ///
        void setHighlighting(int start, int length, const QTextCharFormat &format);


    signals:

        ///
        ///  @fn    onMatch : signal
        ///  @brief Will fire if a match is found.
        ///
        ///  The signal will only fire if the rule containing the match
        ///  has a valid and unique string identifier (e.g <rule id="foo">)
        ///
        ///  @param id The identifier of the sent match
        ///  @param sequence The matched sequence
        ///  @param line Zero-based number of line
        ///
        void onMatch(const QString &id, QString sequence, qint32 line);


    protected:

        ///
        ///  @fn    highlightBlock
        ///  @brief Highlights the given text line.
        ///  @param text Current line to process
        ///
        void highlightBlock(const QString &text) Q_DECL_OVERRIDE;


    private:

        //
        // Private class members
        //
        const QList<QSyntaxRule> *m_Rules;
        const QCodeEditorDesign *m_Design;
        const QCodeEditor *m_Parent;
        QList<QTextCharFormat> m_Formats;
    };
}


#endif  // __KGL_QCODEEDITORHIGHLIGHTER_HPP__
