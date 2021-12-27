/* Copyright (C) 2014, 2016 Luk Bettale

   This file is part of VM8051.

   VM8051 is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with VM8051.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef LIB8051HOOKS_H
#define LIB8051HOOKS_H

#include <stdio.h>
#include <stdint.h>

#include "lib8051.h"

extern void (*operate_hook_list[8]) (struct vm8051 *vm, void *copro);
extern void (*print_hook_list[8]) (struct vm8051 *vm, void *copro);

extern void add_hook (struct vm8051 *vm, void *contents, unsigned int index);
extern void operate_hooks (struct vm8051 *vm);
extern void print_hooks (struct vm8051 *vm);
extern void free_hooks (struct vm8051 *vm);

#endif  /* LIB8051HOOKS_H */
