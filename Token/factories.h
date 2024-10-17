#ifndef FACTORIES_H
#define FACTORIES_H

#include "Operation/plus.h"
#include "Operation/minus.h"
#include "Operation/multiply.h"
#include "Operation/divide.h"
#include "Operation/power.h"

namespace Factory {
    Operation* makeOperation(char ch);
}

#endif // FACTORIES_H
