#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>
#include <QVector>
#include <QRegularExpressionMatchIterator>

class Highlighter : public QSyntaxHighlighter
{
  Q_OBJECT;

  public:
    Highlighter(QTextDocument *parent = 0);

  protected:
    void highlightBlock(const QString &text) override;
  private:
    struct HighlightingRule
    {
      QRegularExpression pattern;
      QTextCharFormat format;
    };
    QVector<HighlightingRule> v_highlightRules;

    QRegularExpression commentEndExpression;
    QRegularExpression commentStartExpression;

    QTextCharFormat multiplicationFormat;
    QTextCharFormat classFormat;
    QTextCharFormat memberFormat;
    QTextCharFormat numberFormat;
    QTextCharFormat keywordFormat;
    QTextCharFormat datatypeFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
};
