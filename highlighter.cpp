#include "highlighter.hpp"

Highlighter::Highlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
  HighlightingRule rule;

  memberFormat.setForeground(QColor(220, 100, 100));
  numberFormat.setFontWeight(QFont::Bold);
  rule.pattern = QRegularExpression(QStringLiteral("(->)\\s*\\w+"));
  rule.format = memberFormat;
  v_highlightRules.append(rule);
  // rule.pattern = QRegularExpression(QStringLiteral("(->)\\s*\\w+\."));
  // rule.format = memberFormat;
  // v_highlightRules.append(rule);
  // rule.pattern = QRegularExpression(QStringLiteral("(->)\\s*\\w+\\("));
  // rule.format = memberFormat;
  // v_highlightRules.append(rule);
  // rule.pattern = QRegularExpression(QStringLiteral("(->)\\s*\\w+,"));
  // rule.format = memberFormat;
  // v_highlightRules.append(rule);

  datatypeFormat.setForeground(QColor(50, 200, 200));
  datatypeFormat.setFontWeight(QFont::Bold);
  const QString datatypePatterns[] =
  {
    QStringLiteral("\\bchar\\b"), QStringLiteral("\\bdouble\\b"), QStringLiteral("\\bint\\b"),
    QStringLiteral("\\blong\\b"), QStringLiteral("\\bshort\\b"), QStringLiteral("\\bbool\\b"),
    QStringLiteral("\\bunsigned\\b"), QStringLiteral("\\bvoid\\b"), QStringLiteral("\\bsigned\\b"),
    QStringLiteral("\\b[A-Za-z0-9_]+\\s+(?=[A-Za-z0-9_\\*\\&])"), QStringLiteral("public\\s+([A-Za-z0-9_,])+"),
    QStringLiteral("private\\s+([A-Za-z0-9_,])+"), QStringLiteral("protected\\s+([A-Za-z0-9_,])+"),
	 QStringLiteral("class\\s+([A-Za-z0-9_,])+"), QStringLiteral("struct\\s+([A-Za-z0-9_,])+")
  };
  for(const QString &pattern : datatypePatterns)
  {
    rule.pattern = QRegularExpression(pattern);
    rule.format = datatypeFormat;
    v_highlightRules.append(rule);
  }

  rule.pattern = QRegularExpression(QStringLiteral("[A-Za-z0-9_]+\\s*(?=\\*=)"));
  rule.format = multiplicationFormat;
  v_highlightRules.append(rule);

  keywordFormat.setForeground(QColor(200, 50, 200));
  keywordFormat.setFontWeight(QFont::Bold);
  const QString keywordPatterns[] =
  {
    QStringLiteral("\\bclass\\b"), QStringLiteral("\\bconst\\b"), QStringLiteral("\\benum\\b"),
    QStringLiteral("\\bexplicit\\b"), QStringLiteral("\\bfriend\\b"), QStringLiteral("\\binline\\b"),
    QStringLiteral("\\bnamespace\\b"), QStringLiteral("\\boperator\\b"), QStringLiteral("\\bprivate\\b"),
    QStringLiteral("\\bprotected\\b"), QStringLiteral("\\bpublic\\b"), QStringLiteral("\\bsignals\\b"),
    QStringLiteral("\\bslots\\b"), QStringLiteral("\\bstatic\\b"), QStringLiteral("\\bstruct\\b"),
    QStringLiteral("\\btemplate\\b"), QStringLiteral("\\btypedef\\b"), QStringLiteral("\\btypename\\b"),
    QStringLiteral("\\bunion\\b"), QStringLiteral("\\bvirtual\\b"), QStringLiteral("\\bvolatile\\b"),
    QStringLiteral("\\bnew\\b"), QStringLiteral("\\bdelete\\b"), QStringLiteral("\\breturn\\b"),
    QStringLiteral("\\<\\<"), QStringLiteral("\\&"), QStringLiteral("\\."), QStringLiteral("->"), QStringLiteral("="),
    QStringLiteral("\\*")

  };
  for(const QString &pattern : keywordPatterns)
  {
    rule.pattern = QRegularExpression(pattern);
    rule.format = keywordFormat;
    v_highlightRules.append(rule);
  }
  rule.pattern = QRegularExpression(QStringLiteral("#.*\\b"));
  rule.format = keywordFormat;
  v_highlightRules.append(rule);

  numberFormat.setForeground(QColor(200, 150, 0));
  numberFormat.setFontWeight(QFont::Bold);
  rule.pattern = QRegularExpression(QStringLiteral("[0-9]+"));
  rule.format = numberFormat;
  v_highlightRules.append(rule);

  multiplicationFormat.setForeground(QColor(240, 240, 240));
  multiplicationFormat.setFontWeight(QFont::Bold);
  rule.pattern = QRegularExpression(QStringLiteral("(=\\s*)[A-Za-z0-9_]+(?=\\s*\\*)"));
  rule.format = multiplicationFormat;
  v_highlightRules.append(rule);
  rule.pattern = QRegularExpression(QStringLiteral("[A-Za-z_]+[0-9]+|[0-9]+[A-Za-z_]+"));
  rule.format = multiplicationFormat;
  v_highlightRules.append(rule);

  functionFormat.setForeground(QColor(50, 120, 200));
  rule.pattern = QRegularExpression(QStringLiteral("\\b[A-Za-z0-9_]+(?=\\()"));
  rule.format = functionFormat;
  v_highlightRules.append(rule);

  quotationFormat.setForeground(QColor(100, 200, 50));
  rule.pattern = QRegularExpression(QStringLiteral("<.*>"));
  rule.format = quotationFormat;
  v_highlightRules.append(rule);
  rule.pattern = QRegularExpression(QStringLiteral("\"([^\"]*\\s*)\""));
  rule.format = quotationFormat;
  v_highlightRules.append(rule);
  rule.pattern = QRegularExpression(QStringLiteral("'([^']*\\s*)'"));
  rule.format = quotationFormat;
  v_highlightRules.append(rule);

  singleLineCommentFormat.setForeground(Qt::gray);
  rule.pattern = QRegularExpression(QStringLiteral("//[^\n]*"));
  rule.format = singleLineCommentFormat;
  v_highlightRules.append(rule);

  multiLineCommentFormat.setForeground(Qt::gray);

  commentStartExpression = QRegularExpression(QStringLiteral("/\\*"));
  commentEndExpression = QRegularExpression(QStringLiteral("\\*/"));
}

void Highlighter::highlightBlock(const QString &text)
{
  for(const HighlightingRule &rule : qAsConst(v_highlightRules))
  {
    QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
    while(matchIterator.hasNext())
    {
      QRegularExpressionMatch match = matchIterator.next();
      setFormat(match.capturedStart(), match.capturedLength(), rule.format);
    }
  }
  setCurrentBlockState(0);
  int startIndex = 0;
  if(previousBlockState() != 1)
  {
    startIndex = text.indexOf(commentStartExpression);
  }
  while(startIndex >= 0)
  {
    QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
    int endIndex = match.capturedStart();
    int commentLength = 0;
    if(endIndex == -1)
    {
      setCurrentBlockState(1);
      commentLength = text.length() - startIndex;
    }
    else
    {
      commentLength = endIndex - startIndex + match.capturedLength();
    }
    setFormat(startIndex, commentLength, multiLineCommentFormat);
    startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
  }
}
