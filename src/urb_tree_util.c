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
/// @file urb_tree_util.c
/// @author Issam SAID
/// @brief Implement the utilities used to traverse Red-Black trees.
///
#include <urb_tree/sentinel.h>
#include <urb_tree/util.h>
#include <urb_tree/guard.h>
#include <urb_tree/error.h>
#include <urb_tree/log.h>
#include <urb_tree/colors.h>

CPPGUARD_BEGIN();

void urb_tree_walk(urb_t **urb, 
                   void (*key_function)(void*), void (*value_function)(void*)) {         
    urb_t *n = *urb;
    if (n == &urb_sentinel) return;                                   
    if (key_function) key_function(n->key);              
    if (value_function) value_function(n->value);              
    if (n->left != &urb_sentinel)                                     
        urb_tree_walk(&n->left, key_function, value_function);
    if (n->right != &urb_sentinel)                                    
        urb_tree_walk(&n->right, key_function, value_function);
}

void urb_tree_print(urb_t **urb, void (*print_node)(void*, void*)) {         
    urb_t *n = *urb;
    if (n == &urb_sentinel) return;
    URB_PRINT("start node");
    if (n->color == red) printf(C_RED);
    print_node(n->key, n->value);    
    if (n->color == red) printf(C_END);  
    if (n->parent && n->parent != &urb_sentinel) {
        URB_PRINT("parent");
        if (n->parent->color == red) printf(C_RED);
        print_node(n->parent->key, n->parent->value); 
        if (n->parent->color == red) printf(C_END);  
    }
    if (n->left != &urb_sentinel) {
        URB_PRINT("left");
        if (n->left->color == red) printf(C_RED);
        print_node(n->left->key, n->left->value); 
        if (n->left->color == red) printf(C_END);  
    }
    if (n->right != &urb_sentinel) {
        URB_PRINT("right");     
        if (n->right->color == red) printf(C_RED);
        print_node(n->right->key, n->right->value);
        if (n->right->color == red) printf(C_END);    
    }                    
    URB_PRINT("end node");
    URB_PRINT("");        
    if (n->left  != &urb_sentinel) urb_tree_print(&n->left,  print_node);
    if (n->right != &urb_sentinel) urb_tree_print(&n->right, print_node);
}

size_t urb_tree_size(urb_t **urb) {
    urb_t *n = *urb;
    if (n == &urb_sentinel) return 0;
    return urb_tree_size(&n->left) + 1 + urb_tree_size(&n->right);
}

urb_t *urb_tree_max(urb_t **urb) {  
    urb_t *max = *urb;               
    while(max->right != &urb_sentinel) max = max->right;
    return max;                                
}

urb_t *urb_tree_min(urb_t **urb) {  
    urb_t *min = *urb;               
    while(min->left != &urb_sentinel) min = min->left;
    return min;                                
}

urb_t *urb_tree_succ(urb_t *n) { 
    urb_t *succ = &urb_sentinel;      
    if (n->right != &urb_sentinel)
        return urb_tree_min(&n->right);
    succ = n->parent;
    while(succ != NULL &&
          succ != &urb_sentinel &&
          n    == succ->right) {
          n  = succ;            
          succ = succ->parent;  
    }                         
    return succ;              
}

urb_t *urb_tree_prev(urb_t *n) { 
    urb_t *prev = &urb_sentinel;      
    if (n->left != &urb_sentinel)
        return urb_tree_max(&n->left);
    prev = n->parent;
    while(prev != NULL &&
          prev != &urb_sentinel &&
          n    == prev->left) {
          n    = prev;            
          prev = prev->parent;  
    }                         
    return prev;              
}
/*

#define IMPLEMENT_PREV_RBN(kT, vT)                              \
    rbn_##kT##_##vT* prev_rbn_##kT##_##vT(rbt_##kT##_##vT *rbt, \
                                          rbn_##kT##_##vT *n) { \
        rbn_##kT##_##vT *prev = NULL;                           \
        if (n->left != rbt->nil)                                \
            return max_rbt_##kT##_##vT(rbt, n->left);           \
        prev = n->parent;                                       \
        while(prev != NULL     &&                               \
              prev != rbt->nil &&                               \
              n  == prev->left) {                               \
            n  = prev;                                          \
            prev = prev->parent;                                \
        }                                                       \
        return prev;                                            \
    }
*/


CPPGUARD_END();  