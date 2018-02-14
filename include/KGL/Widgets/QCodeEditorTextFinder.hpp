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

    class KGL_API QCodeEditorTextFinder : public QWidget{
    Q_OBJECT
    public:
        QCodeEditorTextFinder(QCodeEditor *parent);
        void show();



    private slots:
        void onTextToFindChanged(const QString &text);
        void onTextToReplaceChanged(const QString &text);
        void findNext();
        void findPrev();
        void clearSelections();
        void replaceText();
        void replaceTextAll();

    private:
        QDialog* findDialog;
        QCodeEditor *m_Parent;
        QGridLayout *dialogLayout;
        QPushButton *replaceButton;
        QPushButton *replaceAllButton;
        QLabel *findLabel;
        QLineEdit *textToFind;
        QLabel *replaceLabel;
        QLineEdit *textToReplace;
        QLabel *infoLabel;
        QPushButton *findNextButton;
        QPushButton *findPrevButton;
        QList<QTextEdit::ExtraSelection> selections;
        int currentSelectionIdx;
        bool currentSelectionRemoved;
        int foundCount;
        void highlightText(int begin, int end, QColor color);
        void findText(QString text);
        void updateCurrentSelection();
        void updateInfoLabel();
    };




}
#endif // __KGL_QCODEEDITORTEXTFINDER_HPP__
