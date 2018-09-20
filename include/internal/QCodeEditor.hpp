#pragma once

// Qt
#include <QTextEdit>

class QCompleter;
class QLineNumberArea;
class QSyntaxStyle;
class QStyleSyntaxHighlighter;

/**
 * @brief Class, that describes code editor.
 */
class QCodeEditor : public QTextEdit
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     * @param widget Pointer to parent widget.
     */
    explicit QCodeEditor(QWidget* widget=nullptr);

    // Disable copying
    QCodeEditor(const QCodeEditor&) = delete;
    QCodeEditor& operator=(const QCodeEditor&) = delete;

    /**
     * @brief Method for getting first visible block
     * index.
     * @return Index.
     */
    int getFirstVisibleBlock();

    /**
     * @brief Method for setting highlighter.
     * @param highlighter Pointer to syntex highlighter.
     */
    void setHighlighter(QStyleSyntaxHighlighter* highlighter);

    /**
     * @brief Method for setting syntax sty.e.
     * @param style Pointer to syntax style.
     */
    void setSyntaxStyle(QSyntaxStyle* style);

    /**
     * @brief Method setting auto parentheses enabled.
     */
    void setAutoParentheses(bool enabled);

    /**
     * @brief Method for getting is auto parentheses enabled.
     * Default value: true
     */
    bool autoParentheses() const;

    /**
     * @brief Method for setting tab replacing
     * enabled.
     */
    void setTabReplace(bool enabled);

    /**
     * @brief Method for getting is tab replacing enabled.
     * Default value: true
     */
    bool tabReplace() const;

    /**
     * @brief Method for setting amount of spaces, that will
     * replace tab.
     * @param val Number of spaces.
     */
    void setTabReplaceSize(int val);

    /**
     * @brief Method for getting number of spaces, that will
     * replace tab if `tabReplace` is true.
     * Default: 4
     */
    int tabReplaceSize() const;

    /**
     * @brief Method for setting auto indentation enabled.
     */
    void setAutoIndentation(bool enabled);

    /**
     * @brief Method for getting is auto indentation enabled.
     * Default: true
     */
    bool autoIndentation() const;

    /**
     * @brief Method for setting completer.
     * @param completer Pointer to completer object.
     */
    void setCompleter(QCompleter* completer);

    /**
     * @brief Method for getting completer.
     * @return Pointer to completer.
     */
    QCompleter* completer() const;

public slots:

    /**
     * @brief Slot, that performs insertion of
     * completion info into code.
     * @param s Data.
     */
    void insertCompletion(QString s);

    /**
     * @brief Slot, that performs update of
     * internal editor viewport based on line
     * number area width.
     */
    void updateLineNumberAreaWidth(int);

    /**
     * @brief Slot, that performs update of some
     * part of line number area.
     * @param rect Area that has to be updated.
     */
    void updateLineNumberArea(const QRect& rect);

    /**
     * @brief Slot, that will proceed extra selection
     * for current cursor position.
     */
    void updateExtraSelection();

    /**
     * @brief Slot, that will update editor style.
     */
    void updateStyle();

protected:
    void paintEvent(QPaintEvent* e) override;

    void resizeEvent(QResizeEvent* e) override;

    void keyPressEvent(QKeyEvent* e) override;

    void focusInEvent(QFocusEvent *e) override;

private:

    /**
     * @brief Method, that performs completer processing.
     * Returns true if event has to be dropped.
     * @param e Pointer to key event.
     * @return Shall event be dropped.
     */
    bool proceedCompleterBegin(QKeyEvent *e);
    void proceedCompleterEnd(QKeyEvent* e);

    QChar charUnderCursor(int offset = 0) const;

    QString textUnderCursor() const;

    /**
     * @brief Method, that adds highlighting of
     * currently selected line to extra selection list.
     */
    void highlightCurrentLine(QList<QTextEdit::ExtraSelection>& extraSelection);

    /**
     * @brief Method, that adds highlighting of
     * parenthesis if available.
     */
    void highlightParenthesis(QList<QTextEdit::ExtraSelection>& extraSelection);

    QStyleSyntaxHighlighter* m_highlighter;
    QSyntaxStyle* m_syntaxStyle;
    QLineNumberArea* m_lineNumberArea;
    QCompleter* m_completer;

    bool m_autoIndentation;
    bool m_autoParentheses;
    bool m_replaceTab;
    QString m_tabReplace;
};

