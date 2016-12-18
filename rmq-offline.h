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

struct Query
{
    INT L, R, O;
};

INT rmq_offline ( INT * A, INT n, Query * Q, INT q );
