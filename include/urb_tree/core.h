#ifndef __URB_TREE_CORE_H_
#define __URB_TREE_CORE_H_
///
/// @copyright Copyright (c)2016-, Issam SAID <said.issam@gmail.com>
/// All rights reserved.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions
/// are met:
///
/// 1. Redistributions of source code must retain the above copyright
///    notice, this list of conditions and the following disclaimer.
/// 2. Redistributions in binary form must reproduce the above copyright
///    notice, this list of conditions and the following disclaimer in the
///    documentation and/or other materials provided with the distribution.
/// 3. Neither the name of the copyright holder nor the names of its contributors
///    may be used to endorse or promote products derived from this software
///    without specific prior written permission.
///
/// THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
/// INCLUDING, BUT NOT LIMITED TO, WARRANTIES OF MERCHANTABILITY AND FITNESS
/// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
/// HOLDER OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
/// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
/// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
/// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
/// LIABILITY, WETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
/// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
/// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
/// @file urb_tree/core.h
/// @author Issam SAID
/// @brief The definition of the main routines to manipulate Red-Black trees.
/// @details We recall that the 4 invariants are:
///   1. A node is either red or black.
///   2. The root is always black. 
///      This rule is sometimes omitted. Since the root can 
///      always be changed from red to black, but not necessarily 
///      vice-versa, this rule has little effect on analysis.
///   3. Every red node must have two black child nodes.
///   4. Every path from a given node to any of its descendant 
///      leaves contains the same number of black nodes.
///
#include <urb_tree/guard.h>
#include <urb_tree/types.h>

CPPGUARD_BEGIN();

///
/// @brief Create a key/value pair.
///
urb_t *urb_tree_create(void *key, void *value);

///
/// @brief Delete a key/value pair.
///
int urb_tree_delete(urb_t **urb, 
                    void (*release_key)(void*), void (*release_value)(void*));

///
/// @brief Find a key/value pair from the tree.
///
urb_t *urb_tree_find(urb_t **urb, void *key, int (*compare_key)(void*, void*));

///
/// @brief Insert a key/value pair into the tree.
///
int urb_tree_put(urb_t **urb, urb_t *n, int (*compare_key)(void*, void*));

///
/// @brief Remove a key/value pair from the tree.
///
urb_t *urb_tree_pop(urb_t **urb, void *key, int (*compare_key)(void*, void*));

CPPGUARD_END();

#endif // __URB_TREE_CORE_H_
