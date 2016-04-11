/*
 * Copyright 2013 Andrea Mazzoleni. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY ANDREA MAZZOLENI AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL ANDREA MAZZOLENI OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** \file
 * Dynamic array based on blocks of fixed sizes.
 *
 * This array is able to grow dynamically upon request.
 *
 * This is very similar at ::tommy_arrayblk, but it allows to store elements of any
 * size and not just pointers.
 *
 * Note that in this case tommy_arrayblkof_ref() returns a pointer at the element,
 * and it should be used for both get() and set() operation.
 */

#ifndef __TOMMYARRAYBLKOF_H
#define __TOMMYARRAYBLKOF_H

#include "tommytypes.h"
#include "tommyarray.h"

#include <assert.h> /* for assert */

/******************************************************************************/
/* array */

/**
 * Elements for each block.
 */
#define TOMMY_ARRAYBLKOF_SIZE (64 * 1024)

/**
 * Array.
 */
typedef struct tommy_arrayblkof_struct {
	tommy_array block; /**< Array of blocks. */
	unsigned element_size; /**< Size of the stored element in bytes. */
	unsigned size; /**< Currently allocated and initialized size. */
} tommy_arrayblkof;

/**
 * Initializes the array.
 * \param element_size Size in byte of the element to store in the array.
 */
void tommy_arrayblkof_init(tommy_arrayblkof* array, unsigned element_size);

/**
 * Deinitializes the array.
 */
void tommy_arrayblkof_done(tommy_arrayblkof* array);

/**
 * Grow the size up to the specified value.
 * All the new elements in the array are initialized with the 0 value.
 */
void tommy_arrayblkof_grow(tommy_arrayblkof* array, unsigned size);

/**
 * Gets a reference of the element at the specified position.
 * You must be sure that space for this position is already
 * allocated calling tommy_arrayblkof_grow().
 */
tommy_inline void* tommy_arrayblkof_ref(tommy_arrayblkof* array, unsigned pos)
{
	unsigned char* base;

	assert(pos < array->size);

	base = tommy_cast(unsigned char*, tommy_array_get(&array->block, pos / TOMMY_ARRAYBLKOF_SIZE));

// cppcheck-suppress CastIntegerToAddressAtReturn
	return base + (pos % TOMMY_ARRAYBLKOF_SIZE) * array->element_size;
}

/**
 * Gets the initialized size of the array.
 */
tommy_inline unsigned tommy_arrayblkof_size(tommy_arrayblkof* array)
{
	return array->size;
}

/**
 * Gets the size of allocated memory.
 */
tommy_size_t tommy_arrayblkof_memory_usage(tommy_arrayblkof* array);

#endif

