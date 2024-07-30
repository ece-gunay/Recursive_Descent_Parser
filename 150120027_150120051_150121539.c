 #include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_TOKEN_LENGTH 100

typedef struct {
    char value[MAX_TOKEN_LENGTH];
} Token;


int rightph[100];
int leftph[100];
static int count = 0;
static int counter = 0;
static Token LastToken;


void print4();
void printRightPar();
Token compareLastToken();
void Program();
void TopLevelForm();
void SecondLevelForm();
void Definition();
void DefinitionRight();
void ArgList();
void Statements();
void Expressions();
void Expression();
void Expr();
void FunCall();
void LetExpression();
void LetExpr();
void VarDefs();
void VarDef();
void CondExpression();
void CondBranches();
void CondBranch();
void IfExpression();
void EndExpression();
void BeginExpression();
int single_digit_num(char myChar);
int is_ok(char myChar);
void print4();



FILE *file; // Global variable to hold the file pointer
FILE *output;

int isKeyword(Token token){
	if (!strcmp(token.value, "if")|| !strcmp(token.value, "cond")||
     !strcmp(token.value, "let")||!strcmp(token.value, "define")||!strcmp(token.value, "begin"))
		return 1;
	return 0;
}

int is_character(Token token) {



    int len = strlen(token.value);
    // 'ALL_UNICODE' condition
    if(len == 3) {
        if(token.value[0] == '\'' && token.value[2] == '\'') {
            return 1;
        }

    }
    // '\'' and '\\'  conditions
    else if(len == 4) {
        if((token.value[0] == '\'' && token.value[4] == '\'' && token.value[1] == '\\' && token.value[2] == '\'')
           || ( token.value[0] == '\'' && token.value[1] == '\\' && token.value[2] == '\\' && token.value[4] == '\'' )) {
            return 1;
        }
        else return 0;
    }
    else
        return 0;

}

int single_digit_num(char myChar) {
    int i, len = 1;
    if(len == 1) {
        if (   myChar != '0' && myChar != '1' && myChar != '2'
			&& myChar != '3' && myChar != '4' && myChar != '5'
			&& myChar != '6' && myChar != '7' && myChar != '8'
			&& myChar != '9') {
			    return 0;
                    }
        return 1;
    }
    return 0;
}

int is_floatingNumber(Token token){

	int i,j,k,l,m,n,o,u,p,sasa,lele,baba,gunay,nene,bebe,gege,donmez,mert,ece,erkut,muslu,len = strlen(token.value);
    int x;
    //check "-" or "+" 0. index
    if(is_decimal(token.value) == 1 || is_binary(token.value) == 1 || is_hexadecimal(token.value) == 1) {
        return 0;
    }
	if(token.value[0] == '-' || token.value[0] == '+' ){
        //check "." 1. index
        if(token.value[1] == '.') {
            if(len == 2) {
                return 0;
            }
            for(i = 2; i<len;i++) {
                //check is digit

                if(single_digit_num(token.value[i]) == 1) {

                }
                // check exponent
                else if (token.value[i] == 'e' || token.value[i] == 'E') {
                    //check "-" or "+"
                    if(token.value[i+1] == '-' || token.value[i+1] == '+') {
                        if(token.value[i+2] == NULL) {
                            return 0;
                        }
                        for(l = i+2;l<len;l++) {
                            //check is digit
                            if(single_digit_num(token.value[l]) != 1) {
                                //it is not float
                                return 0;
                            }
                        }
                        //it is float
                        return 1;
                    }
                    else if (token.value[i+1] != '-' && token.value[i+1] != '+') {
                        for(m = i+1; m<len;m++) {
                            if(single_digit_num(token.value[m]) != 1) {
                                return 0;
                            }
                        }
                        return 1;
                    }
                }
                //null condition after digit
                else if (token.value[i+1] == NULL) {
                    return 1;
                }
                else {
                    return 0;
                }


            }
            return 1;

        }
        //   -.   initial condition
        else if(token.value[1] != '.') {
                //after -. must be digit
            if(single_digit_num(token.value[1])!= 1) {
                return 0;
            }

            for(j=1;j<len;j++) {

                if(single_digit_num(token.value[j]) == 1) {

                }
                // -.5e  or -.5E condition checking
                else if (token.value[j] == 'e' || token.value[j] == 'E') {
                        //-.5e- or -.5e+ condition checking
                    if(token.value[j+1] == '-' || token.value[j+1] == '+') {
                        if(single_digit_num(token.value[j+2])!= 1) {
                            return 0;
                        }
                        for(o = j+2;o <len;o++) {
                            if(single_digit_num(token.value[o]) != 1) {
                                return 0;
                            }
                        }
                        return 1;
                    }
                // -.5e5 or -.5E5 condition checking
                    else if (token.value[j+1] != '-' && token.value[j+1] != '+') {
                        if(single_digit_num(token.value[j+1]) != 1) {
                            return 0;
                        }
                        for(u = j+1; u<len;u++) {
                            if(single_digit_num(token.value[u]) != 1) {
                                return 0;
                            }
                        }
                        return 1;
                    }
                }
                //checking -5. condition
                else if ( token.value[j] == '.') {
                    if(single_digit_num(token.value[j+1]) != 1) {
                        return 0;
                    }
                    for(sasa = j+1;sasa <len;sasa++) {
                        if(single_digit_num(token.value[sasa]) == 1) {

                        }
                        //checking -5.5e or -5.5E condition
                        else if (token.value[sasa] == 'e' || token.value[sasa] == 'E') {
                                //checking -5.5e- or -5.5e+ condition
                            if(token.value[sasa+1] == '-' || token.value[sasa+1] == '+' ) {
                                if(single_digit_num(token.value[sasa+2]) != 1) {
                                    return 0;
                                }
                                for(baba = sasa+2;baba<len;baba++) {
                                    if(single_digit_num(token.value[baba]) != 1) {
                                        return 0;
                                    }
                                }
                                return 1;
                            }
                        //checking -5.5e5 or +5.5e5 condition
                            else if (token.value[sasa+1] != '-' && token.value[sasa+1] != '+') {
                                if(single_digit_num(token.value[sasa+1]) != 1) {
                                    return 0;
                                }
                                for(lele = sasa+1;lele<len;lele++) {
                                    if(single_digit_num(token.value[lele]) != 1) {
                                        return 0;
                                    }
                                }
                                return 1;
                            }
                        }
                        //checking -5.5 condition
                        else if (token.value[sasa+1] == NULL ){
                            return 1;
                        }
                        else {
                            return 0;
                        }
                    }
                }
                else {
                    return 0;
                }
            }
            return 1;
        }
	}
    //epsilon initial condition
	else if(token.value[0] != '-' && token.value[0] != '+') {
        //number initial condition
        if(single_digit_num(token.value[0]) == 1) {
            for(gege = 0; gege<len;gege++) {
                if(single_digit_num(token.value[gege]) == 1) {

                }
                //5. condition
                else if (token.value[gege] == '.') {
                    if(single_digit_num(token.value[gege+1]) != 1) {
                        return 0;
                    }
                    for(nene = gege+1;nene<len;nene++) {
                        if(single_digit_num(token.value[nene]) == 1) {

                        }
                        //5.5e or 5.5E condition
                        else if(token.value[nene] == 'e' || token.value[nene] == 'E') {
                                //5.5e- or 5.5e+ condition
                            if(token.value[nene+1] == '-' || token.value[nene+1] == '+') {
                                if(single_digit_num(token.value[nene+2]) != 1) {
                                    return 0;
                                }
                                for(donmez = nene+2; donmez<len; donmez++) {
                                    if(single_digit_num(token.value[donmez]) != 1) {
                                        return 0;
                                    }
                                }
                                return 1;
                            }
                        }
                        //5.5 condition
                        else if (token.value[nene] == NULL) {
                            return 1;
                        }
                        else {
                            return 0;
                        }
                    }
                }
                //5e or 5E condition
                else if (token.value[gege] == 'e' || token.value[gege] == 'E') {
                        //5e- or 5e+ condition
                    if(token.value[gege+1] == '-' || token.value[gege+1] == '+') {
                        if(single_digit_num(token.value[gege+2]) != 1) {
                            return 0;
                        }
                            //5e-5 condition
                        for(ece = gege+2;ece<len;ece++) {
                            if(single_digit_num(token.value[ece]) != 1) {
                                return 0;
                            }
                        }
                        return 1;
                    }
                    //5e5 condition
                    else if (token.value[gege+1] != '-' && token.value[gege+1] != '+') {
                        if(single_digit_num(token.value[gege+2]) != 1) {
                            return 0;
                        }
                        for(mert = gege+1;mert<len;mert++) {
                            if(single_digit_num(token.value[mert]) != 1) {
                                return 0;
                            }
                        }
                        return 1;
                    }
                }
                else {
                    return 0;
                }
            }
        }
        // . initial condition
        else if(token.value[0] == '.') {
            if(single_digit_num(token.value[1]) != 1) {
                return 0;
            }
            //.5 condition
            for(erkut = 1;erkut<len;erkut++) {
                if(single_digit_num(token.value[erkut]) == 1) {

                }
                //.5e or .5E condition
                else if(token.value[erkut] == 'e' || token.value[erkut] == 'E') {
                        //.5e- or .5+ condition
                    if(token.value[erkut+1] == '-' || token.value[erkut+1] == '+') {
                        if(single_digit_num(token.value[erkut+2]) != 1) {
                            return 0;
                        }
                            //.5e-5 condition
                        for(muslu = erkut+2;muslu<len;muslu++) {
                            if(single_digit_num(token.value[muslu]) != 1) {
                                return 0;
                            }
                        }
                        return 1;
                    }
                    //.5e5 condition
                    else if (token.value[erkut+1] != '-' && token.value[erkut+1] != '+') {
                        if(single_digit_num(token.value[erkut+1]) != 1) {
                            return 0;
                        }
                        for(gunay = erkut+1;gunay<len;gunay++) {
                            if(single_digit_num(token.value[gunay]) != 1) {
                                return 0;
                            }

                        }
                        return 1;
                    }
                }
                return 1;
            }
        }
    }
}

int is_string(Token token) {
    int len = strlen(token.value);

    //NULL string literal condition


    //checking first and last indices is "
    if(token.value[0] == '"' && token.value[len-1] == '"') {

        return 1;
    }

    else
        return 0;
}

int is_decimal(Token token){

	int i, len = strlen(token.value);

	if (len == 0)
		return 0;
    // if length of string is 1, check without loop
    if(len == 1) {

        if (   token.value[0] != '0' && token.value[0] != '1' && token.value[0] != '2'
			&& token.value[0] != '3' && token.value[0] != '4' && token.value[0] != '5'
			&& token.value[0] != '6' && token.value[0] != '7' && token.value[0] != '8'
			&& token.value[0] != '9') {

			    return 0;
                    }
        else {

            return 1;
        }


    }
    //checking string is binary or hexadecimal first, then check decimal
    if(!is_binary(token.value) && !is_hexadecimal(token.value) && len != 1) {

        if(len > 1) {
                //-|+|epsilon condition
            if (token.value[0] == '-' || token.value[0] == '+' ) {

                for (i =1; i < len; i++) {

                    if (token.value[i] != '0' && token.value[i] != '1' && token.value[i] != '2'
                    && token.value[i] != '3' && token.value[i] != '4' && token.value[i] != '5'
                    && token.value[i] != '6' && token.value[i] != '7' && token.value[i] != '8'
                    && token.value[i] != '9' ) {
                        return 0;
                    }

                }
                return 1;
            }
                //-|+|epsilon condition
            else if (token.value[0] != '-' && token.value[0] != '+') {
                for (int x = 0 ; x < len+30 ; x++) {

                    if (token.value[x] != '1' && token.value[x] != '0' && token.value[x] != '2'
                && token.value[x] != '3' && token.value[x] != '4' && token.value[x] != '5'
                && token.value[x] != '6' && token.value[x] != '7' && token.value[x] != '8'
                && token.value[x] != '9' ) {

                        return 0;

                    }

                }

                return 1;

            }

        }

    }

}

int isBoolean(Token token) {
    if(!strcmp(token.value, "true") || !strcmp(token.value, "false"))
        return 1;
    return 0;
}

int is_binary(Token token) {
    int i, len = strlen(token.value);

	if (len == 0){return 0;}
    if(len > 2 ) {
            //checking first 2 indices.
        if((token.value[0] == '0' && token.value[1] == 'b')) {
                //checking rest of indices is 1 or 0
            for (i = 2; i < len; i++) {
                if (token.value[i] != '0' && token.value[i] != '1') {

                    return 0;
                }
            }
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }



}

int is_hexadecimal(Token token) {
    int i, len = strlen(token.value);

	if (len == 0){return 0;}

    if(len > 2 ) {
            //checking first 2 indices
        if((token.value[0] == '0' && token.value[1] == 'x')) {
            for (i = 2; i < len; i++) {
                //checking rest of indices is appropriate for hexadecimal number
                if (token.value[i] != '0' && token.value[i] != '1' && token.value[i] != '3' && token.value[i] != '4' &&
                    token.value[i] != '5' && token.value[i] != '6' && token.value[i] != '7' && token.value[i] != '8' &&
                    token.value[i] != '9' && token.value[i] != 'A' && token.value[i] != 'B' && token.value[i] != 'C' &&
                    token.value[i] != 'D' && token.value[i] != 'E' && token.value[i] != 'F' && token.value[i] != 'a' &&
                    token.value[i] != 'b' && token.value[i] != 'c' && token.value[i] != 'd' && token.value[i] != 'e' &&
                    token.value[i] != 'f' && token.value[i] != '2') {
                        return 0;
                }
            }
            return 1;
        }
        else
            return 0;
    }
    else
        return 0;

}

int is_ok(char myChar) {

        if(myChar == '.' || myChar == '-' || myChar == '+') {
        	return 1;
        }
        else {
        	return 0;
		}
}

int is_identifier(Token token){
    int i = 0;
    int len = strlen(token.value);
    if(len == 0) {
        return 0;
    }
    //for 1 index, checking conditions without loop
    if(len == 1) {

        if (token.value[0] == '!' || token.value[0] == '/' || token.value[0] == '*' || token.value[0] == ':' || token.value[0] == '<'
              || token.value[0] == '=' || token.value[0] == '>' || token.value[0] == '?' || token.value[0] == '-' || token.value[0] == '+' || token.value[0] == '.' ||
               (token.value[0] >= 'a' && token.value[0] <= 'z')) {
            return 1;
            }
        else
            return 0;
    }
    //checking conditions with for loop when length of string is greater then 1
    if(len > 1) {

        if ((token.value[0] == '!' || token.value[0] == '/' || token.value[0] == '*' || token.value[0] == ':' || token.value[0] == '<'
              || token.value[0] == '=' || token.value[0] == '>' || token.value[0] == '?' || (token.value[0] >= 'a' && token.value[0] <= 'z'))) {


            for(int xa = 1; xa < len;xa++) {



            	if((token.value[xa] >= 'a' && token.value[xa] <= 'z')  ||  is_ok(token.value[xa]) || single_digit_num(token.value[xa])) {



            }
            	else {

                	return 0;

            }
        }
        return 1;
	}
	else
        return 0;



    }
    else
    	return 0;

}

void openFile(const char *filename) {
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        fprintf(output,"Failed to open the file.\n");
        exit(1);
    }
}

void openFileForOutput(const char *filename) {
    output = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        fprintf(output,"Failed to open the file.\n");
        exit(1);
    }
}

void closeFile() {
    if (file != NULL) {
        fclose(file);
        file = NULL;
    }
}

void closeFileForOutput() {
    if (output != NULL) {
        fclose(output);
        output = NULL;
    }
}

void skipWhitespace() {
    int c;
    while ((c = fgetc(file)) != EOF && isspace(c));
    ungetc(c, file);
}

Token getNextToken(int *i) {

    skipWhitespace();
    Token token;
    Token ph_token;
    int c = fgetc(file);
    int ksks = 0;


    if (c == '(') {
        token.value[0] = '(';
        token.value[1] = '\0';
    }
    else if (c == ')') {
        token.value[0] = ')';
        token.value[1] = '\0';

        rightph[counter] = leftph[count-1];
        counter++;
        leftph[count-1] = 0;
        count--;

    }
    else {
        int first_ph_holder = 0;
        int countph = 0;
        ungetc(c, file);
        fscanf(file, "%s", token.value);
        int length = strlen(token.value);
        for(int m = length; m >= 1 ; m--) {

            if(token.value[strlen(token.value)-m] == ')') {

                countph++;
                if (countph == 1) {
                    first_ph_holder = strlen(token.value)-m;
                }
                rightph[counter] = leftph[count-1];
                counter++;
                leftph[count-1] = 0;
                count--;
            }
        }
        if(first_ph_holder != 0) {
            token.value[first_ph_holder] = '\0';
        }
        countph = 0;
    }
    return token;
}

Token getToken(int *i) {

    Token token = getNextToken(i);

    // Optionally, you can print the tokens for debugging purposes


    return token;
}

void print_token(Token token) {

    printf(" (");
    fprintf(output," (");
    printf("%s",token.value);
    fprintf(output,"%s",token.value);
    printf(")\n");
    fprintf(output,")\n");
}

void print_pharanteses(Token token) {
    printf(" (");
    fprintf(output," (");
    printf("%s",token.value);
    fprintf(output,"%s",token.value);
    printf(")\n");
    fprintf(output,")\n");
}

void Program(int *i) {
    printf("<Program>\n");
    fprintf(output,"<Program>\n");
    TopLevelForm(i);
    Token token = getToken(i);
    if(strcmp(token.value,"(") != 0 ) {
        return 0;
    }
    Program(i);
}

void printRightPar(int *i) {
    if(counter <= 0) {
        return 0;
    }

    *i = rightph[0];

    if( counter >= 2 ) {
        for(int xyz = 0;xyz <= counter-2; xyz++ ) {
            rightph[xyz] = rightph[xyz+1];
        }
        rightph[counter-1] = 0;
    }
    counter--;
    //printf("\ncounter = %d rightph[counter-1] = %d\n",counter,rightph[counter]);
    //printf("LEFTPAR");
    print4(i);
    printf(output,"RIGHTPAR");
    printf(output," (");
    printf(output,")");
    printf(output,")\n");
    fprintf(output,"RIGHTPAR");
    fprintf(output," (");
    fprintf(output,")");
    fprintf(output,")\n");

}

void TopLevelForm(int *i) {
    printf("    <TopLevelForm>\n");
    fprintf(output,"    <TopLevelForm>\n");
    (*i)++;
    Token token = compareLastToken(i);
    strcpy(LastToken.value,"");
    print4(i);
    printf("LEFTPAR");
    fprintf(output,"LEFTPAR");
    leftph[count] = *i;
    count++;
    print_token(token);
    if ( token.value == EOF){
        return;
    }
    SecondLevelForm(i);
    counter++;
    if(counter > 0) {
            counter--;
        printRightPar(i);
    }
    else {
            printf("SYNTAX ERROR [?:?]: ')' is expected. ");
            fprintf(output,"SYNTAX ERROR [?:?]: ')' is expected. ");
    }

}

void SecondLevelForm(int *i) {


    print4(i);
    printf("<SecondLevelForm>\n");
    fprintf(output,"<SecondLevelForm>\n");
    (*i)++;

    Token token = compareLastToken(i);
    strcpy(LastToken.value,"");
    if(strcmp(token.value,"(") == 0 ){
        print4(i);
        printf("LEFTPAR");
        fprintf(output,"LEFTPAR");
        leftph[count] = *i;
        count++;
        print_token(token);
        FunCall(i,token);
        if(counter > 0) {
            printRightPar(i);
        }
        else {
            printf("SYNTAX ERROR [?:?]: ')' is expected. ");
            fprintf(output,"SYNTAX ERROR [?:?]: ')' is expected. ");
        }
    }
    else {
        Definition(i,token);
    }

}

void Definition(int *i,Token prevToken) {

    print4(i);
    printf("<Definition>\n");
    fprintf(output,"<Definition>\n");
    (*i)++;
    if(strcmp(prevToken.value, "define") == 0) {
        print4(i);
        printf("DEFINE");
        fprintf(output,"DEFINE");
        strcpy(LastToken.value,"");
        print_token(prevToken);
        DefinitionRight(i);
    }
    else {
        printf("no Define keyword.");
        fprintf(output,"no Define keyword.");
    }


}

void print4(int *i) {
    for(int j = *i; j>0;j--) {
            printf("    ");
            fprintf(output,"    ");
        }
}

void DefinitionRight(int *i) {

    print4(i);
    printf("<DefinitionRight>\n");
    fprintf(output,"<DefinitionRight>\n");
    (*i)++;
    Token token;
    token = compareLastToken(i);
    strcpy(LastToken.value,"");
    if (is_identifier(token)) {
        Token token = getToken(i); // Consume 'IDENTIFIER'
        Expression(i);
    }
    // SOl parantez eklencek else if'te
    else if(strcmp(token.value,"(") == 0){
        print4(i);
        printf("LEFTPAR");
        fprintf(output,"LEFTPAR");
        leftph[count] = *i;
        count++;
        print_token(token);
        Token token = getToken(i); // Consume '('
        if (is_identifier(token)) {

            print4(i);
            printf("IDENTIFIER");
            fprintf(output,"IDENTIFIER");
            strcpy(LastToken.value,"");
            print_token(token);
            // Consume 'IDENTIFIER'

            print4(i);
            printf("<ArgList>\n");
            fprintf(output,"<ArgList>\n");
            ArgList(i);

            if(counter > 0) {
                printRightPar(i);
            }
            else {
                printf("SYNTAX ERROR [?:?]: ')' is expected. ");
                fprintf(output,"SYNTAX ERROR [?:?]: ')' is expected. ");
            }


            Statements(i);



        }
    }
    else {
        printf("Last token is not identifier or left pharantesess.");
        fprintf(output,"Last token is not identifier or left pharantesess.");
    }
}

void ArgList(int *i) {
(*i)++;




    Token token;
    token = compareLastToken(i);
    strcpy(LastToken.value,"");
    if (is_identifier(token)) {

        print4(i);
        printf("IDENTIFIER");
        fprintf(output,"IDENTIFIER");
        strcpy(LastToken.value,"");
        print_token(token);
        print4(i);
        printf("<ArgList>\n");
        fprintf(output,"<ArgList>\n");

        ArgList(i);
    }
    else {
        print4(i);
        printf("___\n");
        fprintf(output,"___\n");

        for(int leng = 0; leng <= strlen(token.value)-1;leng++) {
            LastToken.value[leng] = token.value[leng];
        }

    }
}

Token compareLastToken(int *i) {
    Token token;
    if(strlen(LastToken.value) == 0) {
        token = getToken(i);
    }
    else {
        strcpy(token.value,LastToken.value);
    }
    return token;
}

void Statements(int *i) {
    print4(i);
    fprintf(output,"<Statements>\n");
    printf("<Statements>\n");
    (*i)++;
    Token token;
    token = compareLastToken(i);

    if (strcmp(token.value,"define") == 0) {
        Definition(i,token);
        Statements(i);
    }
    else {
        Expression(i);
    }
}

void Expressions(int *i) {
    print4(i);
    printf("<Expressions>\n");
    fprintf(output,"<Expressions>\n");
    (*i)++;
    Token token;

    token = compareLastToken(i);

    strcpy(LastToken.value,"");
    if(rightph[counter-1] != 0 && strlen(token.value) != 0) {
        strcpy(LastToken.value,token.value);
        Expression(i);

        (*i)--;
        print4(i);
        printf("<Expressions>\n");
        fprintf(output,"<Expressions>\n");
        (*i)++;
        print4(i);
        printf("___\n");
        fprintf(output,"___\n");
        if(counter > 0) {
        printRightPar(i);
        }
        else {
            printf("SYNTAX ERROR [?:?]: ')' is expected. ");
            fprintf(output,"SYNTAX ERROR [?:?]: ')' is expected. ");
        }
    }
    else if (rightph[counter-1] != 0 && strlen(token.value) == 0) {
        print4(i);
        printf("___\n");
        fprintf(output,"___\n");
        if(counter > 0) {
        printRightPar(i);
        }
        else {
            printf("SYNTAX ERROR [?:?]: ')' is expected. ");
            fprintf(output,"SYNTAX ERROR [?:?]: ')' is expected. ");
        }
    }
    else if (is_decimal(token) == 1 || is_floatingNumber(token) == 1 || is_hexadecimal(token) || is_binary(token)) {
        strcpy(LastToken.value,token.value);
        Expression(i);
        (*i)--;
        Expressions(i);
    }
    else if (is_character(token) == 1) {
        strcpy(LastToken.value,token.value);
        Expression(i);
        (*i)--;
        Expressions(i);
    }
    else if (isBoolean(token) == 1) {
        strcpy(LastToken.value,token.value);
        Expression(i);
        (*i)--;
        Expressions(i);
    }
    else if (is_string(token) == 1) {
        strcpy(LastToken.value,token.value);
        Expression(i);
        (*i)--;
        Expressions(i);
    }
    else if (strcmp(token.value,"(") == 0) {
        strcpy(LastToken.value,token.value);
        Expression(i);
        (*i)--;
        Expressions(i);
    }
    else if (is_identifier(token) == 1 && isKeyword(token) == 0) {

        strcpy(LastToken.value,token.value);
        Expression(i);
        (*i)--;
        Expressions(i);
    }



}

void Expression(int *i) {

    print4(i);
    printf("<Expression>\r");
    fprintf(output,"<Expression>\r");
    (*i)++;
    Token token = compareLastToken(i);
    strcpy(LastToken.value,"");


    if (is_decimal(token) == 1 || is_floatingNumber(token) == 1 || is_hexadecimal(token) || is_binary(token)) {
        print4(i);
        printf("NUMBER");
        fprintf(output,"NUMBER");
        strcpy(LastToken.value,"");
        print_token(token);
    }
    else if (is_character(token) == 1) {
        print4(i);
        printf("CHAR");
        fprintf(output,"CHAR");
        print_token(token);
    }
    else if (isBoolean(token) == 1) {
        print4(i);
        printf("BOOLEAN");
        fprintf(output,"BOOLEAN");
        print_token(token);
    }
    else if (is_string(token) == 1) {
        print4(i);
        printf("STRING");
        fprintf(output,"STRING");
        print_token(token);
    }

    else if (strcmp(token.value,"(") == 0) {
        print4(i);
        printf("LEFTPAR");
        fprintf(output,"LEFTPAR");
        leftph[count] = *i;
        count++;
        print_token(token);
        Expr(i);
        counter++;
        if(counter > 0) {
                counter--;
        printRightPar(i);
        }
        else {
            printf("SYNTAX ERROR [?:?]: ')' is expected. ");
            fprintf(output,"SYNTAX ERROR [?:?]: ')' is expected. ");
        }
    }
    else if (is_identifier(token) == 1 && isKeyword(token) == 0) {
        print4(i);
        printf("IDENTIFIER");
        fprintf(output,"IDENTIFIER");
        strcpy(LastToken.value,"");
        print_token(token);

    }
}

void Expr(int *i) {
    print4(i);
    printf("<Expr>\n");
    fprintf(output,"<Expr>\n");
    (*i)++;

    Token token = getToken(i);
    if (strcmp(token.value,"let") == 0) {
        strcpy(LastToken.value,token.value);
        LetExpression(i);
    }
    else if (strcmp(token.value,"cond") == 0) {
        strcpy(LastToken.value,token.value);
        CondExpression(i);
    }
    else if (strcmp(token.value,"if") == 0) {
        strcpy(LastToken.value,token.value);
        IfExpression(i);                                               //d�zenlenecek

    }
    else if (strcmp(token.value,"begin") == 0) {
        strcpy(LastToken.value,token.value);
        Statements(i);
    }
    else if (is_identifier(token) == 1){
        strcpy(LastToken.value,token.value);
        FunCall(i);
    }
    else {
        printf("No matches with corresponding expressions.");
        fprintf(output,"No matches with corresponding expressions.");
    }
}

void FunCall(int *i) {
    print4(i);
    printf("<FunCall>\n");
    fprintf(output,"<FunCall>\n");
    (*i)++;
    Token token = compareLastToken(i);
    strcpy(LastToken.value,"");
    if (is_identifier(token) == 1 ) {
        print4(i);
        printf("IDENTIFIER");
        fprintf(output,"IDENTIFIER");
        print_token(token);
        Expressions(i);
    }
}

void LetExpression(int *i) {
    print4(i);
    printf("IDENTIFIER");
    fprintf(output,"<LetExpression>\n");
    (*i)++;
    Token token;
    token = compareLastToken(i);
    print4(i);
    printf(output,"LET");
    fprintf(output,"LET");
    strcpy(LastToken.value,"");
    print_token(token);
    LetExpr(i);
}

void LetExpr(int *i) {
    print4(i);
    printf("<LetExpr>\n");
    fprintf(output,"<LetExpr>\n");
    (*i)++;
    Token token = getToken(i);
    if (strcmp(token.value,"(") == 0) {
        print4(i);
        printf("LEFTPAR");
        fprintf(output,"LEFTPAR");
        leftph[count] = *i;
        count++;
        print_token(token);
        VarDefs(i);
        if(counter > 0) {
            printRightPar(i);
        }
        else {
            printf("SYNTAX ERROR [?:?]: ')' is expected. ");
            fprintf(output,"SYNTAX ERROR [?:?]: ')' is expected. ");
        }
        Statements(i);
    }
    else if (is_identifier(token) == 1) {
        print4(i);
        printf("IDENTIFIER");
        fprintf(output,"IDENTIFIER");
        print_token(token);
        Token token = getNextToken(i);
        if (strcmp(token.value,"(") == 0) {
            print4(i);
            printf("LEFTPAR");
            fprintf(output,"LEFTPAR");
            leftph[count] = *i;
            count++;
            print_token(token);
            VarDefs(i);
            if(counter > 0) {
                printRightPar(i);
            }
            else {
                printf("SYNTAX ERROR [?:?]: ')' is expected. ");
                fprintf(output,"SYNTAX ERROR [?:?]: ')' is expected. ");
            }
            Statements(i);
        }
    }
}

void VarDefs(int *i) {
    print4(i);
    printf("<VarDefs>\n");
    fprintf(output,"<VarDefs>\n");
    (*i)++;
    Token token = compareLastToken(i);
    if (strcmp(token.value,"(") == 0) {
        print4(i);
        printf("LEFTPAR");
        fprintf(output,"LEFTPAR");
        leftph[count] = *i;
        count++;
        print_token(token);
        strcpy(LastToken.value,"");
        Token token = getToken(i);

        if (is_identifier(token) == 1) {
            print4(i);
            printf("IDENTIFIER");
            fprintf(output,"IDENTIFIER");
            print_token(token);
            Expression(i);
            if(counter > 0) {
                printRightPar(i);
            }
            else {
                printf("SYNTAX ERROR [?:?]: ')' is expected. ");
                fprintf(output,"SYNTAX ERROR [?:?]: ')' is expected. ");
            }

            VarDef(i);
        }
    }
}

void VarDef(int *i) {
    print4(i);
    printf("<VarDef>\n");
    fprintf(output,"<VarDef>\n");
    (*i)++;
    Token token = getToken(i);
    if(strcmp(token.value,"(") == 0 && rightph[counter-1] == 0) {
        strcpy(LastToken.value,token.value);
        VarDefs(i);
    }
    else {
        print4(i);
        printf("___\n");
        fprintf(output,"___\n");
        strcpy(LastToken.value,token.value);
    }


}

void CondExpression(int *i) {

    print4(i);
    printf("<CondExpression>\n");
    fprintf(output,"<CondExpression>\n");
    (*i)++;
    Token token = compareLastToken(i);
    print4(i);
    (*i)++;
    printf("COND");
    fprintf(output,"COND");
    print_token(token);
    strcpy(LastToken.value,"");
    CondBranches(i);

}

void CondBranches(int *i) {
    print4(i);
    printf("<VarDefs>\n");
    fprintf(output,"<VarDefs>\n");
    (*i)++;
    Token token = compareLastToken(i);
    if (token.value == "(") {
        print4(i);
        printf("LEFTPAR");
        fprintf(output,"LEFTPAR");
        leftph[count] = *i;
        count++;
        print_token(token);
        strcpy(LastToken.value,"");
        Token token = getToken(i);
        Expression(i);
        Statements(i);
        if(counter > 0) {
            printRightPar(i);
        }
        else {
            printf("SYNTAX ERROR [?:?]: ')' is expected. ");
            fprintf(output,"SYNTAX ERROR [?:?]: ')' is expected. ");
        }
        CondBranch(i);
    }
    else {
        printf("SYNTAX ERROR [?:?]: ')' is expected. ");
        fprintf(output,"SYNTAX ERROR [?:?]: ')' is expected. ");
    }
}

void CondBranch(int *i) {

    Token token = getToken(i);
    if (strcmp(token.value,"(") == 0) {
        Expression(i);
        Statements(i);
        if(counter > 0) {
            printRightPar(i);
        }
        else {
            printf("SYNTAX ERROR [?:?]: ')' is expected. ");
            fprintf(output,"SYNTAX ERROR [?:?]: ')' is expected. ");
        }
        CondBranch(i);

    }
}

void IfExpression(int *i) {
    print4(i);
    printf("<IfExpression>\n");
    fprintf(output,"<IfExpression>\n");
    (*i)++;
    Token token = compareLastToken(i);
    print4(i);
    fprintf(output,"IF");
    print_token(token);
    strcpy(LastToken.value,"");
    Expression(i);
    Expression(i);
    EndExpression(i);

}

void EndExpression(int *i) {

    print4(i);
    printf("<EndExpression>\n");
    fprintf(output,"<EndExpression>\n");
    (*i)++;
    Token token = getToken(i);

    if (is_decimal(token) == 1 || is_floatingNumber(token) == 1 || is_hexadecimal(token) || is_binary(token)) {
        strcpy(LastToken.value,token.value);
        Expression(i);
    }
    else if (is_character(token) == 1) {
        strcpy(LastToken.value,token.value);
        Expression(i);
    }
    else if (isBoolean(token) == 1) {
        strcpy(LastToken.value,token.value);
        Expression(i);
    }
    else if (is_string(token) == 1) {
        strcpy(LastToken.value,token.value);
        Expression(i);
    }
    else if (strcmp(token.value,"(") == 0) {
        strcpy(LastToken.value,token.value);
        Expression(i);
    }
    else if (is_identifier(token) == 1 && isKeyword(token) == 0) {
        strcpy(LastToken.value,token.value);
        Expression(i);
    }
}

void BeginExpression(int *i) {

    print4(i);
    printf("<BeginExpression>");
    fprintf(output,"<BeginExpression>");
    (*i)++;
    Token token;
    print4(i);
    printf("BEGIN");
    fprintf(output,"BEGIN");
    (*i)++;
    token = compareLastToken(i);
    strcpy(LastToken.value,"");
    Statements(i);

}

int main() {

    char inputFileName[100];

    printf("Enter the input file name: ");
    scanf("%s", inputFileName);

    openFile(inputFileName);
    openFileForOutput("output.txt");
    int i = 1;
    int *myP = &i;
    Program(&i);
    Token token;
    closeFile();

    if(counter > 0) {
        printf("Lack of Right Parentheses\n");
        fprintf(output, "Lack of Right Parentheses\n");
    }
    if(counter < 0) {
        printf("Excess of Left Parentheses\n");
        fprintf(output, "Excess of Left Parentheses\n");
    }
    closeFileForOutput();
}
