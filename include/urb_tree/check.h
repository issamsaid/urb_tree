#ifndef __URB_TREE_CHECK_H_
#define __URB_TREE_CHECK_H_
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
/// 3. Neither the name of the UPMC nor the names of its contributors
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
/// @file urb_tree/check.h
/// @author Issam SAID
/// @brief The definition of the main routines to check the invariants
///        of Red-Black trees.
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
/// @def URB_TREE_CHECK_INVARIANTS
/// @brief A helper that checks the invariants of Red-Black trees. 
///
#define URB_TREE_CHECK_INVARIANTS(urb) \
    urb_tree_check_invariant_1(urb);   \
    urb_tree_check_invariant_2(urb);   \
    urb_tree_check_invariant_3(urb);   \
    urb_tree_check_invariant_4(urb)

///
/// @brief Check whether the tree satisfies the invariant 1.
///
void urb_tree_check_invariant_1(urb_t **urb);

///
/// @brief Check whether the tree satisfies the invariant 2.
///
void urb_tree_check_invariant_2(urb_t **urb);

///
/// @brief Check whether the tree satisfies the invariant 3.
///
void urb_tree_check_invariant_3(urb_t **urb);

///
/// @brief Check whether the tree satisfies the invariant 4.
///
void urb_tree_check_invariant_4(urb_t **urb);

CPPGUARD_END();

#endif // __URB_TREE_CHECK_H_
