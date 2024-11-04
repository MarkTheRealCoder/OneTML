//
// Created by marco on 03/11/2024.
//

#include "components/Template.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    Template t("title", "<div> Gay </div>");
    string s = "TOP: ";
    cout << (s << t);

}