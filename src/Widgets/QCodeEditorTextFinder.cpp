#include <KGL/Widgets/QCodeEditorTextFinder.hpp>

namespace kgl {

    QCodeEditorTextFinder::QCodeEditorTextFinder(QCodeEditor *parent)
        : QWidget(parent),
          m_Parent(parent)  {

        findDialog = new QDialog(this);
        findDialog->setWindowTitle("Find and replace");
        findDialog->resize(550,100);
        dialogLayout = new QGridLayout;
        replaceButton = new QPushButton("Replace");
        replaceAllButton = new QPushButton("Replace all");
        findLabel = new QLabel("Find:");
        textToFind = new QLineEdit();
        replaceLabel = new QLabel("Replace with:");
        textToReplace = new QLineEdit();
        infoLabel = new QLabel("1/3 ");
        findNextButton = new QPushButton("Find next");
        findPrevButton = new QPushButton("Find prev");
        dialogLayout->addWidget(findLabel,0,0);
        dialogLayout->addWidget(textToFind,0,1);
        dialogLayout->addWidget(textToReplace,1,1);
        dialogLayout->addWidget(findPrevButton,0,2);
        dialogLayout->addWidget(findNextButton,0,3);
        dialogLayout->addWidget(infoLabel,0,4);
        dialogLayout->addWidget(replaceLabel,1,0);
        dialogLayout->addWidget(replaceButton,1,2);
        dialogLayout->addWidget(replaceAllButton,1,3);
        findDialog->setLayout(dialogLayout);
        connect(textToFind,SIGNAL(textChanged(const QString &)),this, SLOT(onTextToFindChanged(const QString &)));
        connect(findNextButton,SIGNAL(pressed()),this,SLOT(findNext()));
        connect(findPrevButton,SIGNAL(pressed()),this,SLOT(findPrev()));
        connect(findDialog, SIGNAL(rejected()),this,SLOT(clearSelections()));
        connect(textToReplace,SIGNAL(textChanged(const QString &)),this, SLOT(onTextToReplaceChanged(const QString &)));
        connect(replaceButton,SIGNAL(pressed()),this,SLOT(replaceText()));
        connect(replaceAllButton,SIGNAL(pressed()),this,SLOT(replaceTextAll()));
        replaceButton->setEnabled(false);
        replaceAllButton->setEnabled(false);
        currentSelectionIdx = 0;
        currentSelectionRemoved = false;
        foundCount = 0;
    }

    void QCodeEditorTextFinder::show(){
        findDialog->show();
        onTextToFindChanged(textToFind->text());
    }

    void QCodeEditorTextFinder::onTextToFindChanged(const QString &text){

        clearSelections();
        findText(text);
        updateInfoLabel();

    }

    void QCodeEditorTextFinder::findText(QString text){
        int orgPos = m_Parent->textCursor().position();
        QColor color = Qt::gray;
        QString code = m_Parent->toPlainText();
        foundCount = 0;
        int pos = orgPos;
        bool wraped = false;
        bool end = false;
        while (pos >=0 && !text.isEmpty() && !end){
            pos = code.indexOf(text,pos); //-1 if not found
            if (wraped == true && (pos >= orgPos || pos < 0)){ //end of search
                end = true;
            }else if (pos >= 0){                //if found
                highlightText(pos + text.count(),pos, color);
                pos = pos + text.count();
                foundCount++;
            }else{  //end of sheet, set pos to begining and search till orgPos
                wraped = true;
                pos = 0;
            }
        }

        if (foundCount >0){
            currentSelectionIdx = 0;
            updateCurrentSelection();
        }
    }

    void QCodeEditorTextFinder::onTextToReplaceChanged(const QString &text){
        if (!text.isEmpty()){
            replaceButton->setEnabled(true);
            replaceAllButton->setEnabled(true);
        }else{
            replaceButton->setEnabled(false);
            replaceAllButton->setEnabled(false);
        }

    }

    void QCodeEditorTextFinder::replaceText(){
        if (textToReplace->text() != textToFind->text() && !m_Parent->textCursor().selectedText().isEmpty()){
            m_Parent->textCursor().insertText(textToReplace->text());
            selections.removeAt(currentSelectionIdx);
            currentSelectionRemoved = true;
            foundCount--;
            updateInfoLabel();
        }
    }

    void QCodeEditorTextFinder::replaceTextAll(){
        int val = m_Parent->verticalScrollBar()->value();
        if (textToReplace->text() != textToFind->text()){
            for (int i = 0; i < foundCount; i++){
                m_Parent->textCursor().insertText(textToReplace->text());
                findNext();
            }

            clearSelections();
            findText(textToFind->text());
            updateInfoLabel();
        }
        m_Parent->verticalScrollBar()->setValue(val);
    }

    void QCodeEditorTextFinder::highlightText(int begin, int end, QColor color){
        QTextEdit::ExtraSelection selection;
        QTextCursor cursor = m_Parent->textCursor();
        cursor.setPosition(begin);
        cursor.setPosition(end,QTextCursor::KeepAnchor);
        selection.format.setBackground(color);
        selection.cursor = cursor;
        selections.append(selection);
    }

    void QCodeEditorTextFinder::clearSelections(){
        selections.clear();
        QTextCursor cursor = m_Parent->textCursor();
        cursor.clearSelection();
        m_Parent->setTextCursor(cursor);
        m_Parent->setExtraSelections(selections);
    }

    void QCodeEditorTextFinder::updateCurrentSelection(){
        if (!selections.isEmpty()){
            m_Parent->setTextCursor(selections[currentSelectionIdx].cursor);
        }
        m_Parent->setExtraSelections(selections);
    }

    void QCodeEditorTextFinder::findNext(){
        if (foundCount > 0 && !currentSelectionRemoved){
            currentSelectionIdx++;
            currentSelectionIdx = currentSelectionIdx % foundCount;
        }else if(foundCount > 0 && currentSelectionRemoved){
            currentSelectionIdx = (currentSelectionIdx+foundCount) % foundCount;
            currentSelectionRemoved = false;
        }
        updateCurrentSelection();
        updateInfoLabel();
    }

    void QCodeEditorTextFinder::findPrev(){
        if (foundCount > 0 && !currentSelectionRemoved){
            currentSelectionIdx--;
            currentSelectionIdx = (currentSelectionIdx+foundCount) % foundCount;
        }else if(foundCount > 0 && currentSelectionRemoved){
            currentSelectionIdx--;
            currentSelectionIdx = (currentSelectionIdx+foundCount) % foundCount;
            currentSelectionRemoved = false;
        }
        updateCurrentSelection();
        updateInfoLabel();
    }

    void QCodeEditorTextFinder::updateInfoLabel(){
        if (foundCount > 0){
            infoLabel->setText((QString::number(currentSelectionIdx+1)) + "/" + (QString::number(foundCount)));
        }else{
            infoLabel->setText("0/0");
        }
    }

}
