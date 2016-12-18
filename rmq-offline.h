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

#include <bits/stdc++.h>

#ifdef _USE_64
typedef int64_t INT;
#endif

/**
 * Query struct.
 *
 * @param L The left index of the query
 * @param R The right index of the query (R >= L)
 * @param O The index of the minimum
 */

struct Query
{
    INT L, R, O;
};

/**
 * This is the only library function.
 *
 * @param A A rewritable array of type INT
 * @param n The array size
 * @param Q An array of type Query
 * @param q The array size
 * @return The answers are returned in Q
 */

INT rmq_offline ( INT * A, INT n, Query * Q, INT q );
