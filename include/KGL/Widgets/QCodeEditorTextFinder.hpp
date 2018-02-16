#ifndef __KGL_QCODEEDITORTEXTFINDER_HPP__
#define __KGL_QCODEEDITORTEXTFINDER_HPP__



#include <KGL/KGLConfig.hpp>
#include <KGL/Widgets/QCodeEditor.hpp>
#include <QWidget>
#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QObject>
#include <QList>
#include <QScrollBar>


namespace kgl {

    ///
    ///  @file      QCodeEditorTextFinder.hpp
    ///  @author    Marek Bula
    ///  @date      February 16th, 2086
    ///  @class     QCodeEditorTextFinder
    ///  @brief     Simple 'search and replace' dialog window.
    ///
    class KGL_API QCodeEditorTextFinder : public QWidget{
    Q_OBJECT
    public:

        ///
        ///  @fn    Constructor
        ///  @brief Initializes a new instance of QCodeEditorTextFinder.
        ///
        QCodeEditorTextFinder(QCodeEditor *parent);

        ///
        ///  @fn    Destructor
        ///  @brief Frees all resources allocated by QCodeEditor.
        ///
        ~QCodeEditorTextFinder();

        ///
        ///  @fn    show
        ///  @brief Shows 'search and replace' dialog window.
        ///
        void show();

    private slots:

        ///
        ///  @fn    onTextToFindChanged
        ///  @brief Clear current selections, find and select text and update info labels.
        ///
        void onTextToFindChanged(const QString& text);

        ///
        ///  @fn    onTextToReplaceChanged
        ///  @brief Activate/deactivate  'replace' buttons.
        ///
        void onTextToReplaceChanged(const QString& text);

        ///
        ///  @fn    findNext
        ///  @brief Go to next occurance of searched phrase.
        ///
        void findNext();

        ///
        ///  @fn    findPrev
        ///  @brief Go to previous occurance of searched phrase.
        ///
        void findPrev();

        ///
        ///  @fn    clearSelections
        ///  @brief Clear all selections of previously found phrase.
        ///
        void clearSelections();

        ///
        ///  @fn    replaceText
        ///  @brief Replace current selection with text from 'm_TextToReplace'.
        ///
        void replaceText();

        ///
        ///  @fn    replaceTextAll
        ///  @brief Replace all selections with text from 'm_TextToReplace'.
        ///
        void replaceTextAll();

    private:

        ///
        ///  @fn    highlightText
        ///  @brief Select and highlight text with specified color and save its selection to 'm_Selections'.
        ///  @param begin index start position of highlighting text
        ///  @param end index finish position of highlighting text
        ///  @param color highlight color
        ///
        void highlightText(int begin, int end, QColor color);

        ///
        ///  @fn    findText
        ///  @brief Find specified text, select it and save its selection to 'm_Selections'.
        ///  @param text phrase to find in editor text
        ///
        void findText(QString text);

        ///
        ///  @fn    updateCurrentSelection
        ///  @brief Update current selection according to m_CurrentSelectionIdx.
        ///
        void updateCurrentSelection();

        ///
        ///  @fn    updateInfoLabel
        ///  @brief Show updated information about search results.
        ///
        void updateInfoLabel();

        QDialog* m_FindDialog;
        QCodeEditor *m_Parent;
        QGridLayout *m_DialogLayout;
        QPushButton *m_ReplaceButton;
        QPushButton *m_ReplaceAllButton;
        QLabel *m_FindLabel;
        QLineEdit *m_TextToFind;
        QLabel *m_ReplaceLabel;
        QLineEdit *m_TextToReplace;
        QLabel *m_InfoLabel;
        QPushButton *m_FindNextButton;
        QPushButton *m_FindPrevButton;
        QList<QTextEdit::ExtraSelection> m_Selections;  ///< holds selections for all occurences of searched phrase
        int m_CurrentSelectionIdx;                      ///< index of selection that is currently selected
        bool m_CurrentSelectionRemoved;                 ///< indicates whether current selection has been removed
        int m_FoundCount;                               ///< number of occurences of searched phrase

    };




}
#endif // __KGL_QCODEEDITORTEXTFINDER_HPP__
