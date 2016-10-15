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
/// @file urb_tree_check.c
/// @author Issam SAID
/// @brief Implement the routines to check the invariants of Red-Black trees.
///
/// @details We recall that the invariants are:
///   1. A node is either red or black.
///   2. The root is always black. 
///      This rule is sometimes omitted. Since the root can 
///      always be changed from red to black, but not necessarily 
///      vice-versa, this rule has little effect on analysis.
///   3. Every red node must have two black child nodes.
///   4. Every path from a given node to any of its descendant 
///      leaves contains the same number of black nodes.
///
#include <stdio.h>
#include <assert.h>
#include <urb_tree/sentinel.h>
#include <urb_tree/check.h>
#include <urb_tree/guard.h>

CPPGUARD_BEGIN();
///
/// @brief Check the invariant 1: a node is either red or black.
///
void urb_tree_check_invariant_1(urb_t **urb) {
    if (*urb == &urb_sentinel) return;
    assert((*urb)->color == red || (*urb)->color == black);                         
    urb_tree_check_invariant_1(&(*urb)->left);  
    urb_tree_check_invariant_1(&(*urb)->right); 
}

///
/// @brief Check the invariant 2: the root is black.
///    This rule is sometimes omitted. Since the root can 
///    always be changedfrom red to black, but not necessarily 
///    vice-versa, this rule has little effect on analysis.
///
void urb_tree_check_invariant_2(urb_t **urb) {
    if (*urb != &urb_sentinel) assert((*urb)->color == black);         
}

///
/// @brief Check the invariant 3: Every red node must have two black children.
///
void urb_tree_check_invariant_3(urb_t **urb) {
    if ((*urb) == &urb_sentinel) return;                         
    if ((*urb)->color == red) {                                 
        if ((*urb)->left)   assert((*urb)->left->color   == black);             
        if ((*urb)->right)  assert((*urb)->right->color  == black);             
        if ((*urb)->parent) assert((*urb)->parent->color == black);             
    }                                                  
    urb_tree_check_invariant_3(&(*urb)->left);     
    urb_tree_check_invariant_3(&(*urb)->right);    
}

///
/// @brief Check the invariant 4: Every path from a given node to any of 
///        its descendant leaves contains the same number of black nodes.
///
int __get_black_count(urb_t **urb) {
    urb_t *n = *urb;
    int count = 0;
    while(n != &urb_sentinel) {                                   
        if (n->color == black) count++;
        n = n->left;
    }
    return count;
}

void __check_black_count_allpaths(urb_t **urb, 
                                  int black_count, int ref_black_count) {
    if ((*urb) == &urb_sentinel) {        
        assert(black_count == ref_black_count);      
        return;
    } else {
        if ((*urb)->color == black) black_count++;  
    }
    __check_black_count_allpaths(&(*urb)->left,  black_count, ref_black_count);     
    __check_black_count_allpaths(&(*urb)->right, black_count, ref_black_count);  
}

void urb_tree_check_invariant_4(urb_t **urb) {
    __check_black_count_allpaths(urb, 0, __get_black_count(urb));
}

CPPGUARD_END();