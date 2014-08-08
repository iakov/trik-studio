HEADERS += \
	$$PWD/tokenPatterns.h \
	$$PWD/parserError.h \
	$$PWD/textLanguageParser.h \
	$$PWD/textLanguageParserInterface.h \
	$$PWD/tokenType.h \
	$$PWD/ast/connection.h \
	$$PWD/ast/node.h \
	$$PWD/ast/range.h \
	$$PWD/ast/unaryOperator.h \
	$$PWD/ast/binaryOperator.h \
	$$PWD/ast/number.h \
	$$PWD/ast/unaryMinus.h \
	$$PWD/ast/not.h \
	$$PWD/ast/bitwiseNegation.h \
	$$PWD/ast/length.h \
	$$PWD/ast/addition.h \
	$$PWD/ast/subtraction.h \
	$$PWD/ast/multiplication.h \
	$$PWD/ast/division.h \
	$$PWD/ast/integerDivision.h \
	$$PWD/ast/modulo.h \
	$$PWD/ast/exponentiation.h \
	$$PWD/ast/bitwiseAnd.h \
	$$PWD/ast/bitwiseOr.h \
	$$PWD/ast/bitwiseXor.h \
	$$PWD/ast/bitwiseLeftShift.h \
	$$PWD/ast/bitwiseRightShift.h \
	$$PWD/ast/concatenation.h \
	$$PWD/ast/equality.h \
	$$PWD/ast/lessThan.h \
	$$PWD/ast/lessOrEqual.h \
	$$PWD/ast/inequality.h \
	$$PWD/ast/greaterThan.h \
	$$PWD/ast/greaterOrEqual.h \
	$$PWD/ast/integerNumber.h \
	$$PWD/ast/floatNumber.h \
	$$PWD/ast/fieldInitialization.h \
	$$PWD/ast/expression.h \
	$$PWD/ast/tableConstructor.h \
	$$PWD/ast/integerNumber.h \
	$$PWD/ast/floatNumber.h \
	$$PWD/ast/string.h \
	$$PWD/ast/true.h \
	$$PWD/ast/false.h \
	$$PWD/ast/nil.h \
	$$PWD/ast/temporaryToken.h \
	$$PWD/ast/temporaryPair.h \
	$$PWD/ast/temporaryList.h \
	$$PWD/details/lexer.h \
	$$PWD/details/token.h  \
	$$PWD/details/tokenStream.h  \
	$$PWD/details/parserCombinators.h \
	$$PWD/details/tokenParser.h \
	$$PWD/details/simpleParser.h \
	$$PWD/details/parserInterface.h \
	$$PWD/details/alternativeParser.h \
	$$PWD/details/transformingParser.h \
	$$PWD/details/concatenationParser.h \
	$$PWD/details/optionalParser.h \
	$$PWD/details/kleeneStarParser.h \
	$$PWD/details/functionTraits.h \
	$$PWD/details/parserRef.h \
	$$PWD/details/expressionParser.h \
	$$PWD/details/precedenceTable.h \

SOURCES += \
	$$PWD/tokenPatterns.cpp \
	$$PWD/parserError.cpp \
	$$PWD/textLanguageParser.cpp \
	$$PWD/ast/connection.cpp \
	$$PWD/ast/node.cpp \
	$$PWD/ast/range.cpp \
	$$PWD/details/lexer.cpp \
	$$PWD/details/token.cpp \
	$$PWD/details/tokenStream.cpp \
	$$PWD/details/precedenceTable.cpp \
