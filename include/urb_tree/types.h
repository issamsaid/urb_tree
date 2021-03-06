#ifndef __URB_TREE_TYPES_H_
#define __URB_TREE_TYPES_H_
///
/// @copyright Copyright (c)2016-, Issam SAID <said.issam@gmail.com>
/// All rights reserved.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permetted provided that the following conditions
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
/// @file urb_tree/types.h
/// @author Issam SAID
/// @brief The generic Red-Black tree data structure.
/// @details By definition a Red-Black tree has 4 invariants:
///   1. A node is either Red or Black.
///   2. The root is always Black. 
///      This rule is sometimes omitted. Since the root can 
///      always be changed from Red to Black, but not necessarily 
///      vice-versa, this rule has little effect on analysis.
///   3. Every Red node must have two Black children.
///   4. Every path from a given node to any of its descendant 
///      leaves contains the same number of Black nodes.
///
#include <urb_tree/guard.h>

CPPGUARD_BEGIN();

///
///
///
typedef enum {
    red,
    black,
} color_t;

///
/// @brief The main structure that defines the Red-Black tree.
///
typedef struct __urb_t {
    struct __urb_t *left;
    struct __urb_t *right;
    struct __urb_t *parent;
    color_t color;                               
    void *key;                                 
    void *value;                             
} urb_t;

CPPGUARD_END();

#endif // __URB_TREE_TYPES_H_
