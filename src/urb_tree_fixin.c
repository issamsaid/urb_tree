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
/// @file urb_tree_fixin.c
/// @author Issam SAID
/// @brief Implement the routines used to statisfy the invariants of 
/// Red-Black trees.
///
/// @details 
///
/// We recall that:
///   1. A node is either red or black.
///   2. The root is always black. 
///      This rule is sometimes omitted. Since the root can 
///      always be changed from red to black, but not necessarily 
///      vice-versa, this rule has little effect on analysis.
///   3. Every red node must have two black child nodes.
///   4. Every path from a given node to any of its descendant 
///      leaves contains the same number of black nodes.
///
/// The defuncts cases are:
/// CASE 1 uncle and parent are RED:
///    - switch the color of the parent to BLACK
///    - switch the color of the uncle to BLACK
///    - switch the color of the grand parent to RED
///    - if root is RED switch its color to BLACK
///
/// CASE 2 parent is RED, uncle is BLACK and:
///    2.1: parent is left of grand parent and child is left of parent
///       - right rotate around the grand parent
///       - switch the color of the grand parent to RED
///       - switch the color of the parent to BLACK
///    2.2: parent is right of grand parent and child is right of parent
///       - left rotate around the grand parent
///       - switch the color of the grand parent to RED
///       - switch the color of the parent to BLACK
///
/// CASE 3 parent is RED, uncle is BLACK and child, 
///        parent, and grandpa are not aligned:
///       - do rotation to bring it to CASE 2
///       - process CASE 2
///
#include <stdio.h>
#include <urb_tree/sentinel.h>
#include <urb_tree/fixin.h>
#include <urb_tree/flags.h>

static inline void urb_tree_left_rotate(urb_t **urb, urb_t *n) {  
    urb_t *y = n->right;
    n->right = y->left;
    if (y->left != &urb_sentinel) y->left->parent = n;
    if (y       != &urb_sentinel) y->parent = n->parent;
    if (n->parent){           
        if (n == n->parent->left) n->parent->left = y; 
        else n->parent->right = y;
    } else { *urb = y; }    
    y->left = n;                 
    if (n != &urb_sentinel) n->parent = y;
}

static inline void urb_tree_right_rotate(urb_t **urb, urb_t *n) {  
    urb_t *y = n->left; 
    n->left  = y->right;           
    if (y->right != &urb_sentinel) y->right->parent = n;     
    if (y != &urb_sentinel) y->parent = n->parent;    
    if (n->parent) {              
        if (n == n->parent->right) n->parent->right = y; 
        else n->parent->left = y;  
    } else { *urb = y; }     
    y->right = n;                 
    if (n != &urb_sentinel) n->parent = y;
}

int urb_tree_fix_put(urb_t **urb, urb_t *n) {
    urb_t *uncle;  
    urb_t *child = n;
    while (child != *urb && child->parent->color == red) {
        //if (child->parent->parent != &urb_sentinel) {
            if (child->parent == child->parent->parent->left) {
                uncle = child->parent->parent->right;
                //if (uncle != &urb_sentinel) {
                    if (uncle->color == red) {           
                        /// CASE 1: uncle and parent are RED.
                        child->parent->color         = black; 
                        uncle->color                 = black; 
                        child->parent->parent->color = red;   
                        child                        = child->parent->parent;
                    } else {
                        /// CASE 3: parent is RED, uncle is BLACK and child, 
                        ///         parent, and grandpa are not aligned.
                        if (child == child->parent->right) {
                            child  = child->parent;         
                            urb_tree_left_rotate(urb, child);
                        }                     
                        /// CASE 2: parent is RED, uncle is BLACK.
                        child->parent->color         = black; 
                        child->parent->parent->color = red;   
                        urb_tree_right_rotate(urb, child->parent->parent);
                    }
                //} else { break; }                                                       
            } else {                                                    
                uncle = child->parent->parent->left; 
                //if (uncle != &urb_sentinel) {                   
                    if (uncle->color == red) {                             
                        /// CASE 1 
                        child->parent->color         = black;              
                        uncle->color                 = black;              
                        child->parent->parent->color = red;                
                        child                        = child->parent->parent;
                    } else {                       
                        /// CASE 3
                        if (child == child->parent->left) {
                            child  = child->parent; 
                            urb_tree_right_rotate(urb, child);
                        }
                        /// CASE 2 
                        child->parent->color         = black;  
                        child->parent->parent->color = red;    
                        urb_tree_left_rotate(urb, child->parent->parent); 
                    }
                //} else { break; }
            }
        //} else { break; }                                                         
    }                                                               
    (*urb)->color = black;                                       
    return URB_SUCCESS;
}

int urb_tree_fix_pop(urb_t **urb, urb_t *n) {
    while (n != *urb && n->color == black) { 
        if (n == n->parent->left) {               
            urb_t *w = n->parent->right;
            if (w->color == red) {               
                w->color         = black;        
                n->parent->color = red;          
                urb_tree_left_rotate(urb, n->parent);
                w = n->parent->right;                       
            }                                               
            if (w->left->color == black && w->right->color == black) { 
                w->color = red;                                     
                n = n->parent;                                      
            } else {                                                
                if (w->right->color == black)  {                    
                    w->left->color = black;                         
                    w->color       = red;                          
                    urb_tree_right_rotate(urb, w);          
                    w = n->parent->right;                          
                }                                                  
                w->color = n->parent->color;                       
                n->parent->color = black;                          
                w->right->color = black;                           
                urb_tree_left_rotate(urb, n->parent);       
                n = *urb;                                     
            }                                                      
        } else {                                                   
            urb_t *w = n->parent->left;                  
            if (w->color == red) {                                 
                w->color = black;                                  
                n->parent->color = red;                            
                urb_tree_right_rotate(urb, n->parent);      
                w = n->parent->left;                               
            }                                                      
            if (w->right->color == black && w->left->color == black) {
                w->color = red;                                    
                n = n->parent;                                     
            } else {                                               
                if (w->left->color == black) {                     
                    w->right->color = black;                       
                    w->color = red;                                
                    urb_tree_left_rotate(urb, w);           
                    w = n->parent->left;                           
                }                                                  
                w->color = n->parent->color;                       
                n->parent->color = black;                          
                w->left->color   = black;                            
                urb_tree_right_rotate(urb, n->parent);      
                n = *urb;                                     
            }                                                      
        }                                                          
    }                                                              
    n->color = black;                                              
    return URB_SUCCESS;
}