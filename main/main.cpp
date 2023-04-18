#include "../menu/Menu.h"

using namespace std;

int main() {
    auto menu = new Menu();
    menu -> menu();
    delete menu;
    return 0;
}

