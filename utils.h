/**
    rmqo: Range Minimum Queries Offline
    Copyright (C) 2016 Mai Alzamel and Solon P. Pissis

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#include "rmq-offline.h"

#define flog2(X) ((unsigned) (8*sizeof (unsigned long long) - __builtin_clzll((X)) - 1))

struct Tuples
{
    INT a, p;
};

struct List{

  List * next;
  INT pos;
};

INT answer_rmqs ( INT * A, INT n, Query * Q, INT q, Query * Q_Prime,  INT * Af );
INT contract( INT * A, INT n, Query * Q, INT q, INT * AQ, INT * s, INT * Af, Query * Q_Prime );
INT recover ( INT * A, INT n, INT * AQ, INT s, INT * Af );
INT create ( INT * A, INT n, INT max, Query * Q, INT q, INT * l_0, List ** l_1, INT * AQ, INT * s, INT * Af, Query * Q_Prime);
INT marking( INT * A, INT max, Query * Q, INT q, INT * l_0, List ** l_1 );
