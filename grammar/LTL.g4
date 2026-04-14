grammar LTL;

formula
    : LPAREN formula RPAREN     # paren
    | NOT formula               # not
    | NEXT formula              # next
    | ALWAYS formula            # always
    | EVENTUALLY formula        # eventually
    | formula AND formula       # and
    | formula OR formula        # or
    | formula IMPLIES formula   # implies
    | formula UNTIL formula     # until
    | TRUE                      # trueLit
    | FALSE                     # falseLit
    | ATOM                      # atomExpr
    ;

TRUE: 'true';
FALSE: 'false';
ATOM: [a-z]+;
NOT: '!';
AND: '/\\';
OR: '\\/';
IMPLIES: '->';
NEXT: 'X';
ALWAYS: 'G';
EVENTUALLY: 'F';
UNTIL: 'U';
LPAREN: '(';
RPAREN: ')';

WS: [ \t\r\n]+ -> skip;

