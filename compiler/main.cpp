#include <cstdio>
#include <iostream>
#include <string>

#include "syntax/Absyn.H"
#include "syntax/Parser.H"
#include "syntax/ParserError.H"
#include "syntax/Printer.H"
#include "typecheck/TypeChecker.h"

void usage() {
    printf("usage: Call with one of the following argument combinations:\n");
    printf("\t--help\t\tDisplay this help message.\n");
    printf("\t(no arguments)\tParse stdin verbosely.\n");
    printf("\t(files)\t\tParse content of files verbosely.\n");
    printf("\t-s (files)\tSilent mode. Parse content of files silently.\n");
}

int main(int argc, char **argv) {
    FILE *input;
    bool quiet = false;
    char *filename = nullptr;

    if (argc > 1) {
        if (strcmp(argv[1], "-s") == 0) {
            quiet = true;
            if (argc > 2) {
                filename = argv[2];
            } else {
                input = stdin;
            }
        } else {
            filename = argv[1];
        }
    }

    if (filename) {
        input = fopen(filename, "r");
        if (!input) {
            usage();
            exit(1);
        }
    } else {
        input = stdin;
    }

    /* The default entry point is used. For other options see Parser.H */
    Program_ *parse_tree = nullptr;
    try {
        parse_tree = pProgram_(input);
    } catch (parse_error &e) {
        std::cerr << "Parse error on line " << e.getLine() << "\n";
    }

    if (parse_tree) {
        if (!quiet) {
//            printf("\n[Abstract Syntax]\n");
//            auto *s = new ShowAbsyn();
//            printf("%s\n\n", s->show(parse_tree));
//            printf("[Program Linearized Tree]\n");
//            auto *p = new PrintAbsyn();
//            printf("%s\n\n", p->print(parse_tree));

            auto *pTypeChecker = new TypeChecker();
            pTypeChecker->visitProgram_(parse_tree);

//            delete p;
//            delete s;
            delete pTypeChecker;
        }
        delete (parse_tree);
        return 0;
    }

    return 1;
}
