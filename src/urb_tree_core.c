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
/// @file urb_tree_core.c
/// @author Issam SAID
/// @brief Implement the main routines to manipulate Red-Black trees.
///
#include <stdbool.h>
#include <urb_tree/core.h>
#include <urb_tree/fixin.h>
#include <urb_tree/error.h>

CPPGUARD_BEGIN();

urb_t urb_sentinel = { &urb_sentinel, \
                       &urb_sentinel, \
                       &urb_sentinel, \
                       black, NULL, NULL};

urb_t *urb_tree_create(void *key, void *value) {
    urb_t *n  = (urb_t *)malloc(sizeof(urb_t));
    if (n == NULL) 
        URB_EXIT(URB_OUT_OF_MEMORY, "failed to allocate urb_tree pair");       
    n->parent = &urb_sentinel;                              
    n->left   = &urb_sentinel;                              
    n->right  = &urb_sentinel;                              
    n->color  = red;                           
    n->key    = key;                                 
    n->value  = value;
    return n;
}

int urb_tree_delete(urb_t **urb, 
                    void (*release_key)(void*), void (*release_value)(void*)) {
    urb_t *i = *urb;
    while (i != &urb_sentinel) {          
        if (i->left != &urb_sentinel) {   
            i = i->left;             
        } else{
            if(i->right != &urb_sentinel) { 
                i = i->right;                 
            } else {                          
                if (release_key) { release_key(i->key); }
                if (release_value) { release_value(i->value); }
                if (i->parent) {                             
                    i = i->parent;                           
                    if (i->left != &urb_sentinel){                
                        free(i->left);                       
                        i->left = &urb_sentinel;                  
                    } else {
                        if (i->right != &urb_sentinel) {       
                            free(i->right );                     
                            i->right = &urb_sentinel;                 
                        }
                    }                                         
                } else {                                     
                    free(i);                                 
                    i = &urb_sentinel;                            
                }                                               
            }                                                 
        }
    }                                                       
    return URB_SUCCESS;                                      
}

int urb_tree_put(urb_t **urb, urb_t *n, int (*compare_key)(void*, void*)) {
    int ret;                                       
    urb_t *p = NULL;        
    urb_t *i = *urb;
    if (n == NULL) 
        URB_EXIT(URB_INVALID_NODE, "the node to insert can not be NULL");
    while (i != &urb_sentinel) {                            
        if((ret = compare_key(n->key, i->key))==0) 
            URB_EXIT(URB_DUPLICATE_KEY, "key already exists");
        p = i;
        i = (ret < 0) ? i->left : i->right;                                        
    }                                                      
    n->parent = p;                                    
    if (p) {    
        if (compare_key(n->key, p->key) < 0) p->left = n;                              
        else p->right = n;                             
    } else {
        *urb = n;
    }                                                  
    urb_tree_fix_put(urb, n);                    
    return URB_SUCCESS;                                    
}                                               

urb_t *urb_tree_find(urb_t **urb, void *key, int (*compare_key)(void*, void*)) {       
    int ret    = 0;                            
    urb_t *i   = *urb;  
    bool found = false;       
    while (i != &urb_sentinel) {                 
        if ((ret = compare_key(key, i->key)) == 0) { found = true; break; }
        i = ret < 0 ? i->left : i->right;            
    }                                                     
    return found == true ? i : &urb_sentinel;      
}

urb_t *urb_tree_pop(urb_t **urb, void *key, int (*compare_key)(void*, void*)) {
    urb_t *kid   = &urb_sentinel;                           
    urb_t *pleaf = &urb_sentinel;       
    urb_t *n     = urb_tree_find(urb, key, compare_key);                     
    if (n == &urb_sentinel) return &urb_sentinel;                             
    if (n->left  == &urb_sentinel || n->right == &urb_sentinel) {      
        pleaf = n;                                           
    } else {                                                  
        pleaf = n->right;                                     
        while (pleaf->left != &urb_sentinel) pleaf = pleaf->left;  
    }                                                          
    if (pleaf->left != &urb_sentinel) kid = pleaf->left;            
    else kid = pleaf->right;                                 
                                                                 
    kid->parent = pleaf->parent;                              
    if (pleaf->parent) {                                      
        if (pleaf == pleaf->parent->left)                    
            pleaf->parent->left = kid;                       
        else                                                        
            pleaf->parent->right = kid;                             
    } else { *urb = kid; }
    if (pleaf != n) {                                               
        void *ktmp;                                                    
        void *vtmp;                                                    
        ktmp         = n->key;                                     
        n->key       = pleaf->key;                                
        pleaf->key   = ktmp;                                      
        vtmp         = n->value;                                  
        n->value     = pleaf->value;                              
        pleaf->value = vtmp;                                        
    }                                                              
                                                                       
    if (pleaf->color == black) urb_tree_fix_pop(urb, kid);  
    pleaf->left   = &urb_sentinel;
    pleaf->parent = &urb_sentinel;
    pleaf->right  = &urb_sentinel;                                              
    return pleaf; 
}                                                 
 
CPPGUARD_END();