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

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "lib8051.h"
#include "lib8051hooks.h"

/* simulate global variables for a struct vm8051 *vm */
#include "lib8051globals.h"

/* 8051 coprocessors list */
struct copro8051
{
  unsigned int index;
  void *contents;
  struct copro8051 *next;
};

/* registers a coprocessor to the vm */
void add_hook (struct vm8051 *vm, void *contents, unsigned int index)
{
  struct copro8051 *copros;

  copros = vm->coprocessors;
  while (copros && copros->index != index)
    copros = copros->next;

  if (!copros)
    {
      copros = malloc (sizeof (struct copro8051));
      copros->index = index;
      copros->contents = contents;
      copros->next = vm->coprocessors;
      vm->coprocessors = copros;
    }
}

/* this table will store all available operate functions */
void (*operate_hook_list[8]) (struct vm8051 *, void *);

/* call the operate function of all available coprocessors */
void operate_hooks (struct vm8051 *vm)
{
  struct copro8051 *copros;

  copros = vm->coprocessors;
  while (copros)
    {
      assert (operate_hook_list[copros->index] != NULL);
      operate_hook_list[copros->index] (vm, copros->contents);
      copros = copros->next;
    }
}

/* this table will store all available print functions */
void (*print_hook_list[8]) (struct vm8051 *, void *);

/* call the operate function of all available coprocessors */
void print_hooks (struct vm8051 *vm)
{
  struct copro8051 *copros;

  copros = vm->coprocessors;
  while (copros)
    {
      assert (print_hook_list[copros->index] != NULL);
      print_hook_list[copros->index] (vm, copros->contents);
      copros = copros->next;
    }
}

void free_hooks (struct vm8051 *vm)
{
  struct copro8051 *copros;

  copros = vm->coprocessors;
  while (copros)
    {
      free (copros->contents);
      copros = copros->next;
      free (vm->coprocessors);
      vm->coprocessors = copros;
    }
}
